/*!
    \file    gd32g5x3_fmc.h
    \brief   definitions for the FMC

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

#ifndef GD32G5X3_FMC_H
#define GD32G5X3_FMC_H

#include "gd32g5x3.h"

/* FMC and option bytes definition */
#define FMC                                    FMC_BASE                                         /*!< FMC base address */

/* registers definitions */
#define FMC_WS                                 REG32(FMC + 0x00000000U)                         /*!< FMC wait state register */
#define FMC_RUNKEY                             REG32(FMC + 0x00000004U)                         /*!< FMC unlock flash mode during run mode key register */
#define FMC_KEY                                REG32(FMC + 0x00000008U)                         /*!< FMC unlock key register */
#define FMC_OBKEY                              REG32(FMC + 0x0000000CU)                         /*!< FMC option bytes unlock key register */
#define FMC_STAT                               REG32(FMC + 0x00000010U)                         /*!< FMC status register */
#define FMC_CTL                                REG32(FMC + 0x00000014U)                         /*!< FMC control register */
#define FMC_ECCCS                              REG32(FMC + 0x00000018U)                         /*!< FMC ECC control and status register */
#define FMC_OBCTL                              REG32(FMC + 0x00000020U)                         /*!< FMC FMC option byte control register */
#define FMC_DCRP_SADDR0                        REG32(FMC + 0x00000024U)                         /*!< FMC DCRP area start address register 0 */
#define FMC_DCRP_EADDR0                        REG32(FMC + 0x00000028U)                         /*!< FMC DCRP area end address register 0 */
#define FMC_BK0WP0                             REG32(FMC + 0x0000002CU)                         /*!< FMC bank0 erase/program protection area 0 register */
#define FMC_BK0WP1                             REG32(FMC + 0x00000030U)                         /*!< FMC bank0 erase/program protection area 1 register */
#define FMC_DCRP_SADDR1                        REG32(FMC + 0x00000044U)                         /*!< FMC DCRP area start address register 1 */
#define FMC_DCRP_EADDR1                        REG32(FMC + 0x00000048U)                         /*!< FMC DCRP area end address register 1 */
#define FMC_BK1WP0                             REG32(FMC + 0x0000004CU)                         /*!< FMC bank1 erase/program protection area 0 register */
#define FMC_BK1WP1                             REG32(FMC + 0x00000050U)                         /*!< FMC bank1 erase/program protection area 1 register */
#define FMC_BK0SCR                             REG32(FMC + 0x00000070U)                         /*!< FMC bank0 securable area register */
#define FMC_BK1SCR                             REG32(FMC + 0x00000074U)                         /*!< FMC bank1 securable area register */
#define FMC_PID                                REG32(FMC + 0x00000100U)                         /*!< FMC product ID register */

/* bits definitions */
/* FMC_WS */
#define FMC_WS_WSCNT                           BITS(0,3)                                        /*!< wait state counter */
#define FMC_WS_PFEN                            BIT(8)                                           /*!< pre-fetch enable */
#define FMC_WS_ICEN                            BIT(9)                                           /*!< IBUS cache enable */
#define FMC_WS_DCEN                            BIT(10)                                          /*!< DBUS cache enable */
#define FMC_WS_ICRST                           BIT(11)                                          /*!< IBUS cache reset */
#define FMC_WS_DCRST                           BIT(12)                                          /*!< DBUS cache reset */
#define FMC_WS_RUN_MDSEL                       BIT(13)                                          /*!< flash power-down mode during run mode */
#define FMC_WS_SLP_MDSEL                       BIT(14)                                          /*!< flash power-down mode during sleep mode */
#define FMC_WS_DBGEN                           BIT(18)                                          /*!< enable/disable the debugger by software */

/* FMC_RUNKEY */
#define FMC_RUNKEY_RUN_KEY                     BITS(0,31)                                       /*!< FMC_WS_RUN_MDSEL unlock key */

/* FMC_KEY */
#define FMC_KEY_KEY                            BITS(0,31)                                       /*!< FMC_CTL unlock key */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY                        BITS(0,31)                                       /*!< option bytes unlock key */

/* FMC_STAT */
#define FMC_STAT_ENDF                          BIT(0)                                           /*!< end of operation flag */
#define FMC_STAT_OPRERR                        BIT(1)                                           /*!< operation error flag bit */
#define FMC_STAT_PGERR                         BIT(3)                                           /*!< flash program error flag */
#define FMC_STAT_WPERR                         BIT(4)                                           /*!< erase/program protection error flag */
#define FMC_STAT_PGAERR                        BIT(5)                                           /*!< flash program alignment error flag */
#define FMC_STAT_PGMERR                        BIT(6)                                           /*!< program size error flag bit */
#define FMC_STAT_PGSERR                        BIT(7)                                           /*!< program sequence error flag bit */
#define FMC_STAT_RPERR                         BIT(14)                                          /*!< read protection error flag bit */
#define FMC_STAT_OBERR                         BIT(15)                                          /*!< option byte read error */
#define FMC_STAT_BUSY                          BIT(16)                                          /*!< flash busy flag */

