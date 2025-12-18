/*!
    \file    gd32f50x_dma.h
    \brief   definitions for the DMA

    \version 2025-11-03, V1.0.0, firmware for GD32F50x
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32F50X_DMA_H
#define GD32F50X_DMA_H

#include "gd32f50x.h"

/* DMA definitions */
#define DMA0                            (DMA_BASE)               /*!< DMA0 base address */
#define DMA1                            (DMA_BASE + 0x0400U)     /*!< DMA1 base address */

/* DMAMUX definitions */
#define DMAMUX                          DMAMUX_BASE              /*!< DMAMUX base address */

/* DMA registers definitions */
#define DMA_INTF(dmax)                  REG32((dmax) + 0x00U)    /*!< DMA interrupt flag register */
#define DMA_INTC(dmax)                  REG32((dmax) + 0x04U)    /*!< DMA interrupt flag clear register */

#define DMA_CH0CTL(dmax)                REG32((dmax) + 0x08U)    /*!< DMA channel 0 control register */
#define DMA_CH0CNT(dmax)                REG32((dmax) + 0x0CU)    /*!< DMA channel 0 counter register */
#define DMA_CH0PADDR(dmax)              REG32((dmax) + 0x10U)    /*!< DMA channel 0 peripheral base address register */
#define DMA_CH0MADDR(dmax)              REG32((dmax) + 0x14U)    /*!< DMA channel 0 memory base address register */

#define DMA_CH1CTL(dmax)                REG32((dmax) + 0x1CU)    /*!< DMA channel 1 control register */
#define DMA_CH1CNT(dmax)                REG32((dmax) + 0x20U)    /*!< DMA channel 1 counter register */
#define DMA_CH1PADDR(dmax)              REG32((dmax) + 0x24U)    /*!< DMA channel 1 peripheral base address register */
#define DMA_CH1MADDR(dmax)              REG32((dmax) + 0x28U)    /*!< DMA channel 1 memory base address register */

#define DMA_CH2CTL(dmax)                REG32((dmax) + 0x30U)    /*!< DMA channel 2 control register */
#define DMA_CH2CNT(dmax)                REG32((dmax) + 0x34U)    /*!< DMA channel 2 counter register */
#define DMA_CH2PADDR(dmax)              REG32((dmax) + 0x38U)    /*!< DMA channel 2 peripheral base address register */
#define DMA_CH2MADDR(dmax)              REG32((dmax) + 0x3CU)    /*!< DMA channel 2 memory base address register */

#define DMA_CH3CTL(dmax)                REG32((dmax) + 0x44U)    /*!< DMA channel 3 control register */
#define DMA_CH3CNT(dmax)                REG32((dmax) + 0x48U)    /*!< DMA channel 3 counter register */
#define DMA_CH3PADDR(dmax)              REG32((dmax) + 0x4CU)    /*!< DMA channel 3 peripheral base address register */
#define DMA_CH3MADDR(dmax)              REG32((dmax) + 0x50U)    /*!< DMA channel 3 memory base address register */

#define DMA_CH4CTL(dmax)                REG32((dmax) + 0x58U)    /*!< DMA channel 4 control register */
#define DMA_CH4CNT(dmax)                REG32((dmax) + 0x5CU)    /*!< DMA channel 4 counter register */
#define DMA_CH4PADDR(dmax)              REG32((dmax) + 0x60U)    /*!< DMA channel 4 peripheral base address register */
#define DMA_CH4MADDR(dmax)              REG32((dmax) + 0x64U)    /*!< DMA channel 4 memory base address register */

#define DMA_CH5CTL(dmax)                REG32((dmax) + 0x6CU)    /*!< DMA channel 5 control register */
#define DMA_CH5CNT(dmax)                REG32((dmax) + 0x70U)    /*!< DMA channel 5 counter register */
#define DMA_CH5PADDR(dmax)              REG32((dmax) + 0x74U)    /*!< DMA channel 5 peripheral base address register */
#define DMA_CH5MADDR(dmax)              REG32((dmax) + 0x78U)    /*!< DMA channel 5 memory base address register */

#define DMA_CH6CTL(dmax)                REG32((dmax) + 0x80U)    /*!< DMA channel 6 control register */
#define DMA_CH6CNT(dmax)                REG32((dmax) + 0x84U)    /*!< DMA channel 6 counter register */
#define DMA_CH6PADDR(dmax)              REG32((dmax) + 0x88U)    /*!< DMA channel 6 peripheral base address register */
#define DMA_CH6MADDR(dmax)              REG32((dmax) + 0x8CU)    /*!< DMA channel 6 memory base address register */

/* DMAMUX registers definitions */
#define DMAMUX_RM_CH0CFG                REG32(DMAMUX + 0x00000000U)          /*!< DMAMUX request multiplexer channel 0 configuration register */
#define DMAMUX_RM_CH1CFG                REG32(DMAMUX + 0x00000004U)          /*!< DMAMUX request multiplexer channel 1 configuration register */
#define DMAMUX_RM_CH2CFG                REG32(DMAMUX + 0x00000008U)          /*!< DMAMUX request multiplexer channel 2 configuration register */
#define DMAMUX_RM_CH3CFG                REG32(DMAMUX + 0x0000000CU)          /*!< DMAMUX request multiplexer channel 3 configuration register */
#define DMAMUX_RM_CH4CFG                REG32(DMAMUX + 0x00000010U)          /*!< DMAMUX request multiplexer channel 4 configuration register */
#define DMAMUX_RM_CH5CFG                REG32(DMAMUX + 0x00000014U)          /*!< DMAMUX request multiplexer channel 5 configuration register */
#define DMAMUX_RM_CH6CFG                REG32(DMAMUX + 0x00000018U)          /*!< DMAMUX request multiplexer channel 6 configuration register */
#define DMAMUX_RM_CH7CFG                REG32(DMAMUX + 0x0000001CU)          /*!< DMAMUX request multiplexer channel 7 configuration register */
#define DMAMUX_RM_CH8CFG                REG32(DMAMUX + 0x00000020U)          /*!< DMAMUX request multiplexer channel 8 configuration register */
#define DMAMUX_RM_CH9CFG                REG32(DMAMUX + 0x00000024U)          /*!< DMAMUX request multiplexer channel 9 configuration register */
#define DMAMUX_RM_CH10CFG               REG32(DMAMUX + 0x00000028U)          /*!< DMAMUX request multiplexer channel 10 configuration register */
#define DMAMUX_RM_CH11CFG               REG32(DMAMUX + 0x0000002CU)          /*!< DMAMUX request multiplexer channel 11 configuration register */

#define DMAMUX_RM_INTF                  REG32(DMAMUX + 0x00000080U)          /*!< DMAMUX request multiplexer channel interrupt flag register */
#define DMAMUX_RM_INTC                  REG32(DMAMUX + 0x00000084U)          /*!< DMAMUX request multiplexer channel interrupt flag clear register */

#define DMAMUX_RG_CH0CFG                REG32(DMAMUX + 0x00000100U)          /*!< DMAMUX generator channel 0 configuration register */
#define DMAMUX_RG_CH1CFG                REG32(DMAMUX + 0x00000104U)          /*!< DMAMUX generator channel 1 configuration register */
#define DMAMUX_RG_CH2CFG                REG32(DMAMUX + 0x00000108U)          /*!< DMAMUX generator channel 2 configuration register */
#define DMAMUX_RG_CH3CFG                REG32(DMAMUX + 0x0000010CU)          /*!< DMAMUX generator channel 3 configuration register */

#define DMAMUX_RG_INTF                  REG32(DMAMUX + 0x00000140U)          /*!< DMAMUX generator channel interrupt flag register */
#define DMAMUX_RG_INTC                  REG32(DMAMUX + 0x00000144U)          /*!< DMAMUX rgenerator channel interrupt flag clear register */

/* bits definitions */
/* DMA_INTF */
#define DMA_INTF_GIF                    BIT(0)                  /*!< global interrupt flag of channel */
#define DMA_INTF_FTFIF                  BIT(1)                  /*!< full transfer finish flag of channel */
#define DMA_INTF_HTFIF                  BIT(2)                  /*!< half transfer finish flag of channel */
#define DMA_INTF_ERRIF                  BIT(3)                  /*!< error flag of channel */

