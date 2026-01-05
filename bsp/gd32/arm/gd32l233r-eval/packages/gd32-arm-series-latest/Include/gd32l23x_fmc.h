/*!
    \file    gd32l23x_fmc.h
    \brief   definitions for the FMC

    \version 2025-08-08, V2.3.0, firmware for GD32L23x, add support for GD32L235
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

#ifndef GD32L23X_FMC_H
#define GD32L23X_FMC_H

#include "gd32l23x.h"

/* FMC and option bytes definition */
#define FMC                            FMC_BASE                                         /*!< FMC base address */
#define OB                             OB_BASE                                          /*!< option bytes base address */

/* registers definitions */
#define FMC_WS                         REG32(FMC + 0x00000000U)                         /*!< FMC wait state register */
#define FMC_KEY                        REG32(FMC + 0x00000004U)                         /*!< FMC unlock key register */
#define FMC_OBKEY                      REG32(FMC + 0x00000008U)                         /*!< FMC option bytes unlock key register */
#define FMC_STAT                       REG32(FMC + 0x0000000CU)                         /*!< FMC status register */
#define FMC_CTL                        REG32(FMC + 0x00000010U)                         /*!< FMC control register */
#define FMC_ADDR                       REG32(FMC + 0x00000014U)                         /*!< FMC address register */
#ifdef GD32L235
#define FMC_ECCCS                      REG32(FMC + 0x00000018U)                         /*!< FMC ECC control and status register */
#endif /* GD32L235 */
#define FMC_OBSTAT                     REG32(FMC + 0x0000001CU)                         /*!< FMC option bytes status register */
#define FMC_WP                         REG32(FMC + 0x00000020U)                         /*!< FMC erase/program protection register */
#define FMC_SLPKEY                     REG32(FMC + 0x00000024U)                         /*!< FMC unlock flash sleep/power-down mode key register */
#define FMC_PID                        REG32(FMC + 0x00000100U)                         /*!< FMC product ID register */

#define OP_BYTE(x)                     REG32(OB + ((uint32_t)((uint32_t)0x04U * (x))))  /*!< option bytes value */
#define OB_SPC_USER                    REG32(OB + 0x00000000U)                          /*!< option bytes security protection value and user value */
#define OB_DATA                        REG32(OB + 0x00000004U)                          /*!< option bytes data value */
#define OB_WP0                         REG32(OB + 0x00000008U)                          /*!< option bytes write protection value 0 */
#define OB_WP1                         REG32(OB + 0x0000000CU)                          /*!< option bytes write protection value 1 */

/* bits definitions */
/* FMC_WS */
#define FMC_WS_WSCNT                   BITS(0,2)                                        /*!< wait state counter */
#define FMC_WS_PFEN                    BIT(4)                                           /*!< pre-fetch enable */
#ifdef GD32L233
#define FMC_WS_LVE                     BIT(7)                                           /*!< low power enable */
#define FMC_WS_RUN_SLP                 BIT(13)                                          /*!< flash enter sleep/power-down mode or idle mode during MCU run/low-power run mode */
#define FMC_WS_SLEEP_SLP               BIT(14)                                          /*!< flash enter sleep mode or power-down mode when MCU enter stop or RUN_SLP bit is set */
#endif /* GD32L233 */
#ifdef GD32L235
#define FMC_WS_RUN_SLP                 BIT(13)                                          /*!< flash enter sleep or idle mode during MCU run mode */
#define FMC_WS_SLEEP_SLP               BIT(14)                                          /*!< flash enter sleep mode or idle mode when MCU enter deep sleep or RUN_SLP bit is set */
#endif /* GD32L235 */

/* FMC_KEY */
#define FMC_KEY_KEY                    BITS(0,31)                                       /*!< FMC_CTL unlock key */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY                BITS(0,31)                                       /*!< option bytes unlock key */

/* FMC_STAT */
#define FMC_STAT_BUSY                  BIT(0)                                           /*!< flash busy flag */
#define FMC_STAT_PGERR                 BIT(2)                                           /*!< flash program error flag */
#define FMC_STAT_PGAERR                BIT(3)                                           /*!< flash program alignment error flag */
#define FMC_STAT_WPERR                 BIT(4)                                           /*!< erase/program protection error flag */
#define FMC_STAT_ENDF                  BIT(5)                                           /*!< end of operation flag */
#ifdef GD32L235
#define FMC_STAT_FSTAT                 BITS(14,15)                                      /*!< flash status */
#else
#define FMC_STAT_FSTAT                 BIT(15)                                          /*!< flash status */
#endif /* GD32L235 */