/* FMC_CTL */
#define FMC_CTL_PG                             BIT(0)                                           /*!< main flash page program command bit */
#define FMC_CTL_PER                            BIT(1)                                           /*!< main flash page erase command bit */
#define FMC_CTL_MER0                           BIT(2)                                           /*!< main flash mass erase for bank0 command bit */
#define FMC_CTL_PNSEL                          BITS(3,10)                                       /*!< page number to erase */
#define FMC_CTL_BKSEL                          BIT(12)                                          /*!< bank number selection for page erase */
#define FMC_CTL_MER1                           BIT(15)                                          /*!< main flash mass erase for bank1 command bit */
#define FMC_CTL_START                          BIT(16)                                          /*!< send erase command to FMC bit */
#define FMC_CTL_OBSTART                        BIT(17)                                          /*!< send option byte change command to FMC bit */
#define FMC_CTL_ENDIE                          BIT(24)                                          /*!< end of operation interrupt enable bit */
#define FMC_CTL_ERRIE                          BIT(25)                                          /*!< operation error interrupt enable bit */
#define FMC_CTL_RPERRIE                        BIT(26)                                          /*!< read protection error interrupt enable */
#define FMC_CTL_OBRLD                          BIT(27)                                          /*!< option byte reload bit */
#define FMC_CTL_SCR0                           BIT(28)                                          /*!< bank0 security access protection bit */
#define FMC_CTL_SCR1                           BIT(29)                                          /*!< bank1 security access protection bit */
#define FMC_CTL_OBLK                           BIT(30)                                          /*!< OB lock bit */
#define FMC_CTL_LK                             BIT(31)                                          /*!< FMC_CTL lock bit */

/* FMC_ECCCS */
#define FMC_ECCCS_ECCADDR                      BITS(0,18)                                       /*!< ECC fail address */
#define FMC_ECCCS_BK_ECC                       BIT(21)                                          /*!< ECC fail bank */
#define FMC_ECCCS_SYS_ECC                      BIT(22)                                          /*!< ECC error correction or double ECC error in system memory */
#define FMC_ECCCS_ECCCORIE                     BIT(24)                                          /*!< one-bit error correction interrupt enable */
#define FMC_ECCCS_ECCCOR1                      BIT(28)                                          /*!< one-bit error correction in 64bit MSB */ 
#define FMC_ECCCS_ECCDET1                      BIT(29)                                          /*!< two-bits error in 64bit MSB */
#define FMC_ECCCS_ECCCOR0                      BIT(30)                                          /*!< one-bit error correction flag(in 64bit MSB when DBS is 0) */
#define FMC_ECCCS_ECCDET0                      BIT(31)                                          /*!< two-bits error detected flag(in 64bit MSB when DBS is 0) */

/* FMC_OBCTL */
#define FMC_OBCTL_SPC                          BITS(0,7)                                        /*!< security protection value */
#define FMC_OBCTL_BOR_TH                       BITS(8,9)                                        /*!< BOR threshold status bits */
#define FMC_OBCTL_NRST_DPSLP                   BIT(12)                                          /*!< option byte deepsleep reset value bit */
#define FMC_OBCTL_NRST_STDBY                   BIT(13)                                          /*!< option byte standby reset value bit */
#define FMC_OBCTL_FMC_SWP                      BIT(15)                                          /*!< FMC memory mapping swap bit */
#define FMC_OBCTL_NFWDG_HW                     BIT(16)                                          /*!< free watchdog configuration bit */
#define FMC_OBCTL_FWDGSPD_DPSLP                BIT(17)                                          /*!< FWDGT suspend option in deepsleep mode configuration bit */
#define FMC_OBCTL_FWDGSPD_STDBY                BIT(18)                                          /*!< FWDGT suspend option in standby mode configuration bit */
#define FMC_OBCTL_BB                           BIT(20)                                          /*!< dual-bank boot bit */
#define FMC_OBCTL_DBS                          BIT(22)                                          /*!< bank mode bit */
#define FMC_OBCTL_NBOOT1                       BIT(23)                                          /*!< NBOOT1 option bit */
#define FMC_OBCTL_SRAM_ECCEN                   BIT(24)                                          /*!< SRAM and TCM SRAM ECC disable bit */
#define FMC_OBCTL_TCMSRAM_ERS                  BIT(25)                                          /*!< TCM SRAM erase while system reset bit */
#define FMC_OBCTL_NSWBT0                       BIT(26)                                          /*!< software BOOT0 bit */
#define FMC_OBCTL_NBOOT0                       BIT(27)                                          /*!< NBOOT0 option bit */
#define FMC_OBCTL_NRST_MDSEL                   BITS(28,29)                                      /*!< reset pin mode bit */

