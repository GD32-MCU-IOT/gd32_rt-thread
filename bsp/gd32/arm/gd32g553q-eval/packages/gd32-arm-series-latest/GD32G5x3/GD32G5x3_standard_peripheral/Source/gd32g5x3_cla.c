/*!
    \file    gd32g5x3_cla.c
    \brief   CLA driver

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

#include "gd32g5x3_cla.h"

/*!
    \brief      reset CLA
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cla_deinit(void)
{
    rcu_periph_reset_enable(RCU_CLARST);
    rcu_periph_reset_disable(RCU_CLARST);
}

/*!
    \brief      enable CLA
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void cla_enable(cla_enum cla_periph)
{
    switch(cla_periph){
        case CLA0:
             CLA_GCTL |= CLA_GCTL_CLA0EN;
             break;
        case CLA1:
             CLA_GCTL |= CLA_GCTL_CLA1EN;
             break;
        case CLA2:
             CLA_GCTL |= CLA_GCTL_CLA2EN;
             break;
        case CLA3:
             CLA_GCTL |= CLA_GCTL_CLA3EN;
             break;
        default: 
             break;
    }
}

/*!
    \brief      disable CLA
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void cla_disable(cla_enum cla_periph)
{
    switch(cla_periph){
        case CLA0:
             CLA_GCTL &= ~CLA_GCTL_CLA0EN;
             break;
        case CLA1:
             CLA_GCTL &= ~CLA_GCTL_CLA1EN;
             break;
        case CLA2:
             CLA_GCTL &= ~CLA_GCTL_CLA2EN;
             break;
        case CLA3:
             CLA_GCTL &= ~CLA_GCTL_CLA3EN;
             break;
        default: 
             break;
    }
}

/*!
    \brief      get CLA output state
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[out] none
    \retval     cla_outputstatus_enum: CLA_OUTPUT_HIGH or CLA_OUTPUT_LOW
*/
cla_outputstatus_enum cla_output_state_get(cla_enum cla_periph)
{
    uint32_t state;
    uint32_t returnval;
    
    /* read cla status register */
    state = CLA_STAT;
    
    switch(cla_periph){
        case CLA0:
             returnval = (state & CLA_STAT_CLA0OUT);
             break;
        case CLA1:
             returnval = ((state & CLA_STAT_CLA1OUT) >> 1U);
             break;
        case CLA2:
             returnval = ((state & CLA_STAT_CLA2OUT) >> 2U);
             break;
        case CLA3:
             returnval = ((state & CLA_STAT_CLA3OUT) >> 3U);
             break;
        default:
             returnval = 0U;
             break;
    }
    if(0U != returnval){
        return CLA_OUTPUT_HIGH;
    }else{
        return CLA_OUTPUT_LOW;
    }
}

