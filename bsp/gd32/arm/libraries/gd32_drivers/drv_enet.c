/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-11-30     aozima       the first version.
 * 2011-12-10     aozima       support dual ethernet.
 * 2011-12-21     aozima       cleanup code.
 * 2012-07-13     aozima       mask all GMAC MMC Interrupt.
 * 2012-07-20     aozima       fixed mask all GMAC MMC Interrupt,and read clear.
 * 2012-07-20     aozima       use memcpy replace byte copy.
 */

#include <rtthread.h>
#include <rthw.h>

#include "lwipopts.h"
#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include <lwip/ip.h>
#include <lwip/dhcp.h>
#include "synopsys_emac.h"
#include <string.h>
#include <netdev.h>
#include <board.h>

#define LOG_TAG    "drv.enet"
#define LOG_LVL    LOG_LVL_DBG
#include <drv_log.h>

//#define EMAC_DEBUG
//#define EMAC_RX_DUMP
//#define EMAC_TX_DUMP

#ifdef EMAC_DEBUG
#define EMAC_TRACE          rt_kprintf
#else
#define EMAC_TRACE(...)
#endif

#define EMAC_SOFT_RESET_TO_S   10    // Software reset timeout in seconds

#define EMAC_RXBUFNB            5
#define EMAC_TXBUFNB            5

#define EMAC_PHY_AUTO           0
#define EMAC_PHY_10MBIT         1
#define EMAC_PHY_100MBIT        2

#define MAX_ADDR_LEN 6

#define NIOCTL_SADDR            0x02

#ifndef GD32_BOARD_MAC_ADDR
#define GD32_BOARD_MAC_ADDR {0x02, 0x02, 0x02, 0x02, 0x02, 0x02}
#endif
#ifndef GD32_BOARD_MAC1_ADDR
#define GD32_BOARD_MAC1_ADDR {0x02, 0x02, 0x02, 0x02, 0x02, 0x11}
#endif

struct gd32_emac_config
{
    const char *name;
    rt_uint8_t port_id;
    rt_uint16_t phy_addr;
    rt_uint32_t enet_periph;
    IRQn_Type irq;
    void (*clock_enable)(void);
    void (*gpio_init)(void);
    rt_uint8_t default_mac[MAX_ADDR_LEN];
};

struct gd32_emac
{
    /* inherit from Ethernet device */
    struct eth_device parent;

    /* interface address info. */
    __ALIGNED(4) rt_uint8_t  dev_addr[MAX_ADDR_LEN];     /* hw address   */

    const char *name;
    rt_uint8_t init_done; /* EMAC initialization done flag */
    rt_uint8_t port_id;
    rt_uint16_t phy_addr;
    rt_uint32_t phy_speed;
    rt_uint32_t enet_periph;
    IRQn_Type ETHER_MAC_IRQ;

    void (*clock_enable)(void);
    void (*gpio_init)(void);

    EMAC_DMADESCTypeDef  *DMATxDescToSet;
    EMAC_DMADESCTypeDef  *DMARxDescToGet;

    rt_align(4) EMAC_DMADESCTypeDef DMARxDscrTab[EMAC_RXBUFNB];
    rt_align(4) EMAC_DMADESCTypeDef DMATxDscrTab[EMAC_TXBUFNB];
    rt_align(4) rt_uint8_t Rx_Buff[EMAC_RXBUFNB][EMAC_MAX_PACKET_SIZE];
    rt_align(4) rt_uint8_t Tx_Buff[EMAC_TXBUFNB][EMAC_MAX_PACKET_SIZE];

    struct rt_semaphore tx_buf_free;
};

void gd32_enet_gpio_config(void);
#ifdef BSP_USING_ETH1
void gd32_enet1_gpio_init(void);
#endif

#if defined(__ICCARM__)
#pragma location = ".sram0"
rt_align(4) static struct gd32_emac gd32_emac_device0;
#ifdef BSP_USING_ETH1
#pragma location = ".sram1"
rt_align(4) static struct gd32_emac gd32_emac_device1;
#endif
#elif defined(__ARMCC_VERSION)
rt_align(4) rt_section("SRAM0") static struct gd32_emac gd32_emac_device0;
#ifdef BSP_USING_ETH1
rt_align(4) rt_section("SRAM1") static struct gd32_emac gd32_emac_device1;
#endif
#elif defined (__GNUC__)
rt_align(4) rt_section(".sram0") static struct gd32_emac gd32_emac_device0;
#ifdef BSP_USING_ETH1
rt_align(4) rt_section(".sram1") static struct gd32_emac gd32_emac_device1;
#endif
#else
#error "unsupported tool chain"
#endif

#if !defined(BSP_USING_ETH0) && !defined(BSP_USING_ETH1)
#error "At least one GD32 Ethernet port must be enabled"
#endif

#ifdef BSP_USING_ETH0
static void gd32_enet0_clock_enable(void)
{
    rcu_periph_clock_enable(RCU_ENET0);
    rcu_periph_clock_enable(RCU_ENET0TX);
    rcu_periph_clock_enable(RCU_ENET0RX);
}
#endif

#ifdef BSP_USING_ETH1
static void gd32_enet1_clock_enable(void)
{
    rcu_periph_clock_enable(RCU_ENET1);
    rcu_periph_clock_enable(RCU_ENET1TX);
    rcu_periph_clock_enable(RCU_ENET1RX);
}
#endif

static const struct gd32_emac_config gd32_emac_cfgs[] =
{
#ifdef BSP_USING_ETH0
    {
        "e0",
        0,
        PHY_ADDRESS,
        ENET0,
        ENET0_IRQn,
        gd32_enet0_clock_enable,
        gd32_enet_gpio_config,
        GD32_BOARD_MAC_ADDR,
    },
#endif
#ifdef BSP_USING_ETH1
    {
        "e1",
        1,
        PHY_ADDRESS_1,
        ENET1,
        ENET1_IRQn,
        gd32_enet1_clock_enable,
        gd32_enet1_gpio_init,
        GD32_BOARD_MAC1_ADDR,
    },
#endif
};

static struct gd32_emac *const gd32_emac_devices[] =
{
#ifdef BSP_USING_ETH0
    &gd32_emac_device0,
#endif
#ifdef BSP_USING_ETH1
    &gd32_emac_device1,
#endif
};

static rt_size_t gd32_emac_device_count(void)
{
    return sizeof(gd32_emac_devices) / sizeof(gd32_emac_devices[0]);
}

static struct gd32_emac *gd32_emac_get_default_device(void)
{
    rt_size_t index;