/* FMC_DCRP_SADDR0 */
#define FMC_DCRP_SADDR0_DCRP0_SADDR            BITS(0,14)                                       /*!< start address of DCRP area 0 */

/* FMC_DCRP_END_ADDR0 */
#define FMC_DCRP_EADDR0_DCRP0_EADDR            BITS(0,14)                                       /*!< end address of DCRP area 0 */
#define FMC_DCRP_EADDR0_DCRP0_EREN             BIT(31)                                          /*!< DCRP area 0 erase enable configuration bit */

/* FMC_BK0WP0 */
#define FMC_BK0WP0_BK0WP0_SADDR                BITS(0,7)                                        /*!< bank0 write protection area 0 start offset */
#define FMC_BK0WP0_BK0WP0_EADDR                BITS(16,23)                                      /*!< bank0 write protection area 0 end offset */

/* FMC_BK0WP1 */
#define FMC_BK0WP1_BK0WP1_SADDR                BITS(0,7)                                        /*!< bank0 write protection area 1 start offset */
#define FMC_BK0WP1_BK0WP1_EADDR                BITS(16,23)                                      /*!< bank0 write protection area 1 end offset */

/* FMC_DCRP_SADDR1 */
#define FMC_DCRP_SADDR1_DCRP1_SADDR            BITS(0,14)                                       /*!< start address of DCRP area 1 */

/* FMC_DCRP_END_ADDR1 */
#define FMC_DCRP_EADDR1_DCRP1_EADDR            BITS(0,14)                                       /*!< end address of DCRP area 1 */

/* FMC_BK1WP0 */
#define FMC_BK1WP0_BK1WP0_SADDR                BITS(0,7)                                        /*!< bank1 write protection area 0 start offset */
#define FMC_BK1WP0_BK1WP0_EADDR                BITS(16,23)                                      /*!< bank1 write protection area 0 end offset */

/* FMC_BK1WP1 */
#define FMC_BK1WP1_BK1WP1_SADDR                BITS(0,7)                                        /*!< bank1 write protection area 1 start offset */
#define FMC_BK1WP1_BK1WP1_EADDR                BITS(16,23)                                      /*!< bank1 write protection area 1 end offset */

/* FMC_BK0SCR */
#define FMC_BK0SCR_SCR_PAGE_CNT0               BITS(0,8)                                        /*!< configure the number of pages in the bank0 securable area */
#define FMC_BK0SCR_BOOTLK                      BIT(16)                                          /*!< this bit is set to force boot from main flash area */

/* FMC_BK1SCR */
#define FMC_BK1SCR_SCR_PAGE_CNT1               BITS(0,8)                                        /*!< configure the number of pages in the bank1 securable area */

/* FMC_PID */
#define FMC_PID_PID                            BITS(0,31)                                       /*!< product ID */

/* FMC_CTL unlock key */
#define FMC_UNLOCK_KEY0                        ((uint32_t)0x45670123U)                          /*!< FMC_CTL unlock key 0 */
#define FMC_UNLOCK_KEY1                        ((uint32_t)0xCDEF89ABU)                          /*!< FMC_CTL unlock key 1 */

/* FMC_CTL_OBLK unlock key */
#define OB_UNLOCK_KEY0                         ((uint32_t)0x08192A3BU)                           /*!< FMC_CTL_OBLK unlock key 0 */
#define OB_UNLOCK_KEY1                         ((uint32_t)0x4C5D6E7FU)                           /*!< FMC_CTL_OBLK unlock key 1 */

/* RUN_MDSEL unlock key */
#define RUN_MDSEL_UNLOCK_KEY0                  ((uint32_t)0x04152637U)                          /*!< RUN_MDSEL unlock key 0 */
#define RUN_MDSEL_UNLOCK_KEY1                  ((uint32_t)0xFAFBFCFDU)                          /*!< RUN_MDSEL unlock key 1 */

