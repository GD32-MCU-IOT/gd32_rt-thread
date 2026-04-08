/*!
    \file    gd32m53x_fmc.h
    \brief   definitions for the FMC

    \version 2026-03-04, V1.0.0, firmware for GD32M53x
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

#ifndef GD32M53X_FMC_H
#define GD32M53X_FMC_H

#include "gd32m53x.h"

/* FMC and option bytes definition */
#define FMC                        FMC_BASE                       /*!< FMC register base address */
#define OB                         OB_BASE                        /*!< option bytes base address */

/* registers definitions */
#define FMC_WS                     REG32((FMC) + 0x00000000U)     /*!< FMC wait state register */
#define FMC_KEY                    REG32((FMC) + 0x00000004U)     /*!< FMC unlock key register */
#define FMC_OBKEY                  REG32((FMC) + 0x00000008U)     /*!< FMC option bytes unlock key register */
#define FMC_STAT                   REG32((FMC) + 0x0000000CU)     /*!< FMC status register */
#define FMC_CTL                    REG32((FMC) + 0x00000010U)     /*!< FMC control register */
#define FMC_ADDR                   REG32((FMC) + 0x00000014U)     /*!< FMC address register */
#define FMC_DATA                   REG32((FMC) + 0x00000018U)     /*!< FMC program data register */
#define FMC_ECCCS                  REG32((FMC) + 0x00000034U)     /*!< FMC ECC control and status register  */
#define FMC_OBSTAT                 REG32((FMC) + 0x00000038U)     /*!< FMC option bytes status register */
#define FMC_WP                     REG32((FMC) + 0x0000003CU)     /*!< FMC erase/program protection register */
#define FMC_PID0                   REG32((FMC) + 0x00000100U)     /*!< FMC product ID register 0 */
#define FMC_PID1                   REG32((FMC) + 0x00000104U)     /*!< FMC product ID register 1 */

#define OP_BYTE(x)                 REG32((OB) + ((uint32_t)((uint32_t)0x04U * (x))))     /*!< option byte value */
#define OB_SPC_USER                REG32((OB) + 0x00000000U)      /*!< option byte security protection value and user value */
#define OB_DATA                    REG32((OB) + 0x00000004U)      /*!< option byte data value*/
#define OB_WP0                     REG32((OB) + 0x00000008U)      /*!< option bytes write protection value 0 */
#define OB_WP1                     REG32((OB) + 0x0000000CU)      /*!< option bytes write protection value 1 */
#define OB_USER1_WWDGT0            REG32((OB) + 0x00000010U)      /*!< option bytes USER1 and WWDGTT0 */
#define OB_WWDGT1_WWDGT2           REG32((OB) + 0x00000014U)      /*!< option bytes WWDGT1 and WWDGT2 */
#define OB_FWDGT0_FWDGT1           REG32((OB) + 0x00000018U)      /*!< option bytes FWDGT0 and FWDGT1 */
#define OB_FWDGT2_FWDGT3           REG32((OB) + 0x0000001CU)      /*!< option bytes FWDGT2 and FWDGT3 */

/* bits definitions */
/* FMC_WS */
#define FMC_WS_WSCNT               BITS(0,2)                      /*!< wait state counter */
#define FMC_WS_PFEN                BIT(4)                         /*!< pre-fetch enable */
#define FMC_WS_ICEN                BIT(9)                         /*!< IBUS cache enable */
#define FMC_WS_DCEN                BIT(10)                        /*!< DBUS cache enable */
#define FMC_WS_ICRST               BIT(11)                        /*!< IBUS cache reset */
#define FMC_WS_DCRST               BIT(12)                        /*!< DBUS cache reset */

/* FMC_KEY */
#define FMC_KEY_KEY                BITS(0,31)                     /*!< FMC_CTL unlock key0 bits */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY            BITS(0,31)                     /*!< option bytes unlock key bits */

/* FMC_STAT */
#define FMC_STAT_BUSY             BIT(0)                         /*!< flash busy flag bit */
#define FMC_STAT_PGSERR           BIT(1)                         /*!< flash program sequence error flag bit */
#define FMC_STAT_PGERR            BIT(2)                         /*!< flash program error flag bit */
#define FMC_STAT_PGAERR           BIT(3)                         /*!< flash program alignment error flag bit */
#define FMC_STAT_WPERR            BIT(4)                         /*!< erase/program protection error flag bit */
#define FMC_STAT_ENDF             BIT(5)                         /*!< end of operation flag bit */
#define FMC_STAT_CBCMDERR         BIT(6)                         /*!< The checked area by the check blank command is all 0xFF or not */