/* FMC_CTL */
#define FMC_CTL_PG                     BIT(0)                                           /*!< main flash program command */
#define FMC_CTL_PER                    BIT(1)                                           /*!< main flash page erase command */
#define FMC_CTL_MER                    BIT(2)                                           /*!< main flash mass erase command */
#define FMC_CTL_OBPG                   BIT(4)                                           /*!< option bytes program command */
#define FMC_CTL_OBER                   BIT(5)                                           /*!< option bytes erase command */
#define FMC_CTL_START                  BIT(6)                                           /*!< send erase command to FMC */
#define FMC_CTL_LK                     BIT(7)                                           /*!< FMC_CTL lock */
#define FMC_CTL_FSTPG                  BIT(8)                                           /*!< main flash fast program command */
#define FMC_CTL_OBWEN                  BIT(9)                                           /*!< option bytes erase/program enable */
#define FMC_CTL_ERRIE                  BIT(10)                                          /*!< error interrupt enable */
#define FMC_CTL_ENDIE                  BIT(12)                                          /*!< end of operation interrupt enable */

/* FMC_ADDR */
#define FMC_ADDR_ADDR                  BITS(0,31)                                       /*!< address of flash to be erased/programmed */

#ifdef GD32L235
/* FMC_ECCCS */
#define FMC_ECCCS_ECCADDR              BITS(16,31)                                      /*!< the offset address of double word where an ECC error is detected */
#define FMC_ECCCORIE                   BIT(15)                                          /*!< one bit error correctable interrupt enable bit */
#define FMC_ECCDETIE                   BIT(14)                                          /*!< two bits error detected interrupt enable bit */
#define FMC_OBECCDET                   BIT(6)                                           /*!< option bytes two bits error detected flag */
#define FMC_OB_ECC                     BIT(5)                                           /*!< ECC bit error detected in reading option bytes flag */
#define FMC_OTP_ECC                    BIT(4)                                           /*!< ECC bit error detected in OTP flag */
#define FMC_ECCCS_MF_ECC               BIT(3)                                           /*!< ECC bit error detected in main flash flag */
#define FMC_ECCCS_SYS_ECC              BIT(2)                                           /*!< ECC bit error detected in system memory flag */
#define FMC_ECCCS_ECCDET               BIT(1)                                           /*!< two bits error detected flag */
#define FMC_ECCCS_ECCCOR               BIT(0)                                           /*!< one bit error detected and correctable flag */
#endif /* GD32L235 */

/* FMC_OBSTAT */
#define FMC_OBSTAT_OBERR               BIT(0)                                           /*!< option bytes read error */
#define FMC_OBSTAT_SPC                 BIT(1)                                           /*!< option bytes security protection code */
#define FMC_OBSTAT_USER                BITS(2,9)                                        /*!< store USER of option bytes block after system reset */
#define FMC_OBSTAT_DATA                BITS(10,25)                                      /*!< store DATA of option bytes block after system reset */

/* FMC_WP */
#define FMC_WP_WP                      BITS(0,31)                                       /*!< store WP of option bytes block after system reset */

/* FMC_SLPKEY */
#define FMC_SLPKEY_KEY                 BITS(0,31)                                       /*!< unlock flash sleep/power-down mode key */

/* FMC_PID */
#define FMC_PID_PID                    BITS(0,31)                                       /*!< product ID */

/* constants definitions */
/* fmc state */
typedef enum {
    FMC_READY,                                                                          /*!< the operation has been completed */
    FMC_BUSY,                                                                           /*!< the operation is in progress */
    FMC_PGERR,                                                                          /*!< program error */
    FMC_PGAERR,                                                                         /*!< program alignment error */
    FMC_WPERR,                                                                          /*!< erase/program protection error */
    FMC_TOERR,                                                                          /*!< timeout error */
    FMC_OB_HSPC,                                                                        /*!< high security protection */
    FMC_SLP,                                                                            /*!< flash sleep or power-down */
} fmc_state_enum;

/* define the FMC bit position and its register index offset */
#define FMC_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define FMC_REG_VAL(offset)             (REG32(FMC + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define FMC_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)
#define FMC_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22U) | (uint32_t)((bitpos2) << 16U)\
                                                            | (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos)))
#define FMC_REG_VAL2(offset)            (REG32(FMC + ((uint32_t)(offset) >> 22U)))
#define FMC_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16U)

