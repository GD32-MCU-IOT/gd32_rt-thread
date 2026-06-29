/*!
    \file    gd32w51x_f5hc_icache.h
    \brief   definitions for the ICACHE

    \version 2026-04-15, V2.0.0, firmware for gd32w51x_f5hc
*/

/*
    Copyright (c) 2026, GigaDevice Semiconductor Inc.

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

#ifndef gd32w51x_f5hc_ICACHE_H
#define gd32w51x_f5hc_ICACHE_H

#include "gd32w51x_f5hc.h"

#define ICACHE         ICACHE_BASE                                   /*!< ICACHE base address */

/* registers definitions */
#define ICACHE_CTL                    REG32(ICACHE + 0x00000000U)               /*!< icache control register */
#define ICACHE_STAT                   REG32(ICACHE + 0x00000004U)               /*!< icache status register */
#define ICACHE_INTEN                  REG32(ICACHE + 0x00000008U)               /*!< icache interrupt enable register */
#define ICACHE_FC                     REG32(ICACHE + 0x0000000CU)               /*!< icache flag clear register */
#define ICACHE_HMC                    REG32(ICACHE + 0x00000010U)               /*!< icache hit monitor register */
#define ICACHE_MMC                    REG32(ICACHE + 0x00000014U)               /*!< icache miss monitor register */
#define ICACHE_CFG(x)                 REG32(ICACHE + 0x00000020U + 0x04U * (x)) /*!< icache regionx(x = 0-3) configure register */

/* bits definitions */
/* ICACHE_CTL */
#define ICACHE_CTL_EN                 BIT(0)                         /*!< enable icache module */
#define ICACHE_CTL_INVAL              BIT(1)                         /*!< cache invalidation */
#define ICACHE_CTL_AMSEL              BIT(2)                         /*!< associativity mode selection */
#define ICACHE_CTL_BSTT               BIT(3)                         /*!< output burst type selection */
#define ICACHE_CTL_HMEN               BIT(16)                        /*!< hit monitor enable */
#define ICACHE_CTL_MMEN               BIT(17)                        /*!< miss monitor enable */
#define ICACHE_CTL_HMRST              BIT(18)                        /*!< hit monitor reset */
#define ICACHE_CTL_MMRST              BIT(19)                        /*!< miss monitor reset */

/* ICACHE_STAT */
#define ICACHE_STAT_BUSY              BIT(0)                         /*!< busy flag */
#define ICACHE_STAT_END               BIT(1)                         /*!< operation end flag */
#define ICACHE_STAT_ERR               BIT(2)                         /*!< error flag */

/* ICACHE_INTEN */
#define ICACHE_INTEN_ENDIE            BIT(1)                         /*!< operation end interrupt enable */
#define ICACHE_INTEN_ERRIE            BIT(2)                         /*!< error interrupt enable */

/* ICACHE_FC */
#define ICACHE_FC_ENDC                BIT(1)                         /*!< clear operation end flag */
#define ICACHE_FC_ERRC                BIT(2)                         /*!< clear error flag */

/* ICACHE_HMC */
#define ICACHE_HMC_HMC                BITS(0,31)                     /*!< icache hit monitor counter */

/* ICACHE_MMC */
#define ICACHE_MMC_MMC                BITS(0,15)                     /*!< icache miss monitor counter */

/* ICACHE_CFGx */
#define ICACHE_CFGx_BADDR             BITS(0,7)                      /*!< icache remap base address */
#define ICACHE_CFGx_SIZE              BITS(9,11)                     /*!< icache remap size */
#define ICACHE_CFGx_EN                BIT(15)                        /*!< icache remap enable */
#define ICACHE_CFGx_RADDR             BITS(16,26)                    /*!< icache remap remap address */
#define ICACHE_CFGx_MSEL              BIT(28)                        /*!< icache cache master for region x */
#define ICACHE_CFGx_OBT               BIT(31)                        /*!< icache output burst type for region x */

/* ICACHE monitor source */
#define ICACHE_MONITOR_HIT            ICACHE_CTL_HMEN                /*!< hit monitor enable */
#define ICACHE_MONITOR_MISS           ICACHE_CTL_MMEN                /*!< miss monitor enable */
#define ICACHE_MONITOR_HIT_MISS       (ICACHE_MONITOR_HIT | ICACHE_MONITOR_MISS) /*!< hit and miss monitor enable */

/* ICACHE monitor reset source */
#define ICACHE_MONITOR_RESET_HIT      ICACHE_CTL_HMRST               /*!< hit monitor reset */
#define ICACHE_MONITOR_RESET_MISS     ICACHE_CTL_MMRST               /*!< miss monitor reset */
#define ICACHE_MONITOR_RESET_HIT_MISS (ICACHE_MONITOR_RESET_HIT | ICACHE_MONITOR_RESET_MISS)  /*!< hit and miss monitor reset */

