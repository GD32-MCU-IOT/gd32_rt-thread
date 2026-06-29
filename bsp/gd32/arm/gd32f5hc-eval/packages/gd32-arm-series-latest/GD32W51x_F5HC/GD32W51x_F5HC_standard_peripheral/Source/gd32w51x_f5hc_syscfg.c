/*!
    \file    gd32w51x_f5hc_syscfg.c
    \brief   SYSCFG driver

    \version 2026-04-15, V2.0.0, firmware for gd32w51x_f5hc
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

#include "gd32w51x_f5hc_syscfg.h"

/* SYSCFG register bit mask */
#define SYSCFG_CFG1_MASK              ((uint32_t)0x00000005U)               /*!< SYSCFG_CFG1 mask */
#define SYSCFG_FPUINTEN_MASK          ((uint32_t)0x0000003FU)               /*!< FPU interrupt enable mask */

/*!
    \brief      reset the SYSCFG registers (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_deinit(void)
{
    rcu_periph_reset_enable(RCU_SYSCFGRST);
    rcu_periph_reset_disable(RCU_SYSCFGRST);
}

/*!
    \brief      configure the GPIO pin as EXTI Line (API_ID(0x0002U))
    \param[in]  exti_port: specify the GPIO port used in EXTI
                only one parameter can be selected which is shown as below:
      \arg          EXTI_SOURCE_GPIOx(x = A,B,C,D): EXTI GPIO port
    \param[in]  exti_pin: specify the EXTI line
                only one parameter can be selected which is shown as below:
      \arg          EXTI_SOURCE_PINx(GPIOA x = 0..15, GPIOB x = 0..15, GPIOC x = 0..15, GPIOD x = 0..6): EXTI GPIO pin
    \param[out] none
    \retval     none
*/
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin)
{
    uint32_t clear_exti_mask = ~((uint32_t)EXTI_SS_MASK << (EXTI_SS_MSTEP(exti_pin)));
    uint32_t config_exti_mask = ((uint32_t)exti_port) << (EXTI_SS_MSTEP(exti_pin));

    switch(exti_pin / EXTI_SS_JSTEP) {
    case EXTISS0:
        /* clear EXTI source line(0..3) */
        SYSCFG_EXTISS0 &= clear_exti_mask;
        /* configure EXTI source line(0..3) */
        SYSCFG_EXTISS0 |= config_exti_mask;
        break;
    case EXTISS1:
        /* clear EXTI source line(4..7) */
        SYSCFG_EXTISS1 &= clear_exti_mask;
        /* configure EXTI source line(4..7) */
        SYSCFG_EXTISS1 |= config_exti_mask;
        break;
    case EXTISS2:
        /* clear EXTI source line(8..11) */
        SYSCFG_EXTISS2 &= clear_exti_mask;
        /* configure EXTI source line(8..11) */
        SYSCFG_EXTISS2 |= config_exti_mask;
        break;
    case EXTISS3:
        /* clear EXTI source line(12..15) */
        SYSCFG_EXTISS3 &= clear_exti_mask;
        /* configure EXTI source line(12..15) */
        SYSCFG_EXTISS3 |= config_exti_mask;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable the compensation cell (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_compensation_pwdn_mode_enable(void)
{
    SYSCFG_CPSCTL |= SYSCFG_CPSCTL_CPS_EN;
}

/*!
    \brief      disable the compensation cell (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_compensation_pwdn_mode_disable(void)
{
    SYSCFG_CPSCTL &= ~(SYSCFG_CPSCTL_CPS_EN);
}

/*!
    \brief      configure SYSCFG clock control security (API_ID(0x0005U))
    \param[in]  access_mode: secure access or secure and non-secure access
                only one parameter can be selected which is shown as below:
                  SYSCFG_SECURE_ACCESS: SYSCFG configuration clock in RCU registers can be written by secure access only
                  SYSCFG_SECURE_NONSECURE_ACCESS: SYSCFG configuration clock in RCU registers can be written by secure and nonsecure access
    \param[out] none
    \retval     none
*/
void syscfg_clock_access_security_config(uint32_t access_mode)
{
    if(access_mode == SYSCFG_SECURE_ACCESS) {
        SYSCFG_SECCFG |= SYSCFG_SECCFG_SYSCFGSE;
    } else if(access_mode == SYSCFG_SECURE_NONSECURE_ACCESS) {
        SYSCFG_SECCFG &= ~SYSCFG_SECCFG_SYSCFGSE;
    } else {
        /* do nothing */
    }
}

/*!
    \brief      configure ClassB security (API_ID(0x0006U))
    \param[in]  access_mode: secure access or secure and non-secure access
                only one parameter can be selected which is shown as below:
                  CLASSB_SECURE_ACCESS: SYSCFG_CFG1 register can be written by secure access only
                  CLASSB_SECURE_NONSECURE_ACCESS: SYSCFG_CFG1 register can be written by secure and non-secure access
    \param[out] none
    \retval     none
*/
void syscfg_classb_access_security_config(uint32_t access_mode)
{
    if(access_mode == CLASSB_SECURE_ACCESS) {
        SYSCFG_SECCFG |= SYSCFG_SECCFG_CLASSBSE;
    } else if(access_mode == CLASSB_SECURE_NONSECURE_ACCESS) {
        SYSCFG_SECCFG &= ~SYSCFG_SECCFG_CLASSBSE;
    } else {
        /* do nothing */
    }
}

/*!
    \brief      configure SRAM1 security (API_ID(0x0007U))
    \param[in]  access_mode: secure access or secure and non-secure access
                only one parameter can be selected which is shown as below:
                  SRAM1_SECURE_ACCESS: SYSCFG_SKEY, SYSCFG_SCS and SYSCFG_SWPx registers can be written by secure only
                  SRAM1_SECURE_NONSECURE_ACCESS: SYSCFG_SKEY, SYSCFG_SCS and SYSCFG_SWPx registers can be written by secure and non-secure access
    \param[out] none
    \retval     none
*/
void syscfg_sram1_access_security_config(uint32_t access_mode)
{
    if(access_mode == SRAM1_SECURE_ACCESS) {
        SYSCFG_SECCFG |= SYSCFG_SECCFG_SRAM1SE;
    } else if(access_mode == SRAM1_SECURE_NONSECURE_ACCESS) {
        SYSCFG_SECCFG &= ~SYSCFG_SECCFG_SRAM1SE;
    } else {
        /* do nothing */
    }
}

/*!
    \brief      configure FPU security (API_ID(0x0008U))
    \param[in]  access_mode: secure access or secure and non-secure access
                only one parameter can be selected which is shown as below:
                  FPU_SECURE_ACCESS: SYSCFG_FPUINTEN register can be written by secure access only
                  FPU_SECURE_NONSECURE_ACCESS: SYSCFG_FPUINTEN register can be written by secure and non-secure access
    \param[out] none
    \retval     none
*/
void syscfg_fpu_access_security_config(uint32_t access_mode)
{
    if(access_mode == FPU_SECURE_ACCESS) {
        SYSCFG_SECCFG |= SYSCFG_SECCFG_FPUSE;
    } else if(access_mode == FPU_SECURE_NONSECURE_ACCESS) {
        SYSCFG_SECCFG &= ~SYSCFG_SECCFG_FPUSE;
    } else {
        /* do nothing */
    }
}

/*!
    \brief      disable VTOR_NS register write (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_vtor_ns_write_disable(void)
{
    SYSCFG_CNSLOCK |= SYSCFG_CNSLOCK_LOCKNSVTOR;
}

/*!
    \brief      disable Non-secure MPU registers write (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_mpu_ns_write_disable(void)
{
    SYSCFG_CNSLOCK |= SYSCFG_CNSLOCK_LOCKNSMPU;
}

/*!
    \brief      disable VTOR_S register PRIS and BFHFNMINS bits in the AIRCR register write (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_vtors_aircr_write_disable(void)
{
    SYSCFG_CSLOCK |= SYSCFG_CSLOCK_VTSAIRLK;
}

/*!
    \brief      disable secure MPU registers writes (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_mpu_s_write_disable(void)
{
    SYSCFG_CSLOCK |= SYSCFG_CSLOCK_SMPULK;
}

/*!
    \brief      disable SAU registers write (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_sau_write_disable(void)
{
    SYSCFG_CSLOCK |= SYSCFG_CSLOCK_SAULK;
}

/*!
    \brief      connect TIMER0/15/16 break input to the selected parameter (API_ID(0x000EU))
    \param[in]  syscfg_lock: specify the parameter to be connected
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_LOCK_LOCKUP: Cortex-M3 lockup output connected to the break input
      \arg        SYSCFG_LOCK_LVD: LVD interrupt connected to the break input
    \param[out] none
    \retval     none
*/
void syscfg_lock_config(uint32_t syscfg_lock)
{
    SYSCFG_CFG1 |= syscfg_lock & SYSCFG_CFG1_MASK;
}

/*!
    \brief      write data to GSSA (API_ID(0x000FU))
    \param[in]  data: the data to be written in to GSSA
    \param[out] none
    \retval     none
*/
void syscfg_gssacmd_write_data(uint8_t data)
{
    SYSCFG_GSSACMD = (uint32_t)data;
}

/*!
    \brief      enable sram1 erase (API_ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: status of result (SUCCESS or ERROR)
*/
ErrStatus syscfg_sram1_erase(void)
{
    ErrStatus status;
    if(SET == (SYSCFG_SCS & SYSCFG_SCS_SRAM1BSY)) {
        status = ERROR;
    } else {
        SYSCFG_SCS |= SYSCFG_SCS_SRAM1ERS;
        status = SUCCESS;
    }
    return status;
}

/*!
    \brief      unlock the write protection of the SRAM1ERS bit in the SYSCFG_SCS register (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_sram1_unlock(void)
{
    SYSCFG_SKEY |= SRAM1ERS_UNLOCK_KEY0;
    SYSCFG_SKEY |= SRAM1ERS_UNLOCK_KEY1;
}

/*!
    \brief      lock the write protection of the SRAM1ERS bit in the SYSCFG_SCS register (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_sram1_lock(void)
{
    SYSCFG_SKEY |= SRAM1ERS_LOCK_KEY0;
    SYSCFG_SKEY |= SRAM1ERS_LOCK_KEY1;
}

/*!
    \brief      SRAM1 write protect range from page0 to page31 (API_ID(0x0013U))
    \param[in]  page: specify the page of SRAM1 to protect
                one or more parameters can be selected which is shown as below:
      \arg          SRAM1_PAGEx_WRITE_PROTECT: enable write protection of SRAM1 page x (x=0,1,...31)
    \param[out] none
    \retval     none
*/
void syscfg_sram1_write_protect_0_31(uint32_t page)
{
    SYSCFG_SWP0 |= (uint32_t)page;
}

/*!
    \brief      SRAM1 write protect range from page32 to page63 (API_ID(0x0014U))
    \param[in]  page: specify the page of SRAM1 to protect
                one or more parameters can be selected which is shown as below:
      \arg          SRAM1_PAGEx_WRITE_PROTECT: enable write protection of SRAM1 page x (x=32,33,...63)
    \param[out] none
    \retval     none
*/
void syscfg_sram1_write_protect_32_63(uint32_t page)
{
    SYSCFG_SWP1 |= (uint32_t)page;
}

/*!
    \brief      get the compensation ready flag (API_ID(0x0015U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus syscfg_compensation_ready_flag_get(void)
{
    FlagStatus status;
    if(RESET != (SYSCFG_CPSCTL & SYSCFG_CPSCTL_CPS_RDY)) {
        status = SET;
    } else {
        status = RESET;
    }
    return status;
}

/*!
    \brief      get SRAM1 erase busy flag (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET of RESET
*/
FlagStatus syscfg_sram1_bsy_flag_get(void)
{
    FlagStatus status;
    if(RESET != (SYSCFG_SCS & SRAM1_BSY_FLAG)) {
        status = SET;
    } else {
        status = RESET;
    }
    return status;
}

/*!
    \brief      enable floating point unit interrupt (API_ID(0x0017U))
    \param[in]  interrupt: interrupt type
                one or more parameter can be selected which is shown as below:
      \arg          INVALID_OPERATION_INT: invalid operation Interrupt
      \arg          DIVIDE_BY_ZERO_INT: divide-by-zero interrupt
      \arg          UNDERFLOW_INT: underflow interrupt
      \arg          OVERFLOW_INT: overflow interrupt
      \arg          INPUT_ABNORMAL_INT: input abnormal interrupt
      \arg          INEXACT_INT: inexact interrupt (interrupt disable at reset)
    \param[out] none
    \retval     none
*/
void syscfg_fpu_interrupt_enable(uint32_t interrupt)
{
    SYSCFG_FPUINTEN |= interrupt & SYSCFG_FPUINTEN_MASK;
}

/*!
    \brief      disable floating point unit interrupt (API_ID(0x0018U))
    \param[in]  interrupt: interrupt type
                one or more parameter can be selected which is shown as below:
      \arg          INVALID_OPERATION_INT: invalid operation Interrupt
      \arg          DIVIDE_BY_ZERO_INT: divide-by-zero interrupt
      \arg          UNDERFLOW_INT: underflow interrupt
      \arg          OVERFLOW_INT: overflow interrupt
      \arg          INPUT_ABNORMAL_INT: input abnormal interrupt
      \arg          INEXACT_INT: inexact interrupt (interrupt disable at reset)
    \param[out] none
    \retval     none
*/
void syscfg_fpu_interrupt_disable(uint32_t interrupt)
{
    SYSCFG_FPUINTEN &= ~(interrupt & SYSCFG_FPUINTEN_MASK);
}