/* DMA_INTC */
#define DMA_INTC_GIFC                   BIT(0)                  /*!< clear global interrupt flag of channel */
#define DMA_INTC_FTFIFC                 BIT(1)                  /*!< clear transfer finish flag of channel */
#define DMA_INTC_HTFIFC                 BIT(2)                  /*!< clear half transfer finish flag of channel */
#define DMA_INTC_ERRIFC                 BIT(3)                  /*!< clear error flag of channel */

/* DMA_CHxCTL, x=0..6 */
#define DMA_CHXCTL_CHEN                 BIT(0)                  /*!< channel enable */
#define DMA_CHXCTL_FTFIE                BIT(1)                  /*!< enable bit for channel full transfer finish interrupt */
#define DMA_CHXCTL_HTFIE                BIT(2)                  /*!< enable bit for channel half transfer finish interrupt */
#define DMA_CHXCTL_ERRIE                BIT(3)                  /*!< enable bit for channel error interrupt */
#define DMA_CHXCTL_DIR                  BIT(4)                  /*!< transfer direction */
#define DMA_CHXCTL_CMEN                 BIT(5)                  /*!< circular mode enable */
#define DMA_CHXCTL_PNAGA                BIT(6)                  /*!< next address generation algorithm of peripheral */
#define DMA_CHXCTL_MNAGA                BIT(7)                  /*!< next address generation algorithm of memory */
#define DMA_CHXCTL_PWIDTH               BITS(8,9)               /*!< transfer data width of peripheral */
#define DMA_CHXCTL_MWIDTH               BITS(10,11)             /*!< transfer data width of memory */
#define DMA_CHXCTL_PRIO                 BITS(12,13)             /*!< priority level */
#define DMA_CHXCTL_M2M                  BIT(14)                 /*!< memory to memory mode */

/* DMA_CHxCNT,x=0..6 */
#define DMA_CHXCNT_CNT                  BITS(0,15)              /*!< transfer counter */

/* DMA_CHxPADDR,x=0..6 */
#define DMA_CHXPADDR_PADDR              BITS(0,31)              /*!< peripheral base address */

/* DMA_CHxMADDR,x=0..6 */
#define DMA_CHXMADDR_MADDR              BITS(0,31)              /*!< memory base address */

/* DMAMUX_RM_CHxCFG,x=0..11 */
#define DMAMUX_RM_CHXCFG_MUXID             BITS(0,7)            /*!< multiplexer input identification */
#define DMAMUX_RM_CHXCFG_SOIE              BIT(8)               /*!< synchronization overrun interrupt enable */
#define DMAMUX_RM_CHXCFG_EVGEN             BIT(9)               /*!< event generation enable */
#define DMAMUX_RM_CHXCFG_SYNCEN            BIT(16)              /*!< synchronization enable */
#define DMAMUX_RM_CHXCFG_SYNCP             BITS(17,18)          /*!< synchronization input polarity */
#define DMAMUX_RM_CHXCFG_NBR               BITS(19,23)          /*!< number of DMA requests to forward */
#define DMAMUX_RM_CHXCFG_SYNCID            BITS(24,28)          /*!< synchronization input identification */

/* DMAMUX_RM_INTF */
#define DMAMUX_RM_INTF_SOIF0               BIT(0)                               /*!< synchronization overrun event flag of request multiplexer channel 0 */
#define DMAMUX_RM_INTF_SOIF1               BIT(1)                               /*!< synchronization overrun event flag of request multiplexer channel 1 */
#define DMAMUX_RM_INTF_SOIF2               BIT(2)                               /*!< synchronization overrun event flag of request multiplexer channel 2 */
#define DMAMUX_RM_INTF_SOIF3               BIT(3)                               /*!< synchronization overrun event flag of request multiplexer channel 3 */
#define DMAMUX_RM_INTF_SOIF4               BIT(4)                               /*!< synchronization overrun event flag of request multiplexer channel 4 */
#define DMAMUX_RM_INTF_SOIF5               BIT(5)                               /*!< synchronization overrun event flag of request multiplexer channel 5 */
#define DMAMUX_RM_INTF_SOIF6               BIT(6)                               /*!< synchronization overrun event flag of request multiplexer channel 6 */
#define DMAMUX_RM_INTF_SOIF7               BIT(7)                               /*!< synchronization overrun event flag of request multiplexer channel 7 */
#define DMAMUX_RM_INTF_SOIF8               BIT(8)                               /*!< synchronization overrun event flag of request multiplexer channel 8 */
#define DMAMUX_RM_INTF_SOIF9               BIT(9)                               /*!< synchronization overrun event flag of request multiplexer channel 9 */
#define DMAMUX_RM_INTF_SOIF10              BIT(10)                              /*!< synchronization overrun event flag of request multiplexer channel 10 */
#define DMAMUX_RM_INTF_SOIF11              BIT(11)                              /*!< synchronization overrun event flag of request multiplexer channel 11 */

/* DMAMUX_RM_INTC */
#define DMAMUX_RM_INTC_SOIFC0              BIT(0)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 0 */
#define DMAMUX_RM_INTC_SOIFC1              BIT(1)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 1 */
#define DMAMUX_RM_INTC_SOIFC2              BIT(2)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 2 */
#define DMAMUX_RM_INTC_SOIFC3              BIT(3)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 3 */
#define DMAMUX_RM_INTC_SOIFC4              BIT(4)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 4 */
#define DMAMUX_RM_INTC_SOIFC5              BIT(5)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 5 */
#define DMAMUX_RM_INTC_SOIFC6              BIT(6)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 6 */
#define DMAMUX_RM_INTC_SOIFC7              BIT(7)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 7 */
#define DMAMUX_RM_INTC_SOIFC8              BIT(8)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 8 */
#define DMAMUX_RM_INTC_SOIFC9              BIT(9)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 9 */
#define DMAMUX_RM_INTC_SOIFC10             BIT(10)                              /*!< clear bit for synchronization overrun event flag of request multiplexer channel 10 */
#define DMAMUX_RM_INTC_SOIFC11             BIT(11)                              /*!< clear bit for synchronization overrun event flag of request multiplexer channel 11 */

/* DMAMUX_RG_CHxCFG,x=0..3 */
#define DMAMUX_RG_CHXCFG_TID               BITS(0,5)                            /*!< trigger input identification */
#define DMAMUX_RG_CHXCFG_TOIE              BIT(8)                               /*!< trigger overrun interrupt enable */
#define DMAMUX_RG_CHXCFG_RGEN              BIT(16)                              /*!< DMA request generator channel x enable */
#define DMAMUX_RG_CHXCFG_RGTP              BITS(17,18)                          /*!< DMA request generator trigger polarity */
#define DMAMUX_RG_CHXCFG_NBRG              BITS(19,23)                          /*!< number of DMA requests to be generated */

/* DMAMUX_RG_INTF */
#define DMAMUX_RG_INTF_TOIF0               BIT(0)                               /*!< trigger overrun event flag of request generator channel 0 */
#define DMAMUX_RG_INTF_TOIF1               BIT(1)                               /*!< trigger overrun event flag of request generator channel 1 */
#define DMAMUX_RG_INTF_TOIF2               BIT(2)                               /*!< trigger overrun event flag of request generator channel 2 */
#define DMAMUX_RG_INTF_TOIF3               BIT(3)                               /*!< trigger overrun event flag of request generator channel 3 */

/* DMAMUX_RG_INTC */
#define DMAMUX_RG_INTC_TOIFC0              BIT(0)                               /*!< clear bit for trigger overrun event flag of request generator channel 0 */
#define DMAMUX_RG_INTC_TOIFC1              BIT(1)                               /*!< clear bit for trigger overrun event flag of request generator channel 1 */
#define DMAMUX_RG_INTC_TOIFC2              BIT(2)                               /*!< clear bit for trigger overrun event flag of request generator channel 2 */
#define DMAMUX_RG_INTC_TOIFC3              BIT(3)                               /*!< clear bit for trigger overrun event flag of request generator channel 3 */

