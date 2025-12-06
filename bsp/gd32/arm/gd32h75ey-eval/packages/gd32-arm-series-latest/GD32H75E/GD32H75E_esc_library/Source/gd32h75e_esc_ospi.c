/*!
    \file    esc_ospi.c
    \brief   ESC ospi driver basic configuration

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

#include <string.h>
#include "gd32h75e_esc_syscfg.h"
#include "gd32h75e_esc_ospi.h"

ospi_parameter_struct ospi_init_struct = {0};

/* write esc core reg by csr */
static void ospi_write_reg(uint8_t *writebuffer, uint16_t address, uint8_t count, ospi_parameter_struct *ospi_struct);
/* read esc core reg by csr */
static void ospi_read_reg(uint8_t *readbuffer, uint16_t address, uint8_t count, ospi_parameter_struct *ospi_struct);
/* write esc pdram by csr */
static void ospi_write_pdram(uint8_t *writebuffer, uint16_t address, uint16_t count, ospi_parameter_struct *ospi_struct);
/* read esc pdram by csr */
static void ospi_read_pdram(uint8_t *readbuffer, uint16_t address, uint16_t count, ospi_parameter_struct *ospi_struct);

/*!
    \brief      initialize OSPI/OSPIM and GPIO
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                               OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                               OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                               OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                             OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \retval     none
*/
void ospi_hw_init(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct)
{
    /* reset the OSPI and OSPIM peripheral */
    ospi_deinit(ospi_periph);
    ospim_deinit();
    /* enable OSPIM and GPIO clock */
    rcu_periph_clock_enable(RCU_OSPIM);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    /*OSPI 8Bit OSPI1*/
    /* configure OSPIM GPIO pin:
           OSPIM_P1_IO0(PF0)
           OSPIM_P1_IO1(PF1)
           OSPIM_P1_IO2(PF2)
           OSPIM_P1_IO3(PF3)
           OSPIM_P1_IO4(PG0)
           OSPIM_P1_IO5(PG1)
           OSPIM_P1_IO6(PG10)
           OSPIM_P1_IO7(PG11)
           OSPIM_P1_CLK(PF4)
           OSPIM_P1_NCS(PG12) */
    gpio_af_set(GPIOF, GPIO_AF_9, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);

    gpio_af_set(GPIOG, GPIO_AF_9, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_11);
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_11);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_11);

    gpio_af_set(GPIOG, GPIO_AF_3, GPIO_PIN_10 | GPIO_PIN_12);
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10 | GPIO_PIN_12);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_10 | GPIO_PIN_12);

    /* enable SCK, CSN, IO[3:0] and IO[7:4] for OSPIM port1 */
    ospim_port_sck_config(OSPIM_PORT1, OSPIM_PORT_SCK_ENABLE);
    ospim_port_csn_config(OSPIM_PORT1, OSPIM_PORT_CSN_ENABLE);
    ospim_port_io3_0_config(OSPIM_PORT1, OSPIM_IO_LOW_ENABLE);
    ospim_port_io7_4_config(OSPIM_PORT1, OSPIM_IO_HIGH_ENABLE);

    rcu_periph_clock_enable(RCU_OSPI1);
    /* configure OSPIM port1 */
    ospim_port_sck_source_select(OSPIM_PORT1, OSPIM_SCK_SOURCE_OSPI1_SCK);
    ospim_port_csn_source_select(OSPIM_PORT1, OSPIM_CSN_SOURCE_OSPI1_CSN);
    ospim_port_io3_0_source_select(OSPIM_PORT1, OSPIM_SRCPLIO_OSPI1_IO_LOW);
    ospim_port_io7_4_source_select(OSPIM_PORT1, OSPIM_SRCPHIO_OSPI1_IO_HIGH);

    /* initialize the parameters of OSPI struct */
    ospi_struct_init(ospi_struct);

    ospi_struct->prescaler = 3U;
    ospi_struct->sample_shift = OSPI_SAMPLE_SHIFTING_NONE;
    ospi_struct->fifo_threshold = OSPI_FIFO_THRESHOLD_4;
    ospi_struct->device_size = OSPI_MESZ_512_MBS;
    ospi_struct->wrap_size = OSPI_DIRECT;
    ospi_struct->cs_hightime = OSPI_CS_HIGH_TIME_3_CYCLE;
    ospi_struct->memory_type = OSPI_MICRON_MODE;
    ospi_struct->delay_hold_cycle = OSPI_DELAY_HOLD_NONE;

    /* initialize OSPI parameter */
    ospi_init(ospi_periph, ospi_struct);
    /* enable OSPI */
    ospi_enable(ospi_periph);
}