/*!
    \brief      configure signal selector input
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[in]  sigs: signal selector
                only one parameter can be selected which is shown as below:
      \arg        SIGS0: signal selector 0
      \arg        SIGS1: signal selector 1
    \param[in]  input: input of signal selector

     SIGS0 input selection:
     only one parameter can be selected which is shown as below:
     --------------------------------------------------------------------------------------------------------------------------------
     |  SIGS0[3:0]|      CLA0SIGS0             |      CLA1SIGS0             |      CLA2SIGS0             |     CLA3SIGS0            |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0000   | CLA0SIGS0_CLA0_ASYNC_OUT   | CLA1SIGS0_CLA0_ASYNC_OUT   | CLA2SIGS0_CLA0_ASYNC_OUT   | CLA3SIGS0_CLA0_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0001   | CLA0SIGS0_CLA1_ASYNC_OUT   | CLA1SIGS0_CLA1_ASYNC_OUT   | CLA2SIGS0_CLA1_ASYNC_OUT   | CLA3SIGS0_CLA1_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0010   | CLA0SIGS0_CLA2_ASYNC_OUT   | CLA1SIGS0_CLA2_ASYNC_OUT   | CLA2SIGS0_CLA2_ASYNC_OUT   | CLA3SIGS0_CLA2_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0011   | CLA3SIGS0_CLA3_ASYNC_OUT   | CLA1SIGS0_CLA3_ASYNC_OUT   | CLA2SIGS0_CLA3_ASYNC_OUT   | CLA3SIGS0_CLA3_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0100   | CLA0SIGS0_TRIGSEL_CLA_IN7  | CLA1SIGS0_TRIGSEL_CLA_IN8  | CLA2SIGS0_TRIGSEL_CLA_IN9  | CLA3SIGS0_TRIGSEL_CLA_IN10    |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0101   | CLA0SIGS0_TRIGSEL_CLA_IN0  | CLA1SIGS0_TRIGSEL_CLA_IN0  | CLA2SIGS0_TRIGSEL_CLA_IN1  | CLA3SIGS0_TRIGSEL_CLA_IN2     |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0110   | CLA0SIGS0_TRIGSEL_CLA_IN1  | CLA1SIGS0_TRIGSEL_CLA_IN3  | CLA2SIGS0_TRIGSEL_CLA_IN3  | CLA3SIGS0_TRIGSEL_CLA_IN4     |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0111   | CLA0SIGS0_TRIGSEL_CLA_IN2  | CLA1SIGS0_TRIGSEL_CLA_IN4  | CLA2SIGS0_TRIGSEL_CLA_IN5  | CLA3SIGS0_TRIGSEL_CLA_IN5     |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1000   | CLA0SIGS0_CLAIN0           | CLA1SIGS0_CLAIN4           | CLA2SIGS0_CLAIN0           | CLA3SIGS0_CLAIN2         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1001   | CLA0SIGS0_CLAIN2           | CLA1SIGS0_CLAIN5           | CLA2SIGS0_CLAIN1           | CLA3SIGS0_CLAIN3         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1010   | CLA0SIGS0_CLAIN4           | CLA1SIGS0_CLAIN8           | CLA2SIGS0_CLAIN8           | CLA3SIGS0_CLAIN6         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1011   | CLA0SIGS0_CLAIN6           | CLA1SIGS0_CLAIN10          | CLA2SIGS0_CLAIN9           | CLA3SIGS0_CLAIN7         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1100   | CLA0SIGS0_CLAIN8           | CLA1SIGS0_CLAIN12          | CLA2SIGS0_CLAIN14          | CLA3SIGS0_CLAIN10        |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1101   | CLA0SIGS0_CLAIN10          | CLA1SIGS0_CLAIN13          | CLA2SIGS0_CLAIN15          | CLA3SIGS0_CLAIN11        |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1110   | CLA0SIGS0_CLAIN12          | CLA1SIGS0_CLAIN16          | CLA2SIGS0_CLAIN16          | CLA3SIGS0_CLAIN18        |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1111   | CLA0SIGS0_CLAIN14          | CLA1SIGS0_CLAIN18          | CLA2SIGS0_CLAIN17          | CLA3SIGS0_CLAIN19        |
     --------------------------------------------------------------------------------------------------------------------------------
     SIGS1 input selection:
     only one parameter can be selected which is shown as below:
     --------------------------------------------------------------------------------------------------------------------------------
     |  SIGS1[3:0]|      CLA0SIGS1             |      CLA1SIGS1             |       CLA2SIGS1            |     CLA3SIGS1            |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0000   | CLA0SIGS1_CLA0_ASYNC_OUT   | CLA1SIGS1_CLA0_ASYNC_OUT   | CLA2SIGS1_CLA0_ASYNC_OUT   | CLA3SIGS1_CLA0_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0001   | CLA0SIGS1_CLA1_ASYNC_OUT   | CLA1SIGS1_CLA1_ASYNC_OUT   | CLA2SIGS1_CLA1_ASYNC_OUT   | CLA3SIGS1_CLA1_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0010   | CLA0SIGS1_CLA2_ASYNC_OUT   | CLA1SIGS1_CLA2_ASYNC_OUT   | CLA2SIGS1_CLA2_ASYNC_OUT   | CLA3SIGS1_CLA2_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0011   | CLA0SIGS1_CLA3_ASYNC_OUT   | CLA1SIGS1_CLA3_ASYNC_OUT   | CLA2SIGS1_CLA3_ASYNC_OUT   | CLA3SIGS1_CLA3_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0100   | CLA0SIGS1_TRIGSEL_CLA_IN11 | CLA1SIGS1_TRIGSEL_CLA_IN11 | CLA2SIGS1_TRIGSEL_CLA_IN11 | CLA3SIGS1_TRIGSEL_CLA_IN11    |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0101   | CLA0SIGS1_TRIGSEL_CLA_IN3  | CLA1SIGS1_TRIGSEL_CLA_IN1  | CLA2SIGS1_TRIGSEL_CLA_IN0  | CLA3SIGS1_TRIGSEL_CLA_IN0     |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0110   | CLA0SIGS1_TRIGSEL_CLA_IN4  | CLA1SIGS1_TRIGSEL_CLA_IN2  | CLA2SIGS1_TRIGSEL_CLA_IN2  | CLA3SIGS1_TRIGSEL_CLA_IN1     |
     --------------------------------------------------------------------------------------------------------------------------------
     |     0111   | CLA0SIGS1_TRIGSEL_CLA_IN5  | CLA1SIGS1_TRIGSEL_CLA_IN5  | CLA2SIGS1_TRIGSEL_CLA_IN4  | CLA3SIGS1_TRIGSEL_CLA_IN3     |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1000   | CLA0SIGS1_CLAIN1           | CLA1SIGS1_CLAIN6           | CLA2SIGS1_CLAIN2           | CLA3SIGS1_CLAIN0         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1001   | CLA0SIGS1_CLAIN3           | CLA1SIGS1_CLAIN7           | CLA2SIGS1_CLAIN3           | CLA3SIGS1_CLAIN1         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1010   | CLA0SIGS1_CLAIN5           | CLA1SIGS1_CLAIN9           | CLA2SIGS1_CLAIN10          | CLA3SIGS1_CLAIN4         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1011   | CLA0SIGS1_CLAIN6           | CLA1SIGS1_CLAIN11          | CLA2SIGS1_CLAIN11          | CLA3SIGS1_CLAIN5         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1100   | CLA0SIGS1_CLAIN9           | CLA1SIGS1_CLAIN14          | CLA2SIGS1_CLAIN12          | CLA3SIGS1_CLAIN8         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1101   | CLA0SIGS1_CLAIN11          | CLA1SIGS1_CLAIN15          | CLA2SIGS1_CLAIN13          | CLA3SIGS1_CLAIN9         |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1110   | CLA0SIGS1_CLAIN13          | CLA1SIGS1_CLAIN17          | CLA2SIGS1_CLAIN18          | CLA3SIGS1_CLAIN16        |
     --------------------------------------------------------------------------------------------------------------------------------
     |     1111   | CLA0SIGS1_CLAIN15          | CLA1SIGS1_CLAIN19          | CLA2SIGS1_CLAIN19          | CLA3SIGS1_CLAIN17        |
     --------------------------------------------------------------------------------------------------------------------------------
    \param[out] none
    \retval     none
*/
void cla_sigs_input_config(cla_enum cla_periph, cla_sigs_enum sigs, uint32_t input)
{
    uint32_t reg;
    reg = CLA_SIGS(cla_periph);
    if(SIGS0 == sigs) {
        reg &= ~CLA_SIGS_SIGS0;
    } else {
        reg &= ~CLA_SIGS_SIGS1;
    }
    reg |= input;
    CLA_SIGS(cla_periph) = reg;
}

