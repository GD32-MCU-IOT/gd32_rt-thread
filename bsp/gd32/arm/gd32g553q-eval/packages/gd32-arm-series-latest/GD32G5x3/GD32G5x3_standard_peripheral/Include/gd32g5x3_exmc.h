/*!
    \file    gd32g5x3_exmc.h
    \brief   definitions for the EXMC

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

#ifndef GD32G5X3_EXMC_H
#define GD32G5X3_EXMC_H

#include "gd32g5x3.h"

/* EXMC definitions */
#define EXMC                              (EXMC_BASE)                   /*!< EXMC register base address */

/* registers definitions */
/* NOR/PSRAM */
#define EXMC_SNCTL0                       REG32(EXMC + 0x00U)           /*!< EXMC SRAM/NOR flash control register 0 */
#define EXMC_SNTCFG0                      REG32(EXMC + 0x04U)           /*!< EXMC SRAM/NOR flash timing configuration register 0 */
#define EXMC_SNWTCFG0                     REG32(EXMC + 0x104U)          /*!< EXMC SRAM/NOR flash write timing configuration register 0 */

#define EXMC_SNCTL1                       REG32(EXMC + 0x08U)           /*!< EXMC SRAM/NOR flash control register 1 */
#define EXMC_SNTCFG1                      REG32(EXMC + 0x0CU)           /*!< EXMC SRAM/NOR flash timing configuration register 1 */
#define EXMC_SNWTCFG1                     REG32(EXMC + 0x10CU)          /*!< EXMC SRAM/NOR flash write timing configuration register 1 */

#define EXMC_SNCTL2                       REG32(EXMC + 0x10U)           /*!< EXMC SRAM/NOR flash control register 2 */
#define EXMC_SNTCFG2                      REG32(EXMC + 0x14U)           /*!< EXMC SRAM/NOR flash timing configuration register 2 */
#define EXMC_SNWTCFG2                     REG32(EXMC + 0x114U)          /*!< EXMC SRAM/NOR flash write timing configuration register 2 */

#define EXMC_SNCTL3                       REG32(EXMC + 0x18U)           /*!< EXMC SRAM/NOR flash control register 3 */
#define EXMC_SNTCFG3                      REG32(EXMC + 0x1CU)           /*!< EXMC SRAM/NOR flash timing configuration register 3 */
#define EXMC_SNWTCFG3                     REG32(EXMC + 0x11CU)          /*!< EXMC SRAM/NOR flash write timing configuration register 3 */

#define EXMC_SNSTAT                       REG32(EXMC + 0x84U)           /*!< EXMC SRAM/NOR flash status registers */

#define EXMC_SNLATDEC0                    REG32(EXMC + 0x300U)          /*!< EXMC SRAM/NOR flash data latency decrease register 0 */
#define EXMC_SNLATDEC1                    REG32(EXMC + 0x304U)          /*!< EXMC SRAM/NOR flash data latency decrease register 1 */
#define EXMC_SNLATDEC2                    REG32(EXMC + 0x308U)          /*!< EXMC SRAM/NOR flash data latency decrease register 2 */
#define EXMC_SNLATDEC3                    REG32(EXMC + 0x30CU)          /*!< EXMC SRAM/NOR flash data latency decrease register 3 */

/* bits definitions */
/* EXMC_SNCTLx,x=0..3 */
#define EXMC_SNCTL_NRBKEN                 BIT(0)                        /*!< NOR bank enable */
#define EXMC_SNCTL_NRMUX                  BIT(1)                        /*!< NOR bank memory address/data multiplexing enable */
#define EXMC_SNCTL_NRTP                   BITS(2,3)                     /*!< NOR bank memory type */
#define EXMC_SNCTL_NRW                    BITS(4,5)                     /*!< NOR bank memory data bus width */
#define EXMC_SNCTL_NREN                   BIT(6)                        /*!< NOR flash access enable */
#define EXMC_SNCTL_SBRSTEN                BIT(8)                        /*!< synchronous burst enable */
#define EXMC_SNCTL_NRWTPOL                BIT(9)                        /*!< NWAIT signal polarity */
#define EXMC_SNCTL_WRAPEN                 BIT(10)                       /*!< wrapped burst mode enable */
#define EXMC_SNCTL_NRWTCFG                BIT(11)                       /*!< NWAIT signal configuration, only work in synchronous mode */
#define EXMC_SNCTL_WEN                    BIT(12)                       /*!< write enable */
#define EXMC_SNCTL_NRWTEN                 BIT(13)                       /*!< NWAIT signal enable */
#define EXMC_SNCTL_EXMODEN                BIT(14)                       /*!< extended mode enable */
#define EXMC_SNCTL_ASYNCWAIT              BIT(15)                       /*!< asynchronous wait enable */
#define EXMC_SNCTL_CPS                    BITS(16,18)                   /*!< CRAM page size */
#define EXMC_SNCTL_SYNCWR                 BIT(19)                       /*!< synchronous write config */
#define EXMC_SNCTL_CCK                    BIT(20)                       /*!< consecutive clock configuration */
#define EXMC_SNCTL_WFIFODIS               BIT(21)                       /*!< write FIFO disable */
#define EXMC_SNCTL_BLSET                  BITS(22,23)                   /*!< byte lane setup time */