/* constants definitions */
/* define the DMAMUX bit position and its register index offset */
#define DMAMUX_REGIDX_BIT(regidx, bitpos) (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define DMAMUX_REG_VAL(offset)            (REG32(DMAMUX + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U)))
#define DMAMUX_BIT_POS(val)               ((uint32_t)(val) & 0x1FU)
#define DMAMUX_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22U) | (uint32_t)((bitpos2) << 16U) \
                                                                | (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos)))
#define DMAMUX_REG_VAL2(offset)            (REG32(DMAMUX + ((uint32_t)(offset) >> 22U)))
#define DMAMUX_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16U)
#define DMAMUX_REG_VAL3(offset)            (REG32(DMAMUX + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U) + 0x4U))

/* register offset */
#define DMAMUX_RM_CH0CFG_REG_OFFSET       ((uint32_t)0x00000000U)                                                      /*!< DMAMUX_RM_CH0CFG register offset */
#define DMAMUX_RM_CH1CFG_REG_OFFSET       ((uint32_t)0x00000004U)                                                      /*!< DMAMUX_RM_CH1CFG register offset */
#define DMAMUX_RM_CH2CFG_REG_OFFSET       ((uint32_t)0x00000008U)                                                      /*!< DMAMUX_RM_CH2CFG register offset */
#define DMAMUX_RM_CH3CFG_REG_OFFSET       ((uint32_t)0x0000000CU)                                                      /*!< DMAMUX_RM_CH3CFG register offset */
#define DMAMUX_RM_CH4CFG_REG_OFFSET       ((uint32_t)0x00000010U)                                                      /*!< DMAMUX_RM_CH4CFG register offset */
#define DMAMUX_RM_CH5CFG_REG_OFFSET       ((uint32_t)0x00000014U)                                                      /*!< DMAMUX_RM_CH5CFG register offset */
#define DMAMUX_RM_CH6CFG_REG_OFFSET       ((uint32_t)0x00000018U)                                                      /*!< DMAMUX_RM_CH6CFG register offset */
#define DMAMUX_RM_CH7CFG_REG_OFFSET       ((uint32_t)0x0000001CU)                                                      /*!< DMAMUX_RM_CH7CFG register offset */
#define DMAMUX_RM_CH8CFG_REG_OFFSET       ((uint32_t)0x00000020U)                                                      /*!< DMAMUX_RM_CH8CFG register offset */
#define DMAMUX_RM_CH9CFG_REG_OFFSET       ((uint32_t)0x00000024U)                                                      /*!< DMAMUX_RM_CH9CFG register offset */
#define DMAMUX_RM_CH10CFG_REG_OFFSET      ((uint32_t)0x00000028U)                                                      /*!< DMAMUX_RM_CH10CFG register offset */
#define DMAMUX_RM_CH11CFG_REG_OFFSET      ((uint32_t)0x0000002CU)                                                      /*!< DMAMUX_RM_CH11CFG register offset */
#define DMAMUX_RG_CH0CFG_REG_OFFSET       ((uint32_t)0x00000100U)                                                      /*!< DMAMUX_RG_CH0CFG register offset */
#define DMAMUX_RG_CH1CFG_REG_OFFSET       ((uint32_t)0x00000104U)                                                      /*!< DMAMUX_RG_CH1CFG register offset */
#define DMAMUX_RG_CH2CFG_REG_OFFSET       ((uint32_t)0x00000108U)                                                      /*!< DMAMUX_RG_CH2CFG register offset */
#define DMAMUX_RG_CH3CFG_REG_OFFSET       ((uint32_t)0x0000010CU)                                                      /*!< DMAMUX_RG_CH3CFG register offset */
#define DMAMUX_RM_INTF_REG_OFFSET         ((uint32_t)0x00000080U)                                                      /*!< DMAMUX_RM_INTF register offset */
#define DMAMUX_RG_INTF_REG_OFFSET         ((uint32_t)0x00000140U)                                                      /*!< DMAMUX_RG_INTF register offset */

/* DMA channel select */
typedef enum {
    DMA_CH0 = 0,                                                                                /*!< DMA Channel 0 */
    DMA_CH1,                                                                                    /*!< DMA Channel 1 */
    DMA_CH2,                                                                                    /*!< DMA Channel 2 */
    DMA_CH3,                                                                                    /*!< DMA Channel 3 */
    DMA_CH4,                                                                                    /*!< DMA Channel 4 */
    DMA_CH5,                                                                                    /*!< DMA Channel 5 */
    DMA_CH6                                                                                     /*!< DMA Channel 6 */
} dma_channel_enum;

/* DMAMUX request multiplexer channel */
typedef enum {
    DMAMUX_MUXCH0 = 0U,                                         /*!< DMAMUX request multiplexer Channel 0 */
    DMAMUX_MUXCH1,                                              /*!< DMAMUX request multiplexer Channel 1 */
    DMAMUX_MUXCH2,                                              /*!< DMAMUX request multiplexer Channel 2 */
    DMAMUX_MUXCH3,                                              /*!< DMAMUX request multiplexer Channel 3 */
    DMAMUX_MUXCH4,                                              /*!< DMAMUX request multiplexer Channel 4 */
    DMAMUX_MUXCH5,                                              /*!< DMAMUX request multiplexer Channel 5 */
    DMAMUX_MUXCH6,                                              /*!< DMAMUX request multiplexer Channel 6 */
    DMAMUX_MUXCH7,                                              /*!< DMAMUX request multiplexer Channel 7 */
    DMAMUX_MUXCH8,                                              /*!< DMAMUX request multiplexer Channel 8 */
    DMAMUX_MUXCH9,                                              /*!< DMAMUX request multiplexer Channel 9 */
    DMAMUX_MUXCH10,                                             /*!< DMAMUX request multiplexer Channel 10 */
    DMAMUX_MUXCH11,                                             /*!< DMAMUX request multiplexer Channel 11 */
} dmamux_multiplexer_channel_enum;

/* DMAMUX request generator channel */
typedef enum {
    DMAMUX_GENCH0 = 0U,                                         /*!< DMAMUX request generator Channel 0 */
    DMAMUX_GENCH1,                                              /*!< DMAMUX request generator Channel 1 */
    DMAMUX_GENCH2,                                              /*!< DMAMUX request generator Channel 2 */
    DMAMUX_GENCH3,                                              /*!< DMAMUX request generator Channel 3 */
} dmamux_generator_channel_enum;

/* DMAMUX interrupt */
typedef enum {
    /* interrupts in CHxCFG register */
    DMAMUX_INT_MUXCH0_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH0CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH1_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH1CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH2_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH2CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH3_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH3CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH4_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH4CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH5_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH5CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH6_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH6CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH7_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH7CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH8_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH8CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH9_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH9CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH10_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH10CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH11_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH11CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt */
    DMAMUX_INT_GENCH0_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH0CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 0 trigger overrun interrupt */
    DMAMUX_INT_GENCH1_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH1CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 1 trigger overrun interrupt */
    DMAMUX_INT_GENCH2_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH2CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 2 trigger overrun interrupt */
    DMAMUX_INT_GENCH3_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH3CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 3 trigger overrun interrupt */
} dmamux_interrupt_enum;