/*!
    \brief      configure CLA LCU control register value
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[in]  lcuctl_value: the value need to set, 0 - 0xFF
    \param[out] none
    \retval     none
*/
void cla_lcu_control_config(cla_enum cla_periph, uint8_t lcuctl_value)
{
    uint32_t reg;
    reg = CLA_LCUCTL(cla_periph);
    reg &= ~CLA_LCU;
    reg |= LCUCTL(lcuctl_value);
    CLA_LCUCTL(cla_periph) = reg;
}

/*!
    \brief      configure CLA output
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[in]  output: output of CLA
                only one parameter can be selected which is shown as below:
      \arg        FLIP_FLOP_OUTPUT: flip-flop output is selected as CLA output
      \arg        LUT_RESULT: LUT result is selected as CLA output
    \param[out] none
    \retval     none
*/
void cla_output_config(cla_enum cla_periph, uint32_t output)
{
    uint32_t reg;
    reg = CLA_CTL(cla_periph);
    reg &= ~CLA_CTL_OSEL;
    reg |= output;
    CLA_CTL(cla_periph) = reg;
}

/*!
    \brief      enable CLA output
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void cla_output_enable(cla_enum cla_periph)
{
    CLA_CTL(cla_periph) |= CLA_CTL_OEN;
}

/*!
    \brief      disable CLA output
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void cla_output_disable(cla_enum cla_periph)
{
    CLA_CTL(cla_periph) &= ~CLA_CTL_OEN;
}

/*!
    \brief      reset the flip-flop output asynchronously
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void cla_flip_flop_output_reset(cla_enum cla_periph)
{
    CLA_CTL(cla_periph) |= CLA_CTL_FFRST;
}

/*!
    \brief      configure clock polarity of flip-flop
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[in]  polarity: clock polarity of flip-flop
                only one parameter can be selected which is shown as below:
      \arg        CLA_CLOCKPOLARITY_POSEDGE: clock rising edge is valid
      \arg        CLA_CLOCKPOLARITY_NEGEDGE: clock falling edge is valid
    \param[out] none
    \retval     none
*/
void cla_flip_flop_clockpolarity_config(cla_enum cla_periph, uint32_t polarity)
{
    uint32_t reg;
    reg = CLA_CTL(cla_periph);
    reg &= ~CLA_CTL_CPOL;
    reg |= polarity;
    CLA_CTL(cla_periph) = reg;
}