/* FMC_CTL */
#define FMC_CTL_PG                BIT(0)                         /*!< main flash program command bit */
#define FMC_CTL_PER               BIT(1)                         /*!< main flash page erase command bit */
#define FMC_CTL_MER               BIT(2)                         /*!< main flash mass erase command bit */
#define FMC_CTL_OBPG              BIT(4)                         /*!< option bytes program command bit */
#define FMC_CTL_OBER              BIT(5)                         /*!< option bytes erase command bit */
#define FMC_CTL_START             BIT(6)                         /*!< send erase command to FMC bit */
#define FMC_CTL_LK                BIT(7)                         /*!< FMC_CTL lock bit */
#define FMC_CTL_FSTPG             BIT(8)                         /*!< main flash fast program command bit */
#define FMC_CTL_OBWEN             BIT(9)                         /*!< option bytes erase/program enable bit */
#define FMC_CTL_ERRIE             BIT(10)                        /*!< error interrupt enable bit */
#define FMC_CTL_ENDIE             BIT(12)                        /*!< end of operation interrupt enable bit */
#define FMC_CTL_BKSEL             BIT(15)                        /*!< MER/PER/FSTPG for main flash or data flash */
#define FMC_CTL_CBCMD             BIT(16)                        /*!< the command to check the selected area is blank or not */
#define FMC_CTL_OBRLD             BIT(17)                        /*!< reload option byte and generate system reset */
#define FMC_CTL_CBCMDLEN          BITS(29,31)                    /*!< CBCMD read length 2^(CBCMDLEN) */

/* FMC_ADDR */
#define FMC_ADDR_ADDR             BITS(0,31)                     /*!< flash erase/program command address bits */

/* FMC_DATA */
#define FMC_DATA_DATA             BITS(0,31)                     /*!< flash erase/program command DATA bits */

/* FMC_ECCCS */
#define FMC_ECCCS_ECCCOR           BIT(0)                         /*!< one bit error detected and correct flag */
#define FMC_ECCCS_ECCDET           BIT(1)                         /*!< two bit errors detect flag */
#define FMC_ECCCS_SYS_ECC          BIT(2)                         /*!< system memory flash read ECC error */
#define FMC_ECCCS_MF_ECC           BIT(3)                         /*!< main flash read ECC error */
#define FMC_ECCCS_OTP_ECC          BIT(4)                         /*!< OTP read ECC error */
#define FMC_ECCCS_OB_ECC           BIT(5)                         /*!< OPT read ECC error */
#define FMC_ECCCS_DF_ECC           BIT(6)                         /*!< data flash read ECC error */
#define FMC_ECCCS_SYSECCBK         BIT(7)                         /*!< ECC error in the first 3K or later 3K region of the information block */
#define FMC_ECCCS_ECCDETIE         BIT(14)                        /*!< two bit errors detect interrupt enable */
#define FMC_ECCCS_ECCCORIE         BIT(15)                        /*!< one bit error detected and correct interrupt enable */
#define FMC_ECCCS_ECCADDR          BITS(16,31)                    /*!< ECC error address offset */

/* FMC_OBSTAT */
#define FMC_OBSTAT_OBERR           BIT(0)                         /*!< option bytes read error bit. */
#define FMC_OBSTAT_SPC             BIT(1)                         /*!< option bytes security protection bit */
#define FMC_OBSTAT_USER            BITS(2,9)                      /*!< store USER of option bytes block after system reset */
#define FMC_OBSTAT_DATA            BITS(10,25)                    /*!< store DATA of option bytes block after system reset. */

/* FMC_WP */
#define FMC_WP_WP                  BITS(0,31)                     /*!< store WP of option bytes block after system reset */

/* FMC_PID */
#define FMC_PID0_PID               BITS(0,31)                     /*!< product ID 0 */
#define FMC_PID1_PID               BITS(0,31)                     /*!< product ID 1 */

