/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "synopsys_emac.h"
#include "board.h"

/* Global pointers on Tx and Rx descriptor used to track transmit and receive descriptors */
extern EMAC_DMADESCTypeDef  *DMATxDescToSet;
extern EMAC_DMADESCTypeDef  *DMARxDescToGet;

#if defined(SOC_SERIES_GD32H77x)

#ifndef EMAC_PHY_LINK_TIMEOUT_TICK
#define EMAC_PHY_LINK_TIMEOUT_TICK      (RT_TICK_PER_SECOND * 10)
#endif

#ifndef EMAC_PHY_LINK_POLL_TICK
#define EMAC_PHY_LINK_POLL_TICK         ((RT_TICK_PER_SECOND / 10) > 0 ? (RT_TICK_PER_SECOND / 10) : 1)
#endif

#ifndef EMAC_PHY_RESET_DELAY_TICK
#define EMAC_PHY_RESET_DELAY_TICK       ((RT_TICK_PER_SECOND / 2) > 0 ? (RT_TICK_PER_SECOND / 2) : 1)
#endif

/*!
    \brief      configure the transmit IP frame checksum offload calculation and insertion, API ID: 0x0006
    \param[in]  desc: the descriptor pointer which users want to configure
    \param[in]  checksum: IP frame checksum configuration
                only one parameter can be selected which is shown as below
      \arg        ENET_CHECKSUM_DISABLE: checksum insertion disabled
      \arg        ENET_CHECKSUM_IPV4HEADER: only IP header checksum calculation and insertion are enabled
      \arg        ENET_CHECKSUM_TCPUDPICMP_SEGMENT: TCP/UDP/ICMP checksum insertion calculated but pseudo-header
      \arg        ENET_CHECKSUM_TCPUDPICMP_FULL: TCP/UDP/ICMP checksum insertion fully calculated
    \param[out] none
    \retval     ErrStatus: ERROR, SUCCESS
*/
ErrStatus enet_transmit_checksum_config(enet_descriptors_struct *desc, uint32_t checksum)
{
    ErrStatus ret = ERROR;

    desc->status &= ~ENET_TDES0_CM;
    desc->status |= (checksum & ENET_TDES0_CM);
    ret = SUCCESS;

    return ret;
}

static rt_int32_t emac_mac_addr_index_get(rt_uint32_t mac_addr)
{
    if ((mac_addr & 0x7U) != 0U)
    {
        return -1;
    }

    mac_addr >>= 3;

    if (mac_addr > 3U)
    {
        return -1;
    }

    return (rt_int32_t)mac_addr;
}


static enet_mediamode_enum emac_get_phy_mediemode(uint32_t enet_periph, rt_uint16_t phy_address)
{
    uint16_t phy_bsr = 0U;
    uint16_t phy_sr = 0U;
    uint16_t phy_value = 0U;
    rt_tick_t start_tick;
    rt_bool_t is_100m = RT_FALSE;
    rt_bool_t is_full_duplex = RT_FALSE;
    __IO enet_mediamode_enum spd_dpm = ENET_100M_FULLDUPLEX;

    phy_value = PHY_Reset;
    if (SUCCESS != enet_phy_write_read(enet_periph, ENET_PHY_WRITE, phy_address, PHY_BCR, &phy_value))
    {
        rt_kprintf("emac phy reset failed.\r\n");
        return spd_dpm;
    }

    rt_thread_delay(EMAC_PHY_RESET_DELAY_TICK);

    phy_value = PHY_AUTONEGOTIATION;
    if (SUCCESS != enet_phy_write_read(enet_periph, ENET_PHY_WRITE, phy_address, PHY_BCR, &phy_value))
    {
        rt_kprintf("emac phy auto negotiation start failed.\r\n");
        return spd_dpm;
    }

    start_tick = rt_tick_get();

    while (1)
    {
        if (SUCCESS != enet_phy_write_read(enet_periph, ENET_PHY_READ, phy_address, PHY_BSR, &phy_bsr))
        {
            rt_kprintf("emac phy status read failed.\r\n");
            return spd_dpm;
        }

        if ((phy_bsr & PHY_LINKED_STATUS) && (phy_bsr & PHY_AUTONEGO_COMPLETE))
        {
            break;
        }

        if ((rt_tick_get() - start_tick) >= EMAC_PHY_LINK_TIMEOUT_TICK)
        {
            rt_kprintf("emac link wait timeout.\r\n");
            return spd_dpm;
        }

        rt_thread_delay(EMAC_PHY_LINK_POLL_TICK);
    }

    if (SUCCESS != enet_phy_write_read(enet_periph, ENET_PHY_READ, phy_address, PHY_SR, &phy_sr))
    {
        rt_kprintf("emac phy negotiation result read failed.\r\n");
        return spd_dpm;
    }

#if (PHY_TYPE == YT8512H || PHY_TYPE == YT8522)
    is_100m = (phy_sr & PHY_SPEED_STATUS) ? RT_TRUE : RT_FALSE;
#else
    is_100m = (phy_sr & PHY_SPEED_STATUS) ? RT_FALSE : RT_TRUE;
#endif

    is_full_duplex = (phy_sr & PHY_DUPLEX_STATUS) ? RT_TRUE : RT_FALSE;

    if (is_100m)
    {
        spd_dpm = is_full_duplex ? ENET_100M_FULLDUPLEX : ENET_100M_HALFDUPLEX;
        return spd_dpm;
    }

    spd_dpm = is_full_duplex ? ENET_10M_FULLDUPLEX : ENET_10M_HALFDUPLEX;
    return spd_dpm;
}
#endif