/* EXMC_SNTCFGx,x=0..3 */
#define EXMC_SNTCFG_ASET                  BITS(0,3)                     /*!< asynchronous address setup time */
#define EXMC_SNTCFG_AHLD                  BITS(4,7)                     /*!< asynchronous address hold time */
#define EXMC_SNTCFG_DSET                  BITS(8,15)                    /*!< asynchronous data setup time */
#define EXMC_SNTCFG_BUSLAT                BITS(16,19)                   /*!< bus latency */
#define EXMC_SNTCFG_CKDIV                 BITS(20,23)                   /*!< synchronous clock divide ratio */
#define EXMC_SNTCFG_DLAT                  BITS(24,27)                   /*!< synchronous data latency for NOR flash */
#define EXMC_SNTCFG_ASYNCMOD              BITS(28,29)                   /*!< asynchronous access mode */

/* EXMC_SNWTCFGx,x=0..3 */
#define EXMC_SNWTCFG_WASET                BITS(0,3)                     /*!< asynchronous address setup time */
#define EXMC_SNWTCFG_WAHLD                BITS(4,7)                     /*!< asynchronous address hold time */
#define EXMC_SNWTCFG_WDSET                BITS(8,15)                    /*!< asynchronous data setup time */
#define EXMC_SNWTCFG_WBUSLAT              BITS(16,19)                   /*!< bus latency */
#define EXMC_SNWTCFG_WASYNCMOD            BITS(28,29)                   /*!< asynchronous access mode */

/* EXMC_SNSTAT */
#define EXMC_SNSTAT_FIFOEPT               BIT(6)                        /*!< FIFO empty flag */

/* EXMC_SNLATDECx,x=0..3 */
#define EXMC_SNLATDEC_LATDEC                BITS(0,2)                     /*!< data latency decrease for NOR Flash and only valid in synchronous read access */

/* constants definitions */
/* EXMC NOR/SRAM timing initialize struct */
typedef struct
{
    uint32_t asyn_access_mode;                                          /*!< asynchronous access mode */
    uint32_t syn_data_latency;                                          /*!< configure the data latency, synchronous access mode valid */
    uint32_t syn_data_latency_dec;                                      /*!< configure the data latency decreasing value */
    uint32_t syn_clk_division;                                          /*!< configure the clock divide ratio, synchronous access mode valid */
    uint32_t bus_latency;                                               /*!< configure the bus latency */
    uint32_t asyn_data_setuptime;                                       /*!< configure the data setup time, asynchronous access mode valid */
    uint32_t asyn_address_holdtime;                                     /*!< configure the address hold time, asynchronous access mode valid */
    uint32_t asyn_address_setuptime;                                    /*!< configure the data setup time, asynchronous access mode valid */
    uint32_t byte_lane_setuptime;                                       /*!< configure byte lane setup time */    
}exmc_norsram_timing_parameter_struct;

/* EXMC NOR/SRAM initialize struct */
typedef struct
{
    uint32_t norsram_region;                                            /*!< select the region of EXMC NOR/SRAM bank */
    uint32_t write_mode;                                                /*!< the write mode, synchronous mode or asynchronous mode */
    uint32_t extended_mode;                                             /*!< enable or disable the extended mode */
    uint32_t asyn_wait;                                                 /*!< enable or disable the asynchronous wait function */
    uint32_t nwait_signal;                                              /*!< enable or disable the NWAIT signal while in synchronous bust mode */
    uint32_t memory_write;                                              /*!< enable or disable the write operation */
    uint32_t nwait_config;                                              /*!< NWAIT signal configuration, only work in synchronous mode */
    uint32_t wrap_burst_mode;                                           /*!< enable or disable the wrap burst mode */
    uint32_t nwait_polarity;                                            /*!< specifies the polarity of NWAIT signal from memory */
    uint32_t burst_mode;                                                /*!< enable or disable the burst mode */
    uint32_t databus_width;                                             /*!< specifies the databus width of external memory */
    uint32_t memory_type;                                               /*!< specifies the type of external memory */
    uint32_t address_data_mux;                                          /*!< specifies whether the data bus and address bus are multiplexed */
    exmc_norsram_timing_parameter_struct* read_write_timing;            /*!< timing parameters for read and write if the extended mode is not used or the timing 
                                                                             parameters for read if the extended mode is used */
    exmc_norsram_timing_parameter_struct* write_timing;                 /*!< timing parameters for write when the extended mode is used */
}exmc_norsram_parameter_struct;