/* register offset */
#define FMC_STAT_REG_OFFSET             ((uint32_t)0x0000000CU)                         /*!< STAT register offset */
#define FMC_ECCCS_REG_OFFSET            ((uint32_t)0x00000018U)                         /*!< ECCCS register offset */
#define FMC_CTL_REG_OFFSET              ((uint32_t)0x00000010U)                         /*!< CTL register offset */
#define FMC_OBSTAT_REG_OFFSET           ((uint32_t)0x0000001CU)                         /*!< OBSTAT register offset */

/* FMC flags */
typedef enum {
    /* flags in STAT register */
    FMC_FLAG_BUSY = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 0U),                            /*!< flash busy flag */
    FMC_FLAG_PGERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 2U),                           /*!< flash program error flag */
    FMC_FLAG_PGAERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 3U),                          /*!< flash program alignment error flag */
    FMC_FLAG_WPERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 4U),                           /*!< flash erase/program protection error flag */
    FMC_FLAG_END = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 5U),                             /*!< flash end of operation flag */
#ifdef GD32L233
    FMC_FLAG_SLP = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 15U),                            /*!< flash sleep or power-down flag */
#endif /* GD32L233 */
#ifdef GD32L235
    FMC_FLAG_POWERDOWN = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 14U),                      /*!< flash power-down flag */
    FMC_FLAG_SLEEP = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 15U),                          /*!< flash sleep flag */
    /* flags in ECCCS register */
    FMC_FLAG_ECCCOR = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 0U),                         /*!< one bit error detected and correct flag */
    FMC_FLAG_ECCDET = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 1U),                         /*!< two bit error detect flag */
    FMC_FLAG_SYSECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 2U),                         /*!< an ECC error is detected in system memory flag */
    FMC_FLAG_MFECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 3U),                          /*!< an ECC error is detected in main Flash flag */
    FMC_FLAG_OTPECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 4U),                         /*!< an ECC error is detected in OTP flag */
    FMC_FLAG_OBECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 5U),                          /*!< an ECC error is detected in reading option bytes flag */
    FMC_FLAG_OBECCDET = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 6U),                       /*!< option bytes two bit error detect in loading option bytes to register flag */
#endif /* GD32L235 */
    /* flags in OBSTAT register */
    FMC_FLAG_OBERR = FMC_REGIDX_BIT(FMC_OBSTAT_REG_OFFSET, 0U),                         /*!< option bytes error flag */
} fmc_flag_enum;

/* FMC interrupt flags */
typedef enum {
    /* interrupt flags in STAT register */
    FMC_INT_FLAG_PGERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 10U, FMC_STAT_REG_OFFSET, 2U),                 /*!< flash program error interrupt flag */
    FMC_INT_FLAG_PGAERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 10U, FMC_STAT_REG_OFFSET, 3U),                /*!< flash program alignment error interrupt flag */
    FMC_INT_FLAG_WPERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 10U, FMC_STAT_REG_OFFSET, 4U),                 /*!< flash erase/program protection error interrupt flag */
    FMC_INT_FLAG_END = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 12U, FMC_STAT_REG_OFFSET, 5U),                   /*!< flash end of operation interrupt flag */
#ifdef GD32L235
    /* interrupt flags in ECCCS register */
    FMC_INT_FLAG_ECCCOR = FMC_REGIDX_BIT2(FMC_ECCCS_REG_OFFSET, 15U, FMC_ECCCS_REG_OFFSET, 0U),             /*!< one bit error detected and correct interrupt flag */
    FMC_INT_FLAG_ECCDET = FMC_REGIDX_BIT2(FMC_ECCCS_REG_OFFSET, 14U, FMC_ECCCS_REG_OFFSET, 1U),             /*!< two bits error detect interrupt flag */
    FMC_INT_FLAG_OBECCDET = FMC_REGIDX_BIT2(FMC_ECCCS_REG_OFFSET, 14U, FMC_ECCCS_REG_OFFSET, 6U),           /*!< option bytes two bit error detect in loading option bytes to register interrupt flag */
#endif /* GD32L235 */
} fmc_interrupt_flag_enum;

/* FMC interrupt enable */
typedef enum {
    /* interrupt in CTL register */
    FMC_INT_ERR = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 10U),                              /*!< FMC error interrupt */
    FMC_INT_END = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 12U),                              /*!< FMC end of operation interrupt */