/**
  * Initializes the ETHERNET peripheral according to the specified
  */
rt_uint32_t EMAC_init(rt_uint32_t SystemCoreClock, uint32_t enet_periph, rt_uint16_t phy_address)
{
    struct rt_synopsys_eth *ETHERNET_MAC;
    rt_uint32_t enet_init_state = EMAC_ERROR;

    RT_UNUSED(SystemCoreClock);

    ETHERNET_MAC = EMAC_REGS(enet_periph);
    RT_UNUSED(ETHERNET_MAC);

    /*-------------------------------- Reset ethernet -------------------------------*/
    enet_deinit(enet_periph);
    if(SUCCESS != enet_software_reset(enet_periph))
    {
        rt_kprintf("enet software reset failed. \r\n");
        return EMAC_ERROR;
    }

    /* configure the parameters which are usually less cared for enet initialization */
    enet_initpara_config(HALFDUPLEX_OPTION, ENET_CARRIERSENSE_DISABLE|ENET_RECEIVEOWN_ENABLE|ENET_BACKOFFLIMIT_10|ENET_DEFERRALCHECK_DISABLE);

    /*-------------------------------- Initialize ENET ------------------------------*/
#if defined(SOC_SERIES_GD32H77x)
    {
        enet_mediamode_enum mediamode = emac_get_phy_mediemode(enet_periph, phy_address);

#ifdef RT_LWIP_USING_HW_CHECKSUM
        enet_init_state = enet_init(enet_periph, mediamode, ENET_AUTOCHECKSUM_DROP_FAILFRAMES, ENET_BROADCAST_FRAMES_PASS);
#else
        enet_init_state = enet_init(enet_periph, mediamode, ENET_NO_AUTOCHECKSUM, ENET_BROADCAST_FRAMES_PASS);
#endif
    }
#else
#ifdef RT_LWIP_USING_HW_CHECKSUM
    enet_init_state = enet_init(enet_periph, ENET_AUTO_NEGOTIATION, ENET_AUTOCHECKSUM_DROP_FAILFRAMES, ENET_BROADCAST_FRAMES_PASS);
#else
    enet_init_state = enet_init(enet_periph, ENET_AUTO_NEGOTIATION, ENET_NO_AUTOCHECKSUM, ENET_BROADCAST_FRAMES_PASS);
#endif
#endif
    if(SUCCESS != enet_init_state) {
        rt_kprintf("enet init failed. \r\n");
        return EMAC_ERROR;
    } else {
        /* Return Ethernet configuration success */
        return EMAC_SUCCESS;
    }
}

/**
  * Enables or disables the specified ETHERNET DMA interrupts.
  */
void EMAC_INT_config(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t EMAC_DMA_IT, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the selected ETHERNET DMA interrupts */
        ETHERNET_MAC->IER |= EMAC_DMA_IT;
    }
    else
    {
        /* Disable the selected ETHERNET DMA interrupts */
        ETHERNET_MAC->IER &=(~(rt_uint32_t)EMAC_DMA_IT);
    }
}

/**
  * Configures the selected MAC address.
  */
