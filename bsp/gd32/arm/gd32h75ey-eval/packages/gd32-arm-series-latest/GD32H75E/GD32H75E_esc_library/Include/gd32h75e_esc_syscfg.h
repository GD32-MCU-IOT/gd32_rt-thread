/*!
    \file    gd32h75e_esc_syscfg.h
    \brief   definitions for the ESC syscfg

    \version 2025-01-24, V1.1.0, firmware for GD32H75E
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

#include "gd32h75e.h"

#ifndef  GD32H75E_ESC_SYSCFG_H
#define  GD32H75E_ESC_SYSCFG_H

/* ESC_CCTL*/
#define ESC_CCTL_REG_BASE_ADDR              ((uint32_t)0x3300U)                                /* ESC core control register base address */

#define ESC_CCTL_DATA_OFFSET                0x00U                                              /* ESC_CCTL_DATA register offset */
#define ESC_CCTL_CMD_OFFSET                 0x04U                                              /* ESC_CCTL_CMD register offset */
#define ESC_PRAM_FIFO_DR_OFFSET             0x10U                                              /* ESC_PRAM_FIFO_DR register offset */
#define ESC_PRAM_ALR_OFFSET                 0x14U                                              /* ESC_PRAM_ALR_OFFSET register offset */
#define ESC_PRAM_CR_OFFSET                  0x18U                                              /* ESC_PRAM_CR_OFFSET register offset */
#define ESC_PRAM_FIFO_DW_OFFSET             0x20U                                              /* ESC_PRAM_FIFO_DW register offset */
#define ESC_PRAM_ALW_OFFSET                 0x24U                                              /* ESC_PRAM_ALW register offset */
#define ESC_PRAM_CW_OFFSET                  0x28U                                              /* ESC_PRAM_CW register offset */
#define ESC_OPB_CS_OFFSET                   0x30U                                              /* ESC_OPB_CS register offset */

#define PRAM_SPACE_AVBL_COUNT_MASK          0x1fU
#define IS_PRAM_SPACE_AVBL_MASK             0x01U

#define ESC_CCTL_DATA                       (ESC_CCTL_REG_BASE_ADDR+ESC_CCTL_DATA_OFFSET)      /* ESC_CCTL_DATA register */
#define ESC_CCTL_CMD                        (ESC_CCTL_REG_BASE_ADDR+ESC_CCTL_CMD_OFFSET)       /* ESC_CCTL_CMD register */
#define ESC_PRAM_FIFO_DR                    (ESC_CCTL_REG_BASE_ADDR+ESC_PRAM_FIFO_DR_OFFSET)   /* ESC_PRAM_FIFO_DR register */
#define ESC_PRAM_ALR                        (ESC_CCTL_REG_BASE_ADDR+ESC_PRAM_ALR_OFFSET)       /* ESC_PRAM_ALR register */
#define ESC_PRAM_CR                         (ESC_CCTL_REG_BASE_ADDR+ESC_PRAM_CR_OFFSET)        /* ESC_PRAM_CR register */
#define ESC_PRAM_FIFO_DW                    (ESC_CCTL_REG_BASE_ADDR+ESC_PRAM_FIFO_DW_OFFSET)   /* ESC_PRAM_FIFO_DW register */
#define ESC_PRAM_ALW                        (ESC_CCTL_REG_BASE_ADDR+ESC_PRAM_ALW_OFFSET)       /* ESC_PRAM_ALW register  */
#define ESC_PRAM_CW                         (ESC_CCTL_REG_BASE_ADDR+ESC_PRAM_CW_OFFSET)        /* ESC_PRAM_CW register */
#define ESC_OPB_CS                          (ESC_CCTL_REG_BASE_ADDR+ESC_OPB_CS_OFFSET)           /* ESC_OPB_CS register */

#define ESC_PRAM_READ_FIFO_REG              0x04U
#define ESC_PRAM_WRITE_FIFO_REG             0x20U
#define ESC_WRITE_BYTE                      0x80U
#define ESC_READ_BYTE                       0xC0U
#define ESC_CSR_BUSY                        0x80U

/* SYSCFG */
#define  ESC_SYSCFG                         ((uint32_t)0x3900U)                                /* ESC_SYSCFG register base address */

#define  ESC_SYSCFG_CFG0                    (ESC_SYSCFG + 0x00U)                               /* ESC_SYSCFG_CFG0 register */
#define  ESC_SYSCFG_CHIPID                  (ESC_SYSCFG + 0x90U)                               /* ESC_SYSCFG_CHIPID register */
#define  ESC_SYSCFG_CHIPVER                 (ESC_SYSCFG + 0x94U)                               /* ESC_SYSCFG_CHIPVER register */
#define  ESC_SYSCFG_RESERVED                (ESC_SYSCFG + 0xF0U)                               /* ESC_SYSCFG_RESERVED register */

