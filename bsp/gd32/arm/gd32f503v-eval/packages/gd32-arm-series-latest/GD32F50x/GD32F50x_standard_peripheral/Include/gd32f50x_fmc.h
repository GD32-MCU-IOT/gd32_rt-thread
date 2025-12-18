/*!
    \file    gd32f50x_fmc.h
    \brief   definitions for the FMC

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


#ifndef GD32F50X_FMC_H
#define GD32F50X_FMC_H

#include "gd32f50x.h"

/* FMC and option byte definition */
#define FMC                            FMC_BASE                                      /*!< FMC register base address */
#define OB                             OB_BASE                                       /*!< option bytes base address */

/* registers definitions */
#define FMC_KEY0                       REG32((FMC) + 0x04U)                          /*!< FMC unlock key register 0 */
#define FMC_OBKEY                      REG32((FMC) + 0x08U)                          /*!< FMC option bytes unlock key register */
#define FMC_STAT0                      REG32((FMC) + 0x0CU)                          /*!< FMC status register 0 */
#define FMC_CTL0                       REG32((FMC) + 0x10U)                          /*!< FMC control register 0 */
#define FMC_ADDR0                      REG32((FMC) + 0x14U)                          /*!< FMC address register 0 */
#define FMC_OBCTL0                     REG32((FMC) + 0x18U)                          /*!< FMC option byte control register 0 */
#define FMC_OBCTL1                     REG32((FMC) + 0x1CU)                          /*!< FMC option byte control register 1 */
#define FMC_OBCTL2                     REG32((FMC) + 0x20U)                          /*!< FMC option byte control register 2 */
#define FMC_OTP1CFG                    REG32((FMC) + 0x24U)                          /*!< FMC OTP1 configuration register */
#define FMC_OBSTAT                     REG32((FMC) + 0x40U)                          /*!< FMC option bytes status register */
#define FMC_KEY1                       REG32((FMC) + 0x44U)                          /*!< FMC unlock key register 1 */
#define FMC_STAT1                      REG32((FMC) + 0x4CU)                          /*!< FMC status register 1 */
#define FMC_CTL1                       REG32((FMC) + 0x50U)                          /*!< FMC control register 1 */
#define FMC_ADDR1                      REG32((FMC) + 0x54U)                          /*!< FMC address register 1 */
#define FMC_OTP3_STAT                  REG32((FMC) + 0x60U)                          /*!< FMC OTP3 status register */
#define FMC_PID                        REG32((FMC) + 0x100U)                         /*!< FMC product ID register */

#define OB_SPC                         REG16((OB) + 0x00U)                           /*!< option byte security protection value */
#define OB_USER                        REG16((OB) + 0x02U)                           /*!< option byte user value */
#define OB_DATA_0                      REG16((OB) + 0x04U)                           /*!< option byte data0 value */
#define OB_DATA_1                      REG16((OB) + 0x06U)                           /*!< option byte data1 value */
#define OB_WP0                         REG16((OB) + 0x08U)                           /*!< option byte write protection 0 */
#define OB_WP1                         REG16((OB) + 0x0AU)                           /*!< option byte write protection 1 */
#define OB_WP2                         REG16((OB) + 0x0CU)                           /*!< option byte write protection 2 */
#define OB_WP3                         REG16((OB) + 0x0EU)                           /*!< option byte write protection 3 */

/* bits definitions */
/* FMC_KEY0 */
#define FMC_KEY0_KEY                   BITS(0,31)                                    /*!< FMC_CTL0 unlock key bits */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY                BITS(0,31)                                    /*!< option bytes unlock key bits */

/* FMC_STAT0 */
#define FMC_STAT0_BUSY                 BIT(0)                                        /*!< flash busy flag bit */
#define FMC_STAT0_PGERR                BIT(2)                                        /*!< flash program error flag bit */
#define FMC_STAT0_WPERR                BIT(4)                                        /*!< erase/program protection error flag bit */
#define FMC_STAT0_ENDF                 BIT(5)                                        /*!< end of operation flag bit */