void EMAC_MAC_Addr_config(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t MacAddr, rt_uint8_t *Addr)
{
    rt_uint32_t value;
    rt_int32_t index;

    if ((ETHERNET_MAC == RT_NULL) || (Addr == RT_NULL))
    {
        return;
    }

    index = emac_mac_addr_index_get(MacAddr);
    if (index < 0)
    {
        return;
    }

    /* Calculate the selectecd MAC address high register */
    value = ((rt_uint32_t)Addr[5] << 8) | (rt_uint32_t)Addr[4];
    /* Load the selectecd MAC address high register */
    ETHERNET_MAC->MARs[index].MARH = (ETHERNET_MAC->MARs[index].MARH & ~0x0000FFFFU) | value;
    /* Calculate the selectecd MAC address low register */
    value = ((rt_uint32_t)Addr[3] << 24) | ((rt_uint32_t)Addr[2] << 16) | ((rt_uint32_t)Addr[1] << 8) | Addr[0];

    /* Load the selectecd MAC address low register */
    ETHERNET_MAC->MARs[index].MARL = value;
}

/**
  * Configures the selected MAC address filter.
  */
void EMAC_MAC_AddrFilter_config(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t MacAddr, rt_uint32_t FilterMode, rt_uint32_t AddrMask)
{
    rt_uint32_t value;
    rt_int32_t index;

    if (ETHERNET_MAC == RT_NULL)
    {
        return;
    }

    index = emac_mac_addr_index_get(MacAddr);
    if (index < 0)
    {
        return;
    }

    value = ETHERNET_MAC->MARs[index].MARH;
    value &= ~(EMAC_MAC_AddressFilter_Source | EMAC_MAC_AddressFilter_Mask);
    value |= EMAC_MAC_AddressFilter_Enable;

    if (FilterMode == EMAC_MAC_AddressFilter_SA)
    {
        value |= EMAC_MAC_AddressFilter_Source;
    }

    value |= (AddrMask & EMAC_MAC_AddressFilter_Mask);
    ETHERNET_MAC->MARs[index].MARH = value;
}

/**
  * Enables or disables the MAC transmission.
  */
void EMAC_MACTransmissionCmd(struct rt_synopsys_eth * ETHERNET_MAC, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the MAC transmission */
        ETHERNET_MAC->MCR |= EMAC_MACCR_TE;
    }
    else
    {
        /* Disable the MAC transmission */
        ETHERNET_MAC->MCR &= ~EMAC_MACCR_TE;
    }
}

/**
  * Clears the ETHERNET transmit FIFO.
  */
void EMAC_FlushTransmitFIFO(struct rt_synopsys_eth * ETHERNET_MAC)
{
    /* Set the Flush Transmit FIFO bit */
    ETHERNET_MAC->OMR |= EMAC_DMAOMR_FTF;
}

/**
  * Enables or disables the MAC reception.
  */
void EMAC_MACReceptionCmd(struct rt_synopsys_eth * ETHERNET_MAC, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the MAC reception */
        ETHERNET_MAC->MCR |= EMAC_MACCR_RE;
    }
    else
    {
        /* Disable the MAC reception */
        ETHERNET_MAC->MCR &= ~EMAC_MACCR_RE;
    }
}

/**
  * Enables or disables the DMA transmission.
  */
void EMAC_DMATransmissionCmd(struct rt_synopsys_eth * ETHERNET_MAC, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the DMA transmission */
        ETHERNET_MAC->OMR |= EMAC_DMAOMR_ST;
    }
    else
    {
        /* Disable the DMA transmission */
        ETHERNET_MAC->OMR &= ~EMAC_DMAOMR_ST;
    }
}

/**
  * Enables or disables the DMA reception.
  */
void EMAC_DMAReceptionCmd(struct rt_synopsys_eth * ETHERNET_MAC, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the DMA reception */
        ETHERNET_MAC->OMR |= EMAC_DMAOMR_SR;
    }
    else
    {
        /* Disable the DMA reception */
        ETHERNET_MAC->OMR &= ~EMAC_DMAOMR_SR;
    }
}

/**
  * Enables ENET MAC and DMA reception/transmission
  */
void EMAC_start(uint32_t enet_periph)
{
    struct rt_synopsys_eth *ETHERNET_MAC;

    ETHERNET_MAC = EMAC_REGS(enet_periph);

    /* Enable transmit state machine of the MAC for transmission on the MII */
    EMAC_MACTransmissionCmd(ETHERNET_MAC, RT_TRUE);
    /* Flush Transmit FIFO */
    enet_txfifo_flush(enet_periph);
    /* Enable receive state machine of the MAC for reception from the MII */
    EMAC_MACReceptionCmd(ETHERNET_MAC, RT_TRUE);

    /* Start DMA transmission */
    EMAC_DMATransmissionCmd(ETHERNET_MAC, RT_TRUE);
    /* Start DMA reception */
    EMAC_DMAReceptionCmd(ETHERNET_MAC, RT_TRUE);
}