/* ICACHE way mode selection */
#define ICACHE_N_WAYS                 1U                             /*!< icache n-way associative cache */

/* ICACHE burst type selection */
#define ICACHE_WRAP_BURST             0U                             /*!< icache WRAP burst mode */
#define ICACHE_INCR_BURST             1U                             /*!< icache INCR burst mode */

/* ICACHE interrupt source */
#define ICACHE_ENDIE                  ICACHE_INTEN_ENDIE             /*!< operation end interrupt enable */
#define ICACHE_ERRIE                  ICACHE_INTEN_ERRIE             /*!< error interrupt enable */

/* ICACHE flag source */
#define ICACHE_BUSY_FLAG              ICACHE_STAT_BUSY               /*!< busy flag */
#define ICACHE_END_FLAG               ICACHE_STAT_END                /*!< operation end flag */
#define ICACHE_ERR_FLAG               ICACHE_STAT_ERR                /*!< error flag */

/* ICACHE flag clear source */
#define ICACHE_ENDC_FLAG              ICACHE_FC_ENDC                 /*!< operation end clear flag */
#define ICACHE_ERRC_FLAG              ICACHE_FC_ERRC                 /*!< error clear flag */

#define ICACHE_CTL_DEFAULT            0x00000004U                    /*!< icache control register default value */

/* ICACHE REMAP TYPE */
typedef struct {
    uint32_t region_num;                                             /*!< remap region number (0..3) */
    uint32_t base_address;                                           /*!< remap base address */
    uint32_t remap_address;                                          /*!< remap remap address */
    uint32_t remap_size;                                             /*!< remap size */
    uint32_t master_sel;                                             /*!< remap master selection */
} icache_remap_struct;

/* ICACHE REMAP SIZE  */
#define ICACHE_REMAP_2M               1U                             /*!< remap size 2M */
#define ICACHE_REMAP_4M               2U                             /*!< remap size 4M */
#define ICACHE_REMAP_8M               3U                             /*!< remap size 8M */
#define ICACHE_REMAP_16M              4U                             /*!< remap size 16M */
#define ICACHE_REMAP_32M              5U                             /*!< remap size 32M */
#define ICACHE_REMAP_64M              6U                             /*!< remap size 64M */
#define ICACHE_REMAP_128M             7U                             /*!< remap size 128M */

/* ICACHE REMAP REGION*/
#define ICACHE_REMAP_REGION_0         0U                             /*!< remap region 0 */
#define ICACHE_REMAP_REGION_1         1U                             /*!< remap region 1 */
#define ICACHE_REMAP_REGION_2         2U                             /*!< remap region 2 */
#define ICACHE_REMAP_REGION_3         3U                             /*!< remap region 3 */

#ifdef FW_DEBUG_ERR_REPORT
/* Validity check for region_num */
#define NOT_ICACHE_REMAP_REGION(REGION)   ((REGION) > 3U)
#endif

/* function declarations */
/* enable icache */
void icache_enable(void);
/* disable icache */
void icache_disable(void);
/* enable the icache monitor */
void icache_monitor_enable(uint32_t monitor_source);
/* disable the icache monitor */
void icache_monitor_disable(uint32_t monitor_source);
/* reset the icache monitor */
void icache_monitor_reset(uint32_t reset_monitor_source);
/* configure icache way (associativity mode) */
ErrStatus icache_way_configure(void);
/* select icache burst type */
ErrStatus icache_burst_type_select(uint32_t burst_type);
/* invalidate icache */
ErrStatus icache_invalidation(void);
/* get the hit monitor value */
uint32_t icache_hitvalue_get(void);
/* get the miss monitor value */
uint32_t icache_missvalue_get(void);
/* enable the icache remap function */
ErrStatus icache_remap_enable(icache_remap_struct *icache_remap_config);
/* disable the icache remap function */
ErrStatus icache_remap_disable(uint32_t region_num);
/* get icache flag */
FlagStatus icache_flag_get(uint32_t flag);
/* clear icache flag */
void icache_flag_clear(uint32_t flag);
/* enable icache interrupt */
void icache_interrupt_enable(uint32_t interrupt);
/* disable icache interrupt */
void icache_interrupt_disable(uint32_t interrupt);
/* get icache interrupt flag */
FlagStatus icache_interrupt_flag_get(uint32_t interrupt);
/* clear icache interrupt flag */
void icache_interrupt_flag_clear(uint32_t interrupt);

#endif /* gd32w51x_f5hc_ICACHE_H */