/* FMC_CTL0 */
#define FMC_CTL0_PG                    BIT(0)                                        /*!< main flash program for bank0 command bit */
#define FMC_CTL0_PER                   BIT(1)                                        /*!< main flash page erase for bank0 command bit */
#define FMC_CTL0_MER                   BIT(2)                                        /*!< main flash mass erase for bank0 command bit */
#define FMC_CTL0_START                 BIT(6)                                        /*!< send erase command to FMC bit */
#define FMC_CTL0_LK                    BIT(7)                                        /*!< FMC_CTL0 lock bit */
#define FMC_CTL0_ERRIE                 BIT(10)                                       /*!< error interrupt enable bit */
#define FMC_CTL0_ENDIE                 BIT(12)                                       /*!< end of operation interrupt enable bit */
#define FMC_CTL0_RLBE                  BIT(13)                                       /*!< OTP2 read lock block enable bit */
#define FMC_CTL0_PWDN                  BIT(30)                                       /*!< deep power down mode enable when no operation */
#define FMC_CTL0_NWLDE                 BIT(31)                                       /*!< no waiting time area load enable when system reset */

/* FMC_ADDR0 */
#define FMC_ADDR0_ADDR                 BITS(0,31)                                    /*!< Flash erase/program command address bits */

/* FMC_OBCTL0 */
#define FMC_OBCTL0_OB_LK               BIT(0)                                        /*!< FMC_OBCTL0 lock bit */
#define FMC_OBCTL0_OB_START            BIT(1)                                        /*!< send option byte change command to FMC bit */
#define FMC_OBCTL0_SPC                 BITS(8,15)                                    /*!< option bytes security protection code */

/* FMC_OBCTL1 */
#define FMC_OBCTL1_OBERR               BIT(0)                                        /*!< option bytes read error bit */
#define FMC_OBCTL1_NWDG_HW             BIT(2)                                        /*!< option byte watchdog value */
#define FMC_OBCTL1_NRST_DPSLP          BIT(3)                                        /*!< option byte deepsleep reset value */
#define FMC_OBCTL1_NRST_STDBY          BIT(4)                                        /*!< option byte standby reset value */
#define FMC_OBCTL1_SRAM_RST            BIT(5)                                        /*!< option byte sram initialize value */
#define FMC_OBCTL1_ECC_EN              BIT(6)                                        /*!< option byte sram ecc enable/disable */
#define FMC_OBCTL1_NWLD_SEL            BITS(7,8)                                     /*!< select the clock for loading no waiting time area. */
#define FMC_OBCTL1_DATA                BITS(10,25)                                   /*!< store DATA of option bytes block after system reset */

/* FMC_OBCTL2 */
#define FMC_OBCTL2_WP                  BITS(0,31)                                    /*!< store WP of option bytes block after system reset */

/* FMC_OTP1CFG */
#define FMC_OTP1CFG_OTP1REN            BITS(0,15)                                    /*!< FMC OTP1 read enable bits */

/* FMC_OBSTAT */
#define FMC_OBSTAT_SPCL                BIT(0)                                        /*!< security protection is level low */
#define FMC_OBSTAT_SPCH                BIT(1)                                        /*!< security protection is level high */

/* FMC_KEY1 */
#define FMC_KEY1_KEY                   BITS(0,31)                                    /*!< FMC_CTL1 unlock key bits */

/* FMC_STAT1 */
#define FMC_STAT1_BUSY                 BIT(0)                                        /*!< The flash is busy bit */
#define FMC_STAT1_PGERR                BIT(2)                                        /*!< flash program error flag bit */
#define FMC_STAT1_WPERR                BIT(4)                                        /*!< erase/program protection error flag bit */
#define FMC_STAT1_ENDF                 BIT(5)                                        /*!< end of operation flag bit */

/* FMC_CTL1 */
#define FMC_CTL1_PG                    BIT(0)                                        /*!< main flash program for bank1 command bit */
#define FMC_CTL1_PER                   BIT(1)                                        /*!< main flash page erase for bank1 command bit */
#define FMC_CTL1_MER                   BIT(2)                                        /*!< main flash mass erase for bank1 command bit */
#define FMC_CTL1_START                 BIT(6)                                        /*!< send erase command to FMC bit */
#define FMC_CTL1_LK                    BIT(7)                                        /*!< FMC_CTL1 lock bit */
#define FMC_CTL1_ERRIE                 BIT(10)                                       /*!< error interrupt enable bit */
#define FMC_CTL1_ENDIE                 BIT(12)                                       /*!< end of operation interrupt enable bit */

