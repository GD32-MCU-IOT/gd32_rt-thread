/*!
    \file    gd32h75e_ospim.h
    \brief   definitions for the OSPIM

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

#ifndef GD32H75E_OSPIM_H
#define GD32H75E_OSPIM_H

#include "gd32h75e.h"

/* OSPIM definitions */
#define OSPIM                             OSPM_BASE

#define OSPIM_PCFG0                       REG32(OSPIM + 0x00000004U)                      /*!< OSPI I/O manager port configuration register 0 */
#define OSPIM_PCFG1                       REG32(OSPIM + 0x00000008U)                      /*!< OSPI I/O manager port configuration register 1 */

/* OSPIM_PCFG */
#define OSPIM_PCFG_SCKEN                  BIT(0)                                          /*!< enable for sck of port 0 */
#define OSPIM_PCFG_SRCPCK                 BIT(1)                                          /*!< source selection for sck of port n */
#define OSPIM_PCFG_NCSEN                  BIT(8)                                          /*!< enable for csn of port 0 */
#define OSPIM_PCFG_SRCPCS                 BIT(9)                                          /*!< source selection for csn of port n */
#define OSPIM_PCFG_POLEN                  BIT(16)                                         /*!< enable for IO[3:0] of port 0 */
#define OSPIM_PCFG_SRCPLIO                BITS(17,18)                                     /*!< source selection for IO[3:0] of port 0 */
#define OSPIM_PCFG_POHEN                  BIT(24)                                         /*!< enable for IO[7:4] of port 0 */
#define OSPIM_PCFG_SRCPHIO                BITS(25,26)                                     /*!< source selection for IO[7:4] of port 0 */

/* constants definitions */
/* ospi io manager configuration struct definitions */
/* ospim register address */
#define OSPIM_PCFG(regval)                REG32(OSPIM + 0x4U * ((regval) + 1U))             /*!< the address of OSPI manager port configuration register */

/* ospim register address */
#define OSPIM_PORT0                       0x00U                                           /*!< OSPI manager port 0 */
#define OSPIM_PORT1                       0x01U                                           /*!< OSPI manager port 1 */

/* SCK of port */
#define OSPIM_PORT_SCK_DISABLE            0x00000000U                                     /*!< disable SCK of port */
#define OSPIM_PORT_SCK_ENABLE             OSPIM_PCFG_SCKEN                                /*!< disable SCK of port */

/* source selection for SCK of port */
#define OSPIM_SCK_SOURCE_OSPI0_SCK        0x00000000U                                     /*!< the source of SCK is OSPI0_SCK */
#define OSPIM_SCK_SOURCE_OSPI1_SCK        OSPIM_PCFG_SRCPCK                               /*!< the source of SCK is OSPI1_SCK */

/* CSN of port */
#define OSPIM_PORT_CSN_DISABLE            0x00000000U                                     /*!< disable CSN of port */
#define OSPIM_PORT_CSN_ENABLE             OSPIM_PCFG_NCSEN                                /*!< enable CSN of port */

/* source selection for CSN of port */
#define OSPIM_CSN_SOURCE_OSPI0_CSN        0x00000000U                                     /*!< the source of CSN is OSPI0_CSN */
#define OSPIM_CSN_SOURCE_OSPI1_CSN        OSPIM_PCFG_SRCPCS                               /*!< the source of CSN is OSPI1_CSN */

/* IO[3:0] of port */
#define OSPIM_IO_LOW_DISABLE               0x00000000U                                    /*!< disable IO[3:0] of port */
#define OSPIM_IO_LOW_ENABLE                OSPIM_PCFG_POLEN                               /*!< enable IO[3:0] of port */

/* source selection for IO[3:0] of port 0 */
#define OSPIM_SRCPLIO(regval)             (BITS(17,18) & ((uint32_t)(regval) << 17U))
#define OSPIM_SRCPLIO_OSPI0_IO_LOW        OSPIM_SRCPLIO(0)                                /*!< select OSPI0_IO[3:0] in non-multiplexed mode, and select multiplexed IO[3:0] in multiplex mode */
#define OSPIM_SRCPLIO_OSPI0_IO_HIGH       OSPIM_SRCPLIO(1)                                /*!< select OSPI0_IO[7:4] in non-multiplexed mode, and select multiplexed IO[7:4] in multiplex mode */
#define OSPIM_SRCPLIO_OSPI1_IO_LOW        OSPIM_SRCPLIO(2)                                /*!< select OSPI1_IO[3:0], only valied in non-multiplexed mode */
#define OSPIM_SRCPLIO_OSPI1_IO_HIGH       OSPIM_SRCPLIO(3)                                /*!< select OSPI1_IO[7:4], only valied in non-multiplexed mode */

/* IO[7:4] of port */
#define OSPIM_IO_HIGH_DISABLE             0x00000000U                                     /*!< disable IO[7:4] of port */
#define OSPIM_IO_HIGH_ENABLE              OSPIM_PCFG_POHEN                                /*!< enable IO[7:4] of port */