/*!
    \brief      enable ospi mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                             OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                           OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \param[in]  mode: flash interface mode
                only one parameter can be selected which is shown as below:
      \arg        SPI_MODE: SPI mode
      \arg        QSPI_MODE: QSPI mode
      \arg        OSPI_MODE: OSPI mode
    \param[out] none
    \retval     none
*/
void ospi_enable_ospi_mode(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct, interface_mode mode)
{
    ospi_regular_cmd_struct cmd_struct = {0};

    /* initialize write enable command */
    if(SPI_MODE == mode) {
        cmd_struct.ins_mode = OSPI_INSTRUCTION_1_LINE;
    } else if(QSPI_MODE == mode) {
        cmd_struct.ins_mode = OSPI_INSTRUCTION_4_LINES;
    } else {
        cmd_struct.ins_mode = OSPI_INSTRUCTION_8_LINES;
    }
    cmd_struct.operation_type = OSPI_OPTYPE_COMMON_CFG;
    cmd_struct.instruction = CMD_EOIO;
    cmd_struct.ins_size = OSPI_INSTRUCTION_8_BITS;
    cmd_struct.addr_mode = OSPI_ADDRESS_NONE;
    cmd_struct.addr_size = OSPI_ADDRESS_24_BITS;
    cmd_struct.addr_dtr_mode = OSPI_ADDRDTR_MODE_DISABLE;
    cmd_struct.alter_bytes_mode = OSPI_ALTERNATE_BYTES_NONE;
    cmd_struct.alter_bytes_size = OSPI_ALTERNATE_BYTES_24_BITS;
    cmd_struct.alter_bytes_dtr_mode = OSPI_ABDTR_MODE_DISABLE;
    cmd_struct.data_mode = OSPI_DATA_NONE;
    cmd_struct.data_dtr_mode = OSPI_DADTR_MODE_DISABLE;
    cmd_struct.dummy_cycles = OSPI_DUMYC_CYCLES_0;
    cmd_struct.nbdata = 0U;

    /* send the command */
    ospi_command_config(ospi_periph, ospi_struct, &cmd_struct);
}

/*!
    \brief      reset spi mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                             OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                           OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \param[in]  mode: flash interface mode
                only one parameter can be selected which is shown as below:
      \arg        SPI_MODE: SPI mode
      \arg        QSPI_MODE: QSPI mode
      \arg        OSPI_MODE: OSPI mode
    \param[out] none
    \retval     none
*/
void ospi_reset_spi_mode(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct, interface_mode mode)
{
    ospi_regular_cmd_struct cmd_struct = {0};

    /* initialize write enable command */
    if(SPI_MODE == mode) {
        cmd_struct.ins_mode = OSPI_INSTRUCTION_1_LINE;
    } else if(QSPI_MODE == mode) {
        cmd_struct.ins_mode = OSPI_INSTRUCTION_4_LINES;
    } else {
        cmd_struct.ins_mode = OSPI_INSTRUCTION_8_LINES;
    }
    cmd_struct.operation_type = OSPI_OPTYPE_COMMON_CFG;
    cmd_struct.instruction = CMD_RSTIO;
    cmd_struct.ins_size = OSPI_INSTRUCTION_8_BITS;
    cmd_struct.addr_mode = OSPI_ADDRESS_NONE;
    cmd_struct.addr_size = OSPI_ADDRESS_24_BITS;
    cmd_struct.addr_dtr_mode = OSPI_ADDRDTR_MODE_DISABLE;
    cmd_struct.alter_bytes_mode = OSPI_ALTERNATE_BYTES_NONE;
    cmd_struct.alter_bytes_size = OSPI_ALTERNATE_BYTES_24_BITS;
    cmd_struct.alter_bytes_dtr_mode = OSPI_ABDTR_MODE_DISABLE;
    cmd_struct.data_mode = OSPI_DATA_NONE;
    cmd_struct.data_dtr_mode = OSPI_DADTR_MODE_DISABLE;
    cmd_struct.dummy_cycles = OSPI_DUMYC_CYCLES_0;
    cmd_struct.nbdata = 0U;

    /* send the command */
    ospi_command_config(ospi_periph, ospi_struct, &cmd_struct);
}