/**
  * Clears the ETHERNET's DMA interrupt pending bit.
  */
void EMAC_clear_pending(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t pending)
{
    /* Clear the selected ETHERNET DMA IT */
    ETHERNET_MAC->SR = (rt_uint32_t) pending;
}

/**
  * Resumes the DMA Transmission by writing to the DmaRxPollDemand register
  *   (the data written could be anything). This forces the DMA to resume reception.
  */
void EMAC_resume_reception(struct rt_synopsys_eth * ETHERNET_MAC)
{
    ETHERNET_MAC->RPDR = 0;
}

/**
  * Resumes the DMA Transmission by writing to the DmaTxPollDemand register
  *   (the data written could be anything). This forces  the DMA to resume transmission.
  */
void EMAC_resume_transmission(struct rt_synopsys_eth * ETHERNET_MAC)
{
    ETHERNET_MAC->TPDR = 0;
}

/**
  * Read a PHY register
  */
rt_uint16_t EMAC_PHY_read(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint16_t PHYAddress, rt_uint16_t PHYReg)
{
    rt_uint32_t value = 0;
    volatile rt_uint32_t timeout = 0;

    /* Get the ETHERNET MACMIIAR value */
    value = ETHERNET_MAC->GAR;
    /* Keep only the CSR Clock Range CR[2:0] bits value */
    value &= ~MACMIIAR_CR_MASK;
    /* Prepare the MII address register value */
    value |=(((rt_uint32_t)PHYAddress<<11) & EMAC_MACMIIAR_PA); /* Set the PHY device address */
    value |=(((rt_uint32_t)PHYReg<<6) & EMAC_MACMIIAR_MR);      /* Set the PHY register address */
    value &= ~EMAC_MACMIIAR_MW;                              /* Set the read mode */
    value |= EMAC_MACMIIAR_MB;                               /* Set the MII Busy bit */
    /* Write the result value into the MII Address register */
    ETHERNET_MAC->GAR = value;
    /* Check for the Busy flag */
    do
    {
        timeout++;
        value = ETHERNET_MAC->GAR;
    }
    while ((value & EMAC_MACMIIAR_MB) && (timeout < (rt_uint32_t)PHY_READ_TO));
    /* Return ERROR in case of timeout */
    if(timeout == PHY_READ_TO)
    {
        return (rt_uint16_t)EMAC_ERROR;
    }

    /* Return data register value */
    return (rt_uint16_t)(ETHERNET_MAC->GDR);
}

/**
  * Write to a PHY register
  */
rt_uint32_t EMAC_PHY_write(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint16_t PHYAddress, rt_uint16_t PHYReg, rt_uint16_t PHYValue)
{
    rt_uint32_t value = 0;
    volatile rt_uint32_t timeout = 0;

    /* Get the ETHERNET MACMIIAR value */
    value = ETHERNET_MAC->GAR;
    /* Keep only the CSR Clock Range CR[2:0] bits value */
    value &= ~MACMIIAR_CR_MASK;
    /* Prepare the MII register address value */
    value |=(((rt_uint32_t)PHYAddress<<11) & EMAC_MACMIIAR_PA); /* Set the PHY device address */
    value |=(((rt_uint32_t)PHYReg<<6) & EMAC_MACMIIAR_MR);      /* Set the PHY register address */
    value |= EMAC_MACMIIAR_MW;                               /* Set the write mode */
    value |= EMAC_MACMIIAR_MB;                               /* Set the MII Busy bit */
    /* Give the value to the MII data register */
    ETHERNET_MAC->GDR = PHYValue;
    /* Write the result value into the MII Address register */
    ETHERNET_MAC->GAR = value;
    /* Check for the Busy flag */
    do
    {
        timeout++;
        value = ETHERNET_MAC->GAR;
    }
    while ((value & EMAC_MACMIIAR_MB) && (timeout < (rt_uint32_t)PHY_WRITE_TO));
    /* Return ERROR in case of timeout */
    if(timeout == PHY_WRITE_TO)
    {
        return EMAC_ERROR;
    }

    /* Return SUCCESS */
    return EMAC_SUCCESS;
}
