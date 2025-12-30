/*!
    \file    gd32g5x3_dma.h
    \brief   definitions for the DMA

    \version 2025-02-10, V1.1.0, firmware for GD32G5x3
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

#ifndef GD32G5X3_DMA_H
#define GD32G5X3_DMA_H

#include "gd32g5x3.h"

/* DMAx(x=0,1) definitions */
#define DMA0                                    DMA_BASE                       /*!< DMA0 base address */
#define DMA1                                    (DMA_BASE + 0x00000400U)       /*!< DMA1 base address */
/* DMAMUX definitions */
#define DMAMUX                                  DMAMUX_BASE                    /*!< DMA base address */

/* DMAx(x=0,1) registers definitions */
#define DMA_INTF(dmax)                          REG32((dmax) + 0x00000000U)    /*!< DMA interrupt flag register */
#define DMA_INTC(dmax)                          REG32((dmax) + 0x00000004U)    /*!< DMA interrupt flag clear register */
#define DMA_CH0CTL(dmax)                        REG32((dmax) + 0x00000008U)    /*!< DMA channel 0 control register */
#define DMA_CH0CNT(dmax)                        REG32((dmax) + 0x0000000CU)    /*!< DMA channel 0 counter register */
#define DMA_CH0PADDR(dmax)                      REG32((dmax) + 0x00000010U)    /*!< DMA channel 0 peripheral base address register */
#define DMA_CH0MADDR(dmax)                      REG32((dmax) + 0x00000014U)    /*!< DMA channel 0 memory base address register */
#define DMA_CH1CTL(dmax)                        REG32((dmax) + 0x0000001CU)    /*!< DMA channel 1 control register */
#define DMA_CH1CNT(dmax)                        REG32((dmax) + 0x00000020U)    /*!< DMA channel 1 counter register */
#define DMA_CH1PADDR(dmax)                      REG32((dmax) + 0x00000024U)    /*!< DMA channel 1 peripheral base address register */
#define DMA_CH1MADDR(dmax)                      REG32((dmax) + 0x00000028U)    /*!< DMA channel 1 memory base address register */
#define DMA_CH2CTL(dmax)                        REG32((dmax) + 0x00000030U)    /*!< DMA channel 2 control register */
#define DMA_CH2CNT(dmax)                        REG32((dmax) + 0x00000034U)    /*!< DMA channel 2 counter register */
#define DMA_CH2PADDR(dmax)                      REG32((dmax) + 0x00000038U)    /*!< DMA channel 2 peripheral base address register */
#define DMA_CH2MADDR(dmax)                      REG32((dmax) + 0x0000003CU)    /*!< DMA channel 2 memory base address register */
#define DMA_CH3CTL(dmax)                        REG32((dmax) + 0x00000044U)    /*!< DMA channel 3 control register */
#define DMA_CH3CNT(dmax)                        REG32((dmax) + 0x00000048U)    /*!< DMA channel 3 counter register */
#define DMA_CH3PADDR(dmax)                      REG32((dmax) + 0x0000004CU)    /*!< DMA channel 3 peripheral base address register */
#define DMA_CH3MADDR(dmax)                      REG32((dmax) + 0x00000050U)    /*!< DMA channel 3 memory base address register */
#define DMA_CH4CTL(dmax)                        REG32((dmax) + 0x00000058U)    /*!< DMA channel 4 control register */
#define DMA_CH4CNT(dmax)                        REG32((dmax) + 0x0000005CU)    /*!< DMA channel 4 counter register */
#define DMA_CH4PADDR(dmax)                      REG32((dmax) + 0x00000060U)    /*!< DMA channel 4 peripheral base address register */
#define DMA_CH4MADDR(dmax)                      REG32((dmax) + 0x00000064U)    /*!< DMA channel 4 memory base address register */
#define DMA_CH5CTL(dmax)                        REG32((dmax) + 0x0000006CU)    /*!< DMA channel 5 control register */
#define DMA_CH5CNT(dmax)                        REG32((dmax) + 0x00000070U)    /*!< DMA channel 5 counter register */
#define DMA_CH5PADDR(dmax)                      REG32((dmax) + 0x00000074U)    /*!< DMA channel 5 peripheral base address register */
#define DMA_CH5MADDR(dmax)                      REG32((dmax) + 0x00000078U)    /*!< DMA channel 5 memory base address register */
#define DMA_CH6CTL(dmax)                        REG32((dmax) + 0x00000080U)    /*!< DMA channel 6 control register */
#define DMA_CH6CNT(dmax)                        REG32((dmax) + 0x00000084U)    /*!< DMA channel 6 counter register */
#define DMA_CH6PADDR(dmax)                      REG32((dmax) + 0x00000088U)    /*!< DMA channel 6 peripheral base address register */
#define DMA_CH6MADDR(dmax)                      REG32((dmax) + 0x0000008CU)    /*!< DMA channel 6 memory base address register */

#define DMAMUX_RM_CH0CFG                        REG32(DMAMUX + 0x00000000U)    /*!< DMAMUX request multiplexer channel 0 configuration register */
#define DMAMUX_RM_CH1CFG                        REG32(DMAMUX + 0x00000004U)    /*!< DMAMUX request multiplexer channel 1 configuration register */
#define DMAMUX_RM_CH2CFG                        REG32(DMAMUX + 0x00000008U)    /*!< DMAMUX request multiplexer channel 2 configuration register */
#define DMAMUX_RM_CH3CFG                        REG32(DMAMUX + 0x0000000CU)    /*!< DMAMUX request multiplexer channel 3 configuration register */
#define DMAMUX_RM_CH4CFG                        REG32(DMAMUX + 0x00000010U)    /*!< DMAMUX request multiplexer channel 4 configuration register */
#define DMAMUX_RM_CH5CFG                        REG32(DMAMUX + 0x00000014U)    /*!< DMAMUX request multiplexer channel 5 configuration register */
#define DMAMUX_RM_CH6CFG                        REG32(DMAMUX + 0x00000018U)    /*!< DMAMUX request multiplexer channel 6 configuration register */
#define DMAMUX_RM_CH7CFG                        REG32(DMAMUX + 0x0000001CU)    /*!< DMAMUX request multiplexer channel 7 configuration register */
#define DMAMUX_RM_CH8CFG                        REG32(DMAMUX + 0x00000020U)    /*!< DMAMUX request multiplexer channel 8 configuration register */
#define DMAMUX_RM_CH9CFG                        REG32(DMAMUX + 0x00000024U)    /*!< DMAMUX request multiplexer channel 9 configuration register */
#define DMAMUX_RM_CH10CFG                       REG32(DMAMUX + 0x00000028U)    /*!< DMAMUX request multiplexer channel 10 configuration register */
#define DMAMUX_RM_CH11CFG                       REG32(DMAMUX + 0x0000002CU)    /*!< DMAMUX request multiplexer channel 11 configuration register */
#define DMAMUX_RM_CH12CFG                       REG32(DMAMUX + 0x00000030U)    /*!< DMAMUX request multiplexer channel 12 configuration register */
#define DMAMUX_RM_CH13CFG                       REG32(DMAMUX + 0x00000034U)    /*!< DMAMUX request multiplexer channel 13 configuration register */

#define DMAMUX_RM_INTF                          REG32(DMAMUX + 0x00000080U)    /*!< DMAMUX request multiplexer channel interrupt flag register */
#define DMAMUX_RM_INTC                          REG32(DMAMUX + 0x00000084U)    /*!< DMAMUX request multiplexer channel interrupt flag clear register */
#define DMAMUX_RG_CH0CFG                        REG32(DMAMUX + 0x00000100U)    /*!< DMAMUX generator channel 0 configuration register */
#define DMAMUX_RG_CH1CFG                        REG32(DMAMUX + 0x00000104U)    /*!< DMAMUX generator channel 1 configuration register */
#define DMAMUX_RG_CH2CFG                        REG32(DMAMUX + 0x00000108U)    /*!< DMAMUX generator channel 2 configuration register */
#define DMAMUX_RG_CH3CFG                        REG32(DMAMUX + 0x0000010CU)    /*!< DMAMUX generator channel 3 configuration register */
#define DMAMUX_RG_INTF                          REG32(DMAMUX + 0x00000140U)    /*!< DMAMUX generator channel interrupt flag register */
#define DMAMUX_RG_INTC                          REG32(DMAMUX + 0x00000144U)    /*!< DMAMUX generator channel interrupt flag clear register */

/* bits definitions */
/* DMA_INTF */
#define DMA_INTF_GIF                            BIT(0)                         /*!< global interrupt flag of channel */
#define DMA_INTF_FTFIF                          BIT(1)                         /*!< full transfer finish flag of channel */
#define DMA_INTF_HTFIF                          BIT(2)                         /*!< half transfer finish flag of channel */
#define DMA_INTF_ERRIF                          BIT(3)                         /*!< error flag of channel */