/*!
    \brief      ospi write data
    \param[in]  ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                             OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                           OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \param[in]  addr: write start address
    \param[in]  pdata: pointer to data to be written
    \param[in]  data_size: size of data to write
    \param[out] none
    \retval     none
*/
void ospi_write(ospi_parameter_struct *ospi_struct, uint32_t addr, uint8_t *pdata, uint32_t data_size)
{
    ospi_regular_cmd_struct cmd_struct = {0};

    /* initialize program command */
    cmd_struct.instruction = CMD_WRITE;
    cmd_struct.ins_mode = OSPI_INSTRUCTION_8_LINES;
    cmd_struct.addr_mode = OSPI_ADDRESS_8_LINES;
    cmd_struct.data_mode = OSPI_DATA_8_LINES;
    cmd_struct.operation_type = OSPI_OPTYPE_COMMON_CFG;
    cmd_struct.ins_size = OSPI_INSTRUCTION_8_BITS;
    cmd_struct.address = addr | ADDR_NO_INC;
    cmd_struct.addr_size = OSPI_ADDRESS_16_BITS;
    cmd_struct.addr_dtr_mode = OSPI_ADDRDTR_MODE_DISABLE;
    cmd_struct.alter_bytes_mode = OSPI_ALTERNATE_BYTES_NONE;
    cmd_struct.alter_bytes_size = OSPI_ALTERNATE_BYTES_24_BITS;
    cmd_struct.alter_bytes_dtr_mode = OSPI_ABDTR_MODE_DISABLE;
    cmd_struct.nbdata = data_size;
    cmd_struct.data_dtr_mode = OSPI_DADTR_MODE_DISABLE;
    cmd_struct.dummy_cycles = OSPI_DUMYC_CYCLES_0;

    /* send the command */
    ospi_command_config(OSPI1, ospi_struct, &cmd_struct);
    /* transmission of the data */
    ospi_transmit(OSPI1, pdata);
}

/*!
    \brief      ospi read data
    \param[in]  ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                             OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                           OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \param[in]  addr: read start address
    \param[in]  pdata: pointer to data to be read
    \param[in]  data_size: size of data to read
    \param[out] none
    \retval     none
*/
void ospi_read(ospi_parameter_struct *ospi_struct, uint32_t addr, uint8_t *pdata, uint32_t data_size)
{
    ospi_regular_cmd_struct cmd_struct = {0};

    /* initialize program command */
    cmd_struct.instruction = CMD_READ;
    cmd_struct.ins_mode = OSPI_INSTRUCTION_8_LINES;
    cmd_struct.addr_mode = OSPI_ADDRESS_8_LINES;
    cmd_struct.data_mode = OSPI_DATA_8_LINES;
    cmd_struct.dummy_cycles = OSPI_DUMYC_CYCLES_8;
    cmd_struct.operation_type = OSPI_OPTYPE_COMMON_CFG;
    cmd_struct.ins_size = OSPI_INSTRUCTION_8_BITS;
    cmd_struct.address = addr | ADDR_NO_INC;
    cmd_struct.addr_size = OSPI_ADDRESS_16_BITS;
    cmd_struct.addr_dtr_mode = OSPI_ADDRDTR_MODE_DISABLE;
    cmd_struct.alter_bytes_mode = OSPI_ALTERNATE_BYTES_NONE;
    cmd_struct.alter_bytes_size = OSPI_ALTERNATE_BYTES_24_BITS;
    cmd_struct.alter_bytes_dtr_mode = OSPI_ABDTR_MODE_DISABLE;
    cmd_struct.nbdata = data_size;
    cmd_struct.data_dtr_mode = OSPI_DADTR_MODE_DISABLE;

    /* send the command */
    ospi_command_config(OSPI1, ospi_struct, &cmd_struct);
    /* receive of the data */
    ospi_receive(OSPI1, pdata);
}

/*!
    \brief      write esc core reg by csr
    \param[in]  writebuffer: pointer to data to be written
    \param[in]  address: write start address
    \param[in]  count: size of data to write
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                             OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                           OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \param[out] none
    \retval     none
*/
static void ospi_write_reg(uint8_t *writebuffer, uint16_t address, uint8_t count, ospi_parameter_struct *ospi_struct)
{
    UINT32_VAL param32_1 = {0};
    uint32_t i = 0U;
    UINT16_VAL waddr;

    /*Reset/Stop any previous commands.*/
    param32_1.Val = (unsigned long int)ESC_CCTL_CMD_CCTL_STOP;
    ospi_write(ospi_struct, ESC_CCTL_CMD, &param32_1.v[0], 4U);

    /*wait the BUSY bit clear.*/
    do {
        ospi_read(ospi_struct, ESC_CCTL_CMD, &param32_1.v[0], 4U);
    } while((param32_1.v[3] & BUSY_MASK));

    for(i = 0U; i < count; i++) {
        param32_1.v[i] = writebuffer[i];
    }

    /*write buffer data to ESC_CCTL_DATA register.*/
    ospi_write(ospi_struct, ESC_CCTL_DATA, &param32_1.v[0], 4U);

    waddr.Val = address;

    param32_1.v[0] = waddr.byte.LB;
    param32_1.v[1] = waddr.byte.HB;
    param32_1.v[2] = count;
    param32_1.v[3] = ESC_WRITE_BYTE;

    /*write Address to ESC_CCTL_CMD register.*/
    ospi_write(ospi_struct, ESC_CCTL_CMD, &param32_1.v[0], 4U);

    /*wait the BUSY bit clear.*/
    do {
        ospi_read(ospi_struct, ESC_CCTL_CMD, &param32_1.v[0], 4U);
    } while(param32_1.v[3] & ESC_CSR_BUSY);
}

