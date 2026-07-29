/*!
    \file    gd32f50x_exmc.h
    \brief   definitions for the EXMC

    \version 2026-02-25, V1.0.4, firmware for GD32F50x
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

#ifndef GD32F50X_EXMC_H
#define GD32F50X_EXMC_H

#include "gd32f50x.h"

/* EXMC definitions */
#define EXMC                             (EXMC_BASE)                   /*!< EXMC register base address */

/* registers definitions */
/* NOR/PSRAM register */
#define EXMC_PNCTL                       REG32(EXMC + 0x00U)           /*!< EXMC PSRAM/NOR flash control register */
#define EXMC_PNTCFG                      REG32(EXMC + 0x04U)           /*!< EXMC PSRAM/NOR flash timing configuration register */

/* NAND Flash register*/
#define EXMC_NCTL                        REG32(EXMC + 0x60U)           /*!< EXMC NAND control register */
#define EXMC_NSTAT                       REG32(EXMC + 0x64U)           /*!< EXMC NAND interrupt enable register */
#define EXMC_NCTCFG                      REG32(EXMC + 0x68U)           /*!< EXMC NAND common space timing configuration register */
#define EXMC_NATCFG                      REG32(EXMC + 0x6CU)           /*!< EXMC NAND attribute space timing configuration register */
#define EXMC_NECC                        REG32(EXMC + 0x74U)           /*!< EXMC NAND ECC register */

/* bits definitions */
/* EXMC_PNCTL*/
#define EXMC_PNCTL_NRBKEN                 BIT(0)                        /*!< NOR bank enable */
#define EXMC_PNCTL_NRMUX                  BIT(1)                        /*!< NOR bank memory address/data multiplexing enable */
#define EXMC_PNCTL_NRTP                   BITS(2,3)                     /*!< NOR bank memory type */
#define EXMC_PNCTL_NRW                    BITS(4,5)                     /*!< NOR bank memory data bus width */
#define EXMC_PNCTL_NREN                   BIT(6)                        /*!< NOR flash access enable */
#define EXMC_PNCTL_SBRSTEN                BIT(8)                        /*!< synchronous burst enable */
#define EXMC_PNCTL_NRWTPOL                BIT(9)                        /*!< NWAIT signal polarity */
#define EXMC_PNCTL_WRAPEN                 BIT(10)                       /*!< wrapped burst mode enable */
#define EXMC_PNCTL_NRWTCFG                BIT(11)                       /*!< NWAIT signal configuration, only work in synchronous mode  */
#define EXMC_PNCTL_WREN                   BIT(12)                       /*!< write enable */
#define EXMC_PNCTL_NRWTEN                 BIT(13)                       /*!< NWAIT signal enable */
#define EXMC_PNCTL_ASYNCWAIT              BIT(15)                       /*!< asynchronous wait enable */
#define EXMC_PNCTL_CPS                    BITS(16,18)                   /*!< CRAM page size */
#define EXMC_PNCTL_SYNCWR                 BIT(19)                       /*!< synchronous write config */

/* EXMC_PNTCFG */
#define EXMC_PNTCFG_ASET                  BITS(0,3)                     /*!< asynchronous address setup time */
#define EXMC_PNTCFG_AHLD                  BITS(4,7)                     /*!< asynchronous address hold time */
#define EXMC_PNTCFG_DSET                  BITS(8,15)                    /*!< asynchronous data setup time */
#define EXMC_PNTCFG_BUSLAT                BITS(16,19)                   /*!< bus latency */
#define EXMC_PNTCFG_CKDIV                 BITS(20,23)                   /*!< synchronous clock divide ratio */
#define EXMC_PNTCFG_DLAT                  BITS(24,27)                   /*!< synchronous data latency for NOR flash */

/* EXMC_NCTL */
#define EXMC_NCTL_NDWTEN                  BIT(1)                        /*!< wait feature enable */
#define EXMC_NCTL_NDBKEN                  BIT(2)                        /*!< NAND bank enable */
#define EXMC_NCTL_NDTP                    BIT(3)                        /*!< NAND bank memory type */
#define EXMC_NCTL_NDW                     BITS(4,5)                     /*!< NAND bank memory data bus width */
#define EXMC_NCTL_ECCEN                   BIT(6)                        /*!< ECC enable */
#define EXMC_NCTL_CTR                     BITS(9,12)                    /*!< CLE to RE delay */
#define EXMC_NCTL_ATR                     BITS(13,16)                   /*!< ALE to RE delay */
#define EXMC_NCTL_ECCSZ                   BITS(17,19)                   /*!< ECC size */