/* source selection for IO[7:4] of port n */
#define OSPIM_SRCPHIO(regval)             (BITS(25,26) & ((uint32_t)(regval) << 25U))
#define OSPIM_SRCPHIO_OSPI0_IO_LOW        OSPIM_SRCPHIO(0)                                /*!< select OSPI0_IO[3:0] in non-multiplexed mode, and select multiplexed IO[3:0] in multiplex mode */
#define OSPIM_SRCPHIO_OSPI0_IO_HIGH       OSPIM_SRCPHIO(1)                                /*!< select OSPI0_IO[7:4] in non-multiplexed mode, and select multiplexed IO[7:4] in multiplex mode */
#define OSPIM_SRCPHIO_OSPI1_IO_LOW        OSPIM_SRCPHIO(2)                                /*!< select OSPI1_IO[3:0], only valied in non-multiplexed mode */
#define OSPIM_SRCPHIO_OSPI1_IO_HIGH       OSPIM_SRCPHIO(3)                                /*!< select OSPI1_IO[7:4], only valied in non-multiplexed mode */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check OSPIM port  */
#define NOT_OSPIM_PORT(port)                          (((port) != OSPIM_PORT0) && ((port) != OSPIM_PORT1))
/* check OSPIM port sck configuration */
#define NOT_OSPIM_PORT_SCK(sckconfg)                  (((sckconfg) != OSPIM_PORT_SCK_DISABLE) && ((sckconfg) != OSPIM_PORT_SCK_ENABLE))
/* check OSPIM port sck source */
#define NOT_OSPIM_PORT_SCK_SOURCE(sck_source)         (((sck_source) != OSPIM_SCK_SOURCE_OSPI0_SCK) && ((sck_source) != OSPIM_SCK_SOURCE_OSPI1_SCK))
/* check OSPIM port CSN configuration */
#define NOT_OSPIM_PORT_CSN(csnconfig)                 (((csnconfig) != OSPIM_PORT_CSN_DISABLE) && ((csnconfig) != OSPIM_PORT_CSN_ENABLE))
/* check OSPIM port CSN source */
#define NOT_OSPIM_PORT_CSN_SOURCE(csn_source)         (((csn_source) != OSPIM_CSN_SOURCE_OSPI0_CSN) && ((csn_source) != OSPIM_CSN_SOURCE_OSPI1_CSN))
/* check OSPIM IO[3:0] configuration */
#define NOT_OSPIM_IO_LOW(ioconfig)                    (((ioconfig) != OSPIM_IO_LOW_DISABLE) && ((ioconfig) != OSPIM_IO_LOW_ENABLE))
/* check the source of OSPIM IO[3:0] */
#define NOT_OSPIM_SRC_LOW(io_source)                  (((io_source) != OSPIM_SRCPLIO_OSPI0_IO_LOW) && ((io_source) != OSPIM_SRCPLIO_OSPI0_IO_HIGH) && ((io_source) != OSPIM_SRCPLIO_OSPI1_IO_LOW) && ((io_source) != OSPIM_SRCPLIO_OSPI1_IO_HIGH))
/* check OSPIM IO[7:4] configuration */
#define NOT_OSPIM_IO_HIGH(ioconfig)                   (((ioconfig) != OSPIM_IO_HIGH_DISABLE) && ((ioconfig) != OSPIM_IO_HIGH_ENABLE))
/* check the source of OSPIM IO[7:4] */
#define NOT_OSPIM_SRC_HIGH(io_source)                 (((io_source) != OSPIM_SRCPHIO_OSPI0_IO_LOW) && ((io_source) != OSPIM_SRCPHIO_OSPI0_IO_HIGH) && ((io_source) != OSPIM_SRCPHIO_OSPI1_IO_LOW) && ((io_source) != OSPIM_SRCPHIO_OSPI1_IO_HIGH))
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* reset the OSPIM peripheral */
void ospim_deinit(void);

/* ospim port configuration functions */
/* configurate SCK for port */
void ospim_port_sck_config(uint8_t port, uint32_t sckconfg);
/* select source of SCK for port */
void ospim_port_sck_source_select(uint8_t port, uint32_t sck_source);
/* configurate CSN for port */
void ospim_port_csn_config(uint8_t port, uint32_t csnconfig);
/* select source of CSN for port */
void ospim_port_csn_source_select(uint8_t port, uint32_t csn_source);
/* configurate IO[3:0] for port */
void ospim_port_io3_0_config(uint8_t port, uint32_t ioconfig);
/* select source of IO[3:0] for port */
void ospim_port_io3_0_source_select(uint8_t port, uint32_t io_source);
/* configurate IO[7:4] for port */
void ospim_port_io7_4_config(uint8_t port, uint32_t ioconfig);
/* select source of IO[7:4] for port */
void ospim_port_io7_4_source_select(uint8_t port, uint32_t io_source);

#endif /* GD32H75E_OSPIM_H */