/* FMC_ADDR1 */
#define FMC_ADDR1_ADDR                 BITS(0,31)                                    /*!< Flash erase/program command address bits */

/* FMC_OTP3_STAT */
#define FMC_OTP3_STAT_NDBG             BIT(0)                                        /*!< debugging permission setting bit */
#define FMC_OTP3_STAT_NBTSB            BIT(1)                                        /*!< not boot from SRAM or bootloader */
#define FMC_OTP3_STAT_BTFOSEL          BIT(2)                                        /*!< select Boot from flash or OTP1 */
#define FMC_OTP3_STAT_NDBG_LK          BIT(4)                                        /*!< NDBG lock status */
#define FMC_OTP3_STAT_NBTSB_LK         BIT(5)                                        /*!< NBTSB lock status */
#define FMC_OTP3_STAT_BTFOSEL_LK       BIT(6)                                        /*!< BTFOSEL lock status */

/* FMC_PID */
#define FMC_PID_PID                    BITS(0,31)                                    /*!< product ID bits */

/* constants definitions */
/* unlock key */
#define UNLOCK_KEY0                    ((uint32_t)0x45670123U)                       /*!< unlock key 0 */
#define UNLOCK_KEY1                    ((uint32_t)0xCDEF89ABU)                       /*!< unlock key 1 */

/* read protect configure */
#define OBCTL0_SPC(regval)             (BITS(8,15) & ((uint32_t)(regval) << 8))
#define FMC_NSPC                       OBCTL0_SPC(0xAA)                              /*!< no security protection */
#define FMC_LSPC                       OBCTL0_SPC(0xBB)                              /*!< low security protection */
#define FMC_HSPC                       OBCTL0_SPC(0xCC)                              /*!< high security protection */

/* option byte software/hardware free watch dog timer */
#define OB_FWDGT_SW                    FMC_OBCTL1_NWDG_HW                            /*!< software free watchdog */
#define OB_FWDGT_HW                    ((uint32_t)0x00000000U)                       /*!< hardware free watchdog */

/* option byte reset or not entering deep sleep mode */
#define OB_DEEPSLEEP_NRST              FMC_OBCTL1_NRST_DPSLP                         /*!< no reset when entering deepsleep mode */
#define OB_DEEPSLEEP_RST               ((uint32_t)0x00000000U)                       /*!< generate a reset instead of entering deepsleep mode */

/* option byte reset or not entering standby mode */
#define OB_STDBY_NRST                  FMC_OBCTL1_NRST_STDBY                         /*!< no reset when entering standby mode */
#define OB_STDBY_RST                   ((uint32_t)0x00000000U)                       /*!< generate a reset instead of entering standby mode */

/* option byte sram initialize value */
#define OB_SRAM_INI_DISABLE            FMC_OBCTL1_SRAM_RST                           /*!< do not initialize SRAM after power reset */
#define OB_SRAM_INI_ENABLE             ((uint32_t)0x00000000U)                       /*!< initialize SRAM after power reset */

/* option byte sram ecc function value */
#define OB_SRAMECC_ENABLE              FMC_OBCTL1_ECC_EN                             /*!< SRAM ECC enable */
#define OB_SRAMECC_DISABLE             ((uint32_t)0x00000000U)                       /*!< SRAM ECC disable */

/* option byte NWLD_CLK value */
#define OBCTL1_NWLD_SEL(regval)        (BITS(7,8) & ((uint32_t)(regval) << 7))
#define PLL_CLK_200M                   OBCTL1_NWLD_SEL(0)                           /*!< select 200M from PLL */
#define PLL_CLK_160M                   OBCTL1_NWLD_SEL(1)                           /*!< select 160M from PLL */
#define PLL_CLK_120M                   OBCTL1_NWLD_SEL(2)                           /*!< select 120M from PLL */
#define IRC8M_CLK_8M                   OBCTL1_NWLD_SEL(3)                           /*!< select 8M from IRC8M */