#ifdef GD32L235
    /* interrupt in ECCCS register */
    FMC_INT_ECCCOR = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 15U),                         /*!< FMC one bit error correct interrupt */
    FMC_INT_ECCDET = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 14U),                         /*!< FMC two bits error interrupt */
#endif /* GD32L235 */
} fmc_interrupt_enum;

/* FMC/OB unlock key */
#define UNLOCK_KEY0                    ((uint32_t)0x45670123U)                          /*!< FMC/OB unlock key 0 */
#define UNLOCK_KEY1                    ((uint32_t)0xCDEF89ABU)                          /*!< FMC/OB unlock key 1 */

/* SLP unlock key */
#define SLP_UNLOCK_KEY0                ((uint32_t)0x04152637U)                          /*!< SLP unlock key 0 */
#define SLP_UNLOCK_KEY1                ((uint32_t)0xBCAD9E8FU)                          /*!< SLP unlock key 1 */

/* FMC wait state added */
#define WS_WSCNT(regval)               (BITS(0,2) & ((uint32_t)(regval)))
#define FMC_WAIT_STATE_0               WS_WSCNT(0)                                      /*!< 0 wait state added */
#define FMC_WAIT_STATE_1               WS_WSCNT(1)                                      /*!< 1 wait state added */
#define FMC_WAIT_STATE_2               WS_WSCNT(2)                                      /*!< 2 wait state added */
#ifdef GD32L233
#define FMC_WAIT_STATE_3               WS_WSCNT(3)                                      /*!< 3 wait state added */
#endif /* GD32L233 */

/* FMC flash status */
#define FLASH_STATUS(regval)           (BITS(14,15) & ((uint32_t)(regval) << 14U))
#define FMC_FSTAT_IDLE_MODE            FLASH_STATUS(0)                                  /*!< flash is in idle mode */
#ifdef GD32L233
#define FMC_FSTAT_SLP_PD_MODE          FLASH_STATUS(1)                                  /*!< flash is in sleep mode or power-down mode */
#endif /* GD32L233 */
#ifdef GD32L235
#define FMC_FSTAT_POWER_DOWN_MODE      FLASH_STATUS(1)                                  /*!< flash is in power-down mode */
#define FMC_FSTAT_SLEEP_MODE           FLASH_STATUS(2)                                  /*!< flash is in sleep mode */
#endif /* GD32L235 */

/* read protection configuration */
#define FMC_NSPC                       ((uint8_t)0xA5U)                                 /*!< no security protection */
#define FMC_LSPC                       ((uint8_t)0xBBU)                                 /*!< low security protection */
#define FMC_HSPC                       ((uint8_t)0xCCU)                                 /*!< high security protection */

/* option bytes software/hardware free watch dog timer */
#define OB_FWDGT_HW                    ((uint8_t)0x00U)                                 /*!< hardware free watchdog */
#define OB_FWDGT_SW                    ((uint8_t)0x01U)                                 /*!< software free watchdog */

/* option bytes reset or not entering deep sleep mode */
#define OB_DEEPSLEEP_RST               ((uint8_t)0x00U)                                 /*!< generate a reset instead of entering deepsleep mode */
#define OB_DEEPSLEEP_NRST              ((uint8_t)0x02U)                                 /*!< no reset when entering deepsleep mode */

/* option bytes reset or not entering standby mode */
#define OB_STDBY_RST                   ((uint8_t)0x00U)                                 /*!< generate a reset instead of entering standby mode */
#define OB_STDBY_NRST                  ((uint8_t)0x04U)                                 /*!< no reset when entering standby mode */

/* brownout threshold configuration */
#define OB_BOR_TH_VALUE0               ((uint8_t)0x00U)                                 /*!< brownout threshold level 0 */
#define OB_BOR_TH_VALUE1               ((uint8_t)0x20U)                                 /*!< brownout threshold level 1 */
#define OB_BOR_TH_VALUE2               ((uint8_t)0x40U)                                 /*!< brownout threshold level 2 */
#define OB_BOR_TH_VALUE3               ((uint8_t)0x60U)                                 /*!< brownout threshold level 3 */
#define OB_BOR_TH_VALUE4               ((uint8_t)0x80U)                                 /*!< brownout threshold level 4 */

#ifdef GD32L235
/* option bytes sram parity check configuration */
#define OB_SRAM_PARITY_CHECK_DISABLE   ((uint8_t)0x00U)                                 /*!< sram parity check disable */
#define OB_SRAM_PARITY_CHECK_ENABLE    ((uint8_t)0x08U)                                 /*!< sram parity check enable */
#endif /* GD32L235 */