/*!
    \brief      read esc core reg by csr
    \param[in]  readbuffer: pointer to data to be read
    \param[in]  address: read start address
    \param[in]  count: size of data to read
    \param[in]  ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                             OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                           OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \param[out] none
    \retval     none
*/
static void ospi_read_reg(uint8_t *readbuffer, uint16_t address, uint8_t count, ospi_parameter_struct *ospi_struct)
{
    UINT32_VAL param32_1 = {0};
    uint32_t i = 0U;
    UINT16_VAL waddr;

    waddr.Val = address;

    /*Reset/Stop any previous commands.*/
    param32_1.Val = (unsigned long int)ESC_CCTL_CMD_CCTL_STOP;
    ospi_write(ospi_struct, ESC_CCTL_CMD, &param32_1.v[0], 4U);

    /*wait the BUSY bit clear.*/
    do {
        ospi_read(ospi_struct, ESC_CCTL_CMD, &param32_1.v[0], 4U);
    } while((param32_1.v[3] & BUSY_MASK));

    param32_1.v[0] = waddr.byte.LB;
    param32_1.v[1] = waddr.byte.HB;
    param32_1.v[2] = count;
    param32_1.v[3] = ESC_READ_BYTE;

    /*write Address to ESC_CCTL_CMD register.*/
    ospi_write(ospi_struct, ESC_CCTL_CMD, &param32_1.v[0], 4U);

    /*wait the BUSY bit clear.*/
    do {
        ospi_read(ospi_struct, ESC_CCTL_CMD, &param32_1.v[0], 4U);

    } while(param32_1.v[3] & ESC_CSR_BUSY);

    /*read buffer data from ESC_CCTL_DATA register.*/
    ospi_read(ospi_struct, ESC_CCTL_DATA, &param32_1.v[0], 4U);

    for(i = 0; i < count; i++) {
        readbuffer[i] = param32_1.v[i];
    }
}

/*!
    \brief      ospi_write_pdram
    \param[in]  writebuffer: pointer to data to be written
    \param[in]  address: write start address
    \param[in]  count: size of data to write
    \param[in]  ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                             OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                           OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \param[out] none
    \retval     none
*/
static void ospi_write_pdram(uint8_t *writebuffer, uint16_t address, uint16_t count, ospi_parameter_struct *ospi_struct)
{
    UINT32_VAL param32_1 = {0};
    uint16_t i = 0U, nlength, nbyte_position;

    /*Reset or Stop any previous commands.*/
    param32_1.Val = ESC_PRAM_CR_PRAM_STOP_WRITE;
    ospi_write(ospi_struct, ESC_PRAM_CW, &param32_1.v[0], 4U);

    /*wait the BUSY bit clear.*/
    do {
        ospi_read(ospi_struct, ESC_PRAM_CW, &param32_1.v[0], 4U);
    } while((param32_1.v[3] & BUSY_MASK));

    /* Write address and length in the ESC PRAM address and length write register (ESC_PRAM_ALW) */
    param32_1.w[0] = address;
    param32_1.w[1] = count;
    ospi_write(ospi_struct, ESC_PRAM_ALW, &param32_1.v[0], 4U);

    /*Set PRAM Write Busy (PRAM_BUSY_WRITE) bit(ESC PRAM command write register) to start write operatrion*/
    param32_1.Val = ESC_PRAM_CR_PRAM_BUSY_WRITE;
    ospi_write(ospi_struct, ESC_PRAM_CW, &param32_1.v[0], 4U);

    /*Write data to ESC PRAM FIFO data write register */
    nbyte_position = (address & 0x0003U);
    nlength = (4U - nbyte_position) > count ? count : (4U - nbyte_position);
    param32_1.Val = 0U;
    memcpy(&param32_1.v[nbyte_position], writebuffer + i, nlength);
    ospi_write(ospi_struct, ESC_PRAM_FIFO_DW, &param32_1.v[0], 4U);
    count -= nlength;
    i += nlength;

    while(count) {
        nlength = count > 4 ? 4 : count;
        param32_1.Val = 0;
        memcpy(&param32_1, (writebuffer + i), nlength);
        ospi_write(ospi_struct, ESC_PRAM_FIFO_DW, &param32_1.v[0], 4U);
        i += nlength;
        count -= nlength;
    }
}