/* option bytes write protection */
#define OB_WP_0                        BIT(0)                                        /*!< erase/program protection of page 0,1  */
#define OB_WP_1                        BIT(1)                                        /*!< erase/program protection of page 2,3  */
#define OB_WP_2                        BIT(2)                                        /*!< erase/program protection of page 4,5  */
#define OB_WP_3                        BIT(3)                                        /*!< erase/program protection of page 6,7  */
#define OB_WP_4                        BIT(4)                                        /*!< erase/program protection of page 8,9  */
#define OB_WP_5                        BIT(5)                                        /*!< erase/program protection of page 10,11 */
#define OB_WP_6                        BIT(6)                                        /*!< erase/program protection of page 12,13 */
#define OB_WP_7                        BIT(7)                                        /*!< erase/program protection of page 14,15 */
#define OB_WP_8                        BIT(8)                                        /*!< erase/program protection of page 16,17 */
#define OB_WP_9                        BIT(9)                                        /*!< erase/program protection of page 18,19 */
#define OB_WP_10                       BIT(10)                                       /*!< erase/program protection of page 20,21 */
#define OB_WP_11                       BIT(11)                                       /*!< erase/program protection of page 22,23 */
#define OB_WP_12                       BIT(12)                                       /*!< erase/program protection of page 24,25 */
#define OB_WP_13                       BIT(13)                                       /*!< erase/program protection of page 26,27 */
#define OB_WP_14                       BIT(14)                                       /*!< erase/program protection of page 28,29 */
#define OB_WP_15                       BIT(15)                                       /*!< erase/program protection of page 30,31 */
#define OB_WP_16                       BIT(16)                                       /*!< erase/program protection of page 32,33 */
#define OB_WP_17                       BIT(17)                                       /*!< erase/program protection of page 34,35 */
#define OB_WP_18                       BIT(18)                                       /*!< erase/program protection of page 36,37 */
#define OB_WP_19                       BIT(19)                                       /*!< erase/program protection of page 38,39 */
#define OB_WP_20                       BIT(20)                                       /*!< erase/program protection of page 40,41 */
#define OB_WP_21                       BIT(21)                                       /*!< erase/program protection of page 42,43 */
#define OB_WP_22                       BIT(22)                                       /*!< erase/program protection of page 44,45 */
#define OB_WP_23                       BIT(23)                                       /*!< erase/program protection of page 46,47 */
#define OB_WP_24                       BIT(24)                                       /*!< erase/program protection of page 48,49 */
#define OB_WP_25                       BIT(25)                                       /*!< erase/program protection of page 50,51 */
#define OB_WP_26                       BIT(26)                                       /*!< erase/program protection of page 52,53 */
#define OB_WP_27                       BIT(27)                                       /*!< erase/program protection of page 54,55 */
#define OB_WP_28                       BIT(28)                                       /*!< erase/program protection of page 56,57 */
#define OB_WP_29                       BIT(29)                                       /*!< erase/program protection of page 58,59 */
#define OB_WP_30                       BIT(30)                                       /*!< erase/program protection of page 60,61 */
#define OB_WP_31                       BIT(31)                                       /*!< erase/program protection of page 62-383 */
#define OB_WP_ALL                      BITS(0,31)                                    /*!< erase/program protection of all pages */