/* option bytes write protection */
#define OB_WP_NONE                     ((uint32_t)0x00000000U)                          /*!< disable all erase/program protection */
#define OB_WP_0                        ((uint32_t)0x00000001U)                          /*!< erase/program protection of sector 0  */
#define OB_WP_1                        ((uint32_t)0x00000002U)                          /*!< erase/program protection of sector 1  */
#define OB_WP_2                        ((uint32_t)0x00000004U)                          /*!< erase/program protection of sector 2  */
#define OB_WP_3                        ((uint32_t)0x00000008U)                          /*!< erase/program protection of sector 3  */
#define OB_WP_4                        ((uint32_t)0x00000010U)                          /*!< erase/program protection of sector 4  */
#define OB_WP_5                        ((uint32_t)0x00000020U)                          /*!< erase/program protection of sector 5  */
#define OB_WP_6                        ((uint32_t)0x00000040U)                          /*!< erase/program protection of sector 6  */
#define OB_WP_7                        ((uint32_t)0x00000080U)                          /*!< erase/program protection of sector 7  */
#define OB_WP_8                        ((uint32_t)0x00000100U)                          /*!< erase/program protection of sector 8  */
#define OB_WP_9                        ((uint32_t)0x00000200U)                          /*!< erase/program protection of sector 9  */
#define OB_WP_10                       ((uint32_t)0x00000400U)                          /*!< erase/program protection of sector 10 */
#define OB_WP_11                       ((uint32_t)0x00000800U)                          /*!< erase/program protection of sector 11 */
#define OB_WP_12                       ((uint32_t)0x00001000U)                          /*!< erase/program protection of sector 12 */
#define OB_WP_13                       ((uint32_t)0x00002000U)                          /*!< erase/program protection of sector 13 */
#define OB_WP_14                       ((uint32_t)0x00004000U)                          /*!< erase/program protection of sector 14 */
#define OB_WP_15                       ((uint32_t)0x00008000U)                          /*!< erase/program protection of sector 15 */
#define OB_WP_16                       ((uint32_t)0x00010000U)                          /*!< erase/program protection of sector 16 */
#define OB_WP_17                       ((uint32_t)0x00020000U)                          /*!< erase/program protection of sector 17 */
#define OB_WP_18                       ((uint32_t)0x00040000U)                          /*!< erase/program protection of sector 18 */
#define OB_WP_19                       ((uint32_t)0x00080000U)                          /*!< erase/program protection of sector 19 */
#define OB_WP_20                       ((uint32_t)0x00100000U)                          /*!< erase/program protection of sector 20 */
#define OB_WP_21                       ((uint32_t)0x00200000U)                          /*!< erase/program protection of sector 21 */
#define OB_WP_22                       ((uint32_t)0x00400000U)                          /*!< erase/program protection of sector 22 */
#define OB_WP_23                       ((uint32_t)0x00800000U)                          /*!< erase/program protection of sector 23 */
#define OB_WP_24                       ((uint32_t)0x01000000U)                          /*!< erase/program protection of sector 24 */
#define OB_WP_25                       ((uint32_t)0x02000000U)                          /*!< erase/program protection of sector 25 */
#define OB_WP_26                       ((uint32_t)0x04000000U)                          /*!< erase/program protection of sector 26 */
#define OB_WP_27                       ((uint32_t)0x08000000U)                          /*!< erase/program protection of sector 27 */
#define OB_WP_28                       ((uint32_t)0x10000000U)                          /*!< erase/program protection of sector 28 */
#define OB_WP_29                       ((uint32_t)0x20000000U)                          /*!< erase/program protection of sector 29 */
#define OB_WP_30                       ((uint32_t)0x40000000U)                          /*!< erase/program protection of sector 30 */
#define OB_WP_31                       ((uint32_t)0x80000000U)                          /*!< erase/program protection of rest sectors */
#define OB_WP_ALL                      ((uint32_t)0xFFFFFFFFU)                          /*!< erase/program protection of all sectors */

/* FMC timeout */
#define FMC_TIMEOUT_COUNT              ((uint32_t)0x00100000U)                          /*!< FMC timeout count value */

#ifdef GD32L233
/* double-word number in one row data */
#define DOUBLE_WORDS_CNT_IN_ROW        (32U)                                            /*!< the number of fast program words */
#endif /* GD32L233 */