/* constants definitions */
/* option byte USER*/
typedef struct {
    uint8_t nfwdg_hw;                                             /*!< nFWDG_HW option byte USER */
    uint8_t nrst_dpslp;                                           /*!< nRST_DPSLP of option byte USER */
    uint8_t nrst_stdby;                                           /*!< nRST_STDBY of option byte USER */
    uint8_t lvd0en;                                               /*!< LVD0EN of option byte USER */
    uint8_t fwdgspd_dpslp;                                        /*!< FWDGSPD_DPSLP of option byte USER */
    uint8_t fwdgspd_stdby;                                        /*!< FWDGSPD_STDBY of option byte USER */
    uint8_t lvd0t;                                                /*!< LVD0T of option byte USER */
} optionbyte_user_struct;

/* option byte WWDGT_0*/
typedef struct {
    uint8_t psc;                                                  /*!< PSC of option byte WWDGT0 */
    uint8_t wsps;                                                 /*!< WSPS of option byte WWDGT0 */
    uint8_t weps;                                                 /*!< WEPS of option byte WWDGT0 */
    uint8_t ewie;                                                 /*!< EWIE of option byte WWDGT0 */
    uint8_t wdga;                                                 /*!< WDGA of option byte WWDGT0 */
} optionbyte_wwdgt0_struct;

/* fmc state enumeration */
typedef enum {
    FMC_READY = 0U,                                               /*!< the operation has been completed */
    FMC_BUSY,                                                     /*!< the operation is in progress */
    FMC_PGSERR,                                                   /*!< program sequence error */
    FMC_PGERR,                                                    /*!< program error */
    FMC_PGAERR,                                                   /*!< program alignment error */
    FMC_WPERR,                                                    /*!< erase/program protection error */
    FMC_TOERR,                                                    /*!< timeout error */
    FMC_CBCMDERR,                                                 /*!< the checked area not blank error */
    FMC_OB_HSPC                                                   /*!< high security protection */
} fmc_state_enum;

/* FMC erase/program protection enumeration */
typedef enum {
    OB_WP_NONE = ((uint32_t)0x00000000U),                         /*!< disable all erase/program protection */
    OB_WP_0    = ((uint32_t)0x00000001U),                         /*!< erase/program protection of main flash page 0 ~ 7 */
    OB_WP_1    = ((uint32_t)0x00000002U),                         /*!< erase/program protection of main flash page 8 ~ 15 */
    OB_WP_2    = ((uint32_t)0x00000004U),                         /*!< erase/program protection of main flash page 16 ~23 */
    OB_WP_3    = ((uint32_t)0x00000008U),                         /*!< erase/program protection of main flash page 24 ~ 31 */
    OB_WP_4    = ((uint32_t)0x00000010U),                         /*!< erase/program protection of main flash page 32 ~ 39 */
    OB_WP_5    = ((uint32_t)0x00000020U),                         /*!< erase/program protection of main flash page 40 ~ 47 */
    OB_WP_6    = ((uint32_t)0x00000040U),                         /*!< erase/program protection of main flash page 48 ~ 55 */
    OB_WP_7    = ((uint32_t)0x00000080U),                         /*!< erase/program protection of main flash page 56 ~ 63 */
    OB_WP_8    = ((uint32_t)0x00000100U),                         /*!< erase/program protection of main flash page 64 ~ 71 */
    OB_WP_9    = ((uint32_t)0x00000200U),                         /*!< erase/program protection of main flash page 72 ~ 79 */
    OB_WP_10   = ((uint32_t)0x00000400U),                         /*!< erase/program protection of main flash page 80 ~ 87 */
    OB_WP_11   = ((uint32_t)0x00000800U),                         /*!< erase/program protection of main flash page 88 ~ 95 */
    OB_WP_12   = ((uint32_t)0x00001000U),                         /*!< erase/program protection of main flash page 96 ~ 103 */
    OB_WP_13   = ((uint32_t)0x00002000U),                         /*!< erase/program protection of main flash page 104 ~ 111 */
    OB_WP_14   = ((uint32_t)0x00004000U),                         /*!< erase/program protection of main flash page 112 ~ 119 */
    OB_WP_15   = ((uint32_t)0x00008000U),                         /*!< erase/program protection of main flash page 120 ~ 127 */
    OB_WP_16   = ((uint32_t)0x00010000U),                         /*!< erase/program protection of main flash page 128 ~ 135 */
    OB_WP_17   = ((uint32_t)0x00020000U),                         /*!< erase/program protection of main flash page 136 ~ 143 */
    OB_WP_18   = ((uint32_t)0x00040000U),                         /*!< erase/program protection of main flash page 144 ~ 151 */
    OB_WP_19   = ((uint32_t)0x00080000U),                         /*!< erase/program protection of main flash page 152 ~ 159 */
    OB_WP_20   = ((uint32_t)0x00100000U),                         /*!< erase/program protection of main flash page 160 ~ 167 */
    OB_WP_21   = ((uint32_t)0x00200000U),                         /*!< erase/program protection of main flash page 168 ~ 175 */
    OB_WP_22   = ((uint32_t)0x00400000U),                         /*!< erase/program protection of main flash page 176 ~ 183 */
    OB_WP_23   = ((uint32_t)0x00800000U),                         /*!< erase/program protection of main flash page 184 ~ 256 */
    OB_WP_24   = ((uint32_t)0x01000000U),                         /*!< erase/program protection of data flash page 0 ~ 7 */
    OB_WP_25   = ((uint32_t)0x02000000U),                         /*!< erase/program protection of data flash page 8 ~ 15 */
    OB_WP_26   = ((uint32_t)0x04000000U),                         /*!< erase/program protection of data flash page 16 ~23 */
    OB_WP_27   = ((uint32_t)0x08000000U),                         /*!< erase/program protection of data flash page 24 ~ 31 */
    OB_WP_28   = ((uint32_t)0x10000000U),                         /*!< erase/program protection of data flash page 32 ~ 39 */
    OB_WP_29   = ((uint32_t)0x20000000U),                         /*!< erase/program protection of data flash page 40 ~ 47 */
    OB_WP_30   = ((uint32_t)0x40000000U),                         /*!< erase/program protection of data flash page 48 ~ 55 */
    OB_WP_31   = ((uint32_t)0x80000000U),                         /*!< erase/program protection of data flash page 56 ~ 63 */
    OB_WP_ALL = ((uint32_t)0xFFFFFFFFU)                           /*!< erase/program protection of all pages */
} fmc_ob_wp_enum;