/* EXMC_register address */
#define EXMC_SNCTL(region)                REG32(EXMC + 0x08U * (region))                   /*!< EXMC SRAM/NOR flash control registers, region = 0,1,2,3 */
#define EXMC_SNTCFG(region)               REG32(EXMC + 0x04U + 0x08U * (region))           /*!< EXMC SRAM/NOR flash timing configuration registers, region = 0,1,2,3 */
#define EXMC_SNWTCFG(region)              REG32(EXMC + 0x104U + 0x08U * (region))          /*!< EXMC SRAM/NOR flash write timing configuration registers, region = 0,1,2,3 */
#define EXMC_SNLATDEC(region)             REG32(EXMC + 0x300U + 0x04U*((uint32_t)(region)))/*!< EXMC SRAM/NOR flash data latency decrease registers, region = 0,1,2,3 */

/* CRAM page size */
#define SNCTL_CPS(regval)                 (BITS(16,18) & ((uint32_t)(regval) << 16))
#define EXMC_CRAM_AUTO_SPLIT              SNCTL_CPS(0)                  /*!< automatic burst split on page boundary crossing */
#define EXMC_CRAM_PAGE_SIZE_128_BYTES     SNCTL_CPS(1)                  /*!< page size is 128 bytes */
#define EXMC_CRAM_PAGE_SIZE_256_BYTES     SNCTL_CPS(2)                  /*!< page size is 256 bytes */
#define EXMC_CRAM_PAGE_SIZE_512_BYTES     SNCTL_CPS(3)                  /*!< page size is 512 bytes */
#define EXMC_CRAM_PAGE_SIZE_1024_BYTES    SNCTL_CPS(4)                  /*!< page size is 1024 bytes */

/* NOR bank memory data bus width */
#define SNCTL_NRW(regval)                 (BITS(4,5) & ((uint32_t)(regval) << 4))
#define EXMC_NOR_DATABUS_WIDTH_8B         SNCTL_NRW(0)                  /*!< NOR data width is 8 bits */
#define EXMC_NOR_DATABUS_WIDTH_16B        SNCTL_NRW(1)                  /*!< NOR data width is 16 bits */

/* NOR bank memory type */
#define SNCTL_NRTP(regval)                (BITS(2,3) & ((uint32_t)(regval) << 2))
#define EXMC_MEMORY_TYPE_SRAM             SNCTL_NRTP(0)                 /*!< SRAM,ROM */
#define EXMC_MEMORY_TYPE_PSRAM            SNCTL_NRTP(1)                 /*!< PSRAM, CRAM */
#define EXMC_MEMORY_TYPE_NOR              SNCTL_NRTP(2)                 /*!< NOR flash */

/* asynchronous access mode */
#define SNTCFG_ASYNCMOD(regval)           (BITS(28,29) & ((uint32_t)(regval) << 28))
#define EXMC_ACCESS_MODE_A                SNTCFG_ASYNCMOD(0)            /*!< mode A access */
#define EXMC_ACCESS_MODE_B                SNTCFG_ASYNCMOD(1)            /*!< mode B access */
#define EXMC_ACCESS_MODE_C                SNTCFG_ASYNCMOD(2)            /*!< mode C access */
#define EXMC_ACCESS_MODE_D                SNTCFG_ASYNCMOD(3)            /*!< mode D access */