    if (netif_default != RT_NULL)
    {
        for (index = 0; index < gd32_emac_device_count(); index++)
        {
            if (gd32_emac_devices[index]->parent.netif == netif_default)
            {
                return gd32_emac_devices[index];
            }
        }
    }

    return gd32_emac_device_count() ? gd32_emac_devices[0] : RT_NULL;
}

static struct gd32_emac *gd32_emac_find_device_by_name(const char *name)
{
    rt_size_t index;

    if (name == RT_NULL)
    {
        return RT_NULL;
    }

    for (index = 0; index < gd32_emac_device_count(); index++)
    {
        if (rt_strncmp(gd32_emac_devices[index]->name, name, RT_NAME_MAX) == 0)
        {
            return gd32_emac_devices[index];
        }
    }

    return RT_NULL;
}

static rt_bool_t gd32_emac_parse_mac(const char *mac_addr, rt_uint8_t mac[MAX_ADDR_LEN])
{
    static const rt_uint8_t hex_map[] =
    {
        ['0'] = 0, ['1'] = 1, ['2'] = 2, ['3'] = 3, ['4'] = 4,
        ['5'] = 5, ['6'] = 6, ['7'] = 7, ['8'] = 8, ['9'] = 9,
        ['A'] = 10, ['B'] = 11, ['C'] = 12, ['D'] = 13, ['E'] = 14, ['F'] = 15,
        ['a'] = 10, ['b'] = 11, ['c'] = 12, ['d'] = 13, ['e'] = 14, ['f'] = 15,
    };
    rt_size_t index = 0;
    rt_uint8_t nibble = 0;
    rt_uint8_t value = 0;
    char ch;

    if ((mac_addr == RT_NULL) || (mac == RT_NULL))
    {
        return RT_FALSE;
    }

    while ((ch = *mac_addr++) != '\0')
    {
        if ((ch == ':') || (ch == '-'))
        {
            continue;
        }

        if ((((ch >= '0') && (ch <= '9')) ||
             ((ch >= 'A') && (ch <= 'F')) ||
             ((ch >= 'a') && (ch <= 'f'))) == 0)
        {
            return RT_FALSE;
        }

        value = (rt_uint8_t)((value << 4) | hex_map[(rt_uint8_t)ch]);
        nibble++;

        if (nibble == 2)
        {
            if (index >= MAX_ADDR_LEN)
            {
                return RT_FALSE;
            }

            mac[index++] = value;
            value = 0;
            nibble = 0;
        }
    }

    return (index == MAX_ADDR_LEN) && (nibble == 0);
}

static rt_err_t gd32_emac_set_mac(struct gd32_emac *device, const rt_uint8_t mac[MAX_ADDR_LEN])
{
    struct rt_synopsys_eth *ethernet_mac;
    struct netdev *netdev;

    if ((device == RT_NULL) || (mac == RT_NULL))
    {
        return -RT_ERROR;
    }

    ethernet_mac = EMAC_REGS(device->enet_periph);

    rt_memcpy(device->dev_addr, mac, MAX_ADDR_LEN);
    EMAC_MAC_Addr_config(ethernet_mac, EMAC_MAC_Address0, (uint8_t *)device->dev_addr);

    if (device->parent.netif != RT_NULL)
    {
        rt_memcpy(device->parent.netif->hwaddr, device->dev_addr, MAX_ADDR_LEN);
        device->parent.netif->hwaddr_len = MAX_ADDR_LEN;
    }
    else
    {
        LOG_W("%s netif is not ready, MAC will be synced later", device->name);
    }

    netdev = netdev_get_by_name(device->name);
    if (netdev != RT_NULL)
    {
        rt_memcpy(netdev->hwaddr, device->dev_addr, MAX_ADDR_LEN);
        netdev->hwaddr_len = MAX_ADDR_LEN;
    }
    else
    {
        LOG_W("%s netdev is not ready, MAC cache was not synced", device->name);
    }

    return RT_EOK;
}

static rt_err_t gd32_emac_init(rt_device_t dev);
static rt_err_t gd32_emac_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t gd32_emac_close(rt_device_t dev);
static rt_ssize_t gd32_emac_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
static rt_ssize_t gd32_emac_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);
static rt_err_t gd32_emac_control(rt_device_t dev, int cmd, void *args);
rt_err_t gd32_emac_tx(rt_device_t dev, struct pbuf* p);
struct pbuf *gd32_emac_rx(rt_device_t dev);

static void gd32_emac_fill_instance(struct gd32_emac *device, const struct gd32_emac_config *cfg)
{
    rt_memset(device, 0, sizeof(*device));

    device->name = cfg->name;
    device->port_id = cfg->port_id;
    device->phy_addr = cfg->phy_addr;
    device->enet_periph = cfg->enet_periph;
    device->ETHER_MAC_IRQ = cfg->irq;
    device->clock_enable = cfg->clock_enable;
    device->gpio_init = cfg->gpio_init;
    rt_memcpy(device->dev_addr, cfg->default_mac, sizeof(device->dev_addr));

    device->parent.parent.init = gd32_emac_init;
    device->parent.parent.open = gd32_emac_open;
    device->parent.parent.close = gd32_emac_close;
    device->parent.parent.read = gd32_emac_read;
    device->parent.parent.write = gd32_emac_write;
    device->parent.parent.control = gd32_emac_control;
    device->parent.parent.user_data = RT_NULL;

    device->parent.eth_rx = gd32_emac_rx;
    device->parent.eth_tx = gd32_emac_tx;
}

static void gd32_emac_enable_resources(struct gd32_emac *device)
{
    if (device->clock_enable != RT_NULL)
    {
        (*device->clock_enable)();
    }

    if (device->gpio_init != RT_NULL)
    {
        (*device->gpio_init)();
    }
}

static void gd32_emac_restart_dhcp(struct gd32_emac *device)
{
#if LWIP_DHCP
    struct netif *netif;

    if ((device == RT_NULL) || (device->parent.netif == RT_NULL))
    {
        return;
    }

    netif = device->parent.netif;
    rt_kprintf("[%s] Restarting DHCP client...\r\n", device->name);

    if (netif_dhcp_data(netif) != NULL)
    {
        dhcp_stop(netif);
        dhcp_cleanup(netif);
    }

    netif_set_addr(netif, IP4_ADDR_ANY, IP4_ADDR_ANY, IP4_ADDR_ANY);
    rt_thread_delay(RT_TICK_PER_SECOND / 5);
    dhcp_start(netif);

    rt_kprintf("[%s] DHCP client restarted\r\n", device->name);
#else
    RT_UNUSED(device);
#endif
}