/* define the FMC bit position and its register index offset */
#define FMC_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define FMC_REG_VAL(offset)             (REG32(FMC + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define FMC_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)
#define FMC_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                             | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define FMC_REG_VAL2(offset)            (REG32(FMC + ((uint32_t)(offset) >> 22)))
#define FMC_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define FMC_STAT_REG_OFFSET            ((uint32_t)0x0000000CU)                  /*!< STAT0 register offset */
#define FMC_CTL_REG_OFFSET             ((uint32_t)0x00000010U)                  /*!< CTL0 register offset */
#define FMC_ECCCS_REG_OFFSET           ((uint32_t)0x00000034U)                  /*!< ECCCS register offset */
#define FMC_OBSTAT_REG_OFFSET          ((uint32_t)0x00000038U)                  /*!< OBSTAT register offset */

/* FMC flags */
typedef enum {
    /* flags in STAT register */
    FMC_FLAG_BUSY = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 0U),                    /*!< flash busy flag */
    FMC_FLAG_PGSERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 1U),                  /*!< flash program sequence error flag */
    FMC_FLAG_PGERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 2U),                   /*!< flash program error flag */
    FMC_FLAG_PGAERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 3U),                  /*!< flash program alignment error flag */
    FMC_FLAG_WPERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 4U),                   /*!< flash erase/program protection error flag */
    FMC_FLAG_END = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 5U),                     /*!< flash end of operation flag */
    FMC_FLAG_CBCMDERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 6U),                /*!< flash checked area by the check blank command is all 0xFF or not flag */
    /* flags in ECCCS register */
    FMC_FLAG_ECCCOR = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 0U),                 /*!< single bit ECC error flag */
    FMC_FLAG_ECCDET = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 1U),                 /*!< double bit ECC error flag */
    FMC_FLAG_SYSECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 2U),                 /*!< system memory flash read ECC error flag */
    FMC_FLAG_MFECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 3U),                  /*!< main flash read ECC error flag */
    FMC_FLAG_OTPECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 4U),                 /*!< OTP read ECC error flag */
    FMC_FLAG_OBECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 5U),                  /*!< OPT read ECC error flag */
    FMC_FLAG_DFECC = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 6U),                  /*!< data flash read ECC error status */
    FMC_FLAG_SYSECCBK = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 7U),               /*!<  ECC error in the first 3K or later 3K region of the information block */
    /* flags in OBSTAT register */
    FMC_FLAG_OBERR = FMC_REGIDX_BIT(FMC_OBSTAT_REG_OFFSET, 0U)                  /*!< option bytes read error flag */
} fmc_flag_enum;