/* EXMC_NSTAT */
#define EXMC_NSTAT_FFEPT                  BIT(6)                        /*!< FIFO empty flag */

/* EXMC_NCTCFG*/
#define EXMC_NCTCFG_COMSET                BITS(0,7)                     /*!< common memory setup time */
#define EXMC_NCTCFG_COMWAIT               BITS(8,15)                    /*!< common memory wait time */
#define EXMC_NCTCFG_COMHLD                BITS(16,23)                   /*!< common memory hold time */
#define EXMC_NCTCFG_COMHIZ                BITS(24,31)                   /*!< common memory data bus HiZ time */

/* EXMC_NATCFG */
#define EXMC_NATCFG_ATTSET                BITS(0,7)                     /*!< attribute memory setup time */
#define EXMC_NATCFG_ATTWAIT               BITS(8,15)                    /*!< attribute memory wait time */
#define EXMC_NATCFG_ATTHLD                BITS(16,23)                   /*!< attribute memory hold time */
#define EXMC_NATCFG_ATTHIZ                BITS(24,31)                   /*!< attribute memory data bus HiZ time */

/* EXMC_NECC */
#define EXMC_NECC_ECC                     BITS(0,31)                    /*!< ECC result */

/* constants definitions */
/* EXMC NOR/SRAM timing initialize struct */
typedef struct
{
    uint32_t syn_data_latency;                                          /*!< configure the data latency */
    uint32_t syn_clk_division;                                          /*!< configure the clock divide ratio */
    uint32_t bus_latency;                                               /*!< configure the bus latency */
    uint32_t asyn_data_setuptime;                                       /*!< configure the data setup time,asynchronous access mode valid */
    uint32_t asyn_address_holdtime;                                     /*!< configure the address hold time,asynchronous access mode valid */
    uint32_t asyn_address_setuptime;                                    /*!< configure the data setup time,asynchronous access mode valid */
}exmc_norsram_timing_parameter_struct;

/* EXMC NOR/PSRAM initialize struct */
typedef struct
{
    uint32_t write_mode;                                                /*!< the write mode, synchronous mode or asynchronous mode */
    uint32_t asyn_wait;                                                 /*!< enable or disable the asynchronous wait function */
    uint32_t nwait_signal;                                              /*!< enable or disable the NWAIT signal while in synchronous bust mode */
    uint32_t memory_write;                                              /*!< enable or disable the write operation */
    uint32_t nwait_config;                                              /*!< NWAIT signal configuration */
    uint32_t wrap_burst_mode;                                           /*!< enable or disable the wrap burst mode */
    uint32_t nwait_polarity;                                            /*!< specifies the polarity of NWAIT signal from memory */
    uint32_t burst_mode;                                                /*!< enable or disable the burst mode */
    uint32_t databus_width;                                             /*!< specifies the databus width of external memory */
    uint32_t memory_type;                                               /*!< specifies the type of external memory */
    uint32_t address_data_mux;                                          /*!< specifies whether the data bus and address bus are multiplexed */
    exmc_norsram_timing_parameter_struct* read_write_timing;            /*!< timing parameters for read and write */
}exmc_norsram_parameter_struct;

/* EXMC NAND timing initialize struct */
typedef struct
{
    uint32_t databus_hiztime;                                           /*!< configure the data bus HiZ time for write operation */
    uint32_t holdtime;                                                  /*!< configure the address hold time(or the data hold time for write operation) */
    uint32_t waittime;                                                  /*!< configure the minimum wait time */
    uint32_t setuptime;                                                 /*!< configure the address setup time */
}exmc_nand_timing_parameter_struct;