static void gd32_emac_stop_dhcp(struct gd32_emac *device)
{
#if LWIP_DHCP
    struct netif *netif;

    if ((device == RT_NULL) || (device->parent.netif == RT_NULL))
    {
        return;
    }

    netif = device->parent.netif;
    if (netif_dhcp_data(netif) != NULL)
    {
        dhcp_stop(netif);
        rt_kprintf("[%s] DHCP stopped due to link down\r\n", device->name);
    }
#else
    RT_UNUSED(device);
#endif
}

static void gd32_emac_update_mac_mode(uint32_t enet_periph, rt_uint32_t reg_value)
{
    rt_uint32_t mac_cfg;

    mac_cfg = GD32_ENET_MAC_CFG(enet_periph);
    mac_cfg &= ~(ENET_SPEEDMODE_100M | ENET_MODE_FULLDUPLEX);
    mac_cfg |= reg_value;
    GD32_ENET_MAC_CFG(enet_periph) = mac_cfg;
}

void gd32_enet_gpio_config(void);

/**
  * Initializes the DMA Tx descriptors in chain mode.
  */
static void EMAC_DMA_tx_desc_init(EMAC_DMADESCTypeDef *DMATxDescTab, uint8_t* TxBuff, uint32_t TxBuffCount)
{
    uint32_t i = 0;
    EMAC_DMADESCTypeDef *DMATxDesc;

    /* Fill each DMATxDesc descriptor with the right values */
    for(i=0; i < TxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Tx Desc list */
        DMATxDesc = DMATxDescTab + i;
        /* Set Second Address Chained bit */
        DMATxDesc->status = EMAC_DMATxDesc_TCH;

        /* Set Buffer1 address pointer */
        DMATxDesc->buffer1_addr = (uint32_t)(&TxBuff[i*EMAC_MAX_PACKET_SIZE]);

        /* Initialize the next descriptor with the Next Descriptor Polling Enable */
        if(i < (TxBuffCount-1))
        {
            /* Set next descriptor address register with next descriptor base address */
            DMATxDesc->buffer2_next_desc_addr = (uint32_t)(DMATxDescTab+i+1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            DMATxDesc->buffer2_next_desc_addr = (uint32_t) DMATxDescTab;
        }

#ifdef RT_LWIP_USING_HW_CHECKSUM
        enet_transmit_checksum_config(DMATxDesc, ENET_CHECKSUM_TCPUDPICMP_FULL);
#endif
    }
}

/**
  * Initializes the DMA Rx descriptors in chain mode.
  */
static void EMAC_DMA_rx_desc_init(EMAC_DMADESCTypeDef *DMARxDescTab, uint8_t *RxBuff, uint32_t RxBuffCount)
{
    uint32_t i = 0;
    EMAC_DMADESCTypeDef *DMARxDesc;

    /* Fill each DMARxDesc descriptor with the right values */
    for(i=0; i < RxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Rx Desc list */
        DMARxDesc = DMARxDescTab+i;
        /* Set Own bit of the Rx descriptor Status */
        DMARxDesc->status = EMAC_DMARxDesc_OWN;

        /* Set Buffer1 size and Second Address Chained bit */
        DMARxDesc->control_buffer_size = EMAC_DMARxDesc_RCH | (uint32_t)EMAC_MAX_PACKET_SIZE;
        /* Set Buffer1 address pointer */
        DMARxDesc->buffer1_addr = (uint32_t)(&RxBuff[i*EMAC_MAX_PACKET_SIZE]);

        /* Initialize the next descriptor with the Next Descriptor Polling Enable */
        if(i < (RxBuffCount-1))
        {
            /* Set next descriptor address register with next descriptor base address */
            DMARxDesc->buffer2_next_desc_addr = (uint32_t)(DMARxDescTab+i+1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            DMARxDesc->buffer2_next_desc_addr = (uint32_t)(DMARxDescTab);
        }
    }
}

static rt_err_t gd32_emac_init(rt_device_t dev)
{
    struct gd32_emac * gd32_emac_device;
    struct rt_synopsys_eth * ETHERNET_MAC;
    rt_uint32_t result;

    gd32_emac_device = (struct gd32_emac *)dev;
    ETHERNET_MAC = EMAC_REGS(gd32_emac_device->enet_periph);

#if 0
    // soft reset will be performed in EMAC_init, so no need to do it here again.

    /* Software reset */
    ETHERNET_MAC->BMR |= (1<<0); /* [bit0]SWR (Software Reset) */

    /* Wait for software reset */
    rt_tick_t start_tick = rt_tick_get();
    rt_tick_t timeout_tick = EMAC_SOFT_RESET_TO_S * RT_TICK_PER_SECOND;

    while(ETHERNET_MAC->BMR & (1 << 0))
    {
        if ((rt_tick_get() - start_tick) >= timeout_tick)
        {
            rt_kprintf("EMAC software reset timeout.\r\n");
            return EMAC_ERROR;
        }

        rt_thread_delay(rt_tick_from_millisecond(10)); /* 10ms */
    }
#endif

     /* Enable peripheral clock and configure GPIOs for Ethernet */

    /* Configure ETHERNET */
    result = EMAC_init(SystemCoreClock, gd32_emac_device->enet_periph, gd32_emac_device->phy_addr);

    /* mask all GMAC MMC Interrupt.*/
    ETHERNET_MAC->mmc_cntl = (1<<3) | (1<<0); /* MMC Counter Freeze and reset. */
    ETHERNET_MAC->mmc_intr_mask_rx = 0xFFFFFFFF;
    ETHERNET_MAC->mmc_intr_mask_tx = 0xFFFFFFFF;
    ETHERNET_MAC->mmc_ipc_intr_mask_rx = 0xFFFFFFFF;

    ETHERNET_MAC->mmc_cntl &= ~((1<<3) | (1<<0)); /* MMC Counter enable. */


    /* Enable DMA Receive interrupt (need to enable in this case Normal interrupt) */
    EMAC_INT_config(ETHERNET_MAC, EMAC_DMA_INT_NIS | EMAC_DMA_INT_R | EMAC_DMA_INT_T , ENABLE);

    /* Initialize Tx Descriptors list: Chain Mode */
    EMAC_DMA_tx_desc_init(gd32_emac_device->DMATxDscrTab, &gd32_emac_device->Tx_Buff[0][0], EMAC_TXBUFNB);
    gd32_emac_device->DMATxDescToSet = gd32_emac_device->DMATxDscrTab;
    /* Set Transmit Descriptor List Address Register */
    ETHERNET_MAC->TDLAR = (uint32_t) gd32_emac_device->DMATxDescToSet;

    /* Initialize Rx Descriptors list: Chain Mode  */
    EMAC_DMA_rx_desc_init(gd32_emac_device->DMARxDscrTab, &gd32_emac_device->Rx_Buff[0][0], EMAC_RXBUFNB);
    gd32_emac_device->DMARxDescToGet = gd32_emac_device->DMARxDscrTab;
    /* Set Receive Descriptor List Address Register */
    ETHERNET_MAC->RDLAR = (uint32_t) gd32_emac_device->DMARxDescToGet;

    /* MAC address configuration */
    EMAC_MAC_Addr_config(ETHERNET_MAC, EMAC_MAC_Address0, (uint8_t*)&gd32_emac_device->dev_addr[0]);

    NVIC_EnableIRQ( gd32_emac_device->ETHER_MAC_IRQ );

    /* Enable MAC and DMA transmission and reception */
    EMAC_start(gd32_emac_device->enet_periph);

    if (result != EMAC_SUCCESS)
    {
        gd32_emac_device->init_done = 0;
    }
    else
    {
        gd32_emac_device->init_done = 1;
    }

    return RT_EOK;
}

static rt_err_t gd32_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t gd32_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t gd32_emac_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return -RT_ENOSYS;
}

static rt_ssize_t gd32_emac_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    return -RT_ENOSYS;
}