/* DMA_INTC */
#define DMA_INTC_GIFC                           BIT(0)                         /*!< clear global interrupt flag of channel */
#define DMA_INTC_FTFIFC                         BIT(1)                         /*!< clear transfer finish flag of channel */
#define DMA_INTC_HTFIFC                         BIT(2)                         /*!< clear half transfer finish flag of channel */
#define DMA_INTC_ERRIFC                         BIT(3)                         /*!< clear error flag of channel */

/* DMA_CHxCTL,x=0..6 */
#define DMA_CHXCTL_CHEN                         BIT(0)                         /*!< channel x enable */
#define DMA_CHXCTL_FTFIE                        BIT(1)                         /*!< enable bit for channel x transfer complete interrupt */
#define DMA_CHXCTL_HTFIE                        BIT(2)                         /*!< enable bit for channel x transfer half complete interrupt */
#define DMA_CHXCTL_ERRIE                        BIT(3)                         /*!< enable bit for channel x error interrupt */
#define DMA_CHXCTL_DIR                          BIT(4)                         /*!< direction of the data transfer on the channel */
#define DMA_CHXCTL_CMEN                         BIT(5)                         /*!< circulation mode */
#define DMA_CHXCTL_PNAGA                        BIT(6)                         /*!< next address generation algorithm of peripheral */
#define DMA_CHXCTL_MNAGA                        BIT(7)                         /*!< next address generation algorithm of memory */
#define DMA_CHXCTL_PWIDTH                       BITS(8,9)                      /*!< transfer data size of peripheral */
#define DMA_CHXCTL_MWIDTH                       BITS(10,11)                    /*!< transfer data size of memory */
#define DMA_CHXCTL_PRIO                         BITS(12,13)                    /*!< priority level of channelx */
#define DMA_CHXCTL_M2M                          BIT(14)                        /*!< memory to memory mode */

/* DMA_CHxCNT,x=0..6 */
#define DMA_CHXCNT_CNT                          BITS(0,15)                     /*!< transfer counter */

/* DMA_CHxPADDR,x=0..6 */
#define DMA_CHXPADDR_PADDR                      BITS(0,31)                     /*!< peripheral base address */

/* DMA_CHxMADDR,x=0..6 */
#define DMA_CHXMADDR_MADDR                      BITS(0,31)                     /*!< memory base address */

/* DMAMUX_RM_CHxCFG,x=0..13 */
#define DMAMUX_RM_CHXCFG_MUXID                  BITS(0,6)                      /*!< multiplexer input identification */
#define DMAMUX_RM_CHXCFG_SOIE                   BIT(8)                         /*!< synchronization overrun interrupt enable */
#define DMAMUX_RM_CHXCFG_EVGEN                  BIT(9)                         /*!< event generation enable */
#define DMAMUX_RM_CHXCFG_SYNCEN                 BIT(16)                        /*!< synchronization enable */
#define DMAMUX_RM_CHXCFG_SYNCP                  BITS(17,18)                    /*!< synchronization input polarity */
#define DMAMUX_RM_CHXCFG_NBR                    BITS(19,23)                    /*!< number of DMA requests to forward */
#define DMAMUX_RM_CHXCFG_SYNCID                 BITS(24,28)                    /*!< synchronization input identification */

/* DMAMUX_RM_INTF */
#define DMAMUX_RM_INTF_SOIF0                    BIT(0)                         /*!< synchronization overrun event flag of request multiplexer channel 0 */
#define DMAMUX_RM_INTF_SOIF1                    BIT(1)                         /*!< synchronization overrun event flag of request multiplexer channel 1 */
#define DMAMUX_RM_INTF_SOIF2                    BIT(2)                         /*!< synchronization overrun event flag of request multiplexer channel 2 */
#define DMAMUX_RM_INTF_SOIF3                    BIT(3)                         /*!< synchronization overrun event flag of request multiplexer channel 3 */
#define DMAMUX_RM_INTF_SOIF4                    BIT(4)                         /*!< synchronization overrun event flag of request multiplexer channel 4 */
#define DMAMUX_RM_INTF_SOIF5                    BIT(5)                         /*!< synchronization overrun event flag of request multiplexer channel 5 */
#define DMAMUX_RM_INTF_SOIF6                    BIT(6)                         /*!< synchronization overrun event flag of request multiplexer channel 6 */
#define DMAMUX_RM_INTF_SOIF7                    BIT(7)                         /*!< synchronization overrun event flag of request multiplexer channel 7 */
#define DMAMUX_RM_INTF_SOIF8                    BIT(8)                         /*!< synchronization overrun event flag of request multiplexer channel 8 */
#define DMAMUX_RM_INTF_SOIF9                    BIT(9)                         /*!< synchronization overrun event flag of request multiplexer channel 9 */
#define DMAMUX_RM_INTF_SOIF10                   BIT(10)                        /*!< synchronization overrun event flag of request multiplexer channel 10 */
#define DMAMUX_RM_INTF_SOIF11                   BIT(11)                        /*!< synchronization overrun event flag of request multiplexer channel 11 */
#define DMAMUX_RM_INTF_SOIF12                   BIT(12)                        /*!< synchronization overrun event flag of request multiplexer channel 12 */
#define DMAMUX_RM_INTF_SOIF13                   BIT(13)                        /*!< synchronization overrun event flag of request multiplexer channel 13 */

/* DMAMUX_RM_INTC */
#define DMAMUX_RM_INTF_SOIFC0                   BIT(0)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 0 */
#define DMAMUX_RM_INTF_SOIFC1                   BIT(1)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 1 */
#define DMAMUX_RM_INTF_SOIFC2                   BIT(2)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 2 */
#define DMAMUX_RM_INTF_SOIFC3                   BIT(3)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 3 */
#define DMAMUX_RM_INTF_SOIFC4                   BIT(4)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 4 */
#define DMAMUX_RM_INTF_SOIFC5                   BIT(5)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 5 */
#define DMAMUX_RM_INTF_SOIFC6                   BIT(6)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 6 */
#define DMAMUX_RM_INTF_SOIFC7                   BIT(7)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 7 */
#define DMAMUX_RM_INTF_SOIFC8                   BIT(8)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 8 */
#define DMAMUX_RM_INTF_SOIFC9                   BIT(9)                         /*!< clear bit for synchronization overrun event flag of request multiplexer channel 9 */
#define DMAMUX_RM_INTF_SOIFC10                  BIT(10)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 10 */
#define DMAMUX_RM_INTF_SOIFC11                  BIT(11)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 11 */
#define DMAMUX_RM_INTF_SOIFC12                  BIT(12)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 12 */
#define DMAMUX_RM_INTF_SOIFC13                  BIT(13)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 13 */

/* DMAMUX_RG_CHxCFG,x=0..3 */
#define DMAMUX_RG_CHXCFG_TID                    BITS(0,4)                      /*!< trigger input identification */
#define DMAMUX_RG_CHXCFG_TOIE                   BIT(8)                         /*!< trigger overrun interrupt enable */
#define DMAMUX_RG_CHXCFG_RGEN                   BIT(16)                        /*!< DMA request generator channel x enable */
#define DMAMUX_RG_CHXCFG_RGTP                   BITS(17,18)                    /*!< DMA request generator trigger polarity */
#define DMAMUX_RG_CHXCFG_NBRG                   BITS(19,23)                    /*!< number of DMA requests to be generated */

/* DMAMUX_RG_INTF */
#define DMAMUX_RG_INTF_TOIF0                    BIT(0)                         /*!< trigger overrun event flag of request generator channel 0 */
#define DMAMUX_RG_INTF_TOIF1                    BIT(1)                         /*!< trigger overrun event flag of request generator channel 1 */
#define DMAMUX_RG_INTF_TOIF2                    BIT(2)                         /*!< trigger overrun event flag of request generator channel 2 */
#define DMAMUX_RG_INTF_TOIF3                    BIT(3)                         /*!< trigger overrun event flag of request generator channel 3 */

/* DMAMUX_RG_INTC */
#define DMAMUX_RG_INTF_TOIFC0                   BIT(0)                         /*!< clear bit for trigger overrun event flag of request generator channel 0 */
#define DMAMUX_RG_INTF_TOIFC1                   BIT(1)                         /*!< clear bit for trigger overrun event flag of request generator channel 1 */
#define DMAMUX_RG_INTF_TOIFC2                   BIT(2)                         /*!< clear bit for trigger overrun event flag of request generator channel 2 */
#define DMAMUX_RG_INTF_TOIFC3                   BIT(3)                         /*!< clear bit for trigger overrun event flag of request generator channel 3 */

/* constants definitions */
/* define the DMAMUX bit position and its register index offset */
#define DMAMUX_REGIDX_BIT(regidx, bitpos)                      (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define DMAMUX_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22U) | (uint32_t)((bitpos2) << 16U) \
                                                               | (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos)))