/* DMAMUX flags */
typedef enum {
    /* flags in INTF register */
    DMAMUX_FLAG_MUXCH0_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 0U),                                         /*!< DMAMUX request multiplexer channel 0 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH1_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 1U),                                         /*!< DMAMUX request multiplexer channel 1 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH2_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 2U),                                         /*!< DMAMUX request multiplexer channel 2 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH3_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 3U),                                         /*!< DMAMUX request multiplexer channel 3 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH4_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 4U),                                         /*!< DMAMUX request multiplexer channel 4 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH5_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 5U),                                         /*!< DMAMUX request multiplexer channel 5 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH6_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 6U),                                         /*!< DMAMUX request multiplexer channel 6 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH7_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 7U),                                         /*!< DMAMUX request multiplexer channel 7 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH8_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 8 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH9_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 9U),                                         /*!< DMAMUX request multiplexer channel 9 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH10_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 10U),                                        /*!< DMAMUX request multiplexer channel 10 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH11_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 11U),                                        /*!< DMAMUX request multiplexer channel 11 synchronization overrun flag */
    DMAMUX_FLAG_GENCH0_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 0U),                                         /*!< DMAMUX request generator channel 0 trigger overrun flag */
    DMAMUX_FLAG_GENCH1_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 1U),                                         /*!< DMAMUX request generator channel 1 trigger overrun flag */
    DMAMUX_FLAG_GENCH2_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 2U),                                         /*!< DMAMUX request generator channel 2 trigger overrun flag */
    DMAMUX_FLAG_GENCH3_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 3U),                                         /*!< DMAMUX request generator channel 3 trigger overrun flag */
} dmamux_flag_enum;

/* DMAMUX interrupt flags */
typedef enum {
    /* interrupt flags in INTF register */
    DMAMUX_INT_FLAG_MUXCH0_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 0U, DMAMUX_RM_CH0CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH1_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 1U, DMAMUX_RM_CH1CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH2_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 2U, DMAMUX_RM_CH2CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH3_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 3U, DMAMUX_RM_CH3CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH4_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 4U, DMAMUX_RM_CH4CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH5_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 5U, DMAMUX_RM_CH5CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH6_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 6U, DMAMUX_RM_CH6CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH7_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 7U, DMAMUX_RM_CH7CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 7 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH8_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 8U, DMAMUX_RM_CH8CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 8 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH9_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 9U, DMAMUX_RM_CH9CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 9 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH10_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 10U, DMAMUX_RM_CH10CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 10 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH11_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 11U, DMAMUX_RM_CH11CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 11 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH0_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 0U, DMAMUX_RG_CH0CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 0 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH1_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 1U, DMAMUX_RG_CH1CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 1 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH2_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 2U, DMAMUX_RG_CH2CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 2 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH3_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 3U, DMAMUX_RG_CH3CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 3 trigger overrun interrupt flag */
} dmamux_interrupt_flag_enum;

/* DMA initialize struct */
typedef struct {
    uint32_t request;                                                                                                   /*!< channel input identification */
    uint32_t periph_addr;                                                                                               /*!< peripheral base address */
    uint32_t periph_width;                                                                                              /*!< transfer data size of peripheral */
    uint32_t memory_addr;                                                                                               /*!< memory base address */
    uint32_t memory_width;                                                                                              /*!< transfer data size of memory */
    uint32_t number;                                                                                                    /*!< channel transfer number */
    uint32_t priority;                                                                                                  /*!< channel priority level */
    uint32_t periph_inc;                                                                                                /*!< peripheral increasing mode */
    uint32_t memory_inc;                                                                                                /*!< memory increasing mode */
    uint32_t direction;                                                                                                 /*!< channel data transfer direction */
    uint32_t circular_mode;                                                                                             /*!< DMA circular mode */
} dma_parameter_struct;

/* DMAMUX request multiplexer synchronization configuration structure */
typedef struct {
    uint32_t sync_id;                                                                                                   /*!< synchronization input identification */
    uint32_t sync_polarity;                                                                                             /*!< synchronization input polarity */
    uint32_t request_number;                                                                                            /*!< number of DMA requests to forward */
} dmamux_sync_parameter_struct;

/* DMAMUX request generator trigger configuration structure */
typedef struct {
    uint32_t trigger_id;                                                                                                /*!< trigger input identification */
    uint32_t trigger_polarity;                                                                                          /*!< DMAMUX request generator trigger polarity */
    uint32_t request_number;                                                                                            /*!< number of DMA requests to be generated */
} dmamux_gen_parameter_struct;

#define DMA_FLAG_ADD(flag, shift)           ((flag) << ((shift) * 4U))                                                  /*!< DMA channel flag shift */

/* DMA_register address */
#define DMA_CHCTL(dma, channel)             REG32(((dma) + 0x08U) + 0x14U * (uint32_t)(channel))                        /*!< the address of DMA channel CHXCTL register */
#define DMA_CHCNT(dma, channel)             REG32(((dma) + 0x0CU) + 0x14U * (uint32_t)(channel))                        /*!< the address of DMA channel CHXCNT register */
#define DMA_CHPADDR(dma, channel)           REG32(((dma) + 0x10U) + 0x14U * (uint32_t)(channel))                        /*!< the address of DMA channel CHXPADDR register */
#define DMA_CHMADDR(dma, channel)           REG32(((dma) + 0x14U) + 0x14U * (uint32_t)(channel))                        /*!< the address of DMA channel CHXMADDR register */

/* DMAMUX_RM_CHxCFG base address */
#define DMAMUX_RM_CHXCFG_BASE               (DMAMUX)                                                                    /*!< the base address of DMAMUX request multiplexer channel CHxCFG register */

/* DMAMUX request multiplexer channel shift bit */
#define DMAMUX_RM_CHXCFG(channel)           REG32(DMAMUX_RM_CHXCFG_BASE + 0x04U * (uint32_t)(channel))                  /*!< the address of DMAMUX request multiplexer channel CHxCFG register */

/* DMAMUX_RG_CHxCFG base address */
#define DMAMUX_RG_CHXCFG_BASE               (DMAMUX + 0x00000100U)                                                      /*!< the base address of DMAMUX channel request generator CHxCFG register */

/* DMAMUX request generator channel shift bit */
#define DMAMUX_RG_CHXCFG(channel)           REG32(DMAMUX_RG_CHXCFG_BASE + 0x04U * (uint32_t)(channel))                  /*!< the address of DMAMUX channel request generator CHxCFG register */

/* DMA reset value */
#define DMA_CHCTL_RESET_VALUE               ((uint32_t)0x00000000U)                         /*!< the reset value of DMA channel CHXCTL register  */
#define DMA_CHCNT_RESET_VALUE               ((uint32_t)0x00000000U)                         /*!< the reset value of DMA channel CHXCNT register  */
#define DMA_CHPADDR_RESET_VALUE             ((uint32_t)0x00000000U)                         /*!< the reset value of DMA channel CHXPADDR register  */
#define DMA_CHMADDR_RESET_VALUE             ((uint32_t)0x00000000U)                         /*!< the reset value of DMA channel CHXMADDR register  */
#define DMA_CHINTF_RESET_VALUE              (DMA_INTF_GIF | DMA_INTF_FTFIF | \
                                             DMA_INTF_HTFIF | DMA_INTF_ERRIF)               /*!< clear DMA channel DMA_INTF register */

/* DMA_INTF register */
/* interrupt flag bits */
#define DMA_INT_FLAG_GIF                     DMA_INTF_GIF                                    /*!< global interrupt flag of channel */
#define DMA_INT_FLAG_FTF                     DMA_INTF_FTFIF                                  /*!< full transfer finish interrupt flag of channel */
#define DMA_INT_FLAG_HTF                     DMA_INTF_HTFIF                                  /*!< half transfer finish interrupt flag of channel */
#define DMA_INT_FLAG_ERR                     DMA_INTF_ERRIF                                  /*!< error interrupt flag of channel */

/* flag bits */
#define DMA_FLAG_GIF                         DMA_INTF_GIF                                    /*!< global interrupt flag of channel */
#define DMA_FLAG_FTF                         DMA_INTF_FTFIF                                  /*!< full transfer finish flag of channel */
#define DMA_FLAG_HTF                         DMA_INTF_HTFIF                                  /*!< half transfer finish flag of channel */
#define DMA_FLAG_ERR                         DMA_INTF_ERRIF                                  /*!< error flag of channel */

/* DMA_CHxCTL register */
/* interrupt enable bits */
#define DMA_INT_FTF                          DMA_CHXCTL_FTFIE                                /*!< enable bit for channel full transfer finish interrupt */
#define DMA_INT_HTF                          DMA_CHXCTL_HTFIE                                /*!< enable bit for channel half transfer finish interrupt */
#define DMA_INT_ERR                          DMA_CHXCTL_ERRIE                                /*!< enable bit for channel error interrupt */