static rt_err_t gd32_emac_control(rt_device_t dev, int cmd, void *args)
{
    struct gd32_emac * gd32_emac_device = (struct gd32_emac *)dev;

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, &gd32_emac_device->dev_addr[0], MAX_ADDR_LEN);
        else return -RT_ERROR;
        break;

    case NIOCTL_SADDR:
        /* set mac address to enet and netif */
        if (args != RT_NULL)
        {
            return gd32_emac_set_mac(gd32_emac_device, (const rt_uint8_t *)args);
        }
        else
        {
            return -RT_ERROR;
        }

    default :
        break;
    }

    return RT_EOK;
}

static void EMAC_IRQHandler(struct gd32_emac * gd32_emac_device)
{
    rt_uint32_t status, ier;
    struct rt_synopsys_eth * ETHERNET_MAC;

    ETHERNET_MAC = EMAC_REGS(gd32_emac_device->enet_periph);

    /* get DMA IT status */
    status = ETHERNET_MAC->SR;
    ier = ETHERNET_MAC->IER;

    /* GMAC MMC Interrupt. */
    if(status & EMAC_DMA_INT_GMI)
    {
        volatile rt_uint32_t dummy;
        volatile rt_uint32_t * reg;

        EMAC_TRACE("EMAC_DMA_INT_GMI\r\n");

        /* read clear all MMC interrupt. */
        reg = &ETHERNET_MAC->mmc_cntl;
        while((uint32_t)reg < (uint32_t)&ETHERNET_MAC->rxicmp_err_octets)
        {
            dummy = *reg++;
        }

        RT_UNUSED(dummy);
    }

    /* Normal interrupt summary. */
    if(status & EMAC_DMA_INT_NIS)
    {
        rt_uint32_t nis_clear = EMAC_DMA_INT_NIS;

        /* [0]:Transmit Interrupt. */
        if((status & ier) & EMAC_DMA_INT_T) /* packet transmission */
        {
            rt_sem_release(&gd32_emac_device->tx_buf_free);

            nis_clear |= EMAC_DMA_INT_T;
        }

        /* [2]:Transmit Buffer Unavailable. */

        /* [6]:Receive Interrupt. */
        if((status & ier) & EMAC_DMA_INT_R) /* packet reception */
        {
            /* a frame has been received */
            eth_device_ready(&(gd32_emac_device->parent));

            nis_clear |= EMAC_DMA_INT_R;
        }

        /* [14]:Early Receive Interrupt. */

        EMAC_clear_pending(ETHERNET_MAC, nis_clear);
    }

    /* Abnormal interrupt summary. */
    if( status & EMAC_DMA_INT_AIS)
    {
        rt_uint32_t ais_clear = EMAC_DMA_INT_AIS;

        /* [1]:Transmit Process Stopped. */
        /* [3]:Transmit Jabber Timeout. */
        /* [4]: Receive FIFO Overflow. */
        /* [5]: Transmit Underflow. */
        /* [7]: Receive Buffer Unavailable. */
        /* [8]: Receive Process Stopped. */
        /* [9]: Receive Watchdog Timeout. */
        /* [10]: Early Transmit Interrupt. */
        /* [13]: Fatal Bus Error. */

        EMAC_clear_pending(ETHERNET_MAC, ais_clear);
    }
}

static void gd32_emac_irq_dispatch(struct gd32_emac *device)
{
    rt_interrupt_enter();
    EMAC_IRQHandler(device);
    rt_interrupt_leave();
}

#ifdef BSP_USING_ETH0
void ENET0_IRQHandler(void)
{
    gd32_emac_irq_dispatch(&gd32_emac_device0);
}
#endif

#ifdef BSP_USING_ETH1
void ENET1_IRQHandler(void)
{
    gd32_emac_irq_dispatch(&gd32_emac_device1);
}
#endif