/* EXMC NAND initialize struct */
typedef struct
{
    uint32_t nand_bank;                                                 /*!< select the bank of NAND */ 
    uint32_t ecc_size;                                                  /*!< the page size for the ECC calculation */
    uint32_t atr_latency;                                               /*!< configure the latency of ALE low to RB low */
    uint32_t ctr_latency;                                               /*!< configure the latency of CLE low to RB low */
    uint32_t ecc_logic;                                                 /*!< enable or disable the ECC calculation logic */
    uint32_t databus_width;                                             /*!< the NAND flash databus width */
    uint32_t wait_feature;                                              /*!< enable or disable the wait feature */
    exmc_nand_timing_parameter_struct* common_space_timing;             /*!< the timing parameters for NAND flash common space */
    exmc_nand_timing_parameter_struct* attribute_space_timing;          /*!< the timing parameters for NAND flash attribute space */
}exmc_nand_parameter_struct;

/* CRAM page size */
#define PNCTL_CPS(regval)                 (BITS(16,18) & ((uint32_t)(regval) << 16))
#define EXMC_CRAM_AUTO_SPLIT              PNCTL_CPS(0)                  /*!< automatic burst split on page boundary crossing */
#define EXMC_CRAM_PAGE_SIZE_128_BYTES     PNCTL_CPS(1)                  /*!< page size is 128 bytes */
#define EXMC_CRAM_PAGE_SIZE_256_BYTES     PNCTL_CPS(2)                  /*!< page size is 256 bytes */
#define EXMC_CRAM_PAGE_SIZE_512_BYTES     PNCTL_CPS(3)                  /*!< page size is 512 bytes */
#define EXMC_CRAM_PAGE_SIZE_1024_BYTES    PNCTL_CPS(4)                  /*!< page size is 1024 bytes */

/* NOR bank memory data bus width */
#define PNCTL_NRW(regval)                 (BITS(4,5) & ((uint32_t)(regval) << 4))
#define EXMC_NOR_DATABUS_WIDTH_8B         PNCTL_NRW(0)                  /*!< NOR data width is 8 bits */
#define EXMC_NOR_DATABUS_WIDTH_16B        PNCTL_NRW(1)                  /*!< NOR data width is 16 bits */

/* NOR bank memory type */
#define PNCTL_NRTP(regval)                (BITS(2,3) & ((uint32_t)(regval) << 2))
#define EXMC_MEMORY_TYPE_PSRAM            PNCTL_NRTP(1)                 /*!< PSRAM,CRAM */
#define EXMC_MEMORY_TYPE_NOR              PNCTL_NRTP(2)                 /*!< NOR flash */

/* data latency for NOR flash */
#define PNTCFG_DLAT(regval)               (BITS(24,27) & ((uint32_t)(regval) << 24))
#define EXMC_DATALAT_2_CLK                PNTCFG_DLAT(0)                /*!< data latency of first burst access is 2 EXMC_CLK */
#define EXMC_DATALAT_3_CLK                PNTCFG_DLAT(1)                /*!< data latency of first burst access is 3 EXMC_CLK */
#define EXMC_DATALAT_4_CLK                PNTCFG_DLAT(2)                /*!< data latency of first burst access is 4 EXMC_CLK */
#define EXMC_DATALAT_5_CLK                PNTCFG_DLAT(3)                /*!< data latency of first burst access is 5 EXMC_CLK */
#define EXMC_DATALAT_6_CLK                PNTCFG_DLAT(4)                /*!< data latency of first burst access is 6 EXMC_CLK */
#define EXMC_DATALAT_7_CLK                PNTCFG_DLAT(5)                /*!< data latency of first burst access is 7 EXMC_CLK */
#define EXMC_DATALAT_8_CLK                PNTCFG_DLAT(6)                /*!< data latency of first burst access is 8 EXMC_CLK */
#define EXMC_DATALAT_9_CLK                PNTCFG_DLAT(7)                /*!< data latency of first burst access is 9 EXMC_CLK */
#define EXMC_DATALAT_10_CLK               PNTCFG_DLAT(8)                /*!< data latency of first burst access is 10 EXMC_CLK */
#define EXMC_DATALAT_11_CLK               PNTCFG_DLAT(9)                /*!< data latency of first burst access is 11 EXMC_CLK */
#define EXMC_DATALAT_12_CLK               PNTCFG_DLAT(10)               /*!< data latency of first burst access is 12 EXMC_CLK */
#define EXMC_DATALAT_13_CLK               PNTCFG_DLAT(11)               /*!< data latency of first burst access is 13 EXMC_CLK */
#define EXMC_DATALAT_14_CLK               PNTCFG_DLAT(12)               /*!< data latency of first burst access is 14 EXMC_CLK */
#define EXMC_DATALAT_15_CLK               PNTCFG_DLAT(13)               /*!< data latency of first burst access is 15 EXMC_CLK */
#define EXMC_DATALAT_16_CLK               PNTCFG_DLAT(14)               /*!< data latency of first burst access is 16 EXMC_CLK */
#define EXMC_DATALAT_17_CLK               PNTCFG_DLAT(15)               /*!< data latency of first burst access is 17 EXMC_CLK */