/* OTP1 data block read enable */
#define OTP1_DATA_BLOCK_0              BIT(0)                                        /*!< OTP1 read enable of data block 0  */
#define OTP1_DATA_BLOCK_1              BIT(1)                                        /*!< OTP1 read enable of data block 1  */
#define OTP1_DATA_BLOCK_2              BIT(2)                                        /*!< OTP1 read enable of data block 2  */
#define OTP1_DATA_BLOCK_3              BIT(3)                                        /*!< OTP1 read enable of data block 3  */
#define OTP1_DATA_BLOCK_4              BIT(4)                                        /*!< OTP1 read enable of data block 4  */
#define OTP1_DATA_BLOCK_5              BIT(5)                                        /*!< OTP1 read enable of data block 5  */
#define OTP1_DATA_BLOCK_6              BIT(6)                                        /*!< OTP1 read enable of data block 6  */
#define OTP1_DATA_BLOCK_7              BIT(7)                                        /*!< OTP1 read enable of data block 7  */
#define OTP1_DATA_BLOCK_8              BIT(8)                                        /*!< OTP1 read enable of data block 8  */
#define OTP1_DATA_BLOCK_9              BIT(9)                                        /*!< OTP1 read enable of data block 9  */
#define OTP1_DATA_BLOCK_10             BIT(10)                                       /*!< OTP1 read enable of data block 10 */
#define OTP1_DATA_BLOCK_11             BIT(11)                                       /*!< OTP1 read enable of data block 11 */
#define OTP1_DATA_BLOCK_12             BIT(12)                                       /*!< OTP1 read enable of data block 12 */
#define OTP1_DATA_BLOCK_13             BIT(13)                                       /*!< OTP1 read enable of data block 13 */
#define OTP1_DATA_BLOCK_14             BIT(14)                                       /*!< OTP1 read enable of data block 14 */
#define OTP1_DATA_BLOCK_15             BIT(15)                                       /*!< OTP1 read enable of data block 15 */
#define OTP1_DATA_BLOCK_ALL            BITS(0,15)                                    /*!< OTP1 read enable of ALL data blocks */

/* OTP0 address */
#define OTP0_DATA_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FFF7800U)                       /*!< OTP0 data block base address */
#define OTP0_DATA_BLOCK_END_ADDRESS    ((uint32_t)0x1FFF783FU)                       /*!< OTP0 data block end address */
#define OTP0_LOCK_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FFF7840U)                       /*!< OTP0 lock block base address */
#define OTP0_LOCK_BLOCK_END_ADDRESS    ((uint32_t)0x1FFF787FU)                       /*!< OTP0 lock block end address */

/* OTP1 address */
#define OTP1_DATA_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FF00000U)                       /*!< OTP1 data block base address */
#define OTP1_DATA_BLOCK_END_ADDRESS    ((uint32_t)0x1FF1FFFFU)                       /*!< OTP1 data block end address */
#define OTP1_LOCK_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FF20100U)                       /*!< OTP1 lock block base address */
#define OTP1_LOCK_BLOCK_END_ADDRESS    ((uint32_t)0x1FF2010FU)                       /*!< OTP1 lock block end address */

/* OTP2 address */
#define OTP2_DATA_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FF20000U)                       /*!< OTP2 data block base address */
#define OTP2_DATA_BLOCK_END_ADDRESS    ((uint32_t)0x1FF200FFU)                       /*!< OTP2 data block end address */
#define OTP2_WLOCK_BLOCK_BASE_ADDRESS  ((uint32_t)0x1FF20110U)                       /*!< OTP2 write lock block base address */
#define OTP2_WLOCK_BLOCK_END_ADDRESS   ((uint32_t)0x1FF2014FU)                       /*!< OTP2 write lock block end address */
#define OTP2_RLOCK_BLOCK_BASE_ADDRESS  ((uint32_t)0x1FF20150U)                       /*!< OTP2 read lock block base address */
#define OTP2_RLOCK_BLOCK_END_ADDRESS   ((uint32_t)0x1FF2018FU)                       /*!< OTP2 read lock block end address */

/* OTP3 address */
#define OTP3_DATA_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FFF7900U)                       /*!< OTP3 data block base address */
#define OTP3_DATA_BLOCK_END_ADDRESS    ((uint32_t)0x1FFF7923U)                       /*!< OTP3 data block end address */
#define OTP3_LOCK_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FFF7930U)                       /*!< OTP3 lock block base address */
#define OTP3_LOCK_BLOCK_END_ADDRESS    ((uint32_t)0x1FFF793BU)                       /*!< OTP3 lock block end address */

