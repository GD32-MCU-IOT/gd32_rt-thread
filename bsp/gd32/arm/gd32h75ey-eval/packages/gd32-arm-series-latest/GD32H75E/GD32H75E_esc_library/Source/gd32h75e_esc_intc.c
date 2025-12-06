/*!
    \file    gd32h75e_esc_intc.c
    \brief   ESC intc driver basic configuration

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
#include "gd32h75e_esc_ospi.h"
#include "gd32h75e_esc_intc.h"

/* INTC_CTL_DEAS offset */
#define INTC_CTL_DEAS_OFFSET                ((uint32_t)24U)

/* read and write register value */
static uint32_t read_intc_register(uint32_t reg_address);
static void write_intc_register(uint32_t reg_address, uint32_t temp_value);

/*!
    \brief      read INTC register value
    \param[in]  reg: input register address
      \arg        INTC_CTL: INTC control register
      \arg        INTC_FLAG: INTC flag register
      \arg        INTC_EN: INTC enable register
    \param[out] none
    \retval     value of INTC ESC register: 0 - 0xFFFFFFFF
*/
static uint32_t read_intc_register(uint32_t reg_address)
{
    uint32_t temp_value;
    ospi_read(&ospi_init_struct, reg_address, (uint8_t *)&temp_value, 4U);
    return temp_value;
}

/*!
    \brief      write INTC register value
    \param[in]  reg: input register address
      \arg        INTC_CTL: INTC control register
      \arg        INTC_FLAG: INTC flag register
      \arg        INTC_EN: INTC enable register
    \param[in]  temp_value: value of INTC ESC register(0 - 0xFFFFFFFF)
    \param[out] none
    \retval     none
*/
static void write_intc_register(uint32_t reg_address, uint32_t temp_value)
{
    ospi_write(&ospi_init_struct, reg_address, (uint8_t *)&temp_value, 4U);
}

/*!
    \brief      configure INTC interrupt de-assertion interval
    \param[in]  deas: configure the de-assertion interval, uints in 10us, must be between 0 and 0xFF
      \arg        0x00 - 0xFF
    \param[out] none
    \retval     none
*/
void intc_deas_config(uint8_t deas)
{
    uint32_t temp_value;

    temp_value = read_intc_register(INTC_CTL);
    temp_value &= ~INTC_CTL_DEAS;
    temp_value |= ((uint32_t)deas << INTC_CTL_DEAS_OFFSET);
    write_intc_register(INTC_CTL, temp_value);
}

/*!
    \brief      configure INTC interrupt de-assertion interval clear
    \param[in]  deasc: clear de-assertion interval counter
                only one parameter can be selected which is shown as below:
      \arg        INTC_DEAS: no effect
      \arg        INTC_DEAS_CLEAR: clear interrupt de-assertion interval
    \param[out] none
    \retval     none
*/
void intc_deasc_config(uint32_t deasc)
{
    uint32_t temp_value;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_INTC_CTL_DEASC(deasc)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0002U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp_value = read_intc_register(INTC_CTL);
        temp_value &= ~INTC_CTL_DEASC;
        temp_value |= deasc;
        write_intc_register(INTC_CTL, temp_value);
    }
}

/*!
    \brief      configure IRQ pin out enable, polarity, clock and mode
    \param[in]  irqen: IRQ pin output enable
      \arg        IRQ_DISABLE: Disable IRQ pin output
      \arg        IRQ_ENABLE: Enable IRQ pin output
    \param[in]  irqpol: IRQ pin output polarity
      \arg        IRQ_POL_LOW: IRQ pin output activation level is low
      \arg        IRQ_POL_HIGH: IRQ pin output activation level is high
    \param[in]  irqckout: IRQ clock output
      \arg        IRQ_NO_CKOUT: No clock output
      \arg        IRQ_CKOUT: IRQ pin output crystal oscillator clock
    \param[in]  irqmode: IRQ pin output mode
      \arg        IRQ_OPEN_DRAIN_MODE: Output open-drain mode
      \arg        IRQ_OPEN_DRAIN_MODE: Output push-pull mode
    \param[out] none
    \retval     none
*/
void intc_irq_config(uint32_t irqen, uint32_t irqpol, uint32_t irqckout, uint32_t irqmode)
{
    uint32_t temp_value;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_INTC_CTL_IRQEN(irqen)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_INTC_CTL_IRPOL(irqpol)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_INTC_CTL_IRQCKOUT(irqckout)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_INTC_CTL_IRQMODE(irqmode)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp_value = read_intc_register(INTC_CTL);
        temp_value &= ~(INTC_CTL_IRQEN | INTC_CTL_IRQPOL | INTC_CTL_IRQCKOUT | INTC_CTL_IRQMODE);
        temp_value |= irqen | irqpol | irqckout | irqmode;
        write_intc_register(INTC_CTL, temp_value);
    }
}