#define DMAMUX_REG_VAL(offset)                                 (REG32(DMAMUX + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U)))
#define DMAMUX_REG_VAL2(offset)                                (REG32(DMAMUX + ((uint32_t)(offset) >> 22U)))
#define DMAMUX_REG_VAL3(offset)                                (REG32(DMAMUX + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U) + 0x4U))

#define DMAMUX_BIT_POS(val)                                    ((uint32_t)(val) & 0x1FU)
#define DMAMUX_BIT_POS2(val)                                   (((uint32_t)(val) & 0x001F0000U) >> 16U)

/* register offset */
#define DMAMUX_RM_CH0CFG_REG_OFFSET       ((uint32_t)0x00000000U)                                                         /*!< DMAMUX_RM_CH0CFG register offset */
#define DMAMUX_RM_CH1CFG_REG_OFFSET       ((uint32_t)0x00000004U)                                                         /*!< DMAMUX_RM_CH1CFG register offset */
#define DMAMUX_RM_CH2CFG_REG_OFFSET       ((uint32_t)0x00000008U)                                                         /*!< DMAMUX_RM_CH2CFG register offset */
#define DMAMUX_RM_CH3CFG_REG_OFFSET       ((uint32_t)0x0000000CU)                                                         /*!< DMAMUX_RM_CH3CFG register offset */
#define DMAMUX_RM_CH4CFG_REG_OFFSET       ((uint32_t)0x00000010U)                                                         /*!< DMAMUX_RM_CH4CFG register offset */
#define DMAMUX_RM_CH5CFG_REG_OFFSET       ((uint32_t)0x00000014U)                                                         /*!< DMAMUX_RM_CH5CFG register offset */
#define DMAMUX_RM_CH6CFG_REG_OFFSET       ((uint32_t)0x00000018U)                                                         /*!< DMAMUX_RM_CH6CFG register offset */
#define DMAMUX_RM_CH7CFG_REG_OFFSET       ((uint32_t)0x0000001CU)                                                         /*!< DMAMUX_RM_CH7CFG register offset */
#define DMAMUX_RM_CH8CFG_REG_OFFSET       ((uint32_t)0x00000020U)                                                         /*!< DMAMUX_RM_CH8CFG register offset */
#define DMAMUX_RM_CH9CFG_REG_OFFSET       ((uint32_t)0x00000024U)                                                         /*!< DMAMUX_RM_CH9CFG register offset */
#define DMAMUX_RM_CH10CFG_REG_OFFSET      ((uint32_t)0x00000028U)                                                         /*!< DMAMUX_RM_CH10CFG register offset */
#define DMAMUX_RM_CH11CFG_REG_OFFSET      ((uint32_t)0x0000002CU)                                                         /*!< DMAMUX_RM_CH11CFG register offset */
#define DMAMUX_RM_CH12CFG_REG_OFFSET      ((uint32_t)0x00000030U)                                                         /*!< DMAMUX_RM_CH12CFG register offset */
#define DMAMUX_RM_CH13CFG_REG_OFFSET      ((uint32_t)0x00000034U)                                                         /*!< DMAMUX_RM_CH13CFG register offset */

#define DMAMUX_RG_CH0CFG_REG_OFFSET       ((uint32_t)0x00000100U)                                                         /*!< DMAMUX_RG_CH0CFG register offset */
#define DMAMUX_RG_CH1CFG_REG_OFFSET       ((uint32_t)0x00000104U)                                                         /*!< DMAMUX_RG_CH1CFG register offset */
#define DMAMUX_RG_CH2CFG_REG_OFFSET       ((uint32_t)0x00000108U)                                                         /*!< DMAMUX_RG_CH2CFG register offset */
#define DMAMUX_RG_CH3CFG_REG_OFFSET       ((uint32_t)0x0000010CU)                                                         /*!< DMAMUX_RG_CH3CFG register offset */

#define DMAMUX_RM_INTF_REG_OFFSET         ((uint32_t)0x00000080U)                                                         /*!< DMAMUX_RM_INTF register offset */
#define DMAMUX_RM_INTC_REG_OFFSET         ((uint32_t)0x00000084U)                                                         /*!< DMAMUX_RM_INTC register offset */
#define DMAMUX_RG_INTF_REG_OFFSET         ((uint32_t)0x00000140U)                                                         /*!< DMAMUX_RG_INTF register offset */
#define DMAMUX_RG_INTC_REG_OFFSET         ((uint32_t)0x00000144U)                                                         /*!< DMAMUX_RG_INTC register offset */

/* DMA channel select */
typedef enum 
{
    DMA_CH0 = 0U,                         /*!< DMA Channel 0 */
    DMA_CH1,                              /*!< DMA Channel 1 */
    DMA_CH2,                              /*!< DMA Channel 2 */
    DMA_CH3,                              /*!< DMA Channel 3 */
    DMA_CH4,                              /*!< DMA Channel 4 */
    DMA_CH5,                              /*!< DMA Channel 5 */
    DMA_CH6                               /*!< DMA Channel 6 */
} dma_channel_enum;

/* DMAMUX request line multiplexer channel */
typedef enum 
{
    DMAMUX_MULTIPLEXER_CH0 = 0,           /*!< DMAMUX request multiplexer Channel0 */
    DMAMUX_MULTIPLEXER_CH1,               /*!< DMAMUX request multiplexer Channel1 */
    DMAMUX_MULTIPLEXER_CH2,               /*!< DMAMUX request multiplexer Channel2 */
    DMAMUX_MULTIPLEXER_CH3,               /*!< DMAMUX request multiplexer Channel3 */
    DMAMUX_MULTIPLEXER_CH4,               /*!< DMAMUX request multiplexer Channel4 */
    DMAMUX_MULTIPLEXER_CH5,               /*!< DMAMUX request multiplexer Channel5 */
    DMAMUX_MULTIPLEXER_CH6,               /*!< DMAMUX request multiplexer Channel6 */
    DMAMUX_MULTIPLEXER_CH7,               /*!< DMAMUX request multiplexer Channel7 */
    DMAMUX_MULTIPLEXER_CH8,               /*!< DMAMUX request multiplexer Channel8 */
    DMAMUX_MULTIPLEXER_CH9,               /*!< DMAMUX request multiplexer Channel9 */
    DMAMUX_MULTIPLEXER_CH10,              /*!< DMAMUX request multiplexer Channel10 */
    DMAMUX_MULTIPLEXER_CH11,              /*!< DMAMUX request multiplexer Channel11 */
    DMAMUX_MULTIPLEXER_CH12,              /*!< DMAMUX request multiplexer Channel12 */
    DMAMUX_MULTIPLEXER_CH13               /*!< DMAMUX request multiplexer Channel13 */
} dmamux_multiplexer_channel_enum;

/* DMAMUX request generator channel */
typedef enum {
    DMAMUX_GENCH0 = 0U,                   /*!< DMAMUX request generator Channel0 */
    DMAMUX_GENCH1,                        /*!< DMAMUX request generator Channel1 */
    DMAMUX_GENCH2,                        /*!< DMAMUX request generator Channel2 */
    DMAMUX_GENCH3                         /*!< DMAMUX request generator Channel3 */
} dmamux_generator_channel_enum;

/* DMAMUX interrupt enable or disable */
typedef enum {
    /* interrupts in CHxCFG register */
    DMAMUX_INT_MUXCH0_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH0CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH1_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH1CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH2_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH2CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH3_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH3CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH4_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH4CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH5_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH5CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH6_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH6CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH7_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH7CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 7 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH8_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH8CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 8 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH9_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH9CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 9 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH10_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH10CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 10 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH11_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH11CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 11 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH12_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH12CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 12 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH13_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH13CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 13 synchronization overrun interrupt */
    DMAMUX_INT_GENCH0_TO = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH0CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request generator channel 0 trigger overrun interrupt */
    DMAMUX_INT_GENCH1_TO = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH1CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request generator channel 1 trigger overrun interrupt */
    DMAMUX_INT_GENCH2_TO = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH2CFG_REG_OFFSET, 8U),                                         /*!< DMAMUX request generator channel 2 trigger overrun interrupt */
    DMAMUX_INT_GENCH3_TO = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH3CFG_REG_OFFSET, 8U)                                          /*!< DMAMUX request generator channel 3 trigger overrun interrupt */
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
    DMAMUX_FLAG_MUXCH12_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 12U),                                        /*!< DMAMUX request multiplexer channel 12 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH13_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 13U),                                        /*!< DMAMUX request multiplexer channel 13 synchronization overrun flag */
    DMAMUX_FLAG_GENCH0_TO = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 0U),                                          /*!< DMAMUX request generator channel 0 trigger overrun flag */
    DMAMUX_FLAG_GENCH1_TO = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 1U),                                          /*!< DMAMUX request generator channel 1 trigger overrun flag */
    DMAMUX_FLAG_GENCH2_TO = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 2U),                                          /*!< DMAMUX request generator channel 2 trigger overrun flag */
    DMAMUX_FLAG_GENCH3_TO = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 3U)                                           /*!< DMAMUX request generator channel 3 trigger overrun flag */
} dmamux_flag_enum;