/* define the FMC bit position and its register index offset */
#define FMC_REGIDX_BIT(regidx, bitpos)              (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define FMC_REG_VAL(offset)                         (REG32(FMC + ((uint32_t)(offset) >> 6)))
#define FMC_BIT_POS(val)                            ((uint32_t)(val) & 0x1FU)
#define FMC_REGIDX_BITS(regidx, bitpos0, bitpos1)   (((uint32_t)(regidx) << 12) | ((uint32_t)(bitpos0) << 6) | (uint32_t)(bitpos1))
#define FMC_REG_VALS(offset)                        (REG32(FMC + ((uint32_t)(offset) >> 12)))
#define FMC_BIT_POS0(val)                           (((uint32_t)(val) >> 6) & 0x1FU)
#define FMC_BIT_POS1(val)                           ((uint32_t)(val) & 0x1FU)
#define FMC_REG_OFFSET_GET(flag)                    ((uint32_t)(flag) >> 12)

/* configuration register */
#define FMC_STAT0_REG_OFFSET                        0x0CU                            /*!< status register 0 offset */
#define FMC_CTL0_REG_OFFSET                         0x10U                            /*!< control register 0 offset */
#define FMC_STAT1_REG_OFFSET                        0x4CU                            /*!< status register 1 offset */
#define FMC_CTL1_REG_OFFSET                         0x50U                            /*!< control register 1 offset */
#define FMC_OBCTL1_REG_OFFSET                       0x1CU                            /*!< option byte status register offset */

/* fmc state */
typedef enum {
    FMC_READY,                                                                       /*!< the operation has been completed */
    FMC_BUSY,                                                                        /*!< the operation is in progress */
    FMC_PGERR,                                                                       /*!< program error */
    FMC_WPERR,                                                                       /*!< erase/program protection error */
    FMC_TOERR,                                                                       /*!< timeout error */
} fmc_state_enum;

/* FMC interrupt enable */
typedef enum {
    FMC_INT_BANK0_END     = FMC_REGIDX_BIT(FMC_CTL0_REG_OFFSET, 12U),                /*!< FMC bank0 end of operation */
    FMC_INT_BANK0_ERR     = FMC_REGIDX_BIT(FMC_CTL0_REG_OFFSET, 10U),                /*!< FMC bank0 error */
    FMC_INT_BANK1_END     = FMC_REGIDX_BIT(FMC_CTL1_REG_OFFSET, 12U),                /*!< FMC bank1 end of operation */
    FMC_INT_BANK1_ERR     = FMC_REGIDX_BIT(FMC_CTL1_REG_OFFSET, 10U),                /*!< FMC bank1 error */
} fmc_interrupt_enum;

/* FMC flags */
typedef enum {
    FMC_FLAG_BANK0_BUSY   = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 0U),                /*!< FMC bank0 busy flag */
    FMC_FLAG_BANK0_PGERR  = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 2U),                /*!< FMC bank0 operation error flag bit */
    FMC_FLAG_BANK0_WPERR  = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 4U),                /*!< FMC bank0 erase/program protection error flag bit */
    FMC_FLAG_BANK0_END    = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 5U),                /*!< FMC bank0 end of operation flag bit */
    FMC_FLAG_OBERR        = FMC_REGIDX_BIT(FMC_OBCTL1_REG_OFFSET, 0U),               /*!< FMC option bytes read error flag */
    FMC_FLAG_BANK1_BUSY   = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 0U),                /*!< FMC bank1 busy flag */
    FMC_FLAG_BANK1_PGERR  = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 2U),                /*!< FMC bank1 operation error flag bit */
    FMC_FLAG_BANK1_WPERR  = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 4U),                /*!< FMC bank1 erase/program protection error flag bit */
    FMC_FLAG_BANK1_END    = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 5U),                /*!< FMC bank1 end of operation flag bit */
} fmc_flag_enum;