/*!
    \brief      enable INTC interrupt
    \param[in]  int_type: INTC interrupt enable type
                only one parameter can be selected which is shown as below:
      \arg        SW_INT_ENABLE: enable software interrupt
      \arg        READY_INT_ENABLE: enable device ready interrupt
      \arg        PHYB_INT_ENABLE: enable ethernet PHY B interrupt
      \arg        PHYA_INT_ENABLE: enable ethernet PHY A interrupt
      \arg        TIM_INT_ENABLE: enable timer interrupt
      \arg        PME_INT_ENABLE: enable PME interrupt
      \arg        AHB2OPB_INT_ENABLE: enable AHB2OPB bridge interrupt
      \arg        ECAT_INT_ENABLE: enable etherCAT interrupt
    \param[out] none
    \retval     none
*/
void intc_interrupt_enable(intc_enable_enum int_type)
{
    uint32_t temp_value;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_INTC_ENABLE(int_type)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0004U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp_value = read_intc_register(INTC_EN);
        temp_value |= int_type;
        write_intc_register(INTC_EN, temp_value);
    }
}

/*!
    \brief      disable INTC interrupt
    \param[in]  int_type: INTC interrupt disable type
                only one parameter can be selected which is shown as below:
      \arg        SW_INT_DISABLE: disable software interrupt
      \arg        READY_INT_DISABLE: disable device ready interrupt
      \arg        PHYB_INT_DISABLE: disable ethernet PHY B interrupt
      \arg        PHYA_INT_DISABLE: disable ethernet PHY A interrupt
      \arg        TIM_INT_DISABLE: disable timer interrupt
      \arg        PME_INT_DISABLE: disable PME interrupt
      \arg        AHB2OPB_INT_DISABLE: disable AHB2OPB bridge interrupt
      \arg        ECAT_INT_DISABLE: disable etherCAT interrupt
    \param[out] none
    \retval     none
*/
void intc_interrupt_disable(intc_disable_enum int_type)
{
    uint32_t temp_value;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_INTC_ENABLE(int_type)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0005U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp_value = read_intc_register(INTC_EN);
        temp_value &= ~int_type;
        write_intc_register(INTC_EN, temp_value);
    }
}

/*!
    \brief      get INTC interrupt flag
    \param[in]  flag_type: INTC interrupt flag type
                only one parameter can be selected which is shown as below:
      \arg        SW_INT_FLAG_GET: get software interrupt flag
      \arg        READY_INT_FLAG_GET: get device ready interrupt flag
      \arg        PHYB_INT_FLAG_GET: get ethernet PHY B interrupt flag
      \arg        PHYA_INT_FLAG_GET: get ethernet PHY A interrupt flag
      \arg        TIM_INT_FLAG_GET: get timer interrupt flag
      \arg        PME_INT_FLAG_GET: get PME interrupt flag
      \arg        AHB2OPB_INT_FLAG_GET: get AHB2OPB bridge interrupt flag
      \arg        ECAT_INT_FLAG_GET: get etherCAT interrupt flag
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus intc_interrupt_flag_get(intc_get_flag_enum flag_type)
{
    uint32_t temp_value;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_INTC_FLAG_GET(flag_type)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0006U), ERR_PARAM_OUT_OF_RANGE);
        return RESET;
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp_value = read_intc_register(INTC_FLAG);
    }

    if(temp_value & flag_type) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear INTC interrupt flag
    \param[in]  flag_type: INTC interrupt flag type
                only one parameter can be selected which is shown as below:
      \arg        SW_INT_FLAG_CLEAR: clear software interrupt flag
      \arg        READY_INT_FLAG_CLEAR: clear device ready interrupt flag
      \arg        TIM_INT_FLAG_CLEAR: clear timer interrupt flag
      \arg        PME_INT_FLAG_CLEAR: clear PME interrupt flag
    \param[out] none
    \retval     none
*/
void intc_interrupt_flag_clear(intc_clear_flag_enum flag_type)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_INTC_FLAG_CLEAR(flag_type)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        write_intc_register(INTC_FLAG, flag_type);
    }
}

/*!
    \brief      get interrupt de-assertion interval status
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus intc_deasstat_get(void)
{
    uint32_t temp_value;
    temp_value = read_intc_register(INTC_CTL);

    if(temp_value & INTC_CTL_DEASSTAT) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      get internal IRQ line status
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus intc_irqstat_get(void)
{
    uint32_t temp_value;
    temp_value = read_intc_register(INTC_CTL);

    if(temp_value & INTC_CTL_IRQSTAT) {
        return SET;
    } else {
        return RESET;
    }
}