/* FMC wait state added */
#define WS_WSCNT(regval)                       (BITS(0,3) & ((uint32_t)(regval)))
#define FMC_WAIT_STATE_0                       WS_WSCNT(0)                                      /*!< 0 wait state added */
#define FMC_WAIT_STATE_1                       WS_WSCNT(1)                                      /*!< 1 wait state added */
#define FMC_WAIT_STATE_2                       WS_WSCNT(2)                                      /*!< 2 wait state added */
#define FMC_WAIT_STATE_3                       WS_WSCNT(3)                                      /*!< 3 wait state added */
#define FMC_WAIT_STATE_4                       WS_WSCNT(4)                                      /*!< 4 wait state added */
#define FMC_WAIT_STATE_5                       WS_WSCNT(5)                                      /*!< 5 wait state added */
#define FMC_WAIT_STATE_6                       WS_WSCNT(6)                                      /*!< 6 wait state added */
#define FMC_WAIT_STATE_7                       WS_WSCNT(7)                                      /*!< 7 wait state added */
#define FMC_WAIT_STATE_8                       WS_WSCNT(8)                                      /*!< 8 wait state added */
#define FMC_WAIT_STATE_9                       WS_WSCNT(9)                                      /*!< 9 wait state added */
#define FMC_WAIT_STATE_10                      WS_WSCNT(10)                                     /*!< 10 wait state added */
#define FMC_WAIT_STATE_11                      WS_WSCNT(11)                                     /*!< 11 wait state added */
#define FMC_WAIT_STATE_12                      WS_WSCNT(12)                                     /*!< 12 wait state added */
#define FMC_WAIT_STATE_13                      WS_WSCNT(13)                                     /*!< 13 wait state added */
#define FMC_WAIT_STATE_14                      WS_WSCNT(14)                                     /*!< 14 wait state added */
#define FMC_WAIT_STATE_15                      WS_WSCNT(15)                                     /*!< 15 wait state added */
                     
/* option byte security protection configuration */
#define FMC_NSPC                              ((uint8_t)0xAAU)                                  /*!< no protection */
#define FMC_LSPC                              ((uint8_t)0xBBU)                                  /*!< protection level low */
#define FMC_HSPC                              ((uint8_t)0xCCU)                                  /*!< protection level high */

/* option byte BOR threshold value */
#define OBCTL_BOR_TH(regval)                  (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define OB_BOR_TH_VALUE0                      OBCTL_BOR_TH(0)                                   /*!< BOR threshold value 0 */
#define OB_BOR_TH_VALUE1                      OBCTL_BOR_TH(1)                                   /*!< BOR threshold value 1 */
#define OB_BOR_TH_VALUE2                      OBCTL_BOR_TH(2)                                   /*!< BOR threshold value 2 */
#define OB_BOR_TH_VALUE3                      OBCTL_BOR_TH(3)                                   /*!< BOR threshold value 3 */

/* option byte reset or not entering deep sleep mode */
#define OBCTL_NRST_DPSLP(regval)              (BIT(12) & ((uint32_t)(regval) << 12U))
#define OB_DEEPSLEEP_RST                      OBCTL_NRST_DPSLP(0)                               /*!< generate a reset instead of entering deepsleep mode */
#define OB_DEEPSLEEP_NRST                     OBCTL_NRST_DPSLP(1)                               /*!< no reset when entering deepsleep mode */

/* option byte reset or not entering standby mode */
#define OBCTL_NRST_STDBY(regval)              (BIT(13) & ((uint32_t)(regval) << 13U))
#define OB_STDBY_RST                          OBCTL_NRST_STDBY(0)                               /*!< generate a reset instead of entering standby mode */
#define OB_STDBY_NRST                         OBCTL_NRST_STDBY(1)                               /*!< no reset when entering deepsleep mode */

/* option byte software/hardware free watchdog timer */
#define OBCTL_NFWDG_HW(regval)                (BIT(16) & ((uint32_t)(regval) << 16U))
#define OB_FWDGT_HW                           OBCTL_NFWDG_HW(0)                                 /*!< hardware free watchdog */
#define OB_FWDGT_SW                           OBCTL_NFWDG_HW(1)                                 /*!< software free watchdog */

/* option byte FWDG status in deep-sleep mode */
#define OBCTL_FWDGSPD_DPSLP(regval)           (BIT(17) & ((uint32_t)(regval) << 17U))
#define OB_DPSLP_FWDGT_SUSPEND                OBCTL_FWDGSPD_DPSLP(0)                            /*!< free watchdog is suspended in deep-sleep mode */
#define OB_DPSLP_FWDGT_RUN                    OBCTL_FWDGSPD_DPSLP(1)                            /*!< free watchdog is running in deep-sleep mode */

/* option byte FWDG status in standby mode */
#define OBCTL_FWDGSPD_STDBY(regval)           (BIT(18) & ((uint32_t)(regval) << 18U))
#define OB_STDBY_FWDGT_SUSPEND                OBCTL_FWDGSPD_STDBY(0)                            /*!< free watchdog is suspended in standby mode */
#define OB_STDBY_FWDGT_RUN                    OBCTL_FWDGSPD_STDBY(1)                            /*!< free watchdog is running in standby mode */