/*!
    \brief      configure clock source of flip-flop 
    \param[in]  cla_periph: CLAx(x=0,1,2,3)
    \param[in]  clock_source: clock source of flip-flop
                only one parameter can be selected which is shown as below:
      \arg        PRE_CLA_LUT_RESULT: the result of the previous CLA units
      \arg        SIGS0_OUTPUT: the signal selector output of SIGS0
      \arg        HCLK: HCLK
      \arg        TIMER_TRGO: TIMER_TRGO
    \param[out] none
    \retval     none
*/
void cla_flip_flop_clocksource_config(cla_enum cla_periph, uint32_t clock_source)
{
    uint32_t reg;
    reg = CLA_CTL(cla_periph);
    reg &= ~CLA_CTL_CSEL;
    reg |= clock_source;
    CLA_CTL(cla_periph) = reg;
}

/*!
    \brief      check CLA flag is set or not
    \param[in]  flag: CLA flags,refer to cla_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CLA_FLAG_CLA0NF: CLA0 unit falling edge flag
      \arg        CLA_FLAG_CLA0PF: CLA0 unit rising edge flag
      \arg        CLA_FLAG_CLA1NF: CLA1 unit falling edge flag
      \arg        CLA_FLAG_CLA1PF: CLA1 unit rising edge flag
      \arg        CLA_FLAG_CLA2NF: CLA2 unit falling edge flag
      \arg        CLA_FLAG_CLA2PF: CLA2 unit rising edge flag
      \arg        CLA_FLAG_CLA3NF: CLA3 unit falling edge flag
      \arg        CLA_FLAG_CLA3PF: CLA3 unit rising edge flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cla_flag_get(cla_flag_enum flag)
{
    uint32_t interrupt_flag_register;
    uint32_t returnval;
    
    interrupt_flag_register = CLA_INTF;
    
    switch(flag){
        case CLA_FLAG_CLA0NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA0NF);
             break;
        case CLA_FLAG_CLA0PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA0PF) >> 1U;
             break;
        case CLA_FLAG_CLA1NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA1NF) >> 2U;
             break;
        case CLA_FLAG_CLA1PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA1PF) >> 3U;
             break;
        case CLA_FLAG_CLA2NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA2NF) >> 4U;
             break;
        case CLA_FLAG_CLA2PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA2PF) >> 5U;
             break;
        case CLA_FLAG_CLA3NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA3NF) >> 6U;
             break;
        case CLA_FLAG_CLA3PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA3PF) >> 7U;
             break;
        default:
             returnval = 0U;
             break;
    }
    if(SET == returnval){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CLA flag
    \param[in]  flag: CLA flags,refer to cla_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CLA_FLAG_CLA0NF: CLA0 unit falling edge flag
      \arg        CLA_FLAG_CLA0PF: CLA0 unit rising edge flag
      \arg        CLA_FLAG_CLA1NF: CLA1 unit falling edge flag
      \arg        CLA_FLAG_CLA1PF: CLA1 unit rising edge flag
      \arg        CLA_FLAG_CLA2NF: CLA2 unit falling edge flag
      \arg        CLA_FLAG_CLA2PF: CLA2 unit rising edge flag
      \arg        CLA_FLAG_CLA3NF: CLA3 unit falling edge flag
      \arg        CLA_FLAG_CLA3PF: CLA3 unit rising edge flag
    \param[out] none
    \retval     none
*/
void cla_flag_clear(cla_flag_enum flag)
{
    switch(flag){
        case CLA_FLAG_CLA0NF:
             CLA_INTF &= ~CLA_INTF_CLA0NF;
             break;
        case CLA_FLAG_CLA0PF:
             CLA_INTF &= ~CLA_INTF_CLA0PF;
             break;
        case CLA_FLAG_CLA1NF:
             CLA_INTF &= ~CLA_INTF_CLA1NF;
             break;
        case CLA_FLAG_CLA1PF:
             CLA_INTF &= ~CLA_INTF_CLA1PF;
             break;
        case CLA_FLAG_CLA2NF:
             CLA_INTF &= ~CLA_INTF_CLA2NF;
             break;
        case CLA_FLAG_CLA2PF:
             CLA_INTF &= ~CLA_INTF_CLA2PF;
             break;
        case CLA_FLAG_CLA3NF:
             CLA_INTF &= ~CLA_INTF_CLA3NF;
             break;
        case CLA_FLAG_CLA3PF:
             CLA_INTF &= ~CLA_INTF_CLA3PF;
             break;
        default:
            break;
    }
}