/* DMAMUX interrupt flags */
typedef enum {
    /* interrupt flags in INTF register */
    DMAMUX_INT_FLAG_MUXCH0_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 0U, DMAMUX_RM_CH0CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH1_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 1U, DMAMUX_RM_CH1CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH2_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 2U, DMAMUX_RM_CH2CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH3_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 3U, DMAMUX_RM_CH3CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH4_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 4U, DMAMUX_RM_CH4CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH5_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 5U, DMAMUX_RM_CH5CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH6_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 6U, DMAMUX_RM_CH6CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH7_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 7U, DMAMUX_RM_CH7CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 7 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH8_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 8U, DMAMUX_RM_CH8CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 8 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH9_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 9U, DMAMUX_RM_CH9CFG_REG_OFFSET, 8U),    /*!< DMAMUX request multiplexer channel 9 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH10_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 10U, DMAMUX_RM_CH10CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 10 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH11_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 11U, DMAMUX_RM_CH11CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 11 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH12_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 12U, DMAMUX_RM_CH12CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 12 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH13_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 13U, DMAMUX_RM_CH13CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 13 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH0_TO = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 0U, DMAMUX_RG_CH0CFG_REG_OFFSET, 8U),    /*!< DMAMUX request generator channel 0 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH1_TO = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 1U, DMAMUX_RG_CH1CFG_REG_OFFSET, 8U),    /*!< DMAMUX request generator channel 1 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH2_TO = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 2U, DMAMUX_RG_CH2CFG_REG_OFFSET, 8U),    /*!< DMAMUX request generator channel 2 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH3_TO = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 3U, DMAMUX_RG_CH3CFG_REG_OFFSET, 8U)     /*!< DMAMUX request generator channel 3 trigger overrun interrupt flag */
} dmamux_interrupt_flag_enum;

/* DMA initialization structure */
typedef struct
{
    uint32_t periph_addr;                 /*!< peripheral base address */
    uint32_t periph_width;                /*!< transfer data size of peripheral */
    uint32_t memory_addr;                 /*!< memory base address */
    uint32_t memory_width;                /*!< transfer data size of memory */
    uint32_t number;                      /*!< channel transfer number */
    uint32_t priority;                    /*!< channel priority level */
    uint8_t periph_inc;                   /*!< peripheral increasing mode */
    uint8_t memory_inc;                   /*!< memory increasing mode */
    uint8_t direction;                    /*!< channel data transfer direction */
    uint32_t request;                     /*!< channel input identification */
} dma_parameter_struct;

/* DMAMUX request multiplexer synchronization configuration structure */
typedef struct
{
    uint32_t sync_id;                     /*!< synchronization input identification */
    uint32_t sync_polarity;               /*!< synchronization input polarity */
    uint32_t request_number;              /*!< number of DMA requests to forward */
} dmamux_sync_parameter_struct;

/* DMAMUX request generator trigger configuration structure */
typedef struct
{
    uint32_t trigger_id;                  /*!< trigger input identification */
    uint32_t trigger_polarity;            /*!< DMA request generator trigger polarity */
    uint32_t request_number;              /*!< number of DMA requests to be generated */
} dmamux_gen_parameter_struct;

/* DMA reset value */
#define DMA_CHCTL_RESET_VALUE             ((uint32_t)0x00000000U)                                                /*!< the reset value of DMA channel CHXCTL register */
#define DMA_CHCNT_RESET_VALUE             ((uint32_t)0x00000000U)                                                /*!< the reset value of DMA channel CHXCNT register */
#define DMA_CHPADDR_RESET_VALUE           ((uint32_t)0x00000000U)                                                /*!< the reset value of DMA channel CHXPADDR register */
#define DMA_CHMADDR_RESET_VALUE           ((uint32_t)0x00000000U)                                                /*!< the reset value of DMA channel CHXMADDR register */
#define DMA_CHINTF_RESET_VALUE            (DMA_INTF_GIF | DMA_INTF_FTFIF | \
                                           DMA_INTF_HTFIF | DMA_INTF_ERRIF)                                      /*!< the reset value of DMA channel DMA_INTF register */

#define DMA_FLAG_ADD(flag, shift)          ((uint32_t)((flag) << ((uint32_t)((uint32_t)(shift) * 4U))))                          /*!< DMA channel flag shift */

/* DMA channel shift bit */
#define DMA_CHCTL(dma, channel)            REG32(((dma) + 0x00000008U) + 0x14U * (uint32_t)(channel))            /*!< the address of DMA channel CHXCTL register */
#define DMA_CHCNT(dma, channel)            REG32(((dma) + 0x0000000CU) + 0x14U * (uint32_t)(channel))            /*!< the address of DMA channel CHXCNT register */
#define DMA_CHPADDR(dma, channel)          REG32(((dma) + 0x00000010U) + 0x14U * (uint32_t)(channel))            /*!< the address of DMA channel CHXPADDR register */
#define DMA_CHMADDR(dma, channel)          REG32(((dma) + 0x00000014U) + 0x14U * (uint32_t)(channel))            /*!< the address of DMA channel CHXMADDR register */

/* DMAMUX_RM_CHxCFG base address */
#define DMAMUX_RM_CHXCFG_BASE             (DMAMUX)                                                               /*!< the base address of DMAMUX channel CHxCFG register */

/* DMAMUX request multiplexer channel shift bit */
#define DMAMUX_RM_CHXCFG(channel)         REG32(DMAMUX_RM_CHXCFG_BASE + 0x4U * (uint32_t)(channel))              /*!< the address of DMAMUX channel CHxCFG register */

/* DMAMUX_RG_CHxCFG base address */
#define DMAMUX_RG_CHXCFG_BASE             (DMAMUX + 0x00000100U)                                                 /*!< the base address of DMAMUX channel request generator CHxCFG register */

/* DMAMUX request generator channel shift bit */
#define DMAMUX_RG_CHXCFG(channel)         REG32(DMAMUX_RG_CHXCFG_BASE + 0x4U * (uint32_t)(channel))              /*!< the address of DMAMUX channel request generator CHxCFG register */

/* DMA interrupt flag bits */
#define DMA_INT_FLAG_G                    DMA_INTF_GIF                                     /*!< global interrupt flag of channel */
#define DMA_INT_FLAG_FTF                  DMA_INTF_FTFIF                                   /*!< full transfer finish interrupt flag of channel */
#define DMA_INT_FLAG_HTF                  DMA_INTF_HTFIF                                   /*!< half transfer finish interrupt flag of channel */
#define DMA_INT_FLAG_ERR                  DMA_INTF_ERRIF                                   /*!< error interrupt flag of channel */

/* DMA flag bits */
#define DMA_FLAG_G                        DMA_INTF_GIF                                     /*!< global interrupt flag of channel */
#define DMA_FLAG_FTF                      DMA_INTF_FTFIF                                   /*!< full transfer finish flag of channel */
#define DMA_FLAG_HTF                      DMA_INTF_HTFIF                                   /*!< half transfer finish flag of channel */
#define DMA_FLAG_ERR                      DMA_INTF_ERRIF                                   /*!< error flag of channel */

/* DMA interrupt enable bits */
#define DMA_INT_FTF                       DMA_CHXCTL_FTFIE                                 /*!< enable bit for channel full transfer finish interrupt */
#define DMA_INT_HTF                       DMA_CHXCTL_HTFIE                                 /*!< enable bit for channel half transfer finish interrupt */
#define DMA_INT_ERR                       DMA_CHXCTL_ERRIE                                 /*!< enable bit for channel error interrupt */

/* DMA transfer direction */
#define DMA_PERIPHERAL_TO_MEMORY          ((uint32_t)0x00000000U)                          /*!< read from peripheral and write to memory */
#define DMA_MEMORY_TO_PERIPHERAL          ((uint32_t)0x00000001U)                          /*!< read from memory and write to peripheral */

/* DMA peripheral increasing mode */
#define DMA_PERIPH_INCREASE_DISABLE       ((uint32_t)0x00000000U)                          /*!< next address of peripheral is fixed address mode */
#define DMA_PERIPH_INCREASE_ENABLE        ((uint32_t)0x00000001U)                          /*!< next address of peripheral is increasing address mode */

/* DMA memory increasing mode */
#define DMA_MEMORY_INCREASE_DISABLE       ((uint32_t)0x00000000U)                          /*!< next address of memory is fixed address mode */
#define DMA_MEMORY_INCREASE_ENABLE        ((uint32_t)0x00000001U)                          /*!< next address of memory is increasing address mode */