/* FMC interrupt flags */
typedef enum {
    /* interrupt flags in STAT0 register */
    FMC_INT_FLAG_PGSERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 10U, FMC_STAT_REG_OFFSET, 1U),        /*!< flash program sequence error interrupt flag */
    FMC_INT_FLAG_PGERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 10U, FMC_STAT_REG_OFFSET, 2U),         /*!< flash program error interrupt flag */
    FMC_INT_FLAG_PGAERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 10U, FMC_STAT_REG_OFFSET, 3U),        /*!< flash program alignment error interrupt flag */
    FMC_INT_FLAG_WPERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 10U, FMC_STAT_REG_OFFSET, 4U),         /*!< flash erase/program protection error interrupt flag */
    FMC_INT_FLAG_END = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 12U, FMC_STAT_REG_OFFSET, 5U),           /*!< flash end of operation interrupt flag */
    FMC_INT_FLAG_CBCMDERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 10U, FMC_STAT_REG_OFFSET, 6U),      /*!< flash checked area by the check blank command is all 0xFF or not interrupt flag */
    /* interrupt flags in ECCCS register */
    FMC_INT_FLAG_ECCCOR = FMC_REGIDX_BIT2(FMC_ECCCS_REG_OFFSET, 15U, FMC_ECCCS_REG_OFFSET, 0U),     /*!< single bit ECC error interrupt flag */
    FMC_INT_FLAG_ECCDET = FMC_REGIDX_BIT2(FMC_ECCCS_REG_OFFSET, 14U, FMC_ECCCS_REG_OFFSET, 1U)      /*!< double bit ECC error interrupt flag */
} fmc_interrupt_flag_enum;

/* FMC interrupt */
typedef enum {
    /* interrupt in CTL0 register */
    FMC_INT_ERR = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 10U),                       /*!< FMC flash error interrupt */
    FMC_INT_END = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 12U),                       /*!< FMC flash end of operation interrupt */
    /* interrupt in ECCCS register */
    FMC_INT_ECCDET = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 14U),                  /*!< FMC double ECC error interrupt */
    FMC_INT_ECCCOR = FMC_REGIDX_BIT(FMC_ECCCS_REG_OFFSET, 15U)                   /*!< FMC single ECC error interrupt */
} fmc_interrupt_enum;

/* unlock key */
#define UNLOCK_KEY0                ((uint32_t)0x45670123U)        /*!< unlock key 0 */
#define UNLOCK_KEY1                ((uint32_t)0xCDEF89ABU)        /*!< unlock key 1 */

/* FMC wait state counter */
#define WS_WSCNT(regval)           (BITS(0,2) & ((uint32_t)(regval)))
#define FMC_WAIT_STATE_0           WS_WSCNT(0)                    /*!< FMC 0 wait state */
#define FMC_WAIT_STATE_1           WS_WSCNT(1)                    /*!< FMC 1 wait state */
#define FMC_WAIT_STATE_2           WS_WSCNT(2)                    /*!< FMC 2 wait state */
#define FMC_WAIT_STATE_3           WS_WSCNT(3)                    /*!< FMC 3 wait state */
#define FMC_WAIT_STATE_4           WS_WSCNT(4)                    /*!< FMC 4 wait state */
#define FMC_WAIT_STATE_5           WS_WSCNT(5)                    /*!< FMC 5 wait state */
#define FMC_WAIT_STATE_6           WS_WSCNT(6)                    /*!< FMC 6 wait state */

/* read protect configure */
#define FMC_NSPC                   ((uint8_t)0xA5U)               /*!< no security protection */
#define FMC_LSPC                   ((uint8_t)0xBBU)               /*!< low security protection */
#define FMC_HSPC                   ((uint8_t)0xCCU)               /*!< high security protection */