/* option byte boot bank value */
#define OBCTL_BB(regval)                      (BIT(20) & ((uint32_t)(regval) << 20U))
#define OB_BB_DISABLE                         OBCTL_BB(0)                                       /*!< boot from bank0 */
#define OB_BB_ENABLE                          OBCTL_BB(1)                                       /*!< boot from bank1 or bank0 if bank1 is void */

/* option byte double-bank/single-bank selection */
#define OBCTL_DBS(regval)                     (BIT(22) & ((uint32_t)(regval) << 22U))
#define OB_SINGLE_BANK_MODE                   OBCTL_DBS(0)                                      /*!< single-bank selection */
#define OB_DUAL_BANK_MODE                     OBCTL_DBS(1)                                      /*!< double-bank selection */

/* option byte boot1 configuration */
#define OBCTL_NBOOT1(regval)                  (BIT(23) & ((uint32_t)(regval) << 23U))
#define OB_NBOOT1_VALUE_0                     OBCTL_NBOOT1(0)                                   /*!< option byte BOOT1 is value 1 */
#define OB_NBOOT1_VALUE_1                     OBCTL_NBOOT1(1)                                   /*!< option byte BOOT1 is value 0 */

/* option byte boot0 configuration */
#define OBCTL_NBOOT0(regval)                  (BIT(27) & ((uint32_t)(regval) << 27U))
#define OB_NBOOT0_VALUE_0                     OBCTL_NBOOT0(0)                                   /*!< option byte BOOT0 is value 1 */
#define OB_NBOOT0_VALUE_1                     OBCTL_NBOOT0(1)                                   /*!< option byte BOOT0 is value 0 */

/* option byte SRAM and TCM SRAM ECC enable */
#define OBCTL_SRAM_ECCEN(regval)              (BIT(24) & ((uint32_t)(regval) << 24U))
#define OB_SRAM_ECC_ENABLE                    OBCTL_SRAM_ECCEN(0)                                /*!< SRAM and TCM SRAM ECC enable */
#define OB_SRAM_ECC_DISABLE                   OBCTL_SRAM_ECCEN(1)                                /*!< SRAM and TCM SRAM ECC disable */

/* option byte TCM SRAM erase when system reset */
#define OBCTL_TCMSRAM_ERS(regval)             (BIT(25) & ((uint32_t)(regval) << 25U))
#define OB_TCMSRAM_ERASE_ENABLE               OBCTL_TCMSRAM_ERS(0)                               /*!< TCM SRAM erased if a system reset occurs */
#define OB_TCMSRAM_ERASE_DISABLE              OBCTL_TCMSRAM_ERS(1)                               /*!< TCM SRAM is not erased if a system reset occurs */

/* option byte software boot0 */
#define OBCTL_NSWBT0(regval)                  (BIT(26) & ((uint32_t)(regval) << 26U))
#define OB_NSWBOOT0_FROM_OB_BOOT0             OBCTL_NSWBT0(0)                                   /*!< BOOT0 taken from the option bit NBOOT0 */
#define OB_NSWBOOT0_FROM_PIN                  OBCTL_NSWBT0(1)                                   /*!< BOOT0 taken from PB8/BOOT0 pin */

/* option byte reset pin mode */  
#define OBCTL_RST_MD(regval)                  (BITS(28,29) & ((uint32_t)(regval) << 28U))
#define OB_NRST_PIN_INPUT_MODE                OBCTL_RST_MD(1)                                   /*!< a low level on the NRST pin can reset system, internal reset can not drive NRST pin */
#define OB_NRST_PIN_NORMAL_GPIO               OBCTL_RST_MD(2)                                   /*!< NRST pin function as normal GPIO */
#define OB_NRST_PIN_INPUT_OUTPUT_MODE         OBCTL_RST_MD(3)                                   /*!< NRST pin configure as input/output mode */

/* option byte DCRP erase enable configuration */
#define OB_DCRP_EADDR_DCRP_EREN(regval)       (BIT(31) & ((uint32_t)(regval) << 31U))
#define OB_DCRP_AREA_ERASE_DISABLE            OB_DCRP_EADDR_DCRP_EREN(0)                        /*!< DCRP is not erased when a SPC value is decreased from value 1 to value 0 */
#define OB_DCRP_AREA_ERASE_ENABLE             OB_DCRP_EADDR_DCRP_EREN(1)                        /*!< DCRP is erased when a SPC value is decreased from value 1 to value 0 */

/* option byte boot lock */
#define OB_SCR0_BOOTLK(regval)                (BIT(16) & ((uint32_t)(regval) << 16U))
#define OB_BOOT_UNLOCK                        OB_SCR0_BOOTLK(0)                                 /*!< unlock boot */
#define OB_BOOT_LOCK_FROM_MAIN_FLASH          OB_SCR0_BOOTLK(1)                                 /*!< boot from main flash */