/* DMA transfer data size of peripheral */
#define CHCTL_PWIDTH(regval)              (BITS(8,9) & ((uint32_t)(regval) << 8U))         /*!< transfer data size of peripheral */
#define DMA_PERIPHERAL_WIDTH_8BIT         CHCTL_PWIDTH(0U)                                 /*!< transfer data size of peripheral is 8-bit */
#define DMA_PERIPHERAL_WIDTH_16BIT        CHCTL_PWIDTH(1U)                                 /*!< transfer data size of peripheral is 16-bit */
#define DMA_PERIPHERAL_WIDTH_32BIT        CHCTL_PWIDTH(2U)                                 /*!< transfer data size of peripheral is 32-bit */

/* DMA transfer data size of memory */
#define CHCTL_MWIDTH(regval)              (BITS(10,11) & ((uint32_t)(regval) << 10U))      /*!< transfer data size of memory */
#define DMA_MEMORY_WIDTH_8BIT             CHCTL_MWIDTH(0U)                                 /*!< transfer data size of memory is 8-bit */
#define DMA_MEMORY_WIDTH_16BIT            CHCTL_MWIDTH(1U)                                 /*!< transfer data size of memory is 16-bit */
#define DMA_MEMORY_WIDTH_32BIT            CHCTL_MWIDTH(2U)                                 /*!< transfer data size of memory is 32-bit */

/* DMA channel priority level */
#define CHCTL_PRIO(regval)                (BITS(12,13) & ((uint32_t)(regval) << 12U))      /*!< DMA channel priority level */
#define DMA_PRIORITY_LOW                  CHCTL_PRIO(0U)                                   /*!< low priority */
#define DMA_PRIORITY_MEDIUM               CHCTL_PRIO(1U)                                   /*!< medium priority */
#define DMA_PRIORITY_HIGH                 CHCTL_PRIO(2U)                                   /*!< high priority */
#define DMA_PRIORITY_ULTRA_HIGH           CHCTL_PRIO(3U)                                   /*!< ultra high priority */

/* DMA transfer counter */
#define DMA_CHANNEL_CNT_MASK              DMA_CHXCNT_CNT                                   /*!< transfer counter mask */