/* FMC interrupt flags */
typedef enum {
    FMC_INT_FLAG_BANK0_PGERR  = FMC_REGIDX_BITS(FMC_STAT0_REG_OFFSET, 2U, 10U),      /*!< FMC bank0 operation error interrupt flag bit */
    FMC_INT_FLAG_BANK0_WPERR  = FMC_REGIDX_BITS(FMC_STAT0_REG_OFFSET, 4U, 10U),      /*!< FMC bank0 erase/program protection error interrupt flag bit */
    FMC_INT_FLAG_BANK0_END    = FMC_REGIDX_BITS(FMC_STAT0_REG_OFFSET, 5U, 12U),      /*!< FMC bank0 end of operation interrupt flag bit */
    FMC_INT_FLAG_BANK1_PGERR  = FMC_REGIDX_BITS(FMC_STAT1_REG_OFFSET, 2U, 10U),      /*!< FMC bank1 operation error interrupt flag bit */
    FMC_INT_FLAG_BANK1_WPERR  = FMC_REGIDX_BITS(FMC_STAT1_REG_OFFSET, 4U, 10U),      /*!< FMC bank1 erase/program protection error interrupt flag bit */
    FMC_INT_FLAG_BANK1_END    = FMC_REGIDX_BITS(FMC_STAT1_REG_OFFSET, 5U, 12U),      /*!< FMC bank1 end of operation interrupt flag bit */
} fmc_interrupt_flag_enum;

/* FMC timeout */
#define FMC_TIMEOUT_COUNT              ((uint32_t)0x0FFF0000U)                      /*!< FMC timeout count value */

/* FMC BANK address */
#define FMC_SIZE                       REG16(0x1FFFF7E0U)                           /*!< FMC size */
#define FLASH_BASE_ADDRESS             ((uint32_t)0x08000000U)                      /*!< flash base address */
#define FLASH_END_ADDRESS              (FLASH_BASE_ADDRESS + (FMC_SIZE * 0x400U))   /*!< flash end address */
#define FMC_BANK0_END_ADDRESS          ((uint32_t)0x0807FFFFU)                      /*!< FMC bank0 end address */
#define FMC_BANK0_SIZE                 ((uint32_t)0x00000200U)                      /*!< FMC bank0 size */
#define OTP_BASE_ADDRESS               ((uint32_t)0x1FF00000U)                      /*!< OTP base address */
#define OTP_END_ADDRESS                ((uint32_t)0x1FFF7940U)                      /*!< OTP end address */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check FMC page valid address */
#define NOT_FMC_PAGE_VALID_ADDRESS(page_address)      (((page_address) >= FLASH_END_ADDRESS) || ((page_address) < FLASH_BASE_ADDRESS))
/* check FMC flash valid word address */
#define NOT_FMC_FLASH_WORD_ADDRESS(address)           (((address) >= FLASH_END_ADDRESS) || ((address) < FLASH_BASE_ADDRESS) || (0U != ((address) & 0x00000003U)))
/* check FMC flash valid halfword address */
#define NOT_FMC_FLASH_HALFWORD_ADDRESS(address)       (((address) >= FLASH_END_ADDRESS) || ((address) < FLASH_BASE_ADDRESS) || (0U != ((address) & 0x00000001U)))
/* check FMC OTP valid byte address */
#define NOT_FMC_OTP_BYTE_ADDRESS(address)             (((address) < OTP_BASE_ADDRESS) || ((address) >= OTP_END_ADDRESS))
/* check FMC OTP valid halfword address */
#define NOT_FMC_OTP_HALFWORD_ADDRESS(address)         ((((address) < OTP_BASE_ADDRESS) || ((address) >= OTP_END_ADDRESS)) || (0U != ((address) & 0x00000001U)))
/* check FMC OTP valid word address */
#define NOT_FMC_OTP_WORD_ADDRESS(address)             ((((address) < OTP_BASE_ADDRESS) || ((address) >= OTP_END_ADDRESS)) || (0U != ((address) & 0x00000003U)))
/* check FMC OB_WP value */
#define NOT_FMC_OB_WP(ob_wp)                          (0U != (((ob_wp) & 0x7FFFFFFFU) >> (FMC_SIZE /0x10U)))

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* FMC main memory programming functions */
/* unlock the main FMC operation */
void fmc_unlock(void);
/* unlock the FMC bank0 operation */
void fmc_bank0_unlock(void);
/* unlock the FMC bank1 operation */
void fmc_bank1_unlock(void);
/* lock the main FMC operation */
void fmc_lock(void);
/* lock the FMC bank0 operation */
void fmc_bank0_lock(void);
/* lock the FMC bank1 operation */
void fmc_bank1_lock(void);
/* erase page */
fmc_state_enum fmc_page_erase(uint32_t page_address);
/* erase whole chip */
fmc_state_enum fmc_mass_erase(void);
/* erase bank0 */
fmc_state_enum fmc_bank0_erase(void);
/* erase bank1 */
fmc_state_enum fmc_bank1_erase(void);
/* program a word at the corresponding address */
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data);
/* program a half word at the corresponding address */
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data);