/* option byte bank mapping swap */
#define OB_BKMAP_SWAP(regval)                 (BIT(15) & ((uint32_t)(regval) << 15U))
#define OB_BANK_MAPPING_SWAP                  OB_BKMAP_SWAP(0)                                 /*!< bank mapping swap */
#define OB_BANK_MAPPING_NOT_SWAP              OB_BKMAP_SWAP(1)                                 /*!< bank mapping not swap */

/* FMC interrupt enable */
#define FMC_INT_ERR                           FMC_CTL_ERRIE                                     /*!< FMC error interrupt enable */
#define FMC_INT_END                           FMC_CTL_ENDIE                                     /*!< FMC end of operation interrupt enable */
#define FMC_INT_RPERR                         FMC_CTL_RPERRIE                                   /*!< read protection error interrupt enable */
#define FMC_INT_ECCCOR                        FMC_ECCCS_ECCCORIE                                /*!< one-bit error interrupt enable */

/* FMC flags */
#define FMC_FLAG_BUSY                         FMC_STAT_BUSY                                     /*!< FMC busy flag */
#define FMC_FLAG_ENDF                         FMC_STAT_ENDF                                     /*!< FMC end of operation flag */
#define FMC_FLAG_OBERR                        FMC_STAT_OBERR                                    /*!< option byte read error */
#define FMC_FLAG_RPERR                        FMC_STAT_RPERR                                    /*!< read protection error */
#define FMC_FLAG_PGSERR                       FMC_STAT_PGSERR                                   /*!< program sequence error */
#define FMC_FLAG_PGMERR                       FMC_STAT_PGMERR                                   /*!< program size error*/
#define FMC_FLAG_PGAERR                       FMC_STAT_PGAERR                                   /*!< program alignment error */
#define FMC_FLAG_WPERR                        FMC_STAT_WPERR                                    /*!< erase/program protection error */
#define FMC_FLAG_PGERR                        FMC_STAT_PGERR                                    /*!< program error */
#define FMC_FLAG_OPRERR                       FMC_STAT_OPRERR                                   /*!< operation error */
#define FMC_FLAG_ECCDET0                      FMC_ECCCS_ECCDET0                                 /*!< two-bits error(in 64bit LSB when DBS is 0) */
#define FMC_FLAG_ECCCOR0                      FMC_ECCCS_ECCCOR0                                 /*!< one-bit error(in 64bit LSB when DBS is 0) */
#define FMC_FLAG_ECCDET1                      FMC_ECCCS_ECCDET1                                 /*!< two-bits error in 64bit MSB */ 
#define FMC_FLAG_ECCCOR1                      FMC_ECCCS_ECCCOR1                                 /*!< one-bit error in 64bit MSB */

/* FMC interrupt flags */
#define FMC_INT_FLAG_RPERR                    FMC_STAT_RPERR                                    /*!< read protection error interrupt flag */
#define FMC_INT_FLAG_OPRERR                   FMC_STAT_OPRERR                                   /*!< operation error interrupt flag */
#define FMC_INT_FLAG_END                      FMC_STAT_ENDF                                     /*!< end of operation interrupt flag */
#define FMC_INT_FLAG_ECCCOR0                  FMC_ECCCS_ECCCOR0                                  /*!< one-bit error detected and corrected flag */
#define FMC_INT_FLAG_ECCCOR1                  FMC_ECCCS_ECCCOR1                                  /*!< one-bit error detected and corrected flag of 64bit MSB */

#define BKSCR_SCR_PAGE_CNT_OFFSET             (0U)                                              /*!< bit offset of SCR_PAGE_CNT0/SCR_PAGE_CNT1 in FMC_BK0SCR/FMC_BK1SCR */
#define DCRP_SADDR_DCRP_SADDR_OFFSET          (0U)                                              /*!< bit offset of DCRP0_SADDR/DCRP1_SADDR in FMC_DCRP_SADDR0/FMC_DCRP_SADDR1 */
#define DCRP_EADDR_DCRP_EADDR_OFFSET          (0U)                                              /*!< bit offset of DCRP0_EADDR/DCRP1_EADDR in FMC_DCRP_EADDR0/FMC_DCRP_EADDR1 */
#define DCRP_EADDR_DCRP_EREN_OFFSET           (31U)                                             /*!< bit offset of DCRP_EREN in FMC_DCRP0_EADDR */
#define BKWP_BKWP_SADDR_OFFSET                (0U)                                              /*!< bit offset of BK0WP0_SADDR/BK0WP1_SADDR/BK1WP0_SADDR/BK1WP1_SADDR in FMC_BK0WP0/FMC_BK0WP1/FMC_BK1WP0/FMC_BK1WP1 */
#define BKWP_BKWP_EADDR_OFFSET                (16U)                                             /*!< bit offset of BK0WP0_EADDR/BK0WP1_EADDR/BK1WP0_EADDR/BK1WP1_EADDR in FMC_BK0WP0/FMC_BK0WP1/FMC_BK1WP0/FMC_BK1WP1 */