/* synchronous clock divide ratio */
#define PNTCFG_CKDIV(regval)              (BITS(20,23) & ((uint32_t)(regval) << 20))
#define EXMC_SYN_CLOCK_RATIO_DISABLE      PNTCFG_CKDIV(0)               /*!< EXMC_CLK disable */
#define EXMC_SYN_CLOCK_RATIO_2_CLK        PNTCFG_CKDIV(1)               /*!< EXMC_CLK = HCLK/2 */
#define EXMC_SYN_CLOCK_RATIO_3_CLK        PNTCFG_CKDIV(2)               /*!< EXMC_CLK = HCLK/3 */
#define EXMC_SYN_CLOCK_RATIO_4_CLK        PNTCFG_CKDIV(3)               /*!< EXMC_CLK = HCLK/4 */
#define EXMC_SYN_CLOCK_RATIO_5_CLK        PNTCFG_CKDIV(4)               /*!< EXMC_CLK = HCLK/5 */
#define EXMC_SYN_CLOCK_RATIO_6_CLK        PNTCFG_CKDIV(5)               /*!< EXMC_CLK = HCLK/6 */
#define EXMC_SYN_CLOCK_RATIO_7_CLK        PNTCFG_CKDIV(6)               /*!< EXMC_CLK = HCLK/7 */
#define EXMC_SYN_CLOCK_RATIO_8_CLK        PNTCFG_CKDIV(7)               /*!< EXMC_CLK = HCLK/8 */
#define EXMC_SYN_CLOCK_RATIO_9_CLK        PNTCFG_CKDIV(8)               /*!< EXMC_CLK = HCLK/9 */
#define EXMC_SYN_CLOCK_RATIO_10_CLK       PNTCFG_CKDIV(9)               /*!< EXMC_CLK = HCLK/10 */
#define EXMC_SYN_CLOCK_RATIO_11_CLK       PNTCFG_CKDIV(10)              /*!< EXMC_CLK = HCLK/11 */
#define EXMC_SYN_CLOCK_RATIO_12_CLK       PNTCFG_CKDIV(11)              /*!< EXMC_CLK = HCLK/12 */
#define EXMC_SYN_CLOCK_RATIO_13_CLK       PNTCFG_CKDIV(12)              /*!< EXMC_CLK = HCLK/13 */
#define EXMC_SYN_CLOCK_RATIO_14_CLK       PNTCFG_CKDIV(13)              /*!< EXMC_CLK = HCLK/14 */
#define EXMC_SYN_CLOCK_RATIO_15_CLK       PNTCFG_CKDIV(14)              /*!< EXMC_CLK = HCLK/15 */
#define EXMC_SYN_CLOCK_RATIO_16_CLK       PNTCFG_CKDIV(15)              /*!< EXMC_CLK = HCLK/16 */

/* ECC size */
#define NCTL_ECCSZ(regval)               (BITS(17,19) & ((uint32_t)(regval) << 17))
#define EXMC_ECC_SIZE_256BYTES            NCTL_ECCSZ(0)                 /* ECC size is 256 bytes */
#define EXMC_ECC_SIZE_512BYTES            NCTL_ECCSZ(1)                 /* ECC size is 512 bytes */
#define EXMC_ECC_SIZE_1024BYTES           NCTL_ECCSZ(2)                 /* ECC size is 1024 bytes */
#define EXMC_ECC_SIZE_2048BYTES           NCTL_ECCSZ(3)                 /* ECC size is 2048 bytes */
#define EXMC_ECC_SIZE_4096BYTES           NCTL_ECCSZ(4)                 /* ECC size is 4096 bytes */
#define EXMC_ECC_SIZE_8192BYTES           NCTL_ECCSZ(5)                 /* ECC size is 8192 bytes */