/* DMAMUX request multiplexer channel input identification */
#define RM_CHXCFG_MUXID(regval)            (BITS(0,7) & ((uint32_t)(regval) << 0U))        /*!< multiplexer input identification */
#define DMA_REQUEST_M2M                    RM_CHXCFG_MUXID(0U)                             /*!< memory to memory transfer */
#define DMA_REQUEST_GENERATOR0             RM_CHXCFG_MUXID(1U)                             /*!< DMAMUX request generator 0 */
#define DMA_REQUEST_GENERATOR1             RM_CHXCFG_MUXID(2U)                             /*!< DMAMUX request generator 1 */
#define DMA_REQUEST_GENERATOR2             RM_CHXCFG_MUXID(3U)                             /*!< DMAMUX request generator 2 */
#define DMA_REQUEST_GENERATOR3             RM_CHXCFG_MUXID(4U)                             /*!< DMAMUX request generator 3 */
#define DMA_REQUEST_ADC0                   RM_CHXCFG_MUXID(5U)                             /*!< DMAMUX ADC0 request */
#define DMA_REQUEST_DAC0_CH0               RM_CHXCFG_MUXID(6U)                             /*!< DMAMUX DAC0 CH0 request */
#define DMA_REQUEST_DAC0_CH1               RM_CHXCFG_MUXID(7U)                             /*!< DMAMUX DAC0 CH1 request */
#define DMA_REQUEST_TIMER5_UP              RM_CHXCFG_MUXID(8U)                             /*!< DMAMUX TIMER5 UP request */
#define DMA_REQUEST_TIMER6_UP              RM_CHXCFG_MUXID(9U)                             /*!< DMAMUX TIMER6 UP request */
#define DMA_REQUEST_SPI0_RX                RM_CHXCFG_MUXID(10U)                            /*!< DMAMUX SPI0 RX request */
#define DMA_REQUEST_SPI0_TX                RM_CHXCFG_MUXID(11U)                            /*!< DMAMUX SPI0 TX request */
#define DMA_REQUEST_SPI1_RX                RM_CHXCFG_MUXID(12U)                            /*!< DMAMUX SPI1 RX request */
#define DMA_REQUEST_SPI1_TX                RM_CHXCFG_MUXID(13U)                            /*!< DMAMUX SPI1 TX request */
#define DMA_REQUEST_SPI2_RX                RM_CHXCFG_MUXID(14U)                            /*!< DMAMUX SPI2 RX request */
#define DMA_REQUEST_SPI2_TX                RM_CHXCFG_MUXID(15U)                            /*!< DMAMUX SPI2 TX request */
#define DMA_REQUEST_I2C0_RX                RM_CHXCFG_MUXID(16U)                            /*!< DMAMUX I2C0 RX request */
#define DMA_REQUEST_I2C0_TX                RM_CHXCFG_MUXID(17U)                            /*!< DMAMUX I2C0 TX request */
#define DMA_REQUEST_I2C1_RX                RM_CHXCFG_MUXID(18U)                            /*!< DMAMUX I2C1 RX request */
#define DMA_REQUEST_I2C1_TX                RM_CHXCFG_MUXID(19U)                            /*!< DMAMUX I2C1 TX request */
#define DMA_REQUEST_I2C2_RX                RM_CHXCFG_MUXID(20U)                            /*!< DMAMUX I2C2 RX request */
#define DMA_REQUEST_I2C2_TX                RM_CHXCFG_MUXID(21U)                            /*!< DMAMUX I2C2 TX request */
#define DMA_REQUEST_I2C3_RX                RM_CHXCFG_MUXID(22U)                            /*!< DMAMUX I2C3 RX request */
#define DMA_REQUEST_I2C3_TX                RM_CHXCFG_MUXID(23U)                            /*!< DMAMUX I2C3 TX request */
#define DMA_REQUEST_USART0_RX              RM_CHXCFG_MUXID(24U)                            /*!< DMAMUX USART0 RX request */
#define DMA_REQUEST_USART0_TX              RM_CHXCFG_MUXID(25U)                            /*!< DMAMUX USART0 TX request */
#define DMA_REQUEST_USART1_RX              RM_CHXCFG_MUXID(26U)                            /*!< DMAMUX USART1 RX request */
#define DMA_REQUEST_USART1_TX              RM_CHXCFG_MUXID(27U)                            /*!< DMAMUX USART1 TX request */
#define DMA_REQUEST_USART2_RX              RM_CHXCFG_MUXID(28U)                            /*!< DMAMUX USART2 RX request */
#define DMA_REQUEST_USART2_TX              RM_CHXCFG_MUXID(29U)                            /*!< DMAMUX USART2 TX request */
#define DMA_REQUEST_UART3_RX               RM_CHXCFG_MUXID(30U)                            /*!< DMAMUX UART3 RX request */
#define DMA_REQUEST_UART3_TX               RM_CHXCFG_MUXID(31U)                            /*!< DMAMUX UART3 TX request */
#define DMA_REQUEST_UART4_RX               RM_CHXCFG_MUXID(32U)                            /*!< DMAMUX UART4 RX request */
#define DMA_REQUEST_UART4_TX               RM_CHXCFG_MUXID(33U)                            /*!< DMAMUX UART4 TX request */
#define DMA_REQUEST_ADC1                   RM_CHXCFG_MUXID(34U)                            /*!< DMAMUX ADC1 request */
#define DMA_REQUEST_ADC2                   RM_CHXCFG_MUXID(35U)                            /*!< DMAMUX ADC2 request */
#define DMA_REQUEST_ADC3                   RM_CHXCFG_MUXID(36U)                            /*!< DMAMUX ADC3 request */
#define DMA_REQUEST_QSPI                   RM_CHXCFG_MUXID(37U)                            /*!< DMAMUX QSPI request */
#define DMA_REQUEST_DAC1_CH0               RM_CHXCFG_MUXID(38U)                            /*!< DMAMUX DAC1 CH0 request */
#define DMA_REQUEST_DAC1_CH1               RM_CHXCFG_MUXID(39U)                            /*!< DMAMUX DAC1 CH1 request */
#define DMA_REQUEST_TIMER0_CH0             RM_CHXCFG_MUXID(40U)                            /*!< DMAMUX TIMER0 CH0 request */
#define DMA_REQUEST_TIMER0_CH1             RM_CHXCFG_MUXID(41U)                            /*!< DMAMUX TIMER0 CH1 request */
#define DMA_REQUEST_TIMER0_CH2             RM_CHXCFG_MUXID(42U)                            /*!< DMAMUX TIMER0 CH2 request */
#define DMA_REQUEST_TIMER0_CH3             RM_CHXCFG_MUXID(43U)                            /*!< DMAMUX TIMER0 CH3 request */
#define DMA_REQUEST_TIMER0_CH0N            RM_CHXCFG_MUXID(44U)                            /*!< DMAMUX TIMER0 CH0N request */
#define DMA_REQUEST_TIMER0_CH1N            RM_CHXCFG_MUXID(45U)                            /*!< DMAMUX TIMER0 CH1N request */
#define DMA_REQUEST_TIMER0_CH2N            RM_CHXCFG_MUXID(46U)                            /*!< DMAMUX TIMER0 CH2N request */
#define DMA_REQUEST_TIMER0_CH3N            RM_CHXCFG_MUXID(47U)                            /*!< DMAMUX TIMER0 CH3N request */
#define DMA_REQUEST_TIMER0_UP              RM_CHXCFG_MUXID(48U)                            /*!< DMAMUX TIMER0 UP request */
#define DMA_REQUEST_TIMER0_TRIG            RM_CHXCFG_MUXID(49U)                            /*!< DMAMUX TIMER0 TRIG request */
#define DMA_REQUEST_TIMER0_COM             RM_CHXCFG_MUXID(50U)                            /*!< DMAMUX TIMER0 COM request */
#define DMA_REQUEST_TIMER7_CH0             RM_CHXCFG_MUXID(51U)                            /*!< DMAMUX TIMER7 CH0 request */
#define DMA_REQUEST_TIMER7_CH1             RM_CHXCFG_MUXID(52U)                            /*!< DMAMUX TIMER7 CH1 request */
#define DMA_REQUEST_TIMER7_CH2             RM_CHXCFG_MUXID(53U)                            /*!< DMAMUX TIMER7 CH2 request */
#define DMA_REQUEST_TIMER7_CH3             RM_CHXCFG_MUXID(54U)                            /*!< DMAMUX TIMER7 CH3 request */
#define DMA_REQUEST_TIMER7_CH0N            RM_CHXCFG_MUXID(55U)                            /*!< DMAMUX TIMER7 CH0N request */
#define DMA_REQUEST_TIMER7_CH1N            RM_CHXCFG_MUXID(56U)                            /*!< DMAMUX TIMER7 CH1N request */
#define DMA_REQUEST_TIMER7_CH2N            RM_CHXCFG_MUXID(57U)                            /*!< DMAMUX TIMER7 CH2N request */
#define DMA_REQUEST_TIMER7_CH3N            RM_CHXCFG_MUXID(58U)                            /*!< DMAMUX TIMER7 CH3N request */
#define DMA_REQUEST_TIMER7_UP              RM_CHXCFG_MUXID(59U)                            /*!< DMAMUX TIMER7 UP request */
#define DMA_REQUEST_TIMER7_TRIG            RM_CHXCFG_MUXID(60U)                            /*!< DMAMUX TIMER7 TRIG request */
#define DMA_REQUEST_TIMER7_COM             RM_CHXCFG_MUXID(61U)                            /*!< DMAMUX TIMER7 COM request */
#define DMA_REQUEST_TIMER1_CH0             RM_CHXCFG_MUXID(62U)                            /*!< DMAMUX TIMER1 CH0 request */
#define DMA_REQUEST_TIMER1_CH1             RM_CHXCFG_MUXID(63U)                            /*!< DMAMUX TIMER1 CH1 request */
#define DMA_REQUEST_TIMER1_CH2             RM_CHXCFG_MUXID(64U)                            /*!< DMAMUX TIMER1 CH2 request */
#define DMA_REQUEST_TIMER1_CH3             RM_CHXCFG_MUXID(65U)                            /*!< DMAMUX TIMER1 CH3 request */
#define DMA_REQUEST_TIMER1_UP              RM_CHXCFG_MUXID(66U)                            /*!< DMAMUX TIMER1 UP request */
#define DMA_REQUEST_TIMER1_TRIG            RM_CHXCFG_MUXID(67U)                            /*!< DMAMUX TIMER1 TRIG request */
#define DMA_REQUEST_TIMER2_CH0             RM_CHXCFG_MUXID(68U)                            /*!< DMAMUX TIMER2 CH0 request */
#define DMA_REQUEST_TIMER2_CH1             RM_CHXCFG_MUXID(69U)                            /*!< DMAMUX TIMER2 CH1 request */
#define DMA_REQUEST_TIMER2_CH2             RM_CHXCFG_MUXID(70U)                            /*!< DMAMUX TIMER2 CH2 request */
#define DMA_REQUEST_TIMER2_CH3             RM_CHXCFG_MUXID(71U)                            /*!< DMAMUX TIMER2 CH3 request */
#define DMA_REQUEST_TIMER2_UP              RM_CHXCFG_MUXID(72U)                            /*!< DMAMUX TIMER2 UP request */
#define DMA_REQUEST_TIMER2_TRIG            RM_CHXCFG_MUXID(73U)                            /*!< DMAMUX TIMER2 TRIG request */
#define DMA_REQUEST_TIMER3_CH0             RM_CHXCFG_MUXID(74U)                            /*!< DMAMUX TIMER3 CH0 request */
#define DMA_REQUEST_TIMER3_CH1             RM_CHXCFG_MUXID(75U)                            /*!< DMAMUX TIMER3 CH1 request */
#define DMA_REQUEST_TIMER3_CH2             RM_CHXCFG_MUXID(76U)                            /*!< DMAMUX TIMER3 CH2 request */
#define DMA_REQUEST_TIMER3_CH3             RM_CHXCFG_MUXID(77U)                            /*!< DMAMUX TIMER3 CH3 request */
#define DMA_REQUEST_TIMER3_UP              RM_CHXCFG_MUXID(78U)                            /*!< DMAMUX TIMER3 UP request */
#define DMA_REQUEST_TIMER3_TRIG            RM_CHXCFG_MUXID(79U)                            /*!< DMAMUX TIMER3 TRIG request */
#define DMA_REQUEST_TIMER4_CH0             RM_CHXCFG_MUXID(80U)                            /*!< DMAMUX TIMER4 CH0 request */
#define DMA_REQUEST_TIMER4_CH1             RM_CHXCFG_MUXID(81U)                            /*!< DMAMUX TIMER4 CH1 request */
#define DMA_REQUEST_TIMER4_CH2             RM_CHXCFG_MUXID(82U)                            /*!< DMAMUX TIMER4 CH2 request */
#define DMA_REQUEST_TIMER4_CH3             RM_CHXCFG_MUXID(83U)                            /*!< DMAMUX TIMER4 CH3 request */
#define DMA_REQUEST_TIMER4_UP              RM_CHXCFG_MUXID(84U)                            /*!< DMAMUX TIMER4 UP request */
#define DMA_REQUEST_TIMER4_TRIG            RM_CHXCFG_MUXID(85U)                            /*!< DMAMUX TIMER4 TRIG request */
#define DMA_REQUEST_TIMER14_CH0            RM_CHXCFG_MUXID(86U)                            /*!< DMAMUX TIMER14 CH0 request */
#define DMA_REQUEST_TIMER14_CH1            RM_CHXCFG_MUXID(87U)                            /*!< DMAMUX TIMER14 CH1 request */
#define DMA_REQUEST_TIMER14_CH0N           RM_CHXCFG_MUXID(88U)                            /*!< DMAMUX TIMER14 CH0N request */
#define DMA_REQUEST_TIMER14_UP             RM_CHXCFG_MUXID(89U)                            /*!< DMAMUX TIMER14 UP request */
#define DMA_REQUEST_TIMER14_TRIG           RM_CHXCFG_MUXID(90U)                            /*!< DMAMUX TIMER14 TRIG request */
#define DMA_REQUEST_TIMER14_COM            RM_CHXCFG_MUXID(91U)                            /*!< DMAMUX TIMER14 COM request */
#define DMA_REQUEST_TIMER15_CH0            RM_CHXCFG_MUXID(92U)                            /*!< DMAMUX TIMER15 CH0 request */
#define DMA_REQUEST_TIMER15_CH0N           RM_CHXCFG_MUXID(93U)                            /*!< DMAMUX TIMER15 CH0N request */
#define DMA_REQUEST_TIMER15_UP             RM_CHXCFG_MUXID(94U)                            /*!< DMAMUX TIMER15 UP request */
#define DMA_REQUEST_TIMER16_CH0            RM_CHXCFG_MUXID(95U)                            /*!< DMAMUX TIMER16 CH0 request */
#define DMA_REQUEST_TIMER16_CH0N           RM_CHXCFG_MUXID(96U)                            /*!< DMAMUX TIMER16 CH0N request */
#define DMA_REQUEST_TIMER16_UP             RM_CHXCFG_MUXID(97U)                            /*!< DMAMUX TIMER16 UP request */
#define DMA_REQUEST_TIMER19_CH0            RM_CHXCFG_MUXID(98U)                            /*!< DMAMUX TIMER19 CH0 request */
#define DMA_REQUEST_TIMER19_CH1            RM_CHXCFG_MUXID(99U)                            /*!< DMAMUX TIMER19 CH1 request */
#define DMA_REQUEST_TIMER19_CH2            RM_CHXCFG_MUXID(100U)                           /*!< DMAMUX TIMER19 CH2 request */
#define DMA_REQUEST_TIMER19_CH3            RM_CHXCFG_MUXID(101U)                           /*!< DMAMUX TIMER19 CH3 request */
#define DMA_REQUEST_TIMER19_CH0N           RM_CHXCFG_MUXID(102U)                           /*!< DMAMUX TIMER19 CH0N request */
#define DMA_REQUEST_TIMER19_CH1N           RM_CHXCFG_MUXID(103U)                           /*!< DMAMUX TIMER19 CH1N request */
#define DMA_REQUEST_TIMER19_CH2N           RM_CHXCFG_MUXID(104U)                           /*!< DMAMUX TIMER19 CH2N request */
#define DMA_REQUEST_TIMER19_CH3N           RM_CHXCFG_MUXID(105U)                           /*!< DMAMUX TIMER19 CH3N request */
#define DMA_REQUEST_TIMER19_UP             RM_CHXCFG_MUXID(106U)                           /*!< DMAMUX TIMER19 UP request */
#define DMA_REQUEST_TIMER19_TRIG           RM_CHXCFG_MUXID(107U)                           /*!< DMAMUX TIMER19 TRIG request */
#define DMA_REQUEST_TIMER19_COM            RM_CHXCFG_MUXID(108U)                           /*!< DMAMUX TIMER19 COM request */
#define DMA_REQUEST_CAU_IN                 RM_CHXCFG_MUXID(109U)                           /*!< DMAMUX CAU_IN request */
#define DMA_REQUEST_CAU_OUT                RM_CHXCFG_MUXID(110U)                           /*!< DMAMUX CAU_OUT request */
#define DMA_REQUEST_HRTIMER_MASTER         RM_CHXCFG_MUXID(111U)                           /*!< DMAMUX HRTIMER MASTER request */
#define DMA_REQUEST_HRTIMER_TIMER0         RM_CHXCFG_MUXID(112U)                           /*!< DMAMUX HRTIMER TIMERA request */
#define DMA_REQUEST_HRTIMER_TIMER1         RM_CHXCFG_MUXID(113U)                           /*!< DMAMUX HRTIMER TIMERB request */
#define DMA_REQUEST_HRTIMER_TIMER2         RM_CHXCFG_MUXID(114U)                           /*!< DMAMUX HRTIMER TIMERC request */
#define DMA_REQUEST_HRTIMER_TIMER3         RM_CHXCFG_MUXID(115U)                           /*!< DMAMUX HRTIMER TIMERD request */
#define DMA_REQUEST_HRTIMER_TIMER4         RM_CHXCFG_MUXID(116U)                           /*!< DMAMUX HRTIMER TIMERA request */
#define DMA_REQUEST_HRTIMER_TIMER5         RM_CHXCFG_MUXID(117U)                           /*!< DMAMUX HRTIMER TIMERB request */
#define DMA_REQUEST_HRTIMER_TIMER6         RM_CHXCFG_MUXID(118U)                           /*!< DMAMUX HRTIMER TIMERC request */
#define DMA_REQUEST_HRTIMER_TIMER7         RM_CHXCFG_MUXID(119U)                           /*!< DMAMUX HRTIMER TIMERD request */
#define DMA_REQUEST_DAC2_CH0               RM_CHXCFG_MUXID(120U)                           /*!< DMAMUX DAC2 CH0 request */
#define DMA_REQUEST_DAC2_CH1               RM_CHXCFG_MUXID(121U)                           /*!< DMAMUX DAC2 CH1 request */
#define DMA_REQUEST_DAC3_CH0               RM_CHXCFG_MUXID(122U)                           /*!< DMAMUX DAC3 CH0 request */
#define DMA_REQUEST_DAC3_CH1               RM_CHXCFG_MUXID(123U)                           /*!< DMAMUX DAC3 CH1 request */
#define DMA_REQUEST_HPDF_FLT0              RM_CHXCFG_MUXID(124U)                           /*!< DMAMUX HPDF FLT0 request */
#define DMA_REQUEST_HPDF_FLT1              RM_CHXCFG_MUXID(125U)                           /*!< DMAMUX HPDF FLT1 request */
#define DMA_REQUEST_HPDF_FLT2              RM_CHXCFG_MUXID(126U)                           /*!< DMAMUX HPDF FLT2 request */
#define DMA_REQUEST_HPDF_FLT3              RM_CHXCFG_MUXID(127U)                           /*!< DMAMUX HPDF FLT3 request */
#define DMA_REQUEST_FAC_READ               RM_CHXCFG_MUXID(128U)                           /*!< DMAMUX FAC READ request */
#define DMA_REQUEST_FAC_WRITE              RM_CHXCFG_MUXID(129U)                           /*!< DMAMUX FAC WRITE request */
#define DMA_REQUEST_TMU_INPUT              RM_CHXCFG_MUXID(130U)                           /*!< DMAMUX TMU INPUT request */
#define DMA_REQUEST_TMU_OUTPUT             RM_CHXCFG_MUXID(131U)                           /*!< DMAMUX TMU OUTPUT request */
#define DMA_REQUEST_CAN0                   RM_CHXCFG_MUXID(132U)                           /*!< DMAMUX CAN0 request */
#define DMA_REQUEST_CAN1                   RM_CHXCFG_MUXID(133U)                           /*!< DMAMUX CAN1 request */
#define DMA_REQUEST_CAN2                   RM_CHXCFG_MUXID(134U)                           /*!< DMAMUX CAN2 request */