#define MAIN_FLASH_BASE_ADDRESS               ((uint32_t)0x08000000U)                           /*!< main flash base address */
#define MAIN_FLASH_SIZE                       ((uint16_t)REG32(0x1FFFB3E0U))                    /*!< main flash size */
#define MAIN_FLASH_BANK_SIZE                  (MAIN_FLASH_SIZE >> 1)                            /*!< main flash bank size */
#define MAIN_FLASH_PAGE_SIZE_DBANK            ((uint32_t)0x00000400U)                           /*!< main flash page size for dual bank mode */
#define MAIN_FLASH_PAGE_SIZE_SBANK            ((uint32_t)0x00000800U)                           /*!< main flash page size for single bank mode */
#define FMC_TIMEOUT_COUNT                     ((uint32_t)0xFFFFFFFFU)                           /*!< count to judge FMC timeout */

#define INVLD_AREA_ADDRESS                    ((uint32_t)0x00000000U)                           /*!< the area address is invalid */
#define VLD_AREA_ADDRESS                      ((uint32_t)0x00000001U)                           /*!< the area address is valid */
#define INVLD_AREA_SIZE                       ((uint32_t)0x00000000U)                           /*!< the area size is invalid */
#define VLD_AREA_SIZE                         ((uint32_t)0x00000001U)                           /*!< the area size is valid */

/* DCRP area definition */
#define DCRP_AREA0                            ((uint32_t)0x00000000U)                           /*!< the DCRP area of bank0 when DBS=1 or the first area of whole memory when DBS=0 */
#define DCRP_AREA1                            ((uint32_t)0x00000001U)                           /*!< the DCRP area of bank1 when DBS=1 or the first area of whole memory when DBS=0 */
/* write protection area definition */
#define BK0WP_AREA0                           ((uint32_t)0x00000000U)                           /*!< the first area of bank0 when DBS=1 or the first area of whole memory when DBS=0 */
#define BK0WP_AREA1                           ((uint32_t)0x00000001U)                           /*!< the second area of bank0 when DBS=1 or the second area of whole memory when DBS=0 */
#define BK1WP_AREA0                           ((uint32_t)0x00000002U)                           /*!< the first area of bank1 when DBS=1 or the third area of whole memory when DBS=0 */
#define BK1WP_AREA1                           ((uint32_t)0x00000003U)                           /*!< the second area of bank1 when DBS=1 or the fourth area of whole memory when DBS=0 */
/* secure area definition */
#define SCR_AREA0                             ((uint32_t)0x00000000U)                           /*!< the secure area of bank0 */
#define SCR_AREA1                             ((uint32_t)0x00000001U)                           /*!< the secure area of bank1 */
/* bank definition */
#define FMC_BANK0                             ((uint32_t)0x00000000U)                           /*!< FMC bank0 */
#define FMC_BANK1                             ((uint32_t)0x00000001U)                           /*!< FMC bank1 */

/* constants definitions */
/* fmc state */
typedef enum
{
    FMC_READY = 0,                                                                              /*!< the operation has been completed */
    FMC_BUSY,                                                                                   /*!< the operation is in progress */
    FMC_OBERR,                                                                                  /*!< option byte read error */
    FMC_RPERR,                                                                                  /*!< read protection error */
    FMC_PGSERR,                                                                                 /*!< program sequence error */
    FMC_PGMERR,                                                                                 /*!< program size error*/
    FMC_PGAERR,                                                                                 /*!< program alignment error */
    FMC_WPERR,                                                                                  /*!< erase/program protection error */
    FMC_PGERR,                                                                                  /*!< program error */
    FMC_OPRERR,                                                                                 /*!< operation error */
    FMC_TOERR,                                                                                  /*!< timeout error */
    FMC_OB_HSPC,                                                                                /*!< high security protection */
    FMC_OB_LSPC,                                                                                /*!< low security protection */
}fmc_state_enum;