/*!
    \brief      enable CLA falling edge interrupt
    \param[in]  clanie: CLA falling edge interrupt enable
                only one parameter can be selected which is shown as below:
      \arg        CLA0NIE: CLA0 falling edge interrupt enable
      \arg        CLA1NIE: CLA1 falling edge interrupt enable
      \arg        CLA2NIE: CLA2 falling edge interrupt enable
      \arg        CLA3NIE: CLA3 falling edge interrupt enable
    \param[out] none
    \retval     none
*/
void cla_negedge_interrupt_enable(uint32_t clanie)
{
    CLA_INTE |= clanie;
}

/*!
    \brief      disable CLA falling edge interrupt
    \param[in]  clanidis: CLA falling edge interrupt disable
                only one parameter can be selected which is shown as below:
      \arg        CLA0NI_DISABLE: CLA0 falling edge interrupt disable
      \arg        CLA1NI_DISABLE: CLA1 falling edge interrupt disable
      \arg        CLA2NI_DISABLE: CLA2 falling edge interrupt disable
      \arg        CLA3NI_DISABLE: CLA3 falling edge interrupt disable
    \param[out] none
    \retval     none
*/
void cla_negedge_interrupt_disable(uint32_t clanidis)
{
    CLA_INTE &= ~clanidis;
}

/*!
    \brief      enable CLA rising edge interrupt
    \param[in]  clapie: CLA rising edge interrupt enable
                only one parameter can be selected which is shown as below:
      \arg        CLA0PIE: CLA0 rising edge interrupt enable
      \arg        CLA1PIE: CLA1 rising edge interrupt enable
      \arg        CLA2PIE: CLA2 rising edge interrupt enable
      \arg        CLA3PIE: CLA3 rising edge interrupt enable
    \param[out] none
    \retval     none
*/
void cla_posedge_interrupt_enable(uint32_t clapie)
{
    CLA_INTE |= clapie;
}

/*!
    \brief      disable CLA rising edge interrupt
    \param[in]  clapidis: CLA rising edge interrupt disable
                only one parameter can be selected which is shown as below:
      \arg        CLA0PI_DISABLE: CLA0 rising edge interrupt disable
      \arg        CLA1PI_DISABLE: CLA1 rising edge interrupt disable
      \arg        CLA2PI_DISABLE: CLA2 rising edge interrupt disable
      \arg        CLA3PI_DISABLE: CLA3 rising edge interrupt disable
    \param[out] none
    \retval     none
*/
void cla_posedge_interrupt_disable(uint32_t clapidis)
{
    CLA_INTE &= ~clapidis;
}