/* ALE to RE delay */
#define NCTL_ATR(regval)                 (BITS(13,16) & ((uint32_t)(regval) << 13))
#define EXMC_ALE_RE_DELAY_1_HCLK          NCTL_ATR(0)                   /* ALE to RE delay = 1*HCLK */
#define EXMC_ALE_RE_DELAY_2_HCLK          NCTL_ATR(1)                   /* ALE to RE delay = 2*HCLK */
#define EXMC_ALE_RE_DELAY_3_HCLK          NCTL_ATR(2)                   /* ALE to RE delay = 3*HCLK */
#define EXMC_ALE_RE_DELAY_4_HCLK          NCTL_ATR(3)                   /* ALE to RE delay = 4*HCLK */
#define EXMC_ALE_RE_DELAY_5_HCLK          NCTL_ATR(4)                   /* ALE to RE delay = 5*HCLK */
#define EXMC_ALE_RE_DELAY_6_HCLK          NCTL_ATR(5)                   /* ALE to RE delay = 6*HCLK */
#define EXMC_ALE_RE_DELAY_7_HCLK          NCTL_ATR(6)                   /* ALE to RE delay = 7*HCLK */
#define EXMC_ALE_RE_DELAY_8_HCLK          NCTL_ATR(7)                   /* ALE to RE delay = 8*HCLK */
#define EXMC_ALE_RE_DELAY_9_HCLK          NCTL_ATR(8)                   /* ALE to RE delay = 9*HCLK */
#define EXMC_ALE_RE_DELAY_10_HCLK         NCTL_ATR(9)                   /* ALE to RE delay = 10*HCLK */
#define EXMC_ALE_RE_DELAY_11_HCLK         NCTL_ATR(10)                  /* ALE to RE delay = 11*HCLK */
#define EXMC_ALE_RE_DELAY_12_HCLK         NCTL_ATR(11)                  /* ALE to RE delay = 12*HCLK */
#define EXMC_ALE_RE_DELAY_13_HCLK         NCTL_ATR(12)                  /* ALE to RE delay = 13*HCLK */
#define EXMC_ALE_RE_DELAY_14_HCLK         NCTL_ATR(13)                  /* ALE to RE delay = 14*HCLK */
#define EXMC_ALE_RE_DELAY_15_HCLK         NCTL_ATR(14)                  /* ALE to RE delay = 15*HCLK */
#define EXMC_ALE_RE_DELAY_16_HCLK         NCTL_ATR(15)                  /* ALE to RE delay = 16*HCLK */

/* CLE to RE delay */
#define NCTL_CTR(regval)                 (BITS(9,12) & ((uint32_t)(regval) << 9))
#define EXMC_CLE_RE_DELAY_1_HCLK          NCTL_CTR(0)                  /* CLE to RE delay = 1*HCLK */
#define EXMC_CLE_RE_DELAY_2_HCLK          NCTL_CTR(1)                  /* CLE to RE delay = 2*HCLK */
#define EXMC_CLE_RE_DELAY_3_HCLK          NCTL_CTR(2)                  /* CLE to RE delay = 3*HCLK */
#define EXMC_CLE_RE_DELAY_4_HCLK          NCTL_CTR(3)                  /* CLE to RE delay = 4*HCLK */
#define EXMC_CLE_RE_DELAY_5_HCLK          NCTL_CTR(4)                  /* CLE to RE delay = 5*HCLK */
#define EXMC_CLE_RE_DELAY_6_HCLK          NCTL_CTR(5)                  /* CLE to RE delay = 6*HCLK */
#define EXMC_CLE_RE_DELAY_7_HCLK          NCTL_CTR(6)                  /* CLE to RE delay = 7*HCLK */
#define EXMC_CLE_RE_DELAY_8_HCLK          NCTL_CTR(7)                  /* CLE to RE delay = 8*HCLK */
#define EXMC_CLE_RE_DELAY_9_HCLK          NCTL_CTR(8)                  /* CLE to RE delay = 9*HCLK */
#define EXMC_CLE_RE_DELAY_10_HCLK         NCTL_CTR(9)                  /* CLE to RE delay = 10*HCLK */
#define EXMC_CLE_RE_DELAY_11_HCLK         NCTL_CTR(10)                 /* CLE to RE delay = 11*HCLK */
#define EXMC_CLE_RE_DELAY_12_HCLK         NCTL_CTR(11)                 /* CLE to RE delay = 12*HCLK */
#define EXMC_CLE_RE_DELAY_13_HCLK         NCTL_CTR(12)                 /* CLE to RE delay = 13*HCLK */
#define EXMC_CLE_RE_DELAY_14_HCLK         NCTL_CTR(13)                 /* CLE to RE delay = 14*HCLK */
#define EXMC_CLE_RE_DELAY_15_HCLK         NCTL_CTR(14)                 /* CLE to RE delay = 15*HCLK */
#define EXMC_CLE_RE_DELAY_16_HCLK         NCTL_CTR(15)                 /* CLE to RE delay = 16*HCLK */