/* option bytes software/hardware free watch dog timer */
#define OB_FWDGT_HW                ((uint8_t)0x00U)               /*!< hardware free watchdog */
#define OB_FWDGT_SW                ((uint8_t)0x01U)               /*!< software free watchdog */

/* option bytes reset or not entering deep-sleep mode */
#define OB_DEEPSLEEP_RST           ((uint8_t)0x00U)               /*!< generate a reset instead of entering deepsleep mode */
#define OB_DEEPSLEEP_NRST          ((uint8_t)0x02U)               /*!< no reset when entering deepsleep mode */

/* option bytes reset or not entering standby mode */
#define OB_STDBY_RST               ((uint8_t)0x00U)               /*!< generate a reset instead of entering standby mode */
#define OB_STDBY_NRST              ((uint8_t)0x04U)               /*!< no reset when entering standby mode */

/* option bytes voltage monitoring 0 enabled or not after a reset */
#define OB_LVDOEN_ENABLE           ((uint8_t)0x00U)               /*!< voltage monitoring 0 reset is enabled after a reset */
#define OB_LVDOEN_DISABLE          ((uint8_t)0x08U)               /*!< voltage monitoring 0 reset is disabled after a reset */

/* option bytes fwdgt deepsleep */
#define OB_FWDGDPSLP_ENABLE        ((uint8_t)0x00U)               /*!< fwdgt deepsleep */
#define OB_FWDGDPSLP_DISABLE       ((uint8_t)0x10U)               /*!< fwdgt deepsleep */

/* option bytes fwdgt standby */
#define OB_FWDGSTANDBY_ENABLE      ((uint8_t)0x00U)               /*!< fwdgt standby */
#define OB_FWDGSTANDBY_DISABLE     ((uint8_t)0x20U)               /*!< fwdgt standby */

/* option bytes lvd0t value */
#define OB_LVD0T_VALUE2            ((uint8_t)0x80U)               /*!< 2.90V/2.82V(raising/falling) */
#define OB_LVD0T_VALUE3            ((uint8_t)0xC0U)               /*!< 4.31V/4.23V(raising/falling) */

/* option bytes software/hardware window watchdog timer */
#define OB_WWDGT_HW                ((uint8_t)0x00U)               /*!< hardware window watchdog */
#define OB_WWDGT_SW                ((uint8_t)0x01U)               /*!< software window watchdog */

/* option bytes sram ecc check */
#define OB_SRAMECC_DISABLE         ((uint8_t)0x00U)               /*!< sram ecc disable */
#define OB_SRAMECC_ENABLE          ((uint8_t)0x02U)               /*!< sram ecc ensable */

/* option bytes SWD */
#define OB_SWD_DISABLE             ((uint8_t)0x00U)               /*!< swd mode disable */
#define OB_SWD_ENABLE              ((uint8_t)0x04U)               /*!< swd mode ensable */

/* option bytes nrst mode */
#define OB_NRST_MODE_VALUE1        ((uint8_t)0x00U)               /*!< nrst mode = 1 */
#define OB_NRST_MODE_VALUE2        ((uint8_t)0x40U)               /*!< nrst mode = 2 */
#define OB_NRST_MODE_VALUE3        ((uint8_t)0xC0U)               /*!< nrst mode = 3 */

/* option bytes prescaler for WWDG counter clock from option byte */
#define OB_WWDG_PSC8               ((uint8_t)0x00U)               /*!< (PCLK1 / 4096) / 8 */
#define OB_WWDG_PSC4               ((uint8_t)0x01U)               /*!< (PCLK1 / 4096) / 4 */
#define OB_WWDG_PSC2               ((uint8_t)0x02U)               /*!< (PCLK1 / 4096) / 2 */
#define OB_WWDG_PSC1               ((uint8_t)0x03U)               /*!< (PCLK1 / 4096) / 1 */

/* option bytes wwdg window start position */
#define OB_WSPS_VALUE25            ((uint8_t)0x00U)               /*!< WWDG window start position 25 */
#define OB_WSPS_VALUE50            ((uint8_t)0x04U)               /*!< WWDG window start position 50 */
#define OB_WSPS_VALUE75            ((uint8_t)0x08U)               /*!< WWDG window start position 75 */
#define OB_WSPS_VALUE100           ((uint8_t)0x0CU)               /*!< WWDG window start position 100 */