/*!
    \brief      check CLA interrupt flag is set or not 
    \param[in]  int_flag: CLA interrupt flags,refer to cla_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CLA_INT_FLAG_CLA0NF: CLA0 unit falling edge interrupt flag
      \arg        CLA_INT_FLAG_CLA0PF: CLA0 unit rising edge interrupt flag
      \arg        CLA_INT_FLAG_CLA1NF: CLA1 unit falling edge interrupt flag
      \arg        CLA_INT_FLAG_CLA1PF: CLA1 unit rising edge interrupt flag
      \arg        CLA_INT_FLAG_CLA2NF: CLA2 unit falling edge interrupt flag
      \arg        CLA_INT_FLAG_CLA2PF: CLA2 unit rising edge interrupt flag
      \arg        CLA_INT_FLAG_CLA3NF: CLA3 unit falling edge interrupt flag
      \arg        CLA_INT_FLAG_CLA3PF: CLA3 unit rising edge interrupt flag
    \param[out] none
    \retval     none
*/
FlagStatus cla_interrupt_flag_get(cla_interrupt_flag_enum int_flag)
{
    uint32_t cla_inte = CLA_INTE;
    uint32_t cla_intf = CLA_INTF;
    
    switch(int_flag){
        case CLA_INT_FLAG_CLA0NF:
             cla_inte = cla_inte & CLA_INTE_CLA0NIE;
             cla_intf = cla_intf & CLA_INTF_CLA0NF;
             break;
        case CLA_INT_FLAG_CLA0PF:
             cla_inte = cla_inte & CLA_INTE_CLA0PIE;
             cla_intf = cla_intf & CLA_INTF_CLA0PF;
             break;
        case CLA_INT_FLAG_CLA1NF:
             cla_inte = cla_inte & CLA_INTE_CLA1NIE;
             cla_intf = cla_intf & CLA_INTF_CLA1NF;
             break;
        case CLA_INT_FLAG_CLA1PF:
             cla_inte = cla_inte & CLA_INTE_CLA1PIE;
             cla_intf = cla_intf & CLA_INTF_CLA1PF;
             break;
        case CLA_INT_FLAG_CLA2NF:
             cla_inte = cla_inte & CLA_INTE_CLA2NIE;
             cla_intf = cla_intf & CLA_INTF_CLA2NF;
             break;
        case CLA_INT_FLAG_CLA2PF:
             cla_inte = cla_inte & CLA_INTE_CLA2PIE;
             cla_intf = cla_intf & CLA_INTF_CLA2PF;
             break;
        case CLA_INT_FLAG_CLA3NF:
             cla_inte = cla_inte & CLA_INTE_CLA3NIE;
             cla_intf = cla_intf & CLA_INTF_CLA3NF;
             break;
        case CLA_INT_FLAG_CLA3PF:
             cla_inte = cla_inte & CLA_INTE_CLA3PIE;
             cla_intf = cla_intf & CLA_INTF_CLA3PF;
             break;
        default:
             break;
    }
    if((0U != cla_inte) && (0U != cla_intf)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CLA interrupt flag
    \param[in]  int_flag: CLA interrupt flags,refer to cla_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CLA_INT_FLAG_CLA0NF: CLA0 unit falling edge interrupt flag
      \arg        CLA_INT_FLAG_CLA0PF: CLA0 unit rising edge interrupt flag
      \arg        CLA_INT_FLAG_CLA1NF: CLA1 unit falling edge interrupt flag
      \arg        CLA_INT_FLAG_CLA1PF: CLA1 unit rising edge interrupt flag
      \arg        CLA_INT_FLAG_CLA2NF: CLA2 unit falling edge interrupt flag
      \arg        CLA_INT_FLAG_CLA2PF: CLA2 unit rising edge interrupt flag
      \arg        CLA_INT_FLAG_CLA3NF: CLA3 unit falling edge interrupt flag
      \arg        CLA_INT_FLAG_CLA3PF: CLA3 unit rising edge interrupt flag
    \param[out] none
    \retval     none
*/
void cla_interrupt_flag_clear(cla_interrupt_flag_enum int_flag)
{
    switch(int_flag){
        case CLA_INT_FLAG_CLA0NF:
             CLA_INTF &= ~CLA_INTF_CLA0NF;
             break;
        case CLA_INT_FLAG_CLA0PF:
             CLA_INTF &= ~CLA_INTF_CLA0PF;
             break;
        case CLA_INT_FLAG_CLA1NF:
             CLA_INTF &= ~CLA_INTF_CLA1NF;
             break;
        case CLA_INT_FLAG_CLA1PF:
             CLA_INTF &= ~CLA_INTF_CLA1PF;
             break;
        case CLA_INT_FLAG_CLA2NF:
             CLA_INTF &= ~CLA_INTF_CLA2NF;
             break;
        case CLA_INT_FLAG_CLA2PF:
             CLA_INTF &= ~CLA_INTF_CLA2PF;
             break;
        case CLA_INT_FLAG_CLA3NF:
             CLA_INTF &= ~CLA_INTF_CLA3NF;
             break;
        case CLA_INT_FLAG_CLA3PF:
             CLA_INTF &= ~CLA_INTF_CLA3PF;
             break;
        default:
             break;
    }
}