/* data latency for NOR flash */
#define SNTCFG_DLAT(regval)               (BITS(24,27) & ((uint32_t)(regval) << 24))
#define EXMC_DATALAT_2_CLK                SNTCFG_DLAT(0)                /*!< data latency of first burst access is 2 EXMC_CLK */
#define EXMC_DATALAT_3_CLK                SNTCFG_DLAT(1)                /*!< data latency of first burst access is 3 EXMC_CLK */
#define EXMC_DATALAT_4_CLK                SNTCFG_DLAT(2)                /*!< data latency of first burst access is 4 EXMC_CLK */
#define EXMC_DATALAT_5_CLK                SNTCFG_DLAT(3)                /*!< data latency of first burst access is 5 EXMC_CLK */
#define EXMC_DATALAT_6_CLK                SNTCFG_DLAT(4)                /*!< data latency of first burst access is 6 EXMC_CLK */
#define EXMC_DATALAT_7_CLK                SNTCFG_DLAT(5)                /*!< data latency of first burst access is 7 EXMC_CLK */
#define EXMC_DATALAT_8_CLK                SNTCFG_DLAT(6)                /*!< data latency of first burst access is 8 EXMC_CLK */
#define EXMC_DATALAT_9_CLK                SNTCFG_DLAT(7)                /*!< data latency of first burst access is 9 EXMC_CLK */
#define EXMC_DATALAT_10_CLK               SNTCFG_DLAT(8)                /*!< data latency of first burst access is 10 EXMC_CLK */
#define EXMC_DATALAT_11_CLK               SNTCFG_DLAT(9)                /*!< data latency of first burst access is 11 EXMC_CLK */
#define EXMC_DATALAT_12_CLK               SNTCFG_DLAT(10)               /*!< data latency of first burst access is 12 EXMC_CLK */
#define EXMC_DATALAT_13_CLK               SNTCFG_DLAT(11)               /*!< data latency of first burst access is 13 EXMC_CLK */
#define EXMC_DATALAT_14_CLK               SNTCFG_DLAT(12)               /*!< data latency of first burst access is 14 EXMC_CLK */
#define EXMC_DATALAT_15_CLK               SNTCFG_DLAT(13)               /*!< data latency of first burst access is 15 EXMC_CLK */
#define EXMC_DATALAT_16_CLK               SNTCFG_DLAT(14)               /*!< data latency of first burst access is 16 EXMC_CLK */
#define EXMC_DATALAT_17_CLK               SNTCFG_DLAT(15)               /*!< data latency of first burst access is 17 EXMC_CLK */

/* synchronous clock divide ratio */
#define SNTCFG_CKDIV(regval)              (BITS(20,23) & ((uint32_t)(regval) << 20))
#define EXMC_SYN_CLOCK_RATIO_DISABLE      SNTCFG_CKDIV(0)               /*!< EXMC_CLK disable */
#define EXMC_SYN_CLOCK_RATIO_2_CLK        SNTCFG_CKDIV(1)               /*!< frequency EXMC_CLK = HCLK/2 */
#define EXMC_SYN_CLOCK_RATIO_3_CLK        SNTCFG_CKDIV(2)               /*!< frequency EXMC_CLK = HCLK/3 */
#define EXMC_SYN_CLOCK_RATIO_4_CLK        SNTCFG_CKDIV(3)               /*!< frequency EXMC_CLK = HCLK/4 */
#define EXMC_SYN_CLOCK_RATIO_5_CLK        SNTCFG_CKDIV(4)               /*!< frequency EXMC_CLK = HCLK/5 */
#define EXMC_SYN_CLOCK_RATIO_6_CLK        SNTCFG_CKDIV(5)               /*!< frequency EXMC_CLK = HCLK/6 */
#define EXMC_SYN_CLOCK_RATIO_7_CLK        SNTCFG_CKDIV(6)               /*!< frequency EXMC_CLK = HCLK/7 */
#define EXMC_SYN_CLOCK_RATIO_8_CLK        SNTCFG_CKDIV(7)               /*!< frequency EXMC_CLK = HCLK/8 */
#define EXMC_SYN_CLOCK_RATIO_9_CLK        SNTCFG_CKDIV(8)               /*!< frequency EXMC_CLK = HCLK/9 */
#define EXMC_SYN_CLOCK_RATIO_10_CLK       SNTCFG_CKDIV(9)               /*!< frequency EXMC_CLK = HCLK/10 */
#define EXMC_SYN_CLOCK_RATIO_11_CLK       SNTCFG_CKDIV(10)              /*!< frequency EXMC_CLK = HCLK/11 */
#define EXMC_SYN_CLOCK_RATIO_12_CLK       SNTCFG_CKDIV(11)              /*!< frequency EXMC_CLK = HCLK/12 */
#define EXMC_SYN_CLOCK_RATIO_13_CLK       SNTCFG_CKDIV(12)              /*!< frequency EXMC_CLK = HCLK/13 */
#define EXMC_SYN_CLOCK_RATIO_14_CLK       SNTCFG_CKDIV(13)              /*!< frequency EXMC_CLK = HCLK/14 */
#define EXMC_SYN_CLOCK_RATIO_15_CLK       SNTCFG_CKDIV(14)              /*!< frequency EXMC_CLK = HCLK/15 */
#define EXMC_SYN_CLOCK_RATIO_16_CLK       SNTCFG_CKDIV(15)              /*!< frequency EXMC_CLK = HCLK/16 */