/* option bytes wwdg window end position */
#define OB_WEPS_VALUE75            ((uint8_t)0x00U)               /*!< WWDG window end position 75 */
#define OB_WEPS_VALUE50            ((uint8_t)0x10U)               /*!< WWDG window end position 50 */
#define OB_WEPS_VALUE25            ((uint8_t)0x20U)               /*!< WWDG window end position 25 */
#define OB_WEPS_VALUE0             ((uint8_t)0x30U)               /*!< WWDG window end position 0 */

/* option bytes early wakeup interrupt */
#define OB_EWIE_ENABLE             ((uint8_t)0x00U)               /*!< early wakeup interrupt disable */
#define OB_EWIE_DISABLE            ((uint8_t)0x40U)               /*!< early wakeup interrupt enable */

/* option bytes wwdgt to generate a reset */
#define OB_WWDGT_RST_DISABLE       ((uint8_t)0x00U)               /*!< disable wwdgt to generate a reset */
#define OB_WWDGT_RST_ENABLE        ((uint8_t)0x80U)               /*!< enable wwdgt to generate a reset */

/* option bytes enable fwdgt to generate a reset */
#define OB_FWDGT_RST_DISABLE       ((uint8_t)0x00U)               /*!< disable fwdgt to generate a reset */
#define OB_FWDGT_RST_ENABLE        ((uint8_t)0x80U)               /*!< enable fwdgt to generate a reset */

/* option bytes free watchdog timer prescaler selection */
#define OB_FWDGT_PSC4              ((uint8_t)0x00U)               /*!< free watchdog timer prescaler selection 1/4 */
#define OB_FWDGT_PSC8              ((uint8_t)0x10U)               /*!< free watchdog timer prescaler selection 1/8 */
#define OB_FWDGT_PSC16             ((uint8_t)0x20U)               /*!< free watchdog timer prescaler selection 1/16 */
#define OB_FWDGT_PSC32             ((uint8_t)0x30U)               /*!< free watchdog timer prescaler selection 1/32 */
#define OB_FWDGT_PSC64             ((uint8_t)0x40U)               /*!< free watchdog timer prescaler selection 1/64 */
#define OB_FWDGT_PSC128            ((uint8_t)0x50U)               /*!< free watchdog timer prescaler selection 1/128 */
#define OB_FWDGT_PSC256            ((uint8_t)0x60U)               /*!< free watchdog timer prescaler selection 1/256 */

#define MFLASH_BASE_ADDRESS        ((uint32_t)0x08000000U)        /*!< FMC main flash base address */
#define MFLASH_SIZE                ((uint32_t)0x00040000U)        /*!< FMC main flash size */
#define DFLASH_BASE_ADDRESS        ((uint32_t)(0x08800000U)       /*!< FMC data flash base address */
#define DFLASH_SIZE                ((uint32_t)0x00010000U)        /*!< FMC data flash size */
#define FMC_TIMEOUT_COUNT          ((uint32_t)0x0FF00000U)        /*!< count to judge of FMC timeout 0x00100000U*/
#define DOUBLEWORD_CNT_IN_ROW      ((uint8_t)0x20U)               /*!< main flash double-word count in one row data */
#define DOUBLEWORD_DATA_CNT_IN_ROW ((uint8_t)0x08U)               /*!< data flash double-word count in one row data */
#define CBCMDLEN_OF_ONE_ROW_MAIN   ((uint8_t)0x04U)               /*!< main flash CBCMD read length of one row data */
#define CBCMDLEN_OF_ONE_ROW_DATA   ((uint8_t)0x02U)               /*!< data flash CBCMD read length of one row data */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check address */
#define NOT_FMC_VALID_ADDRESS(address)                            (((address) < 0x08000000U) || (((address) < 0x08800000U) && ((address) > 0x0803FFFFU)) || \
                                                                   ((address) > 0x0880FFFFU))