/* DMAMUX request generator trigger input identification */
#define RG_CHXCFG_TID(regval)              (BITS(0,4) & ((uint32_t)(regval) << 0U))        /*!< trigger input identification */
#define DMAMUX_TRIGGER_EXTI0               RG_CHXCFG_TID(0U)                               /*!< trigger input is EXTI0 */
#define DMAMUX_TRIGGER_EXTI1               RG_CHXCFG_TID(1U)                               /*!< trigger input is EXTI1 */
#define DMAMUX_TRIGGER_EXTI2               RG_CHXCFG_TID(2U)                               /*!< trigger input is EXTI2 */
#define DMAMUX_TRIGGER_EXTI3               RG_CHXCFG_TID(3U)                               /*!< trigger input is EXTI3 */
#define DMAMUX_TRIGGER_EXTI4               RG_CHXCFG_TID(4U)                               /*!< trigger input is EXTI4 */
#define DMAMUX_TRIGGER_EXTI5               RG_CHXCFG_TID(5U)                               /*!< trigger input is EXTI5 */
#define DMAMUX_TRIGGER_EXTI6               RG_CHXCFG_TID(6U)                               /*!< trigger input is EXTI6 */
#define DMAMUX_TRIGGER_EXTI7               RG_CHXCFG_TID(7U)                               /*!< trigger input is EXTI7 */
#define DMAMUX_TRIGGER_EXTI8               RG_CHXCFG_TID(8U)                               /*!< trigger input is EXTI8 */
#define DMAMUX_TRIGGER_EXTI9               RG_CHXCFG_TID(9U)                               /*!< trigger input is EXTI9 */
#define DMAMUX_TRIGGER_EXTI10              RG_CHXCFG_TID(10U)                              /*!< trigger input is EXTI10 */
#define DMAMUX_TRIGGER_EXTI11              RG_CHXCFG_TID(11U)                              /*!< trigger input is EXTI11 */
#define DMAMUX_TRIGGER_EXTI12              RG_CHXCFG_TID(12U)                              /*!< trigger input is EXTI12 */
#define DMAMUX_TRIGGER_EXTI13              RG_CHXCFG_TID(13U)                              /*!< trigger input is EXTI13 */
#define DMAMUX_TRIGGER_EXTI14              RG_CHXCFG_TID(14U)                              /*!< trigger input is EXTI14 */
#define DMAMUX_TRIGGER_EXTI15              RG_CHXCFG_TID(15U)                              /*!< trigger input is EXTI15 */
#define DMAMUX_TRIGGER_EVTX_OUT0           RG_CHXCFG_TID(16U)                              /*!< trigger input is Evtx_out0 */
#define DMAMUX_TRIGGER_EVTX_OUT1           RG_CHXCFG_TID(17U)                              /*!< trigger input is Evtx_out1 */
#define DMAMUX_TRIGGER_EVTX_OUT2           RG_CHXCFG_TID(18U)                              /*!< trigger input is Evtx_out2 */
#define DMAMUX_TRIGGER_EVTX_OUT3           RG_CHXCFG_TID(19U)                              /*!< trigger input is Evtx_out3 */
#define DMAMUX_TRIGGER_LPTIMER_OUT         RG_CHXCFG_TID(20U)                              /*!< trigger input is LPTIMER OUT */