/* NAND bank memory data bus width */
#define NCTL_NDW(regval)                 (BITS(4,5) & ((uint32_t)(regval) << 4))
#define EXMC_NAND_DATABUS_WIDTH_8B        NCTL_NDW(0)                  /*!< NAND data width is 8 bits */
#define EXMC_NAND_DATABUS_WIDTH_16B       NCTL_NDW(1)                  /*!< NAND data width is 16 bits */

/* EXMC NOR/PSRAM write mode */
#define EXMC_ASYN_WRITE                   ((uint32_t)0x00000000U)       /*!< asynchronous write mode */
#define EXMC_SYN_WRITE                    EXMC_PNCTL_SYNCWR             /*!< synchronous write mode */

/* EXMC NWAIT signal configuration */
#define EXMC_NWAIT_CONFIG_BEFORE          ((uint32_t)0x00000000U)       /*!< NWAIT signal is active one data cycle before wait state */
#define EXMC_NWAIT_CONFIG_DURING          EXMC_PNCTL_NRWTCFG            /*!< NWAIT signal is active during wait state */

/* EXMC NWAIT signal polarity configuration */
#define EXMC_NWAIT_POLARITY_LOW           ((uint32_t)0x00000000U)       /*!< low level is active of NWAIT */
#define EXMC_NWAIT_POLARITY_HIGH          EXMC_PNCTL_NRWTPOL            /*!< high level is active of NWAIT */

/* EXMC NAND bank definition */
#define EXMC_BANK1_NAND                   ((uint32_t)0x00000001U)       /*!< bank1 NAND flash */

/* EXMC flag bits */
#define EXMC_NAND_FLAG_FIFOE              EXMC_NSTAT_FFEPT              /*!< FIFO empty flag */

/* function declarations */
/* initialization functions */
/* NOR/PSRAM */
/* deinitialize EXMC NOR/PSRAM region */
void exmc_norsram_deinit(void);
/* initialize exmc_norpsram_parameter_struct with the default values */
void exmc_norsram_struct_para_init(exmc_norsram_parameter_struct* exmc_norsram_init_struct);
/* initialize EXMC NOR/PSRAM region */
void exmc_norsram_init(exmc_norsram_parameter_struct* exmc_norsram_init_struct);
/* enable EXMC NOR/PSRAM region */
void exmc_norsram_enable(void);
/* disable EXMC NOR/PSRAM region */
void exmc_norsram_disable(void);
/* NAND */
/* deinitialize EXMC NAND bank */
void exmc_nand_deinit(void);
/* initialize exmc_norsram_parameter_struct with the default values */
void exmc_nand_struct_para_init(exmc_nand_parameter_struct* exmc_nand_init_struct);
/* initialize EXMC NAND bank */
void exmc_nand_init(exmc_nand_parameter_struct* exmc_nand_init_struct);
/* enable EXMC NAND bank */
void exmc_nand_enable(void);
/* disable EXMC NAND bank */
void exmc_nand_disable(void);

/* NOR/PSRAM */
/* configure CRAM page size */
void exmc_norsram_page_size_config(uint32_t page_size);
/* NAND */
/* enable the EXMC NAND ECC function */
void exmc_nand_ecc_enable(void);
/* disable the EXMC NAND ECC function */
void exmc_nand_ecc_disable(void);
/* get the EXMC ECC value */
uint32_t exmc_ecc_get(void);

/* interrupt & flag functions */
/* get EXMC flag status */
FlagStatus exmc_flag_get(uint32_t flag);

#endif /* GD32F50X_EXMC_H */