/* check check blank address configuration */
#define NOT_FMC_VALID_BLANK_ADDRESS_CONFIG(address, length)       ((((address)%0x400U) + ((2U << ((length) + 3U)))) > 0x400U)
/* check interface 0 address */
#define NOT_FMC_VALID_OTP_ADDRESS(address)                        (((address) < 0x1FFF7000U) || ((address) > 0x1FFF71FFU))
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* unlock the main flash and data flash operation */
void fmc_unlock(void);
/* lock the main flash and data flash operation */
void fmc_lock(void);
/* set the wait state counter value */
void fmc_wscnt_set(uint32_t wscnt);
/* enable pre-fetch */
void fmc_prefetch_enable(void);
/* disable pre-fetch */
void fmc_prefetch_disable(void);
/* enable IBUS cache */
void fmc_ibus_enable(void);
/* disable IBUS cache */
void fmc_ibus_disable(void);
/* enable DBUS cache */
void fmc_dbus_enable(void);
/* disable DBUS cache */
void fmc_dbus_disable(void);
/* reset IBUS cache enable */
void fmc_ibus_reset_enable(void);
/* reset IBUS cache disable */
void fmc_ibus_reset_disable(void);
/* reset DBUS cache enable*/
void fmc_dbus_reset_enable(void);
/* reset DBUS cache disable */
void fmc_dbus_reset_disable(void);
/* check whether flash page is blank or not by check blank command */
fmc_state_enum fmc_blank_check(uint32_t address, uint8_t length);
/* erase main flash or data flash page */
fmc_state_enum fmc_page_erase(uint32_t page_address);
/* erase main flash */
fmc_state_enum fmc_mflash_mass_erase(void);
/* erase data flash */
fmc_state_enum fmc_dflash_mass_erase(void);
/* erase whole chip */
fmc_state_enum fmc_mass_erase(void);
/* FMC program four words at the corresponding address */
fmc_state_enum fmc_fourword_program(uint32_t address, uint64_t data_l, uint64_t data_h);
/* FMC fast program one row data starting at the corresponding address */
fmc_state_enum fmc_fast_program(uint32_t address, uint64_t data[]);
/* FMC program four words at the corresponding address in otp */
fmc_state_enum fmc_otp_fourword_program(uint32_t address, uint64_t data_l, uint64_t data_h);

/* FMC option bytes programming functions */
/* unlock the option bytes operation */
void ob_unlock(void);
/* lock the option bytes operation */
void ob_lock(void);
/* reload the option byte and generate a system reset */
void ob_reset(void);
/* erase the option bytes */
fmc_state_enum ob_erase(void);
/* enable write protect */
fmc_state_enum ob_write_protection_enable(fmc_ob_wp_enum ob_wp);
/* configure the option bytes security protection */
fmc_state_enum ob_security_protection_config(uint8_t ob_spc);
/* write the FMC option bytes */
fmc_state_enum ob_user_write(optionbyte_user_struct *optionbyte_user);
/* program option bytes data */
fmc_state_enum ob_data_program(uint16_t ob_data);
/* write the FMC option bytes USER1 */
fmc_state_enum ob_user1_write(uint8_t ob_wwdg_hw, uint8_t ob_sram_ecc, uint8_t ob_swd_mode, uint8_t ob_nrst_mod);
/* write the FMC option bytes WWDGT0 */
fmc_state_enum ob_wwdgt0_write(optionbyte_wwdgt0_struct *optionbyte_wwdg0);
/* write the FMC option bytes WWDGT1 and WWDGT2 */
fmc_state_enum ob_wwdgt1_wwdgt2_write(uint16_t ob_wwdg_cnt);
/* write the FMC option bytes FWDGT0 and FWDGT1 and FWDGT2 and FWDGT3 */
fmc_state_enum ob_fwdgt_write(uint16_t ob_fwdgt_wnd, uint8_t ob_fwdgt_psc, uint8_t ob_fwdgt_rst,
                              uint16_t ob_fwdgt_reload);
/* get the FMC option bytes user */
uint8_t ob_user_get(void);
/* get OB_DATA in register FMC_OBSTAT */
uint16_t ob_data_get(void);
/* get the FMC option bytes write protection */
uint32_t ob_write_protection_get(void);
/* get option bytes security protection state */
FlagStatus ob_security_protection_flag_get(void);
/* get ecc error address */
uint16_t fmc_ecc_error_address_get(void);

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
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum int_flag);
/* clear FMC interrupt flag state */
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum int_flag);

#endif /* GD32M53X_FMC_H */