/* EtherNet Device Interface */
rt_err_t gd32_emac_tx( rt_device_t dev, struct pbuf* p)
{
    struct pbuf* q;
    char * to;
    struct gd32_emac * gd32_emac_device;
    struct rt_synopsys_eth * ETHERNET_MAC;

    gd32_emac_device = (struct gd32_emac *)dev;
    ETHERNET_MAC = EMAC_REGS(gd32_emac_device->enet_periph);

    /* get free tx buffer */
    {
        rt_err_t result;
        result = rt_sem_take(&gd32_emac_device->tx_buf_free, RT_TICK_PER_SECOND/10);
        if (result != RT_EOK) {
            return -RT_ERROR;
        }
    }

    to = (char *)gd32_emac_device->DMATxDescToSet->buffer1_addr;

    for (q = p; q != NULL; q = q->next)
    {
        /* Copy the frame to be sent into memory pointed by the current ETHERNET DMA Tx descriptor */
        rt_memcpy(to, q->payload, q->len);
        to += q->len;
    }

#ifdef EMAC_TX_DUMP
    {
        rt_uint32_t i;
        rt_uint8_t *ptr = (rt_uint8_t*)(gd32_emac_device->DMATxDescToSet->buffer1_addr);

        EMAC_TRACE("\r\n%c%c tx_dump:", gd32_emac_device->parent.netif->name[0], gd32_emac_device->parent.netif->name[1]);
        for(i=0; i<p->tot_len; i++)
        {
            if( (i%8) == 0 )
            {
                EMAC_TRACE("  ");
            }
            if( (i%16) == 0 )
            {
                EMAC_TRACE("\r\n");
            }
            EMAC_TRACE("%02x ",*ptr);
            ptr++;
        }
        EMAC_TRACE("\r\ndump done!\r\n");
    }
#endif

    /* Setting the Frame Length: bits[12:0] */
    gd32_emac_device->DMATxDescToSet->control_buffer_size = (p->tot_len & EMAC_DMATxDesc_TBS1);
    /* Setting the last segment and first segment bits (in this case a frame is transmitted in one descriptor) */
    gd32_emac_device->DMATxDescToSet->status |= EMAC_DMATxDesc_LS | EMAC_DMATxDesc_FS;
    /* Enable TX Completion Interrupt */
    gd32_emac_device->DMATxDescToSet->status |= EMAC_DMATxDesc_IC;
#ifdef RT_LWIP_USING_HW_CHECKSUM
    gd32_emac_device->DMATxDescToSet->status |= EMAC_DMATxDesc_ChecksumTCPUDPICMPFull;
    /* clean ICMP checksum */
    {
        struct eth_hdr *ethhdr = (struct eth_hdr *)(gd32_emac_device->DMATxDescToSet->buffer1_addr);
        /* is IP ? */
        if( ethhdr->type == htons(ETHTYPE_IP) )
        {
            struct ip_hdr *iphdr = (struct ip_hdr *)(gd32_emac_device->DMATxDescToSet->buffer1_addr + SIZEOF_ETH_HDR);
            /* is ICMP ? */
            if( IPH_PROTO(iphdr) == IP_PROTO_ICMP )
            {
                struct icmp_echo_hdr *iecho = (struct icmp_echo_hdr *)(gd32_emac_device->DMATxDescToSet->buffer1_addr + SIZEOF_ETH_HDR + sizeof(struct ip_hdr) );
                iecho->chksum = 0;
            }
        }
    }
#endif
    /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
    gd32_emac_device->DMATxDescToSet->status |= EMAC_DMATxDesc_OWN;
    /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
    if ((ETHERNET_MAC->SR & EMAC_DMASR_TBUS) != (uint32_t)RESET)
    {
        /* Clear TBUS ETHERNET DMA flag */
        ETHERNET_MAC->SR = EMAC_DMASR_TBUS;
        /* Transmit Poll Demand to resume DMA transmission*/
        ETHERNET_MAC->TPDR = 0;
    }

    /* Update the ETHERNET DMA global Tx descriptor with next Tx decriptor */
    /* Chained Mode */
    /* Selects the next DMA Tx descriptor list for next buffer to send */
    gd32_emac_device->DMATxDescToSet = (EMAC_DMADESCTypeDef *)(gd32_emac_device->DMATxDescToSet->buffer2_next_desc_addr);

    /* Return SUCCESS */
    return RT_EOK;
}

/* reception a Ethernet packet. */
struct pbuf * gd32_emac_rx(rt_device_t dev)
{
    struct pbuf* p;
    rt_uint32_t framelength = 0;
    struct gd32_emac * gd32_emac_device;
    struct rt_synopsys_eth * ETHERNET_MAC;

    gd32_emac_device = (struct gd32_emac *)dev;
    ETHERNET_MAC = EMAC_REGS(gd32_emac_device->enet_periph);

    /* init p pointer */
    p = RT_NULL;

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    if(((gd32_emac_device->DMARxDescToGet->status & EMAC_DMARxDesc_OWN) != (uint32_t)RESET))
    {
        return p;
    }

        if (((gd32_emac_device->DMARxDescToGet->status & EMAC_DMARxDesc_ES) == (uint32_t)RESET) &&
            ((gd32_emac_device->DMARxDescToGet->status & EMAC_DMARxDesc_LS) != (uint32_t)RESET) &&
            ((gd32_emac_device->DMARxDescToGet->status & EMAC_DMARxDesc_FS) != (uint32_t)RESET))
    {
        /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
        framelength = ((gd32_emac_device->DMARxDescToGet->status & EMAC_DMARxDesc_FL)
                       >> EMAC_DMARXDESC_FRAME_LENGTHSHIFT) - 4;

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, framelength, PBUF_RAM);

        if (p != RT_NULL)
        {
            const char * from;
            struct pbuf* q;

            from = (const char *)gd32_emac_device->DMARxDescToGet->buffer1_addr;

            for (q = p; q != RT_NULL; q= q->next)
            {
                /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
                rt_memcpy(q->payload, from, q->len);
                from += q->len;
            }
#ifdef EMAC_RX_DUMP
            {
                rt_uint32_t i;
                rt_uint8_t *ptr = (rt_uint8_t*)(gd32_emac_device->DMARxDescToGet->buffer1_addr);

                EMAC_TRACE("\r\n%c%c rx_dump:", gd32_emac_device->parent.netif->name[0], gd32_emac_device->parent.netif->name[1]);
                for(i=0; i<p->tot_len; i++)
                {
                    if( (i%8) == 0 )
                    {
                        EMAC_TRACE("  ");
                    }
                    if( (i%16) == 0 )
                    {
                        EMAC_TRACE("\r\n");
                    }
                    EMAC_TRACE("%02x ",*ptr);
                    ptr++;
                }
                EMAC_TRACE("\r\ndump done!\r\n");
            }
#endif
        }
    }

    /* Set Own bit of the Rx descriptor Status: gives the buffer back to ETHERNET DMA */
    gd32_emac_device->DMARxDescToGet->status = EMAC_DMARxDesc_OWN;

    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((ETHERNET_MAC->SR & EMAC_DMASR_RBUS) != (uint32_t)RESET)
    {
        /* Clear RBUS ETHERNET DMA flag */
        ETHERNET_MAC->SR = EMAC_DMASR_RBUS;
        /* Resume DMA reception */
        ETHERNET_MAC->RPDR = 0;
    }

    /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */
    /* Chained Mode */
    if((gd32_emac_device->DMARxDescToGet->control_buffer_size & EMAC_DMARxDesc_RCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Rx descriptor list for next buffer to read */
        gd32_emac_device->DMARxDescToGet = (EMAC_DMADESCTypeDef *)(gd32_emac_device->DMARxDescToGet->buffer2_next_desc_addr);
    }
    else /* Ring Mode */
    {
        if((gd32_emac_device->DMARxDescToGet->control_buffer_size & EMAC_DMARxDesc_RER) != (uint32_t)RESET)
        {
            /* Selects the first DMA Rx descriptor for next buffer to read: last Rx descriptor was used */
            gd32_emac_device->DMARxDescToGet = (EMAC_DMADESCTypeDef *)(ETHERNET_MAC->RDLAR);
        }
        else
        {
            /* Selects the next DMA Rx descriptor list for next buffer to read */
            gd32_emac_device->DMARxDescToGet = (EMAC_DMADESCTypeDef *)((uint32_t)gd32_emac_device->DMARxDescToGet + sizeof(EMAC_DMADESCTypeDef) + ((ETHERNET_MAC->BMR & EMAC_DMABMR_DSL) >> 2));
        }
    }

    return p;
}