/* program a word at the OTP address */
fmc_state_enum fmc_otp_word_program(uint32_t address, uint32_t data);
/* program a half word at the OTP address */
fmc_state_enum fmc_otp_half_word_program(uint32_t address, uint16_t data);
/* program a byte at the OTP address */
fmc_state_enum fmc_otp_byte_program(uint32_t address, uint8_t data);

/* enable no waiting time area load after system reset */
void fmc_nwa_enable(void);
/* disable no waiting time area load after system reset */
void fmc_nwa_disable(void);
/* set OTP1 data block not be read */
void otp1_read_disable(uint32_t block);
/* enable read lock block protection for OTP2 */
void otp2_rlock_enable(void);
/* enable deep power down mode when no operation */
void fmc_deep_power_down_enable(void);
/* disable deep power down mode when no operation */
void fmc_deep_power_down_disable(void);

/* FMC option bytes programming functions */
/* unlock the option byte operation */
void ob_unlock(void);
/* lock the option byte operation */
void ob_lock(void);
/* send option byte change command */
void ob_start(void);
/* erase the option byte */
void ob_erase(void);
/* enable write protection */
ErrStatus ob_write_protection_enable(uint32_t ob_wp);
/* disable write protection */
ErrStatus ob_write_protection_disable(uint32_t ob_wp);
/* configure security protection level */
void ob_security_protection_config(uint32_t ob_spc);
/* program the FMC user option byte */
void ob_user_write(uint32_t ob_fwdgt, uint32_t ob_deepsleep, uint32_t ob_stdby);
/* configure the option byte sram initialize value */
void ob_sram_init_config(uint32_t init_mode);
/* configure the option byte sram ecc enable value */
void ob_sram_ecc_config(uint32_t ecc_mode);
/* configure the option byte the clock for loading no waiting time area */
void ob_nwa_clock_config(uint32_t clock_mode);
/* program option bytes data */
void ob_data_write(uint16_t data);
/* get the option byte sram initialize value */
uint32_t ob_sram_init_get(void);
/* get the option byte sram ecc enable value */
uint32_t ob_sram_ecc_get(void);
/* get the option byte the clock for loading no waiting time area */
uint32_t ob_nwa_clock_get(void);
/* get the FMC data option byte */
uint16_t ob_data_get(void);
/* get the FMC option byte write protection */
uint32_t ob_write_protection_get(void);
/* get option byte security protection code value */
uint32_t ob_spc_get(void);

/* FMC interrupts and flags management functions */
/* check flag is set or not */
FlagStatus fmc_flag_get(fmc_flag_enum flag);
/* clear the FMC flag */
void fmc_flag_clear(fmc_flag_enum flag);
/* enable FMC interrupt */
void fmc_interrupt_enable(fmc_interrupt_enum interrupt);
/* disable FMC interrupt */
void fmc_interrupt_disable(fmc_interrupt_enum interrupt);
/* get FMC interrupt flag state */
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum flag);
/* clear FMC interrupt flag state */
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum flag);

/* get the FMC bank0 state */
fmc_state_enum fmc_bank0_state_get(void);
/* get the FMC bank1 state */
fmc_state_enum fmc_bank1_state_get(void);
/* check whether FMC bank0 is ready or not */
fmc_state_enum fmc_bank0_ready_wait(uint32_t timeout);
/* check whether FMC bank1 is ready or not */
fmc_state_enum fmc_bank1_ready_wait(uint32_t timeout);

#endif /* GD32F50X_FMC_H */