/* transfer direction */
#define DMA_PERIPHERAL_TO_MEMORY             ((uint8_t)0x0000U)                              /*!< read from peripheral and write to memory */
#define DMA_MEMORY_TO_PERIPHERAL             ((uint8_t)0x0001U)                              /*!< read from memory and write to peripheral */

/* peripheral increasing mode */
#define DMA_PERIPH_INCREASE_DISABLE          ((uint8_t)0x0000U)                              /*!< next address of peripheral is fixed address mode */
#define DMA_PERIPH_INCREASE_ENABLE           ((uint8_t)0x0001U)                              /*!< next address of peripheral is increasing address mode */

/* memory increasing mode */
#define DMA_MEMORY_INCREASE_DISABLE          ((uint8_t)0x0000U)                              /*!< next address of memory is fixed address mode */
#define DMA_MEMORY_INCREASE_ENABLE           ((uint8_t)0x0001U)                              /*!< next address of memory is increasing address mode */

#define DMA_CIRCULAR_MODE_DISABLE            ((uint32_t)0x00000000U)                         /*!< circular mode disable */
#define DMA_CIRCULAR_MODE_ENABLE             ((uint32_t)0x00000001U)                         /*!< circular mode enable */

/* transfer data size of peripheral */
#define CHCTL_PWIDTH(regval)                 (BITS(8,9) & ((uint32_t)(regval) << 8))         /*!< transfer data size of peripheral */
#define DMA_PERIPHERAL_WIDTH_8BIT            CHCTL_PWIDTH(0)                                 /*!< transfer data size of peripheral is 8-bit */
#define DMA_PERIPHERAL_WIDTH_16BIT           CHCTL_PWIDTH(1)                                 /*!< transfer data size of peripheral is 16-bit */
#define DMA_PERIPHERAL_WIDTH_32BIT           CHCTL_PWIDTH(2)                                 /*!< transfer data size of peripheral is 32-bit */

/* transfer data size of memory */
#define CHCTL_MWIDTH(regval)                 (BITS(10,11) & ((uint32_t)(regval) << 10))      /*!< transfer data size of memory */
#define DMA_MEMORY_WIDTH_8BIT                CHCTL_MWIDTH(0)                                 /*!< transfer data size of memory is 8-bit */
#define DMA_MEMORY_WIDTH_16BIT               CHCTL_MWIDTH(1)                                 /*!< transfer data size of memory is 16-bit */
#define DMA_MEMORY_WIDTH_32BIT               CHCTL_MWIDTH(2)                                 /*!< transfer data size of memory is 32-bit */

/* channel priority level */
#define CHCTL_PRIO(regval)                   (BITS(12,13) & ((uint32_t)(regval) << 12))      /*!< DMA channel priority level */
#define DMA_PRIORITY_LOW                     CHCTL_PRIO(0)                                   /*!< low priority */
#define DMA_PRIORITY_MEDIUM                  CHCTL_PRIO(1)                                   /*!< medium priority */
#define DMA_PRIORITY_HIGH                    CHCTL_PRIO(2)                                   /*!< high priority */
#define DMA_PRIORITY_ULTRA_HIGH              CHCTL_PRIO(3)                                   /*!< ultra high priority */

/* channel transfer mode */
#define CHCTL_TM(regval)                    (BIT(4) & ((uint32_t)(regval) << 4U))
#define DMA_PERIPH_TO_MEMORY                CHCTL_TM(0)                                     /*!< read from peripheral and write to memory */
#define DMA_MEMORY_TO_PERIPH                CHCTL_TM(1)                                     /*!< read from memory and write to peripheral */

/* memory to memory mode */
#define DMA_MEMORY_TO_MEMORY_DISABLE        ((uint32_t)0x00000000U)                         /*!<Memory to Memory mode disable*/
#define DMA_MEMORY_TO_MEMORY_ENABLE         ((uint32_t)0x00000001U)                         /*!<Memory to Memory mode enable*/

/* DMA_CHxCNT register */
/* transfer counter */
#define DMA_CHANNEL_CNT_MASK                DMA_CHXCNT_CNT                                  /*!< transfer counter mask */