/*!
    \brief      ospi read pdram
    \param[in]  readbuffer: pointer to data to be read
    \param[in]  address: read start address
    \param[in]  count: size of data to read
    \param[in]  ospi_struct: OSPI parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
                  sample_shift: OSPI_SAMPLE_SHIFTING_NONE, OSPI_SAMPLE_SHIFTING_HALF_CYCLE
                  device_size: OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                             OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
                  cs_hightime: OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
                  memory_type: OSPI_MICRON_MODE, OSPI_MACRONIX_MODE, OSPI_STANDARD_MODE
                             OSPI_MACRONIX_RAM_MODE,
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                           OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
                  delay_hold_cycle: OSPI_DELAY_HOLD_NONE, OSPI_DELAY_HOLD_QUARTER_CYCLE
    \param[out] none
    \retval     none
*/
static void ospi_read_pdram(uint8_t *readbuffer, uint16_t address, uint16_t count, ospi_parameter_struct *ospi_struct)
{
    UINT32_VAL param32_1 = {0};
    uint16_t i = 0U, nlength, nbyte_position;

    /*Reset/stop any previous commands.*/
    param32_1.Val = (unsigned long int)ESC_PRAM_CR_PRAM_STOP_READ;
    ospi_write(ospi_struct, ESC_PRAM_CR, &param32_1.v[0], 4U);

    /*wait the BUSY bit clear.*/
    do {
        ospi_read(ospi_struct, ESC_PRAM_CR, &param32_1.v[0], 4U);
    } while((param32_1.v[3] & BUSY_MASK));

    /*Write address and length in the ESC PRAM address and length read register (ESC_PRAM_ALR)*/
    param32_1.w[0] = address;
    param32_1.w[1] = count;
    ospi_write(ospi_struct, ESC_PRAM_ALR, &param32_1.v[0], 4U);

    /*Set PRAM Read Busy (PRAM_BUSY_READ) bit(ESC PRAM command read register) to start read operation*/
    param32_1.Val = ESC_PRAM_CR_PRAM_BUSY_READ;
    ospi_write(ospi_struct, ESC_PRAM_CR, &param32_1.v[0], 4U);

    /*Read data from ESC PRAM FIFO data read register */
    ospi_read(ospi_struct, ESC_PRAM_FIFO_DR, &param32_1.v[0], 4U);
    nbyte_position = (address & 0x0003U);
    nlength = (4U - nbyte_position) > count ? count : (4U - nbyte_position);
    memcpy(readbuffer + i, &param32_1.v[nbyte_position], nlength);
    count -= nlength;
    i += nlength;

    while(count) {
        ospi_read(ospi_struct, ESC_PRAM_FIFO_DR, &param32_1.v[0], 4U);
        nlength = count > 4 ? 4 : count;
        memcpy((readbuffer + i), &param32_1, nlength);
        i += nlength;
        count -= nlength;
    }
}

/*!
    \brief      read esc register
    \param[in]  readbuffer: pointer to data to be read
    \param[in]  address: read start address
    \param[in]  count: size of data to read
    \param[out] none
    \retval     none
*/
void ospi_read_register(uint8_t *readbuffer, uint16_t address, uint16_t count)
{
    if(address >= 0x1000U) {
        ospi_read_pdram(readbuffer, address, count, &ospi_init_struct);
    } else {
        ospi_read_reg(readbuffer, address, count, &ospi_init_struct);
    }
}

/*!
    \brief      write esc register
    \param[in]  writebuffer: pointer to data to be write
    \param[in]  address: write start address
    \param[in]  count: size of data to write
    \param[out] none
    \retval     none
*/
void ospi_write_register(uint8_t *writebuffer, uint16_t address, uint16_t count)
{
    if(address >= 0x1000U) {
        ospi_write_pdram(writebuffer, address, count, &ospi_init_struct);
    } else {
        ospi_write_reg(writebuffer, address, count, &ospi_init_struct);
    }
}