/*!
    \brief      configures the nested vectored interrupt controller
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void gd32_emac_nvic_configuration(IRQn_Type irq)
{
    nvic_irq_enable(irq, 1U, 0U);
}

#if 0 /* GPIO configuration is defined in board_msd_init.c */
/*!
   \brief      configures the different GPIO ports
   \param[in]  none
   \param[out] none
   \retval     none
*/
rt_weak void gd32_enet_gpio_config(void)
{
   rcu_periph_clock_enable(RCU_GPIOA);
   rcu_periph_clock_enable(RCU_GPIOB);
   rcu_periph_clock_enable(RCU_GPIOC);
   rcu_periph_clock_enable(RCU_GPIOD);
   rcu_periph_clock_enable(RCU_GPIOE);
   rcu_periph_clock_enable(RCU_GPIOG);
   rcu_periph_clock_enable(RCU_GPIOH);

   gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_8);
   gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
   gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,GPIO_PIN_8);

   /* enable SYSCFG clock */
   rcu_periph_clock_enable(RCU_SYSCFG);

   /* choose DIV2 to get 50MHz from 200MHz on CKOUT0 pin (PA8) to clock the PHY */
   rcu_ckout0_config(RCU_CKOUT0SRC_PLL0P, RCU_CKOUT0_DIV12);
   syscfg_enet_phy_interface_config(ENET0, SYSCFG_ENET_PHY_RMII);

   /* PA1: ETH_RMII_REF_CLK */
   gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
   gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_1);

   /* PA2: ETH_MDIO */
   gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
   gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_2);

   /* PA7: ETH_RMII_CRS_DV */
   gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
   gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_7);

   gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_1);
   gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_2);
   gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_7);

   /* PG11: ETH_RMII_TX_EN */
   gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);
   gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_11);

   /* PB12: ETH_RMII_TXD0 */
   gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
   gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_12);

   /* PG12: ETH_RMII_TXD1 */
   gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
   gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_12);

   gpio_af_set(GPIOG, GPIO_AF_11, GPIO_PIN_11);
   gpio_af_set(GPIOB, GPIO_AF_11, GPIO_PIN_12);
   gpio_af_set(GPIOG, GPIO_AF_11, GPIO_PIN_12);

   /* PC1: ETH_MDC */
   gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
   gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_1);

   /* PC4: ETH_RMII_RXD0 */
   gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
   gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_4);

   /* PC5: ETH_RMII_RXD1 */
   gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
   gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_5);

   gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_1);
   gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_4);
   gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_5);
}
#endif

#define PHY_LINK_MASK     BIT(1)
#define PHY_10M_MASK      BIT(2)
#define PHY_100M_MASK     BIT(3)
#define PHY_DUPLEX_MASK   BIT(4)

static void phy_monitor(void *parameter)
{
    struct gd32_emac *gd32_emac_device = (struct gd32_emac *)parameter;
    uint8_t phy_addr = 0xFF;
    uint8_t phy_speed_new = 0;
    rt_uint16_t temp;
    rt_uint32_t reg_value = 0;

    if (gd32_emac_device == RT_NULL)
    {
        return;
    }

    phy_addr = gd32_emac_device->phy_addr;

    /* RESET PHY */
    rt_kprintf("[%s] Initializing PHY...\r\n", gd32_emac_device->name);
    #if 0
    haidware_reset_phy();
    #else
    temp = PHY_Reset;
    enet_phy_write_read(gd32_emac_device->enet_periph, ENET_PHY_WRITE, phy_addr, PHY_BCR, &temp);
    #endif

    rt_thread_delay(RT_TICK_PER_SECOND*2);

    temp = PHY_AUTONEGOTIATION;
    enet_phy_write_read(gd32_emac_device->enet_periph, ENET_PHY_WRITE, phy_addr, PHY_BCR, &temp);

    rt_kprintf("[%s] PHY initialized, starting link monitoring...\r\n", gd32_emac_device->name);

    while(1)
    {
        uint16_t status;
        enet_phy_write_read(gd32_emac_device->enet_periph, ENET_PHY_READ, phy_addr, PHY_BSR, &status);

        phy_speed_new = 0;

        if ((status & PHY_LINKED_STATUS) && (status & PHY_AUTONEGO_COMPLETE))
        {
            uint16_t SR;

            enet_phy_write_read(gd32_emac_device->enet_periph, ENET_PHY_READ, phy_addr, PHY_SR, &SR);
            phy_speed_new = PHY_LINK_MASK;
            #if (PHY_TYPE == YT8512H || PHY_TYPE == YT8522)
            if((SR & PHY_SPEED_STATUS))
            {
                phy_speed_new |= PHY_100M_MASK;
            }
            #else
            if((SR & PHY_SPEED_STATUS) == 0)
            {
                phy_speed_new |= PHY_100M_MASK;
            }
            #endif
            if(SR & PHY_DUPLEX_STATUS)
            {
                phy_speed_new |= PHY_DUPLEX_MASK;
            }
        }

        /* linkchange */
        if(phy_speed_new != gd32_emac_device->phy_speed)
        {
            if(phy_speed_new & PHY_LINK_MASK)
            {
                rt_kprintf("[%s] Link established - ", gd32_emac_device->name);

                if(phy_speed_new & PHY_100M_MASK)
                {
                    rt_kprintf("100Mbps");
                    reg_value = ENET_SPEEDMODE_100M;
                }
                else
                {
                    rt_kprintf("10Mbps");
                    reg_value = ENET_SPEEDMODE_10M;
                }

                if(phy_speed_new & PHY_DUPLEX_MASK)
                {
                    rt_kprintf(" full-duplex\r\n");
                    reg_value |= ENET_MODE_FULLDUPLEX;
                }
                else
                {
                    rt_kprintf(" half-duplex\r\n");
                    reg_value |= ENET_MODE_HALFDUPLEX;
                }

                if(gd32_emac_device->init_done == 0)
                {
                    rt_kprintf("[%s] First link up, reinitializing network interface\r\n", gd32_emac_device->name);

                    if (gd32_emac_init((rt_device_t)gd32_emac_device) != RT_EOK)
                    {
                        rt_kprintf("[%s] EMAC init failed, keep link down\r\n", gd32_emac_device->name);
                        rt_thread_delay(RT_TICK_PER_SECOND / 2);
                        continue;
                    }
                }
                else
                {
                    gd32_emac_update_mac_mode(gd32_emac_device->enet_periph, reg_value);
                }

                eth_device_linkchange(&gd32_emac_device->parent, RT_TRUE);

                gd32_emac_restart_dhcp(gd32_emac_device);

                rt_kprintf("[%s] Link up process completed\r\n", gd32_emac_device->name);
            } /* link up. */
            else
            {
                rt_kprintf("[%s] Link down detected\r\n", gd32_emac_device->name);

                /* stop DHCP */
                gd32_emac_stop_dhcp(gd32_emac_device);

                eth_device_linkchange(&gd32_emac_device->parent, RT_FALSE);
            } /* link down. */

            gd32_emac_device->phy_speed = phy_speed_new;
        } /* linkchange */

        rt_thread_delay(RT_TICK_PER_SECOND / 2);
    } /* while(1) */
}