/* DMAMUX request multiplexer channel input identification */
#define RM_CHXCFG_MUXID(regval)             (BITS(0,7) & ((uint32_t)(regval) << 0U))                                     /*!< multiplexer input identification */
#define DMA_REQUEST_M2M                     RM_CHXCFG_MUXID(0U)                                                          /*!< memory to memory transfer */
#define DMA_REQUEST_GENERATOR0              RM_CHXCFG_MUXID(1U)                                                          /*!< DMAMUX request generator 0 */
#define DMA_REQUEST_GENERATOR1              RM_CHXCFG_MUXID(2U)                                                          /*!< DMAMUX request generator 1 */
#define DMA_REQUEST_GENERATOR2              RM_CHXCFG_MUXID(3U)                                                          /*!< DMAMUX request generator 2 */
#define DMA_REQUEST_GENERATOR3              RM_CHXCFG_MUXID(4U)                                                          /*!< DMAMUX request generator 3 */
#define DMA_REQUEST_ADC0_ROUTINE            RM_CHXCFG_MUXID(5U)                                                          /*!< DMAMUX ADC0 ROUTINE request */
#define DMA_REQUEST_ADC0_INSERTED           RM_CHXCFG_MUXID(6U)                                                          /*!< DMAMUX ADC0 INSERTED request */
#define DMA_REQUEST_DAC0_CH0                RM_CHXCFG_MUXID(7U)                                                          /*!< DMAMUX DAC0 CH0 request */
#define DMA_REQUEST_TIMER5_UP               RM_CHXCFG_MUXID(8U)                                                          /*!< DMAMUX TIMER5 UP request */
#define DMA_REQUEST_TIMER6_UP               RM_CHXCFG_MUXID(9U)                                                          /*!< DMAMUX TIMER6 UP request */
#define DMA_REQUEST_SPI0_RX                 RM_CHXCFG_MUXID(10U)                                                         /*!< DMAMUX SPI0 RX request */
#define DMA_REQUEST_SPI0_TX                 RM_CHXCFG_MUXID(11U)                                                         /*!< DMAMUX SPI0 TX request */
#define DMA_REQUEST_SPI1_RX                 RM_CHXCFG_MUXID(12U)                                                         /*!< DMAMUX SPI1 RX request */
#define DMA_REQUEST_SPI1_TX                 RM_CHXCFG_MUXID(13U)                                                         /*!< DMAMUX SPI1 TX request */
#define DMA_REQUEST_SPI2_RX                 RM_CHXCFG_MUXID(14U)                                                         /*!< DMAMUX SPI2 RX request */
#define DMA_REQUEST_SPI2_TX                 RM_CHXCFG_MUXID(15U)                                                         /*!< DMAMUX SPI2 TX request */
#define DMA_REQUEST_I2C0_RX                 RM_CHXCFG_MUXID(16U)                                                         /*!< DMAMUX I2C0 RX request */
#define DMA_REQUEST_I2C0_TX                 RM_CHXCFG_MUXID(17U)                                                         /*!< DMAMUX I2C0 TX request */
#define DMA_REQUEST_I2C1_RX                 RM_CHXCFG_MUXID(18U)                                                         /*!< DMAMUX I2C1 RX request */
#define DMA_REQUEST_I2C1_TX                 RM_CHXCFG_MUXID(19U)                                                         /*!< DMAMUX I2C1 TX request */
#define DMA_REQUEST_USART0_RX               RM_CHXCFG_MUXID(20U)                                                         /*!< DMAMUX USART0 RX request */
#define DMA_REQUEST_USART0_TX               RM_CHXCFG_MUXID(21U)                                                         /*!< DMAMUX USART0 TX request */
#define DMA_REQUEST_USART1_RX               RM_CHXCFG_MUXID(22U)                                                         /*!< DMAMUX USART1 RX request */
#define DMA_REQUEST_USART1_TX               RM_CHXCFG_MUXID(23U)                                                         /*!< DMAMUX USART1 TX request */
#define DMA_REQUEST_USART2_RX               RM_CHXCFG_MUXID(24U)                                                         /*!< DMAMUX USART2 RX request */
#define DMA_REQUEST_USART2_TX               RM_CHXCFG_MUXID(25U)                                                         /*!< DMAMUX USART2 TX request */
#define DMA_REQUEST_UART3_RX                RM_CHXCFG_MUXID(26U)                                                         /*!< DMAMUX UART3 RX request */
#define DMA_REQUEST_UART3_TX                RM_CHXCFG_MUXID(27U)                                                         /*!< DMAMUX UART3 TX request */
#define DMA_REQUEST_TIMER0_CH0              RM_CHXCFG_MUXID(28U)                                                         /*!< DMAMUX TIMER0 CH0 request */
#define DMA_REQUEST_TIMER0_CH1              RM_CHXCFG_MUXID(29U)                                                         /*!< DMAMUX TIMER0 CH1 request */
#define DMA_REQUEST_TIMER0_CH2              RM_CHXCFG_MUXID(30U)                                                         /*!< DMAMUX TIMER0 CH2 request */
#define DMA_REQUEST_TIMER0_CH3              RM_CHXCFG_MUXID(31U)                                                         /*!< DMAMUX TIMER0 CH3 request */
#define DMA_REQUEST_TIMER0_UP               RM_CHXCFG_MUXID(32U)                                                         /*!< DMAMUX TIMER0 UP request */
#define DMA_REQUEST_TIMER0_TRG              RM_CHXCFG_MUXID(33U)                                                         /*!< DMAMUX TIMER0 TRG request */
#define DMA_REQUEST_TIMER0_CMT              RM_CHXCFG_MUXID(34U)                                                         /*!< DMAMUX TIMER0 CMT request */
#define DMA_REQUEST_TIMER7_CH0              RM_CHXCFG_MUXID(35U)                                                         /*!< DMAMUX TIMER7 CH0 request */
#define DMA_REQUEST_TIMER7_CH1              RM_CHXCFG_MUXID(36U)                                                         /*!< DMAMUX TIMER7 CH1 request */
#define DMA_REQUEST_TIMER7_CH2              RM_CHXCFG_MUXID(37U)                                                         /*!< DMAMUX TIMER7 CH2 request */
#define DMA_REQUEST_TIMER7_CH3              RM_CHXCFG_MUXID(38U)                                                         /*!< DMAMUX TIMER7 CH3 request */
#define DMA_REQUEST_TIMER7_UP               RM_CHXCFG_MUXID(39U)                                                         /*!< DMAMUX TIMER7 UP request */
#define DMA_REQUEST_TIMER7_TRG              RM_CHXCFG_MUXID(40U)                                                         /*!< DMAMUX TIMER7 TRG request */
#define DMA_REQUEST_TIMER7_CMT              RM_CHXCFG_MUXID(41U)                                                         /*!< DMAMUX TIMER7 CMT request */
#define DMA_REQUEST_TIMER1_CH0              RM_CHXCFG_MUXID(42U)                                                         /*!< DMAMUX TIMER1 CH0 request */
#define DMA_REQUEST_TIMER1_CH1              RM_CHXCFG_MUXID(43U)                                                         /*!< DMAMUX TIMER1 CH1 request */
#define DMA_REQUEST_TIMER1_CH2              RM_CHXCFG_MUXID(44U)                                                         /*!< DMAMUX TIMER1 CH2 request */
#define DMA_REQUEST_TIMER1_CH3              RM_CHXCFG_MUXID(45U)                                                         /*!< DMAMUX TIMER1 CH3 request */
#define DMA_REQUEST_TIMER1_UP               RM_CHXCFG_MUXID(46U)                                                         /*!< DMAMUX TIMER1 UP request */
#define DMA_REQUEST_TIMER1_TRG              RM_CHXCFG_MUXID(47U)                                                         /*!< DMAMUX TIMER1 TRG request */
#define DMA_REQUEST_TIMER2_CH0              RM_CHXCFG_MUXID(48U)                                                         /*!< DMAMUX TIMER2 CH0 request */
#define DMA_REQUEST_TIMER2_CH1              RM_CHXCFG_MUXID(49U)                                                         /*!< DMAMUX TIMER2 CH1 request */
#define DMA_REQUEST_TIMER2_CH2              RM_CHXCFG_MUXID(50U)                                                         /*!< DMAMUX TIMER2 CH2 request */
#define DMA_REQUEST_TIMER2_CH3              RM_CHXCFG_MUXID(51U)                                                         /*!< DMAMUX TIMER2 CH3 request */
#define DMA_REQUEST_TIMER2_UP               RM_CHXCFG_MUXID(52U)                                                         /*!< DMAMUX TIMER2 UP request */
#define DMA_REQUEST_TIMER2_TRG              RM_CHXCFG_MUXID(53U)                                                         /*!< DMAMUX TIMER2 TRG request */
#define DMA_REQUEST_TIMER3_CH0              RM_CHXCFG_MUXID(54U)                                                         /*!< DMAMUX TIMER3 CH0 request */
#define DMA_REQUEST_TIMER3_CH1              RM_CHXCFG_MUXID(55U)                                                         /*!< DMAMUX TIMER3 CH1 request */
#define DMA_REQUEST_TIMER3_CH2              RM_CHXCFG_MUXID(56U)                                                         /*!< DMAMUX TIMER3 CH2 request */
#define DMA_REQUEST_TIMER3_CH3              RM_CHXCFG_MUXID(57U)                                                         /*!< DMAMUX TIMER3 CH3 request */
#define DMA_REQUEST_TIMER3_UP               RM_CHXCFG_MUXID(58U)                                                         /*!< DMAMUX TIMER3 UP request */
#define DMA_REQUEST_TIMER3_TRG              RM_CHXCFG_MUXID(59U)                                                         /*!< DMAMUX TIMER3 TRG request */
#define DMA_REQUEST_TIMER4_CH0              RM_CHXCFG_MUXID(60U)                                                         /*!< DMAMUX TIMER4 CH0 request */
#define DMA_REQUEST_TIMER4_CH1              RM_CHXCFG_MUXID(61U)                                                         /*!< DMAMUX TIMER4 CH1 request */
#define DMA_REQUEST_TIMER4_CH2              RM_CHXCFG_MUXID(62U)                                                         /*!< DMAMUX TIMER4 CH2 request */
#define DMA_REQUEST_TIMER4_CH3              RM_CHXCFG_MUXID(63U)                                                         /*!< DMAMUX TIMER4 CH3 request */
#define DMA_REQUEST_TIMER4_UP               RM_CHXCFG_MUXID(64U)                                                         /*!< DMAMUX TIMER4 UP request */
#define DMA_REQUEST_TIMER4_TRG              RM_CHXCFG_MUXID(65U)                                                         /*!< DMAMUX TIMER4 TRG request */
#define DMA_REQUEST_ADC1_ROUTINE            RM_CHXCFG_MUXID(66U)                                                         /*!< DMAMUX ADC1 ROUTINE request */
#define DMA_REQUEST_ADC1_INSERTED           RM_CHXCFG_MUXID(67U)                                                         /*!< DMAMUX ADC1 INSERTED request */
#define DMA_REQUEST_ADC2_ROUTINE            RM_CHXCFG_MUXID(68U)                                                         /*!< DMAMUX ADC2 ROUTINE request */
#define DMA_REQUEST_ADC2_INSERTED           RM_CHXCFG_MUXID(69U)                                                         /*!< DMAMUX ADC2 INSERTED request */
#define DMA_REQUEST_TIMER15_CH0             RM_CHXCFG_MUXID(72U)                                                         /*!< DMAMUX TIMER15 CH0 request */
#define DMA_REQUEST_TIMER15_CH1             RM_CHXCFG_MUXID(73U)                                                         /*!< DMAMUX TIMER15 CH1 request */
#define DMA_REQUEST_TIMER15_MCH0            RM_CHXCFG_MUXID(74U)                                                         /*!< DMAMUX TIMER15 MCH0 request */
#define DMA_REQUEST_TIMER15_UP              RM_CHXCFG_MUXID(75U)                                                         /*!< DMAMUX TIMER15 UP request */
#define DMA_REQUEST_TIMER15_TRG             RM_CHXCFG_MUXID(76U)                                                         /*!< DMAMUX TIMER15 TRG request */
#define DMA_REQUEST_TIMER15_CMT             RM_CHXCFG_MUXID(77U)                                                         /*!< DMAMUX TIMER15 CMT request */
#define DMA_REQUEST_TIMER16_CH0             RM_CHXCFG_MUXID(78U)                                                         /*!< DMAMUX TIMER16 CH0 request */
#define DMA_REQUEST_TIMER16_CH1             RM_CHXCFG_MUXID(79U)                                                         /*!< DMAMUX TIMER16 CH1 request */
#define DMA_REQUEST_TIMER16_MCH0            RM_CHXCFG_MUXID(80U)                                                         /*!< DMAMUX TIMER16 MCH0 request */
#define DMA_REQUEST_TIMER16_UP              RM_CHXCFG_MUXID(81U)                                                         /*!< DMAMUX TIMER16 UP request */
#define DMA_REQUEST_TIMER16_TRG             RM_CHXCFG_MUXID(82U)                                                         /*!< DMAMUX TIMER16 TRG request */
#define DMA_REQUEST_TIMER16_CMT             RM_CHXCFG_MUXID(83U)                                                         /*!< DMAMUX TIMER16 CMT request */
#define DMA_REQUEST_CAU_IN                  RM_CHXCFG_MUXID(84U)                                                         /*!< DMAMUX CRYP IN request */
#define DMA_REQUEST_CAU_OUT                 RM_CHXCFG_MUXID(85U)                                                         /*!< DMAMUX CRYP OUT request */
#define DMA_REQUEST_HAU_IN                 RM_CHXCFG_MUXID(86U)                                                         /*!< DMAMUX HASH IN request */