/* ESC_CCTL_DATA */
#define ESC_CCTL_DATA_CCTL_DATA             BITS(0,31)                                         /*!< ESC CCTL data */

/* ESC_CCTL_CMD */
#define ESC_CCTL_CMD_CCTL_ADDR              BITS(0,15)                                         /*!< The addresses of ESC core registers that will be accessed */
#define ESC_CCTL_CMD_CCTL_SIZE              BITS(16,18)                                        /*!< ESC CCTL size (byte).1, 2 and 4 are valid, other values are invalid */
#define ESC_CCTL_CMD_CCTL_STOP              BIT(29)                                            /*!< Stop read operation or write operation */
#define ESC_CCTL_CMD_CCTL_RW                BIT(30)                                            /*!< Read operation or write operation */
#define ESC_CCTL_CMD_CCTL_BUSY              BIT(31)                                            /*!< CCTL Busy */

/* ESC_PRAM_FIFO_DR */
#define ESC_PRAM_FIFO_DR_DATAREAD           BITS(0,31)                                         /*!< Data read from ESC PRAM */

/* ESC_PRAM_ALR */
#define ESC_PRAM_ALR_PRAM_ADDR_READ         BITS(0,15)                                         /*!< ESC PRAM data read address */
#define ESC_PRAM_ALR_PRAM_LEN_READ          BITS(0,15)                                         /*!< Data length read from ESC PRAM in bytes */

/* ESC_PRAM_CR */
#define ESC_PRAM_CR_PRAM_VALID_DATA_READ    BIT(0)                                             /*!< PRAM valid data read */
#define ESC_PRAM_CR_PRAM_DATA_CNT_READ      BITS(8,12)                                         /*!< PRAM data read valid count */
#define ESC_PRAM_CR_PRAM_STOP_READ          BIT(30)                                            /*!< Stop PRAM read operation */
#define ESC_PRAM_CR_PRAM_BUSY_READ          BIT(31)                                            /*!< Whether the PRAM is being read */

/* ESC_PRAM_FIFO_DW */
#define ESC_PRAM_FIFO_DW_FIFO_DATA_WRITE    BITS(0,31)                                         /*!< Data write to ESC PRAM */

/* ESC_PRAM_ALW */
#define ESC_PRAM_ALW_PRAM_ADDR_WRITE        BITS(0,15)                                         /*!< ESC PRAM data write address */
#define ESC_PRAM_ALW_PRAM_LEN_WRITE         BITS(16,31)                                        /*!< Data length written to ESC PRAM in bytes */

/* ESC_PRAM_CW */
#define ESC_PRAM_CR_PRAM_VALID_DATA_WRITE   BIT(0)                                             /*!< PRAM valid data read */
#define ESC_PRAM_CR_PRAM_VALID_CNT_WRITE    BITS(8,12)                                         /*!< PRAM data read valid count */
#define ESC_PRAM_CR_PRAM_STOP_WRITE         BIT(30)                                            /*!< Stop PRAM read operation */
#define ESC_PRAM_CR_PRAM_BUSY_WRITE         BIT(31)                                            /*!< Whether the PRAM is being read */

/* ESC_OPB_CS */
#define ESC_OPB_CS_TOEN                     BIT(0)                                             /*!< Time Out enable */
#define ESC_OPB_CS_TO_CNT                   BITS(1,9)                                          /*!< Time Out counter */
#define ESC_OPB_CS_BRP                      BIT(10)                                            /*!< When busy bit is high, prevent register change */
#define ESC_OPB_CS_ESC_CCTLIVIE             BITS(22)                                           /*!< CCTL_SIZE & CCTL_ADDR Illegal value interrupt enable */
#define ESC_OPB_CS_ESC_CCTLIVF              BITS(23)                                           /*!< CCTL_SIZE & CCTL_ADDR illegal value flag */
#define ESC_OPB_CS_WEIE                     BITS(24)                                           /*!< Write error interrupt enable */
#define ESC_OPB_CS_WEF                      BITS(25)                                           /*!< Write error flag */
#define ESC_OPB_CS_TOIE                     BITS(26)                                           /*!< Timer out interrupt enable */
#define ESC_OPB_CS_TOF                      BITS(27)                                           /*!< Time out flag */
#define ESC_OPB_CS_WDLIE                    BITS(28)                                           /*!< Write data lost interrupt enable */
#define ESC_OPB_CS_WDLF                     BITS(29)                                           /*!< Write data lost flag */
#define ESC_OPB_CS_RAAIE                    BITS(30)                                           /*!< Reserved address access interrupt enable */
#define ESC_OPB_CS_RAAIF                    BITS(31)                                           /*!< Reserved address access flag */

/* SYSCFG Function*/
/* get chip id value */
uint32_t syscfg_get_chip_id(void);
/* get chip version value */
uint32_t syscfg_get_chip_version(void);

#endif /* #define GD32H75E_ESC_SYSCFG_H */