int rt_hw_gd32_eth_init(void)
{
    rt_err_t state = RT_EOK;
    rt_size_t index;
    struct gd32_emac *device;
    const struct gd32_emac_config *cfg;
    rt_thread_t tid;
    char tx_sem_name[RT_NAME_MAX];
    char phy_thread_name[RT_NAME_MAX];

    rt_kprintf("rt_gd32_eth_init...\n");

    for (index = 0; index < gd32_emac_device_count(); index++)
    {
        device = gd32_emac_devices[index];
        cfg = &gd32_emac_cfgs[index];

        gd32_emac_fill_instance(device, cfg);

        gd32_emac_enable_resources(device);

        gd32_emac_nvic_configuration(device->ETHER_MAC_IRQ);

        rt_snprintf(tx_sem_name, sizeof(tx_sem_name), "tx%s", device->name);
        rt_sem_init(&device->tx_buf_free, tx_sem_name, EMAC_TXBUFNB, RT_IPC_FLAG_FIFO);

        state = eth_device_init(&device->parent, device->name);
        if (state != RT_EOK)
        {
            return state;
        }

        eth_device_linkchange(&device->parent, RT_FALSE);

        rt_snprintf(phy_thread_name, sizeof(phy_thread_name), "phy_%s", device->name);
        tid = rt_thread_create(phy_thread_name, phy_monitor, device, 1024, 20, 1);
        if (tid != RT_NULL)
        {
            rt_thread_startup(tid);
            rt_kprintf("[ETH] %s PHY monitor thread started\n", device->name);
        }
        else
        {
            rt_kprintf("[ETH] Failed to create %s PHY monitor thread\n", device->name);
            return -RT_ERROR;
        }
    }

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_gd32_eth_init);

#ifdef RT_USING_CACHE
/*!
    \brief      configure the MPU
    \param[in]  none
    \param[out] none
    \retval     none
*/
int enet_mpu_config(void)
{
    mpu_region_init_struct mpu_init_struct;
    mpu_region_struct_para_init(&mpu_init_struct);

    /* disable the MPU */
    ARM_MPU_Disable();
    ARM_MPU_SetRegion(0, 0);

    /* configure the MPU attributes for the entire 4GB area, Reserved, no access */
    /* This configuration is highly recommended to prevent Speculative Prefetching of external memory,
       which may cause CPU read locks and even system errors */
    mpu_init_struct.region_base_address  = 0x0;
    mpu_init_struct.region_size          = MPU_REGION_SIZE_4GB;
    mpu_init_struct.access_permission    = MPU_AP_NO_ACCESS;
    mpu_init_struct.access_bufferable    = MPU_ACCESS_NON_BUFFERABLE;
    mpu_init_struct.access_cacheable     = MPU_ACCESS_NON_CACHEABLE;
    mpu_init_struct.access_shareable     = MPU_ACCESS_SHAREABLE;
    mpu_init_struct.region_number        = MPU_REGION_NUMBER0;
    mpu_init_struct.subregion_disable    = 0x87;
    mpu_init_struct.instruction_exec     = MPU_INSTRUCTION_EXEC_NOT_PERMIT;
    mpu_init_struct.tex_type             = MPU_TEX_TYPE0;
    mpu_region_config(&mpu_init_struct);
    mpu_region_enable();

    /* Configure the DMA descriptors and Rx/Tx buffer*/
    mpu_init_struct.region_base_address = 0x30000000;
    mpu_init_struct.region_size = MPU_REGION_SIZE_32KB;
    mpu_init_struct.access_permission = MPU_AP_FULL_ACCESS;
    mpu_init_struct.access_bufferable    = MPU_ACCESS_BUFFERABLE;
    mpu_init_struct.access_cacheable     = MPU_ACCESS_NON_CACHEABLE;
    mpu_init_struct.access_shareable     = MPU_ACCESS_NON_SHAREABLE;

    mpu_init_struct.region_number = MPU_REGION_NUMBER1;
    mpu_init_struct.subregion_disable = MPU_SUBREGION_ENABLE;
    mpu_init_struct.instruction_exec = MPU_INSTRUCTION_EXEC_PERMIT;
    mpu_init_struct.tex_type = MPU_TEX_TYPE0;
    mpu_region_config(&mpu_init_struct);
    mpu_region_enable();


    /* enable the MPU */
    ARM_MPU_Enable(MPU_MODE_PRIV_DEFAULT);

    return 0;
}

INIT_BOARD_EXPORT(enet_mpu_config);
#endif