/* DMAMUX request generator trigger input identification */
#define RG_CHXCFG_TID(regval)             (BITS(0,4) & ((uint32_t)(regval) << 0U))                                     /*!< trigger input identification */
#define DMAMUX_TRIGGER_EVT0_OUT           RG_CHXCFG_TID(0U)                                                            /*!< trigger input is Evt0_out */
#define DMAMUX_TRIGGER_EVT1_OUT           RG_CHXCFG_TID(1U)                                                            /*!< trigger input is Evt1_out */
#define DMAMUX_TRIGGER_EVT2_OUT           RG_CHXCFG_TID(2U)                                                            /*!< trigger input is Evt2_out */
#define DMAMUX_TRIGGER_EVT3_OUT           RG_CHXCFG_TID(3U)                                                            /*!< trigger input is Evt3_out */
#define DMAMUX_TRIGGER_EXTI0_IT           RG_CHXCFG_TID(4U)                                                            /*!< trigger input is EXTI0 */
#define DMAMUX_TRIGGER_EXTI1_IT           RG_CHXCFG_TID(5U)                                                            /*!< trigger input is EXTI1 */
#define DMAMUX_TRIGGER_EXTI2_IT           RG_CHXCFG_TID(6U)                                                            /*!< trigger input is EXTI2 */
#define DMAMUX_TRIGGER_EXTI3_IT           RG_CHXCFG_TID(7U)                                                            /*!< trigger input is EXTI3 */
#define DMAMUX_TRIGGER_EXTI4_IT           RG_CHXCFG_TID(8U)                                                            /*!< trigger input is EXTI4 */
#define DMAMUX_TRIGGER_EXTI5_IT           RG_CHXCFG_TID(9U)                                                            /*!< trigger input is EXTI5 */
#define DMAMUX_TRIGGER_EXTI6_IT           RG_CHXCFG_TID(10U)                                                           /*!< trigger input is EXTI6 */
#define DMAMUX_TRIGGER_EXTI7_IT           RG_CHXCFG_TID(11U)                                                           /*!< trigger input is EXTI7 */
#define DMAMUX_TRIGGER_EXTI0_EVT          RG_CHXCFG_TID(12U)                                                           /*!< trigger input is EXTI8 */
#define DMAMUX_TRIGGER_EXTI1_EVT          RG_CHXCFG_TID(13U)                                                           /*!< trigger input is EXTI9 */
#define DMAMUX_TRIGGER_EXTI2_EVT          RG_CHXCFG_TID(14U)                                                           /*!< trigger input is EXTI10 */
#define DMAMUX_TRIGGER_EXTI3_EVT          RG_CHXCFG_TID(15U)                                                           /*!< trigger input is EXTI11 */
#define DMAMUX_TRIGGER_EXTI4_EVT          RG_CHXCFG_TID(16U)                                                           /*!< trigger input is EXTI12 */
#define DMAMUX_TRIGGER_EXTI5_EVT          RG_CHXCFG_TID(17U)                                                           /*!< trigger input is EXTI13 */
#define DMAMUX_TRIGGER_EXTI6_EVT          RG_CHXCFG_TID(18U)                                                           /*!< trigger input is EXTI14 */
#define DMAMUX_TRIGGER_EXTI7_EVT          RG_CHXCFG_TID(19U)                                                           /*!< trigger input is EXTI15 */

/* DMAMUX request generator trigger polarity */
#define RG_CHXCFG_RGTP(regval)            (BITS(17,18) & ((uint32_t)(regval) << 17U))                                  /*!< DMA request generator trigger polarity */
#define DMAMUX_GEN_NO_EVENT               RG_CHXCFG_RGTP(0U)                                                           /*!< no event detection */
#define DMAMUX_GEN_RISING                 RG_CHXCFG_RGTP(1U)                                                           /*!< rising edge */
#define DMAMUX_GEN_FALLING                RG_CHXCFG_RGTP(2U)                                                           /*!< falling edge */
#define DMAMUX_GEN_RISING_FALLING         RG_CHXCFG_RGTP(3U)                                                                                                                 /*!< rising and falling edges */

/* number of DMA requests to be generated */
#define RG_CHXCFG_NBRG(regval)            (BITS(19,23) & ((uint32_t)(regval) << 19U))                                  /*!< number of DMA requests to be generated */

/* DMAMUX request multiplexer channel synchronization input identification */
#define RM_CHXCFG_SYNCID(regval)          (BITS(24,28) & ((uint32_t)(regval) << 24U))                                  /*!< synchronization input identification */
#define DMAMUX_SYNC_EVT0_OUT              RM_CHXCFG_SYNCID(0U)                                                         /*!< synchronization input is Evt0_out */
#define DMAMUX_SYNC_EVT1_OUT              RM_CHXCFG_SYNCID(1U)                                                         /*!< synchronization input is Evt1_out */
#define DMAMUX_SYNC_EVT2_OUT              RM_CHXCFG_SYNCID(2U)                                                         /*!< synchronization input is Evt2_out */
#define DMAMUX_SYNC_EVT3_OUT              RM_CHXCFG_SYNCID(3U)                                                         /*!< synchronization input is Evt3_out */
#define DMAMUX_SYNC_EXTI0_IT              RM_CHXCFG_SYNCID(4U)                                                         /*!< synchronization input is EXTI0 */
#define DMAMUX_SYNC_EXTI1_IT              RM_CHXCFG_SYNCID(5U)                                                         /*!< synchronization input is EXTI1 */
#define DMAMUX_SYNC_EXTI2_IT              RM_CHXCFG_SYNCID(6U)                                                         /*!< synchronization input is EXTI2 */
#define DMAMUX_SYNC_EXTI3_IT              RM_CHXCFG_SYNCID(7U)                                                         /*!< synchronization input is EXTI3 */
#define DMAMUX_SYNC_EXTI4_IT              RM_CHXCFG_SYNCID(8U)                                                         /*!< synchronization input is EXTI4 */
#define DMAMUX_SYNC_EXTI5_IT              RM_CHXCFG_SYNCID(9U)                                                         /*!< synchronization input is EXTI5 */
#define DMAMUX_SYNC_EXTI6_IT              RM_CHXCFG_SYNCID(10U)                                                        /*!< synchronization input is EXTI6 */
#define DMAMUX_SYNC_EXTI7_IT              RM_CHXCFG_SYNCID(11U)                                                        /*!< synchronization input is EXTI7 */
#define DMAMUX_SYNC_EXTI0_EVT             RM_CHXCFG_SYNCID(12U)                                                        /*!< synchronization input is EXTI8 */
#define DMAMUX_SYNC_EXTI1_EVT             RM_CHXCFG_SYNCID(13U)                                                        /*!< synchronization input is EXTI9 */
#define DMAMUX_SYNC_EXTI2_EVT             RM_CHXCFG_SYNCID(14U)                                                        /*!< synchronization input is EXTI10 */
#define DMAMUX_SYNC_EXTI3_EVT             RM_CHXCFG_SYNCID(15U)                                                        /*!< synchronization input is EXTI11 */
#define DMAMUX_SYNC_EXTI4_EVT             RM_CHXCFG_SYNCID(16U)                                                        /*!< synchronization input is EXTI12 */
#define DMAMUX_SYNC_EXTI5_EVT             RM_CHXCFG_SYNCID(17U)                                                        /*!< synchronization input is EXTI13 */
#define DMAMUX_SYNC_EXTI6_EVT             RM_CHXCFG_SYNCID(18U)                                                        /*!< synchronization input is EXTI14 */
#define DMAMUX_SYNC_EXTI7_EVT             RM_CHXCFG_SYNCID(19U)                                                        /*!< synchronization input is EXTI15 */