/* EXMC NOR/SRAM bank region definition */
#define EXMC_BANK0_NORSRAM_REGION0        ((uint32_t)0x00000000U)       /*!< bank0 NOR/SRAM region0 */
#define EXMC_BANK0_NORSRAM_REGION1        ((uint32_t)0x00000001U)       /*!< bank0 NOR/SRAM region1 */
#define EXMC_BANK0_NORSRAM_REGION2        ((uint32_t)0x00000002U)       /*!< bank0 NOR/SRAM region2 */
#define EXMC_BANK0_NORSRAM_REGION3        ((uint32_t)0x00000003U)       /*!< bank0 NOR/SRAM region3 */

/* EXMC write FIFO configuration */
#define EXMC_WRITE_FIFO_ENABLE            ((uint32_t)0x00000000U)       /*!< enable write FIFO */
#define EXMC_WRITE_FIFO_DISABLE           EXMC_SNCTL_WFIFODIS           /*!< disable write FIFO */

/* EXMC consecutive clock */
#define EXMC_CLOCK_SYNC_ONLY              ((uint32_t)0x00000000U)       /*!< EXMC_CLK is generated only during synchronous access */
#define EXMC_CLOCK_UNCONDITIONALLY        EXMC_SNCTL_CCK                /*!< EXMC_CLK is generated unconditionally */

/* EXMC NOR/SRAM write mode */
#define EXMC_ASYN_WRITE                   ((uint32_t)0x00000000U)       /*!< asynchronous write mode */
#define EXMC_SYN_WRITE                    EXMC_SNCTL_SYNCWR             /*!< synchronous write mode */

/* EXMC NWAIT signal configuration */
#define EXMC_NWAIT_CONFIG_BEFORE          ((uint32_t)0x00000000U)       /*!< NWAIT signal is active one data cycle before wait state */
#define EXMC_NWAIT_CONFIG_DURING          EXMC_SNCTL_NRWTCFG            /*!< NWAIT signal is active during wait state */

/* EXMC NWAIT signal polarity configuration */
#define EXMC_NWAIT_POLARITY_LOW           ((uint32_t)0x00000000U)       /*!< low level is active of NWAIT */
#define EXMC_NWAIT_POLARITY_HIGH          EXMC_SNCTL_NRWTPOL            /*!< high level is active of NWAIT */

/* EXMC NOR/SRAM status */
#define EXMC_FIFO_NOT_EMPTY               ((uint32_t)0x00000000U)       /*!< NOR/SRAM write FIFO is not empty */
#define EXMC_FIFO_EMPTY                   EXMC_SNSTAT_FIFOEPT           /*!< NOR/SRAM write FIFO is empty */

/* function declarations */
/* NOR/SRAM */
/* deinitialize EXMC NOR/SRAM region */
void exmc_norsram_deinit(uint32_t exmc_norsram_region);
/* initialize exmc_norsram_parameter_struct with the default values */
void exmc_norsram_struct_para_init(exmc_norsram_parameter_struct* exmc_norsram_init_struct);
/* initialize EXMC NOR/SRAM region */
void exmc_norsram_init(exmc_norsram_parameter_struct* exmc_norsram_init_struct);
/* enable EXMC NOR/SRAM region */
void exmc_norsram_enable(uint32_t exmc_norsram_region);
/* disable EXMC NOR/SRAM region */
void exmc_norsram_disable(uint32_t exmc_norsram_region);
/* configure consecutive clock */
void exmc_norsram_consecutive_clock_config(uint32_t clock_mode);
/* configure CRAM page size */
void exmc_norsram_page_size_config(uint32_t exmc_norsram_region, uint32_t page_size);
/* configure EXMC NOR/SRAM(bank0 region0) write FIFO */
void exmc_norsram_write_fifo_config(uint32_t wr_fifo);
/* get EXMC NOR/SRAM(bank0 region0) region FIFO status */
uint32_t exmc_norsram_status_get(void);

#endif /* GD32G5X3_EXMC_H */