#ifdef RT_USING_FINSH
static void gd32_emac_set_mac_cmd(int argc, char **argv)
{
    struct gd32_emac *device;
    const char *device_name;
    const char *mac_string;
    rt_uint8_t mac[MAX_ADDR_LEN];
    rt_err_t result;

    if (argc == 2)
    {
        device = gd32_emac_get_default_device();
        device_name = (device != RT_NULL) ? device->name : RT_NULL;
        mac_string = argv[1];
    }
    else if (argc == 3)
    {
        device_name = argv[1];
        mac_string = argv[2];
        device = gd32_emac_find_device_by_name(device_name);
    }
    else
    {
        rt_kprintf("Usage: set_mac [ifname] XX:XX:XX:XX:XX:XX\n");
        rt_kprintf("   or: set_mac [ifname] XXXXXXXXXXXX\n");
        return;
    }

    if (device == RT_NULL)
    {
        rt_kprintf("Ethernet device not found\n");
        return;
    }

    if (!gd32_emac_parse_mac(mac_string, mac))
    {
        rt_kprintf("Invalid MAC format\n");
        return;
    }

    result = rt_device_control((rt_device_t)&device->parent, NIOCTL_SADDR, mac);
    if (result != RT_EOK)
    {
        rt_kprintf("Failed to update %s MAC\n", device_name);
        return;
    }

    rt_kprintf("%s MAC updated to %02X:%02X:%02X:%02X:%02X:%02X\n",
               device_name,
               mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}
MSH_CMD_EXPORT_ALIAS(gd32_emac_set_mac_cmd, set_mac, set ethernet MAC address);

static void gd32_emac_print_status(struct gd32_emac *device)
{
    rt_uint16_t phy_status, phy_sr;
    struct netif *netif;

    if (device == RT_NULL)
    {
        return;
    }

    netif = device->parent.netif;

    rt_kprintf("=== Ethernet %s Status ===\n", device->name);

    enet_phy_write_read(device->enet_periph, ENET_PHY_READ, device->phy_addr, PHY_BSR, &phy_status);
    enet_phy_write_read(device->enet_periph, ENET_PHY_READ, device->phy_addr, PHY_SR, &phy_sr);

    rt_kprintf("PHY Status Register: 0x%04X\n", phy_status);
    rt_kprintf("PHY Speed Register:  0x%04X\n", phy_sr);
    rt_kprintf("Link Status: %s\n", (phy_status & PHY_LINKED_STATUS) ? "UP" : "DOWN");
    rt_kprintf("Auto-negotiation: %s\n", (phy_status & PHY_AUTONEGO_COMPLETE) ? "Complete" : "In Progress");

    if (phy_status & PHY_LINKED_STATUS)
    {
        rt_kprintf("Speed: %s\n",
#if(PHY_TYPE == YT8512H || PHY_TYPE == YT8522)
                   (phy_sr & PHY_SPEED_STATUS) ? "100Mbps" : "10Mbps"
#else
                   (phy_sr & PHY_SPEED_STATUS) ? "10Mbps" : "100Mbps"
#endif
        );
        rt_kprintf("Duplex: %s\n", (phy_sr & PHY_DUPLEX_STATUS) ? "Full" : "Half");
    }

    rt_kprintf("\n=== Network Interface %s ===\n", device->name);
    if (netif != RT_NULL)
    {
        rt_kprintf("Interface: %c%c%s\n",
                   netif->name[0], netif->name[1],
                   (netif == netif_default) ? " (Default)" : "");
        rt_kprintf("Link: %s\n", netif_is_link_up(netif) ? "UP" : "DOWN");
        rt_kprintf("Status: %s\n", netif_is_up(netif) ? "UP" : "DOWN");
        rt_kprintf("IP: %s\n", ipaddr_ntoa(&(netif->ip_addr)));
        rt_kprintf("Gateway: %s\n", ipaddr_ntoa(&(netif->gw)));
        rt_kprintf("Netmask: %s\n", ipaddr_ntoa(&(netif->netmask)));

#if LWIP_DHCP
        {
            struct dhcp *dhcp = netif_dhcp_data(netif);
            if (dhcp != RT_NULL)
            {
                rt_kprintf("DHCP: Enabled (State: %d)\n", dhcp->state);
            }
            else
            {
                rt_kprintf("DHCP: Disabled\n");
            }
        }
#endif
    }
    else
    {
        rt_kprintf("Network interface not initialized\n");
    }
}

/* command of ethernet status */
void eth_status(void)
{
    rt_size_t index;

    for (index = 0; index < gd32_emac_device_count(); index++)
    {
        gd32_emac_print_status(gd32_emac_devices[index]);
    }
}
FINSH_FUNCTION_EXPORT(eth_status, show ethernet and network status);

/* command to restart DHCP client */
void dhcp_restart(void)
{
    struct gd32_emac *device = gd32_emac_get_default_device();
    struct netif *netif;

    if (device == RT_NULL)
    {
        rt_kprintf("No ethernet device found\n");
        return;
    }

    netif = device->parent.netif;

    if (netif == RT_NULL)
    {
        rt_kprintf("Network interface not found\n");
        return;
    }

    if (!netif_is_link_up(netif))
    {
        rt_kprintf("Network link is down, cannot restart DHCP\n");
        return;
    }

#if LWIP_DHCP
    rt_kprintf("Restarting DHCP client...\n");

    /* stop existing DHCP client */
    if (netif_dhcp_data(netif) != NULL)
    {
        dhcp_stop(netif);
        dhcp_cleanup(netif);
        rt_kprintf("Stopped existing DHCP client\n");
    }

    /* clear IP address */
    netif_set_addr(netif, IP4_ADDR_ANY, IP4_ADDR_ANY, IP4_ADDR_ANY);
    rt_kprintf("Cleared IP address\n");

    /* restart DHCP */
    rt_thread_delay(RT_TICK_PER_SECOND / 5); /* delay 200ms */
    dhcp_start(netif);

    rt_kprintf("DHCP client restarted\n");
#else
    rt_kprintf("DHCP is not enabled in build configuration\n");
#endif
}
FINSH_FUNCTION_EXPORT(dhcp_restart, manually restart DHCP client);

/* command to reset PHY */
void phy_reset(void)
{
    struct gd32_emac *device = gd32_emac_get_default_device();
    rt_uint16_t temp;

    if (device == RT_NULL)
    {
        rt_kprintf("No ethernet device found\n");
        return;
    }

    rt_kprintf("Resetting PHY...\n");

    /* reset PHY */
    temp = PHY_Reset;
    enet_phy_write_read(device->enet_periph, ENET_PHY_WRITE, device->phy_addr, PHY_BCR, &temp);

    rt_thread_delay(RT_TICK_PER_SECOND); /* wait 1 second */

    /* restart auto-negotiation */
    temp = PHY_AUTONEGOTIATION;
    enet_phy_write_read(device->enet_periph, ENET_PHY_WRITE, device->phy_addr, PHY_BCR, &temp);

    rt_kprintf("PHY reset completed\n");
}
FINSH_FUNCTION_EXPORT(phy_reset, reset PHY and restart auto-negotiation);

#endif /* RT_USING_FINSH */