/* DMAMUX request multiplexer synchronization input polarity */
#define RM_CHXCFG_SYNCP(regval)           (BITS(17,18) & ((uint32_t)(regval) << 17U))                                  /*!< synchronization input polarity */
#define DMAMUX_SYNC_NO_EVENT              RM_CHXCFG_SYNCP(0U)                                                          /*!< no event detection */
#define DMAMUX_SYNC_RISING                RM_CHXCFG_SYNCP(1U)                                                          /*!< rising edge */
#define DMAMUX_SYNC_FALLING               RM_CHXCFG_SYNCP(2U)                                                          /*!< falling edge */
#define DMAMUX_SYNC_RISING_FALLING        RM_CHXCFG_SYNCP(3U)                                                          /*!< rising and falling edges */

/* number of DMA requests to forward */
#define RM_CHXCFG_NBR(regval)            (BITS(19,23) & ((uint32_t)(regval) << 19U))                                   /*!< number of DMA requests to forward */

/* function declarations */
/* DMA deinitialization and initialization functions */
/* deinitialize DMA a channel registers */
void dma_deinit(uint32_t dma_periph, dma_channel_enum channelx);
/* initialize the parameters of DMA struct with the default values */
void dma_struct_para_init(dma_parameter_struct *init_struct);
/* initialize DMA channel */
void dma_init(uint32_t dma_periph, dma_channel_enum channelx, dma_parameter_struct *init_struct);
/* enable DMA circulation mode */
void dma_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA circulation mode */
void dma_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable memory to memory mode */
void dma_memory_to_memory_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable memory to memory mode */
void dma_memory_to_memory_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable DMA channel */
void dma_channel_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA channel */
void dma_channel_disable(uint32_t dma_periph, dma_channel_enum channelx);

/* DMA configuration functions */
/* set DMA peripheral base address */
void dma_periph_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address);
/* set DMA memory base address */
void dma_memory_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address);
/* set the number of remaining data to be transferred by the DMA */
void dma_transfer_number_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t number);
/* get the number of remaining data to be transferred by the DMA */
uint32_t dma_transfer_number_get(uint32_t dma_periph, dma_channel_enum channelx);
/* configure priority level of DMA channel */
void dma_priority_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t priority);
/* configure transfer data size of memory */
void dma_memory_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t mwidth);
/* configure transfer data size of peripheral */
void dma_periph_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t pwidth);
/* enable next address increasement algorithm of memory */
void dma_memory_increase_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable next address increasement algorithm of memory */
void dma_memory_increase_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable next address increasement algorithm of peripheral */
void dma_periph_increase_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable next address increasement algorithm of peripheral */
void dma_periph_increase_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* configure the direction of data transfer on the channel */
void dma_transfer_direction_config(uint32_t dma_periph, dma_channel_enum channelx,
                                   uint32_t direction);

/* flag and interrupt functions */
/* check DMA flag is set or not */
FlagStatus dma_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* clear DMA a channel flag */
void dma_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* check DMA flag and interrupt enable bit is set or not */
FlagStatus dma_interrupt_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* clear DMA a channel flag */
void dma_interrupt_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* enable DMA interrupt */
void dma_interrupt_enable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t source);
/* disable DMA interrupt */
void dma_interrupt_disable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t source);

/* DMAMUX functions */
/* DMAMUX request multiplexer functions */
/* initialize the parameters of DMAMUX synchronization mode structure with the default values */
void dmamux_sync_struct_para_init(dmamux_sync_parameter_struct *init_struct);
/* initialize DMAMUX request multiplexer channel synchronization mode */
void dmamux_synchronization_init(dmamux_multiplexer_channel_enum channelx,
                                 dmamux_sync_parameter_struct *init_struct);
/* enable synchronization mode */
void dmamux_synchronization_enable(dmamux_multiplexer_channel_enum channelx);
/* disable synchronization mode */
void dmamux_synchronization_disable(dmamux_multiplexer_channel_enum channelx);
/* enable event generation */
void dmamux_event_generation_enable(dmamux_multiplexer_channel_enum channelx);
/* disable event generation */
void dmamux_event_generation_disable(dmamux_multiplexer_channel_enum channelx);

/* DMAMUX request generator functions */
/* initialize the parameters of DMAMUX request generator structure with the default values */
void dmamux_gen_struct_para_init(dmamux_gen_parameter_struct *init_struct);
/* initialize DMAMUX request generator channel */
void dmamux_request_generator_init(dmamux_generator_channel_enum channelx,
                                   dmamux_gen_parameter_struct *init_struct);
/* enable DMAMUX request generator channel */
void dmamux_request_generator_channel_enable(dmamux_generator_channel_enum channelx);
/* disable DMAMUX request generator channel */
void dmamux_request_generator_channel_disable(dmamux_generator_channel_enum channelx);

/* DMAMUX configuration functions */
/* configure synchronization input polarity */
void dmamux_synchronization_polarity_config(dmamux_multiplexer_channel_enum channelx,
                                            uint32_t polarity);
/* configure number of DMA requests to forward */
void dmamux_request_forward_number_config(dmamux_multiplexer_channel_enum channelx,
                                          uint32_t number);
/* configure synchronization input identification */
void dmamux_sync_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id);
/* configure multiplexer input identification */
void dmamux_request_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id);
/* configure trigger input polarity */
void dmamux_trigger_polarity_config(dmamux_generator_channel_enum channelx, uint32_t polarity);
/* configure number of DMA requests to be generated */
void dmamux_request_generate_number_config(dmamux_generator_channel_enum channelx, uint32_t number);
/* configure trigger input identification */
void dmamux_trigger_id_config(dmamux_generator_channel_enum channelx, uint32_t id);

/* interrupt & flag functions */
/* get DMAMUX flag */
FlagStatus dmamux_flag_get(dmamux_flag_enum flag);
/* clear DMAMUX flag */
void dmamux_flag_clear(dmamux_flag_enum flag);
/* enable DMAMUX interrupt */
void dmamux_interrupt_enable(dmamux_interrupt_enum interrupt);
/* disable DMAMUX interrupt */
void dmamux_interrupt_disable(dmamux_interrupt_enum interrupt);
/* get DMAMUX interrupt flag */
FlagStatus dmamux_interrupt_flag_get(dmamux_interrupt_flag_enum int_flag);
/* clear DMAMUX interrupt flag */
void dmamux_interrupt_flag_clear(dmamux_interrupt_flag_enum int_flag);

#endif /* gd32f50x_DMA_H */