/* function declarations */
/* FMC main flash operation functions */
/* unlock the main FMC operation */
void fmc_unlock(void);
/* lock the main FMC operation */
void fmc_lock(void);
/* set the wait state */
void fmc_wscnt_set(uint32_t wscnt);
/* enable pre-fetch */
void fmc_prefetch_enable(void);
/* disable pre-fetch */
void fmc_prefetch_disable(void);
/* enable IBUS cache */
void fmc_icache_enable(void);
/* disable IBUS cache */
void fmc_icache_disable(void);
/* reset IBUS cache  */
void fmc_icache_reset(void);
/* enable DBUS cache */
void fmc_dcache_enable(void);
/* disable DBUS cache */
void fmc_dcache_disable(void);
/* reset DBUS cache */
void fmc_dcache_reset(void);
/* erase page */
fmc_state_enum fmc_page_erase(uint32_t bank, uint32_t page_number_in_bank);
/* erase bank0 */
fmc_state_enum fmc_bank0_erase(void);
/* erase bank1 */
fmc_state_enum fmc_bank1_erase(void);
/* erase whole chip */
fmc_state_enum fmc_mass_erase(void);
/* program a doubleword at the given address */
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data);
/* get base address of bank0 */
uint32_t fmc_bank0_base_address_get(void);
/* get base address of bank1 */
uint32_t fmc_bank1_base_address_get(void);
/* get page size */
uint32_t fmc_page_size_get(void);
/* enable debugger */
void fmc_debugger_enable(void);
/* disable debugger */
void fmc_debugger_disable(void);
/* flash enter power down mode when MCU enter sleep mode */
void fmc_slp_pd_mode_enable(void);
/* flash exit power down mode when MCU enter sleep mode  */
void fmc_slp_pd_mode_disable(void);
/* enable secure area protection */
void fmc_scr_area_enable(uint32_t scr_area);

/* FMC option bytes operation functions */
/* unlock the option bytes operation */
void ob_unlock(void);
/* lock the option bytes operation */
void ob_lock(void);
/* reload the option bytes operation */
void ob_reload(void);
/* program option bytes USER */
fmc_state_enum ob_user_write(uint32_t ob_user, uint32_t ob_user_mask);
/* configure the option byte security protection */
fmc_state_enum ob_security_protection_config(uint8_t ob_spc);
/* configure the option bytes DCRP area */
fmc_state_enum ob_dcrp_config(uint32_t dcrp_area, uint32_t dcrp_eren, uint32_t dcrp_start_addr, uint32_t dcrp_end_addr);
/* configure the option bytes write protection area */
fmc_state_enum ob_write_protection_config(uint32_t wp_area, uint32_t wp_start, uint32_t wp_end);
/* configure the option bytes secure area */
fmc_state_enum ob_scr_area_config(uint32_t scr_area, uint32_t secure_size);
/* configure the option byte boot lock */
fmc_state_enum ob_boot_lock_config(uint32_t boot_config);
/* configure FMC memory mapping swap bit */
fmc_state_enum ob_bank_memory_swap_config(uint32_t swp_config);
/* get the value of option bytes USER */
uint32_t ob_user_get(void);
/* get option byte BOR threshold value */
uint32_t ob_bor_threshold_get(void);
/* get the value of option bytes security protection level in FMC_OBCTL register */
uint8_t ob_security_protection_level_get(void);
/* get DCRP area configuration */
uint32_t ob_dcrp_area_get(uint32_t dcrp_area, uint32_t *dcrp_erase_option, uint32_t *dcrp_area_start_addr, uint32_t *dcrp_area_end_addr);
/* get the value of option bytes write protection */
uint32_t ob_write_protection_get(uint32_t wp_area, uint32_t *wp_area_start_addr, uint32_t *wp_area_end_addr);
/* get size of secure area */
uint32_t ob_scr_area_size_get(uint32_t scr_area, uint32_t *scr_area_byte_cnt);
/* get boot configuration */
uint32_t ob_boot_config_get(void);
    
/* FMC interrupts and flags management functions */
/* get ECC flag status */
FlagStatus fmc_ecc_flag_get(uint32_t flag);
/* clear ECC flag status */
void fmc_ecc_flag_clear(uint32_t flag);
/* enable ECCCOR interrupt */
void fmc_ecccor_interrupt_enable(void);
/* disable ECCCOR interrupt */
void fmc_ecccor_interrupt_disable(void);
/* get ECCCOR interrupt flag */
FlagStatus fmc_ecccor_interrupt_flag_get(uint32_t flag);
/* clear ECCCOR interrupt flag */
void fmc_ecccor_interrupt_flag_clear(uint32_t flag);
/* get FMC flag status */
FlagStatus fmc_flag_get(uint32_t flag);
/* clear the FMC flag */
void fmc_flag_clear(uint32_t flag);
/* enable FMC interrupt */
void fmc_interrupt_enable(uint32_t interrupt);
/* disable FMC interrupt */
void fmc_interrupt_disable(uint32_t interrupt);
/* get FMC interrupt flag */
FlagStatus fmc_interrupt_flag_get(uint32_t flag);
/* clear FMC interrupt flag */
void fmc_interrupt_flag_clear(uint32_t flag);

#endif /* GD32G5X3_FMC_H */