/* function declarations */
/* FMC main memory programming functions */
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
#ifdef GD32L233
/* enable low power */
void fmc_low_power_enable(void);
/* disable low power */
void fmc_low_power_disable(void);
#endif /* GD32L233 */
/* FMC erase page */
fmc_state_enum fmc_page_erase(uint32_t page_address);
/* FMC erase whole chip */
fmc_state_enum fmc_mass_erase(void);
#ifdef GD32L233
/* FMC program a word at the corresponding address */
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data);
/* FMC fast program a row words at the corresponding address */
fmc_state_enum fmc_fast_program(uint32_t address, uint64_t data[]);
#endif /* GD32L233 */
#ifdef GD32L235
/* FMC program a doubleword at the corresponding address */
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data);
#endif /* GD32L235 */

/* FMC option bytes programming functions */
/* unlock the option bytes operation */
void ob_unlock(void);
/* lock the option bytes operation */
void ob_lock(void);
/* erase the option bytes */
fmc_state_enum ob_erase(void);
/* enable write protection */
fmc_state_enum ob_write_protection_enable(uint32_t ob_wp);
/* configure the option bytes security protection */
fmc_state_enum ob_security_protection_config(uint8_t ob_spc);
/* program option bytes USER */
#ifdef GD32L233
fmc_state_enum ob_user_write(uint8_t ob_fwdgt, uint8_t ob_deepsleep, uint8_t ob_stdby, uint8_t ob_bor_th);
#endif /* GD32L233 */
#ifdef GD32L235
fmc_state_enum ob_user_write(uint8_t ob_fwdgt, uint8_t ob_deepsleep, uint8_t ob_stdby, uint8_t ob_bor_th,
                             uint8_t ob_sram_parity_check);
#endif /* GD32L235 */
/* program option bytes DATA */
fmc_state_enum ob_data_program(uint16_t ob_data);
/* get the value of option bytes USER */
uint8_t ob_user_get(void);
/* get the value of option bytes DATA */
uint16_t ob_data_get(void);
/* get the value of option bytes write protection */
uint32_t ob_write_protection_get(void);
/* get option bytes security protection state */
FlagStatus ob_security_protection_flag_get(void);

#ifdef GD32L235
/* get the address where ECC error occur on */
uint16_t fmc_ecc_address_get(void);
#endif /* GD32L235 */

/* FMC low power functions */
/* unlock operation of RUN_SLP bit in FMC_WS register */
void fmc_slp_unlock(void);
/* flash enter sleep mode when MCU enter deep-sleep mode or RUN_SLP bit is set */
void fmc_sleep_slp_enable(void);
/* flash enter power-down mode(GD32L233)/idle mode(GD32L235) when MCU enter deep-sleep mode or RUN_SLP bit is set */
void fmc_sleep_slp_disable(void);
/* flash enter idle mode when MCU run mode (GD32L235, together with the SLEEP_SLP bit)
/flash enter idle mode when MCU run mode or enter low-power run mode (GD32L233, together with the SLEEP_SLP bit) */
void fmc_run_slp_enable(void);
/* flash enter sleep mode when MCU run mode (GD32L235, together with the SLEEP_SLP bit)
/flash enter sleep or power-down mode when MCU run mode or enter low-power run mode (GD32L233, together with the SLEEP_SLP bit) */
void fmc_run_slp_disable(void);
/* flash enter sleep mode when MCU run mode. Please note that this function needs to run in SRAM. */
void fmc_sleep_mode_enter(void);
#ifdef GD32L233
/* flash enter power down mode when MCU run mode/low-power run mode. Please note that this function needs to run in SRAM. */
void fmc_pd_mode_enter(void);
#endif /* GD32L233 */
/* flash exit sleep or power-down mode when MCU run mode/low-power run mode(GD32L233)
flash exit sleep mode when MCU run mode mode(GD32L235). Please note that this function needs to run in SRAM. */
void fmc_slp_mode_exit(void);

/* FMC interrupts and flags management functions */
/* get FMC flag status */
FlagStatus fmc_flag_get(fmc_flag_enum flag);
/* clear the FMC flag */
void fmc_flag_clear(fmc_flag_enum flag);
/* enable FMC interrupt */
void fmc_interrupt_enable(fmc_interrupt_enum interrupt);
/* disable FMC interrupt */
void fmc_interrupt_disable(fmc_interrupt_enum interrupt);
/* get FMC interrupt flag */
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum int_flag);
/* clear FMC interrupt flag */
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum int_flag);

#endif /* GD32L23X_FMC_H */