/* DMAMUX request generator trigger polarity */
#define RM_CHXCFG_RGTP(regval)              (BITS(17,18) & ((uint32_t)(regval) << 17U))    /*!< DMA request generator trigger polarity */
#define DMAMUX_GEN_NO_EVENT                 RM_CHXCFG_RGTP(0U)                             /*!< no event detection */
#define DMAMUX_GEN_RISING                   RM_CHXCFG_RGTP(1U)                             /*!< rising edge */
#define DMAMUX_GEN_FALLING                  RM_CHXCFG_RGTP(2U)                             /*!< falling edge */
#define DMAMUX_GEN_RISING_FALLING           RM_CHXCFG_RGTP(3U)                             /*!< rising and falling edges */

/* number of DMA requests to be generated */
#define RG_CHXCFG_NBRG(regval)              (BITS(19,23) & ((uint32_t)(regval) << 19U))    /*!< number of DMA requests to be generated */

/* DMAMUX request multiplexer channel synchronization input identification */
#define RM_CHXCFG_SYNCID(regval)            (BITS(24,28) & ((uint32_t)(regval) << 24U))    /*!< synchronization input identification */
#define DMAMUX_SYNC_EXTI0                   RM_CHXCFG_SYNCID(0U)                           /*!< synchronization input is EXTI0 */
#define DMAMUX_SYNC_EXTI1                   RM_CHXCFG_SYNCID(1U)                           /*!< synchronization input is EXTI1 */
#define DMAMUX_SYNC_EXTI2                   RM_CHXCFG_SYNCID(2U)                           /*!< synchronization input is EXTI2 */
#define DMAMUX_SYNC_EXTI3                   RM_CHXCFG_SYNCID(3U)                           /*!< synchronization input is EXTI3 */
#define DMAMUX_SYNC_EXTI4                   RM_CHXCFG_SYNCID(4U)                           /*!< synchronization input is EXTI4 */
#define DMAMUX_SYNC_EXTI5                   RM_CHXCFG_SYNCID(5U)                           /*!< synchronization input is EXTI5 */
#define DMAMUX_SYNC_EXTI6                   RM_CHXCFG_SYNCID(6U)                           /*!< synchronization input is EXTI6 */
#define DMAMUX_SYNC_EXTI7                   RM_CHXCFG_SYNCID(7U)                           /*!< synchronization input is EXTI7 */
#define DMAMUX_SYNC_EXTI8                   RM_CHXCFG_SYNCID(8U)                           /*!< synchronization input is EXTI8 */
#define DMAMUX_SYNC_EXTI9                   RM_CHXCFG_SYNCID(9U)                           /*!< synchronization input is EXTI9 */
#define DMAMUX_SYNC_EXTI10                  RM_CHXCFG_SYNCID(10U)                          /*!< synchronization input is EXTI10 */
#define DMAMUX_SYNC_EXTI11                  RM_CHXCFG_SYNCID(11U)                          /*!< synchronization input is EXTI11 */
#define DMAMUX_SYNC_EXTI12                  RM_CHXCFG_SYNCID(12U)                          /*!< synchronization input is EXTI12 */
#define DMAMUX_SYNC_EXTI13                  RM_CHXCFG_SYNCID(13U)                          /*!< synchronization input is EXTI13 */
#define DMAMUX_SYNC_EXTI14                  RM_CHXCFG_SYNCID(14U)                          /*!< synchronization input is EXTI14 */
#define DMAMUX_SYNC_EXTI15                  RM_CHXCFG_SYNCID(15U)                          /*!< synchronization input is EXTI15 */
#define DMAMUX_SYNC_EVTX_OUT0               RM_CHXCFG_SYNCID(16U)                          /*!< synchronization input is Evtx_out0 */
#define DMAMUX_SYNC_EVTX_OUT1               RM_CHXCFG_SYNCID(17U)                          /*!< synchronization input is Evtx_out1 */
#define DMAMUX_SYNC_EVTX_OUT2               RM_CHXCFG_SYNCID(18U)                          /*!< synchronization input is Evtx_out2 */
#define DMAMUX_SYNC_EVTX_OUT3               RM_CHXCFG_SYNCID(19U)                          /*!< synchronization input is Evtx_out3 */
#define DMAMUX_SYNC_LPTIMER_OUT             RM_CHXCFG_SYNCID(20U)                          /*!< synchronization input is LPTIMER OUT */

/* DMAMUX request multiplexer synchronization input polarity */
#define RM_CHXCFG_SYNCP(regval)             (BITS(17,18) & ((uint32_t)(regval) << 17U))    /*!< synchronization input polarity */
#define DMAMUX_SYNC_NO_EVENT                RM_CHXCFG_SYNCP(0U)                            /*!< no event detection */
#define DMAMUX_SYNC_RISING                  RM_CHXCFG_SYNCP(1U)                            /*!< rising edge */
#define DMAMUX_SYNC_FALLING                 RM_CHXCFG_SYNCP(2U)                            /*!< falling edge */
#define DMAMUX_SYNC_RISING_FALLING          RM_CHXCFG_SYNCP(3U)                            /*!< rising and falling edges */

/* number of DMA requests to forward */
#define RM_CHXCFG_NBR(regval)            (BITS(19,23) & ((uint32_t)(regval) << 19U))       /*!< number of DMA requests to forward */

/* function declarations */
/* DMA functions */
/* DMA initialization functions */
/* deinitialize DMA channel registers */
void dma_deinit(uint32_t dma_periph, dma_channel_enum channelx);
/* initialize the parameters of DMA structure with the default values */
void dma_struct_para_init(dma_parameter_struct* init_struct);
/* initialize DMA channel */
void dma_init(uint32_t dma_periph, dma_channel_enum channelx, dma_parameter_struct* init_struct);
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
/* configure DMA memory base address */
void dma_memory_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address);
/* configure the number of remaining data to be transferred by the DMA */
void dma_transfer_number_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t number);
/* get the number of remaining data to be transferred by the DMA */
uint32_t dma_transfer_number_get(uint32_t dma_periph, dma_channel_enum channelx);
/* configure priority level of DMA channel */
void dma_priority_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t priority);
/* configure transfer data size of memory */
void dma_memory_width_config (uint32_t dma_periph, dma_channel_enum channelx, uint32_t mwidth);
/* configure transfer data size of peripheral */
void dma_periph_width_config (uint32_t dma_periph, dma_channel_enum channelx, uint32_t pwidth);
/* enable next address increasement algorithm of memory */
void dma_memory_increase_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable next address increasement algorithm of memory */
void dma_memory_increase_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable next address increasement algorithm of peripheral */
void dma_periph_increase_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable next address increasement algorithm of peripheral */
void dma_periph_increase_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* configure the direction of data transfer on the channel */
void dma_transfer_direction_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t direction);

/* DMA interrupt and flag functions */
/* check DMA flag is set or not */
FlagStatus dma_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* clear a DMA channel flag */
void dma_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* enable DMA interrupt */
void dma_interrupt_enable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t source);
/* disable DMA interrupt */
void dma_interrupt_disable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t source);
/* check DMA flag and interrupt enable bit is set or not */
FlagStatus dma_interrupt_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t int_flag);
/* clear a DMA channel interrupt flag */
void dma_interrupt_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t int_flag);

/* DMAMUX functions */
/* DMAMUX request multiplexer functions */
/* initialize the parameters of DMAMUX synchronization mode structure with the default values */
void dmamux_sync_struct_para_init(dmamux_sync_parameter_struct *init_struct);
/* initialize DMAMUX request multiplexer channel synchronization mode */
void dmamux_synchronization_init(dmamux_multiplexer_channel_enum channelx, dmamux_sync_parameter_struct *init_struct);
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
void dmamux_request_generator_init(dmamux_generator_channel_enum channelx, dmamux_gen_parameter_struct *init_struct);
/* enable DMAMUX request generator channel */
void dmamux_request_generator_channel_enable(dmamux_generator_channel_enum channelx);
/* disable DMAMUX request generator channel */
void dmamux_request_generator_channel_disable(dmamux_generator_channel_enum channelx);

/* DMAMUX configuration functions */
/* configure synchronization input polarity */
void dmamux_synchronization_polarity_config(dmamux_multiplexer_channel_enum channelx, uint32_t polarity);
/* configure number of DMA requests to forward */
void dmamux_request_forward_number_config(dmamux_multiplexer_channel_enum channelx, uint32_t number);
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

/* DMAMUX interrupt and flag functions */
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

#endif /* GD32G5X3_DMA_H */
