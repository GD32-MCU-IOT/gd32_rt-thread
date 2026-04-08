/*!
    \file    gd32m53x_gptimer.c
    \brief   GPTIMER driver

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

#include "gd32m53x_gptimer.h"

/* GPTIMER init parameter mask */
#define REGISTER_WRITER_PROTECT_MASK      ((uint32_t)0x0000000FU)     /*!< GPTIMER register write protect definitions */
#define DMA_REQUEST_ENABLE_MASK           ((uint32_t)0x007F0000U)     /*!< GPTIMER DMA request enable definitions */
#define OUTPUT_LEVEL_MASK                 ((uint32_t)0x00000003U)     /*!< GPTIMER output level definitions */
#define COMPARISON_GENERATE_TRIGGER_MASK  ((uint32_t)0x0000F000U)     /*!< GPTIMER comparison match generate trigger definitions */
#define TRIGGER_ADC_SKIPPING_VALUE_MASK   ((uint32_t)0x0000000FU)     /*!< GPTIMER trigger adc skipping value definitions */
#define TRIGGER_ADD_SKIPPING_VALUE_MASK   ((uint32_t)0x0000000FU)     /*!< GPTIMER trigger add skipping value definitions */
#define COUNTER_SYNC_RESET_SOURCE_MASK    ((uint32_t)0x000100CFU)     /*!< GPTIMER counter sync reset source definitions */
#define SKIPPING_TIME_MASK                ((uint32_t)0x00000007U)     /*!< GPTIMER skipping time definitions */
#define FLOW_SKIPPING_LINK_MASK           ((uint32_t)0x0000300FU)     /*!< GPTIMER flow interrupt skipping link definitions */
#define INTERRUPT_ENABLE_MASK             ((uint32_t)0x000080BFU)     /*!< GPTIMER interrupt enable definitions */
#define INTERRUPT_FLAG_MASK               ((uint32_t)0x000080BFU)     /*!< GPTIMER interrupt flag definitions */

/*!
    \brief      deinit GPTIMER (API_ID(0x0001U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_deinit(uint32_t timer_periph)
{
    switch(timer_periph) {
    case GPTIMER0:
        /* reset GPTIMER0 */
        rcu_periph_reset_enable(RCU_GPTIMER0RST);
        rcu_periph_reset_disable(RCU_GPTIMER0RST);
        break;
    case GPTIMER1:
        /* reset GPTIMER1 */
        rcu_periph_reset_enable(RCU_GPTIMER1RST);
        rcu_periph_reset_disable(RCU_GPTIMER1RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize GPTIMER init parameter struct with a default value (API_ID(0x0002U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_struct_para_init(gptimer_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->clock_source      = GPTIMER_CLOCK_SOURCE_CK_GPTIMER;
        initpara->clock_polarity    = GPTIMER_CLOCK_POLARITY_RISING;
        initpara->prescaler         = 0U;
        initpara->alignedmode       = GPTIMER_COUNTER_EDGE;
        initpara->counterdirection  = GPTIMER_COUNTER_UP;
        initpara->period            = 65535U;
        initpara->clockdivision     = GPTIMER_CKDIV_DIV1;
        initpara->repetitioncounter = 0U;
    }
}

/*!
    \brief      initialize GPTIMER counter (API_ID(0x0003U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  initpara: init parameter struct
                  clock_source: GPTIMER_CLOCK_SOURCE_CK_GPTIMER, GPTIMER_CLOCK_SOURCE_ETI0, GPTIMER_CLOCK_SOURCE_ETI1, GPTIMER_CLOCK_SOURCE_ETI2
                                GPTIMER_CLOCK_SOURCE_ETI3
                  clock_polarity: GPTIMER_CLOCK_POLARITY_RISING, GPTIMER_CLOCK_POLARITY_FALLING, GPTIMER_CLOCK_POLARITY_BOTH
                  prescaler: prescaler value of the counter clock, 0~65535
                  alignedmode: GPTIMER_COUNTER_EDGE, GPTIMER_COUNTER_CENTER
                  counterdirection: GPTIMER_COUNTER_UP, GPTIMER_COUNTER_DOWN
                  period: counter auto reload value, 0~65535
                  clockdivision: GPTIMER_CKDIV_DIV1, GPTIMER_CKDIV_DIV2, GPTIMER_CKDIV_DIV4
                  repetitioncounter: counter repetition value, 0~4095
    \param[out] none
    \retval     none
*/
void gptimer_init(uint32_t timer_periph, gptimer_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPTIMER_CTL0(timer_periph) &= (~(uint32_t)(GPTIMER_CTL0_CKSSEL | GPTIMER_CTL0_CKESEL));
        GPTIMER_CTL0(timer_periph) |= (uint32_t)(initpara->clock_source & GPTIMER_CTL0_CKSSEL);
        GPTIMER_CTL0(timer_periph) |= (uint32_t)(initpara->clock_polarity & GPTIMER_CTL0_CKESEL);

        /* configure the counter prescaler value */
        GPTIMER_PSC(timer_periph) = (uint16_t)initpara->prescaler;

        /* configure the counter direction and aligned mode */
        GPTIMER_CTL0(timer_periph) &= (~(uint32_t)(GPTIMER_CTL0_DIR | GPTIMER_CTL0_CAM));

        GPTIMER_CTL0(timer_periph) |= (uint32_t)((initpara->counterdirection & GPTIMER_CTL0_DIR) | GPTIMER_CTL0_FDIR);
        GPTIMER_CTL0(timer_periph) &= (~(uint32_t)(GPTIMER_CTL0_FDIR));

        GPTIMER_CTL0(timer_periph) |= (uint32_t)(initpara->alignedmode & GPTIMER_CTL0_CAM);

        GPTIMER_CTL0(timer_periph) &= (~(uint32_t)GPTIMER_CTL0_CKDIV);
        GPTIMER_CTL0(timer_periph) |= (uint32_t)(initpara->clockdivision & GPTIMER_CTL0_CKDIV);
        /* configure the autoreload value */
        GPTIMER_CAR(timer_periph) = (uint32_t)initpara->period;
        /* configure the repetition counter value */
        GPTIMER_CREP(timer_periph) &= ~(uint32_t)(GPTIMER_CREP_CREP);
        GPTIMER_CREP(timer_periph) |= (uint32_t)(initpara->repetitioncounter & GPTIMER_CREP_CREP);
        /* generate an update event */
        switch(timer_periph) {
        case GPTIMER0:
            GPTIMER_RSSEL(timer_periph) |= GPTIMER_RSSEL_SWRSTCNT;
            GPTIMER_SWRST(timer_periph) |= (uint32_t)GPTIMER_SWRST_GPTIMER0SWRST;
            break;
        case GPTIMER1:
            GPTIMER_RSSEL(timer_periph) |= GPTIMER_RSSEL_SWRSTCNT;
            GPTIMER_SWRST(timer_periph) |= (uint32_t)GPTIMER_SWRST_GPTIMER1SWRST;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      enable GPTIMER register write protect function (API_ID(0x0004U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  register_protect:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER_WRITE_PROTECT_SWEN: GPTIMER_SWEN register writer protect
      \arg        GPTIMER_WRITE_PROTECT_SWDIS: GPTIMER_SWDIS register writer protect
      \arg        GPTIMER_WRITE_PROTECT_SWRST: GPTIMER_SWRST register writer protect
      \arg        GPTIMER_WRITE_PROTECT_OTHER: other register writer protect
    \param[out] none
    \retval     none
*/
void gptimer_register_write_protect_enable(uint32_t timer_periph, uint32_t register_protect)
{
    GPTIMER_WP(timer_periph) = (uint32_t)((register_protect & REGISTER_WRITER_PROTECT_MASK) | (uint32_t)(0xA5 << 8));
}

/*!
    \brief      disable GPTIMER register write protect function (API_ID(0x0005U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  register_protect:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER_WRITE_PROTECT_SWEN: GPTIMER_SWEN register writer protect
      \arg        GPTIMER_WRITE_PROTECT_SWDIS: GPTIMER_SWDIS register writer protect
      \arg        GPTIMER_WRITE_PROTECT_SWRST: GPTIMER_SWRST register writer protect
      \arg        GPTIMER_WRITE_PROTECT_OTHER: other register writer protect
    \param[out] none
    \retval     none
*/
void gptimer_register_write_protect_disable(uint32_t timer_periph, uint32_t register_protect)
{
    GPTIMER_WP(timer_periph) = ~(uint32_t)((register_protect & REGISTER_WRITER_PROTECT_MASK) | (uint32_t)(~(0xA5 << 8)));

}

/*!
    \brief      select a GPTIMER clock source (API_ID(0x0006U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  clock_source:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CLOCK_SOURCE_CK_GPTIMER: select CK_GPTIMER as clock source
      \arg        GPTIMER_CLOCK_SOURCE_ETI0: select ETI0 as clock source
      \arg        GPTIMER_CLOCK_SOURCE_ETI1: select ETI1 as clock source
      \arg        GPTIMER_CLOCK_SOURCE_ETI2: select ETI2 as clock source
      \arg        GPTIMER_CLOCK_SOURCE_ETI3: select ETI3 as clock source
    \param[out] none
    \retval     none
*/
void gptimer_clock_source_select(uint32_t timer_periph, uint32_t clock_source)
{
    GPTIMER_CTL0(timer_periph) &= ~(uint32_t)(GPTIMER_CTL0_CKSSEL);
    GPTIMER_CTL0(timer_periph) |= (uint32_t)(clock_source & GPTIMER_CTL0_CKSSEL);

}

/*!
    \brief      configure a GPTIMER clock polarity (API_ID(0x0007U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  clock_polarity:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CLOCK_POLARITY_RISING: select rising edge as clock polarity
      \arg        GPTIMER_CLOCK_POLARITY_FALLING: select falling edge as clock polarity
      \arg        GPTIMER_CLOCK_POLARITY_BOTH: select both edge as clock polarity
    \param[out] none
    \retval     none
*/
void gptimer_clock_polarity_config(uint32_t timer_periph, uint32_t clock_polarity)
{
    GPTIMER_CTL0(timer_periph) &= ~(uint32_t)(GPTIMER_CTL0_CKESEL);
    GPTIMER_CTL0(timer_periph) |= (uint32_t)(clock_polarity & GPTIMER_CTL0_CKESEL);
}

/*!
    \brief      software enable GPTIMER counter (API_ID(0x0008U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  timer_cnt:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER0_COUNT: GPTIMER0 counter
      \arg        GPTIMER1_COUNT: GPTIMER1 counter
    \param[out] none
    \retval     none
*/
void gptimer_counter_software_enable(uint32_t timer_periph, uint32_t timer_cnt)
{
    GPTIMER_SWEN(timer_periph) |= (uint32_t)timer_cnt;
}

/*!
    \brief      software disable GPTIMER counter (API_ID(0x0009U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  timer_cnt:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER0_COUNT: GPTIMER0 counter
      \arg        GPTIMER1_COUNT: GPTIMER1 counter
    \param[out] none
    \retval     none
*/
void gptimer_counter_software_disable(uint32_t timer_periph, uint32_t timer_cnt)
{
    GPTIMER_SWDIS(timer_periph) |= (uint32_t)timer_cnt;
}

/*!
    \brief      software reset GPTIMER counter (API_ID(0x000AU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  timer_cnt:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER0_COUNT: GPTIMER0 counter
      \arg        GPTIMER1_COUNT: GPTIMER1 counter
    \param[out] none
    \retval     none
*/
void gptimer_counter_software_reset(uint32_t timer_periph, uint32_t timer_cnt)
{
    GPTIMER_SWRST(timer_periph) |= (uint32_t)timer_cnt;
}

/*!
    \brief      initialize GPTIMER counter enable source init parameter struct with a default value (API_ID(0x000BU))
    \param[in]  counter_enable_source_para: counter enable source init parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_counter_enable_source_struct_para_init(gptimer_counter_enable_source_parameter_struct
                                                    *counter_enable_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(counter_enable_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x000BU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        counter_enable_source_para->enable_source_eti0 = GPTIMER_ETI0_TRG_DISABLE;
        counter_enable_source_para->enable_source_eti1 = GPTIMER_ETI1_TRG_DISABLE;
        counter_enable_source_para->enable_source_eti2 = GPTIMER_ETI2_TRG_DISABLE;
        counter_enable_source_para->enable_source_eti3 = GPTIMER_ETI3_TRG_DISABLE;
        counter_enable_source_para->enable_source_ch0 =  GPTIMER_CH0_TRG_DISABLE;
        counter_enable_source_para->enable_source_ch1 =  GPTIMER_CH1_TRG_DISABLE;
        counter_enable_source_para->enable_source_evsel0 = GPTIMER_EVSEL0_TRG_DISABLE;
        counter_enable_source_para->enable_source_evsel1 = GPTIMER_EVSEL1_TRG_DISABLE;
        counter_enable_source_para->enable_source_evsel2 = GPTIMER_EVSEL2_TRG_DISABLE;
        counter_enable_source_para->enable_source_evsel3 = GPTIMER_EVSEL3_TRG_DISABLE;
        counter_enable_source_para->enable_source_evsel4 = GPTIMER_EVSEL4_TRG_DISABLE;
        counter_enable_source_para->enable_source_evsel5 = GPTIMER_EVSEL5_TRG_DISABLE;
        counter_enable_source_para->enable_source_evsel6 = GPTIMER_EVSEL6_TRG_DISABLE;
        counter_enable_source_para->enable_source_evsel7 = GPTIMER_EVSEL7_TRG_DISABLE;
        counter_enable_source_para->enable_source_software = GPTIMER_SOFTWARE_TRG_DISABLE;
    }
}

/*!
    \brief      initialize GPTIMER counter enable source (API_ID(0x000CU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  counter_enable_source_para: counter enable source init parameter struct
                  enable_source_eti0: GPTIMER_ETI0_TRG_DISABLE, GPTIMER_ETI0_TRG_EDGE_RISING, GPTIMER_ETI0_TRG_EDGE_FALLING, GPTIMER_ETI0_TRG_EDGE_BOTH
                  enable_source_eti1: GPTIMER_ETI1_TRG_DISABLE, GPTIMER_ETI1_TRG_EDGE_RISING, GPTIMER_ETI1_TRG_EDGE_FALLING, GPTIMER_ETI1_TRG_EDGE_BOTH
                  enable_source_eti2: GPTIMER_ETI2_TRG_DISABLE, GPTIMER_ETI2_TRG_EDGE_RISING, GPTIMER_ETI2_TRG_EDGE_FALLING, GPTIMER_ETI2_TRG_EDGE_BOTH
                  enable_source_eti3: GPTIMER_ETI3_TRG_DISABLE, GPTIMER_ETI3_TRG_EDGE_RISING, GPTIMER_ETI3_TRG_EDGE_FALLING, GPTIMER_ETI3_TRG_EDGE_BOTH
                  enable_source_ch0: GPTIMER_CH0_TRG_DISABLE, GPTIMER_CH0_TRG_EDGE_RISING, GPTIMER_CH0_TRG_EDGE_FALLING, GPTIMER_CH0_TRG_EDGE_BOTH
                  enable_source_ch1: GPTIMER_CH1_TRG_DISABLE, GPTIMER_CH1_TRG_EDGE_RISING, GPTIMER_CH1_TRG_EDGE_FALLING, GPTIMER_CH1_TRG_EDGE_BOTH
                  enable_source_evsel0: GPTIMER_EVSEL0_TRG_DISABLE, GPTIMER_EVSEL0_TRG_ENABLE
                  enable_source_evsel1: GPTIMER_EVSEL1_TRG_DISABLE, GPTIMER_EVSEL1_TRG_ENABLE
                  enable_source_evsel2: GPTIMER_EVSEL2_TRG_DISABLE, GPTIMER_EVSEL2_TRG_ENABLE
                  enable_source_evsel3: GPTIMER_EVSEL3_TRG_DISABLE, GPTIMER_EVSEL3_TRG_ENABLE
                  enable_source_evsel4: GPTIMER_EVSEL4_TRG_DISABLE, GPTIMER_EVSEL4_TRG_ENABLE
                  enable_source_evsel5: GPTIMER_EVSEL5_TRG_DISABLE, GPTIMER_EVSEL5_TRG_ENABLE
                  enable_source_evsel6: GPTIMER_EVSEL6_TRG_DISABLE, GPTIMER_EVSEL6_TRG_ENABLE
                  enable_source_evsel7: GPTIMER_EVSEL7_TRG_DISABLE, GPTIMER_EVSEL7_TRG_ENABLE
                  enable_source_software: GPTIMER_SOFTWARE_TRG_DISABLE, GPTIMER_SOFTWARE_TRG_ENABLE
    \param[out] none
    \retval     none
*/
void gptimer_counter_enable_source_config(uint32_t timer_periph,
                                          gptimer_counter_enable_source_parameter_struct *counter_enable_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(counter_enable_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x000CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPTIMER_ESSEL(timer_periph) = (uint32_t)((uint32_t)(counter_enable_source_para->enable_source_eti0 & GPTIMER_ESSEL_ETI0ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_eti1 & GPTIMER_ESSEL_ETI1ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_eti2 & GPTIMER_ESSEL_ETI2ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_eti3 & GPTIMER_ESSEL_ETI3ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_ch0 & GPTIMER_ESSEL_CH0ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_ch1 & GPTIMER_ESSEL_CH1ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_evsel0 & GPTIMER_ESSEL_EVSEL0ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_evsel1 & GPTIMER_ESSEL_EVSEL1ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_evsel2 & GPTIMER_ESSEL_EVSEL2ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_evsel3 & GPTIMER_ESSEL_EVSEL3ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_evsel4 & GPTIMER_ESSEL_EVSEL4ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_evsel5 & GPTIMER_ESSEL_EVSEL5ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_evsel6 & GPTIMER_ESSEL_EVSEL6ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_evsel7 & GPTIMER_ESSEL_EVSEL7ENCNT) |
                                                 (uint32_t)(counter_enable_source_para->enable_source_software & GPTIMER_ESSEL_SWENCNT));
    }
}

/*!
    \brief      initialize GPTIMER counter disable source init parameter struct with a default value (API_ID(0x000DU))
    \param[in]  counter_disable_source_para: counter disable source init parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_counter_disable_source_struct_para_init(gptimer_counter_disable_source_parameter_struct
                                                     *counter_disable_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(counter_disable_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x000DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        counter_disable_source_para->disable_source_eti0 = GPTIMER_ETI0_TRG_DISABLE;
        counter_disable_source_para->disable_source_eti1 = GPTIMER_ETI1_TRG_DISABLE;
        counter_disable_source_para->disable_source_eti2 = GPTIMER_ETI2_TRG_DISABLE;
        counter_disable_source_para->disable_source_eti3 = GPTIMER_ETI3_TRG_DISABLE;
        counter_disable_source_para->disable_source_ch0 = GPTIMER_CH0_TRG_DISABLE;
        counter_disable_source_para->disable_source_ch1 = GPTIMER_CH1_TRG_DISABLE;
        counter_disable_source_para->disable_source_evsel0 = GPTIMER_EVSEL0_TRG_DISABLE;
        counter_disable_source_para->disable_source_evsel1 = GPTIMER_EVSEL1_TRG_DISABLE;
        counter_disable_source_para->disable_source_evsel2 = GPTIMER_EVSEL2_TRG_DISABLE;
        counter_disable_source_para->disable_source_evsel3 = GPTIMER_EVSEL3_TRG_DISABLE;
        counter_disable_source_para->disable_source_evsel4 = GPTIMER_EVSEL4_TRG_DISABLE;
        counter_disable_source_para->disable_source_evsel5 = GPTIMER_EVSEL5_TRG_DISABLE;
        counter_disable_source_para->disable_source_evsel6 = GPTIMER_EVSEL6_TRG_DISABLE;
        counter_disable_source_para->disable_source_evsel7 = GPTIMER_EVSEL7_TRG_DISABLE;
        counter_disable_source_para->disable_source_software = GPTIMER_SOFTWARE_TRG_DISABLE;
    }
}

/*!
    \brief      initialize GPTIMER counter disable source (API_ID(0x000EU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  counter_disable_source_para: counter disable source init parameter struct
                  disable_source_eti0: GPTIMER_ETI0_TRG_DISABLE, GPTIMER_ETI0_TRG_EDGE_RISING, GPTIMER_ETI0_TRG_EDGE_FALLING, GPTIMER_ETI0_TRG_EDGE_BOTH
                  disable_source_eti1: GPTIMER_ETI1_TRG_DISABLE, GPTIMER_ETI1_TRG_EDGE_RISING, GPTIMER_ETI1_TRG_EDGE_FALLING, GPTIMER_ETI1_TRG_EDGE_BOTH
                  disable_source_eti2: GPTIMER_ETI2_TRG_DISABLE, GPTIMER_ETI2_TRG_EDGE_RISING, GPTIMER_ETI2_TRG_EDGE_FALLING, GPTIMER_ETI2_TRG_EDGE_BOTH
                  disable_source_eti3: GPTIMER_ETI3_TRG_DISABLE, GPTIMER_ETI3_TRG_EDGE_RISING, GPTIMER_ETI3_TRG_EDGE_FALLING, GPTIMER_ETI3_TRG_EDGE_BOTH
                  disable_source_ch0: GPTIMER_CH0_TRG_DISABLE, GPTIMER_CH0_TRG_EDGE_RISING, GPTIMER_CH0_TRG_EDGE_FALLING, GPTIMER_CH0_TRG_EDGE_BOTH
                  disable_source_ch1: GPTIMER_CH1_TRG_DISABLE, GPTIMER_CH1_TRG_EDGE_RISING, GPTIMER_CH1_TRG_EDGE_FALLING, GPTIMER_CH1_TRG_EDGE_BOTH
                  disable_source_evsel0: GPTIMER_EVSEL0_TRG_DISABLE, GPTIMER_EVSEL0_TRG_ENABLE
                  disable_source_evsel1: GPTIMER_EVSEL1_TRG_DISABLE, GPTIMER_EVSEL1_TRG_ENABLE
                  disable_source_evsel2: GPTIMER_EVSEL2_TRG_DISABLE, GPTIMER_EVSEL2_TRG_ENABLE
                  disable_source_evsel3: GPTIMER_EVSEL3_TRG_DISABLE, GPTIMER_EVSEL3_TRG_ENABLE
                  disable_source_evsel4: GPTIMER_EVSEL4_TRG_DISABLE, GPTIMER_EVSEL4_TRG_ENABLE
                  disable_source_evsel5: GPTIMER_EVSEL5_TRG_DISABLE, GPTIMER_EVSEL5_TRG_ENABLE
                  disable_source_evsel6: GPTIMER_EVSEL6_TRG_DISABLE, GPTIMER_EVSEL6_TRG_ENABLE
                  disable_source_evsel7: GPTIMER_EVSEL7_TRG_DISABLE, GPTIMER_EVSEL7_TRG_ENABLE
                  disable_source_software: GPTIMER_SOFTWARE_TRG_DISABLE, GPTIMER_SOFTWARE_TRG_ENABLE
    \param[out] none
    \retval     none
*/
void gptimer_counter_disable_source_config(uint32_t timer_periph,
                                           gptimer_counter_disable_source_parameter_struct *counter_disable_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(counter_disable_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x000EU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPTIMER_DSSEL(timer_periph) = (uint32_t)((uint32_t)(counter_disable_source_para->disable_source_eti0 & GPTIMER_DSSEL_ETI0DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_eti1 & GPTIMER_DSSEL_ETI1DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_eti2 & GPTIMER_DSSEL_ETI2DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_eti3 & GPTIMER_DSSEL_ETI3DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_ch0 & GPTIMER_DSSEL_CH0DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_ch1 & GPTIMER_DSSEL_CH1DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_evsel0 & GPTIMER_DSSEL_EVSEL0DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_evsel1 & GPTIMER_DSSEL_EVSEL1DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_evsel2 & GPTIMER_DSSEL_EVSEL2DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_evsel3 & GPTIMER_DSSEL_EVSEL3DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_evsel4 & GPTIMER_DSSEL_EVSEL4DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_evsel5 & GPTIMER_DSSEL_EVSEL5DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_evsel6 & GPTIMER_DSSEL_EVSEL6DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_evsel7 & GPTIMER_DSSEL_EVSEL7DISCNT) |
                                                 (uint32_t)(counter_disable_source_para->disable_source_software & GPTIMER_DSSEL_SWDISCNT));
    }
}

/*!
    \brief      initialize GPTIMER counter reset source init parameter struct with a default value (API_ID(0x000FU))
    \param[in]  counter_reset_source_para: counter reset source init parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_counter_reset_source_struct_para_init(gptimer_counter_reset_source_parameter_struct
                                                   *counter_reset_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(counter_reset_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x000FU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        counter_reset_source_para->reset_source_eti0 = GPTIMER_ETI0_TRG_DISABLE;
        counter_reset_source_para->reset_source_eti1 = GPTIMER_ETI1_TRG_DISABLE;
        counter_reset_source_para->reset_source_eti2 = GPTIMER_ETI2_TRG_DISABLE;
        counter_reset_source_para->reset_source_eti3 = GPTIMER_ETI3_TRG_DISABLE;
        counter_reset_source_para->reset_source_ch0 = GPTIMER_CH0_TRG_DISABLE;
        counter_reset_source_para->reset_source_ch1 = GPTIMER_CH1_TRG_DISABLE;
        counter_reset_source_para->reset_source_evsel0 = GPTIMER_EVSEL0_TRG_DISABLE;
        counter_reset_source_para->reset_source_evsel1 = GPTIMER_EVSEL1_TRG_DISABLE;
        counter_reset_source_para->reset_source_evsel2 = GPTIMER_EVSEL2_TRG_DISABLE;
        counter_reset_source_para->reset_source_evsel3 = GPTIMER_EVSEL3_TRG_DISABLE;
        counter_reset_source_para->reset_source_evsel4 = GPTIMER_EVSEL4_TRG_DISABLE;
        counter_reset_source_para->reset_source_evsel5 = GPTIMER_EVSEL5_TRG_DISABLE;
        counter_reset_source_para->reset_source_evsel6 = GPTIMER_EVSEL6_TRG_DISABLE;
        counter_reset_source_para->reset_source_evsel7 = GPTIMER_EVSEL7_TRG_DISABLE;
        counter_reset_source_para->reset_source_com_cap_sync = GPTIMER_RESET_SOURCE_DISABLE;
        counter_reset_source_para->reset_source_software = GPTIMER_SOFTWARE_TRG_DISABLE;
    }
}

/*!
    \brief      initialize GPTIMER counter reset source (API_ID(0x0010U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  counter_reset_source_para: counter reset source init parameter struct
                  reset_source_eti0: GPTIMER_ETI0_TRG_DISABLE, GPTIMER_ETI0_TRG_EDGE_RISING, GPTIMER_ETI0_TRG_EDGE_FALLING, GPTIMER_ETI0_TRG_EDGE_BOTH
                  reset_source_eti1: GPTIMER_ETI1_TRG_DISABLE, GPTIMER_ETI1_TRG_EDGE_RISING, GPTIMER_ETI1_TRG_EDGE_FALLING, GPTIMER_ETI1_TRG_EDGE_BOTH
                  reset_source_eti2: GPTIMER_ETI2_TRG_DISABLE, GPTIMER_ETI2_TRG_EDGE_RISING, GPTIMER_ETI2_TRG_EDGE_FALLING, GPTIMER_ETI2_TRG_EDGE_BOTH
                  reset_source_eti3: GPTIMER_ETI3_TRG_DISABLE, GPTIMER_ETI3_TRG_EDGE_RISING, GPTIMER_ETI3_TRG_EDGE_FALLING, GPTIMER_ETI3_TRG_EDGE_BOTH
                  reset_source_ch0: GPTIMER_CH0_TRG_DISABLE, GPTIMER_CH0_TRG_EDGE_RISING, GPTIMER_CH0_TRG_EDGE_FALLING, GPTIMER_CH0_TRG_EDGE_BOTH
                  reset_source_ch1: GPTIMER_CH1_TRG_DISABLE, GPTIMER_CH1_TRG_EDGE_RISING, GPTIMER_CH1_TRG_EDGE_FALLING, GPTIMER_CH1_TRG_EDGE_BOTH
                  reset_source_evsel0: GPTIMER_EVSEL0_TRG_DISABLE, GPTIMER_EVSEL0_TRG_ENABLE
                  reset_source_evsel1: GPTIMER_EVSEL1_TRG_DISABLE, GPTIMER_EVSEL1_TRG_ENABLE
                  reset_source_evsel2: GPTIMER_EVSEL2_TRG_DISABLE, GPTIMER_EVSEL2_TRG_ENABLE
                  reset_source_evsel3: GPTIMER_EVSEL3_TRG_DISABLE, GPTIMER_EVSEL3_TRG_ENABLE
                  reset_source_evsel4: GPTIMER_EVSEL4_TRG_DISABLE, GPTIMER_EVSEL4_TRG_ENABLE
                  reset_source_evsel5: GPTIMER_EVSEL5_TRG_DISABLE, GPTIMER_EVSEL5_TRG_ENABLE
                  reset_source_evsel6: GPTIMER_EVSEL6_TRG_DISABLE, GPTIMER_EVSEL6_TRG_ENABLE
                  reset_source_evsel7: GPTIMER_EVSEL7_TRG_DISABLE, GPTIMER_EVSEL7_TRG_ENABLE
                  reset_source_com_cap_sync: GPTIMER_RESET_SOURCE_DISABLE, GPTIMER_RESET_SOURCE_CH1CV_CMP_CAP, GPTIMER_RESET_SOURCE_CH0CV_CMP_CAP
                                        GPTIMER_RESET_SOURCE_CH1COMADD_CMP, GPTIMER_RESET_SOURCE_CH0COMADD_CMP, GPTIMER_RESET_SOURCE_SYNC_RESET
                  reset_source_software: GPTIMER_SOFTWARE_TRG_DISABLE, GPTIMER_SOFTWARE_TRG_ENABLE
    \param[out] none
    \retval     none
*/
void gptimer_counter_reset_source_config(uint32_t timer_periph,
                                         gptimer_counter_reset_source_parameter_struct *counter_reset_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(counter_reset_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0010U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPTIMER_RSSEL(timer_periph) = (uint32_t)((uint32_t)(counter_reset_source_para->reset_source_eti0 & GPTIMER_RSSEL_ETI0RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_eti1 & GPTIMER_RSSEL_ETI1RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_eti2 & GPTIMER_RSSEL_ETI2RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_eti3 & GPTIMER_RSSEL_ETI3RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_ch0 & GPTIMER_RSSEL_CH0RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_ch1 & GPTIMER_RSSEL_CH1RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_evsel0 & GPTIMER_RSSEL_EVSEL0RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_evsel1 & GPTIMER_RSSEL_EVSEL1RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_evsel2 & GPTIMER_RSSEL_EVSEL2RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_evsel3 & GPTIMER_RSSEL_EVSEL3RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_evsel4 & GPTIMER_RSSEL_EVSEL4RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_evsel5 & GPTIMER_RSSEL_EVSEL5RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_evsel6 & GPTIMER_RSSEL_EVSEL6RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_evsel7 & GPTIMER_RSSEL_EVSEL7RSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_com_cap_sync & GPTIMER_RSSEL_CSIRSTCNT) |
                                                 (uint32_t)(counter_reset_source_para->reset_source_software & GPTIMER_RSSEL_SWRSTCNT));
    }
}

/*!
    \brief      initialize GPTIMER counter up source init parameter struct with a default value (API_ID(0x0011U))
    \param[in]  counter_up_source_para: counter up source init parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_counter_up_source_struct_para_init(gptimer_counter_up_source_parameter_struct *counter_up_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(counter_up_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0011U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        counter_up_source_para->up_count_source_eti0 = GPTIMER_ETI0_TRG_DISABLE;
        counter_up_source_para->up_count_source_eti1 = GPTIMER_ETI1_TRG_DISABLE;
        counter_up_source_para->up_count_source_eti2 = GPTIMER_ETI2_TRG_DISABLE;
        counter_up_source_para->up_count_source_eti3 = GPTIMER_ETI3_TRG_DISABLE;
        counter_up_source_para->up_count_source_ch0 = GPTIMER_CH0_TRG_DISABLE;
        counter_up_source_para->up_count_source_ch1 = GPTIMER_CH1_TRG_DISABLE;
        counter_up_source_para->up_count_source_evsel0 = GPTIMER_EVSEL0_TRG_DISABLE;
        counter_up_source_para->up_count_source_evsel1 = GPTIMER_EVSEL1_TRG_DISABLE;
        counter_up_source_para->up_count_source_evsel2 = GPTIMER_EVSEL2_TRG_DISABLE;
        counter_up_source_para->up_count_source_evsel3 = GPTIMER_EVSEL3_TRG_DISABLE;
        counter_up_source_para->up_count_source_evsel4 = GPTIMER_EVSEL4_TRG_DISABLE;
        counter_up_source_para->up_count_source_evsel5 = GPTIMER_EVSEL5_TRG_DISABLE;
        counter_up_source_para->up_count_source_evsel6 = GPTIMER_EVSEL6_TRG_DISABLE;
        counter_up_source_para->up_count_source_evsel7 = GPTIMER_EVSEL7_TRG_DISABLE;
    }
}

/*!
    \brief      initialize GPTIMER counter up source (API_ID(0x0012U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  counter_up_source_para: counter up source init parameter struct
                  up_count_source_eti0: GPTIMER_ETI0_TRG_DISABLE, GPTIMER_ETI0_TRG_EDGE_RISING, GPTIMER_ETI0_TRG_EDGE_FALLING, GPTIMER_ETI0_TRG_EDGE_BOTH
                  up_count_source_eti1: GPTIMER_ETI1_TRG_DISABLE, GPTIMER_ETI1_TRG_EDGE_RISING, GPTIMER_ETI1_TRG_EDGE_FALLING, GPTIMER_ETI1_TRG_EDGE_BOTH
                  up_count_source_eti2: GPTIMER_ETI2_TRG_DISABLE, GPTIMER_ETI2_TRG_EDGE_RISING, GPTIMER_ETI2_TRG_EDGE_FALLING, GPTIMER_ETI2_TRG_EDGE_BOTH
                  up_count_source_eti3: GPTIMER_ETI3_TRG_DISABLE, GPTIMER_ETI3_TRG_EDGE_RISING, GPTIMER_ETI3_TRG_EDGE_FALLING, GPTIMER_ETI3_TRG_EDGE_BOTH
                  up_count_source_ch0: GPTIMER_CH0_TRG_DISABLE, GPTIMER_CH0_TRG_EDGE_RISING, GPTIMER_CH0_TRG_EDGE_FALLING, GPTIMER_CH0_TRG_EDGE_BOTH
                  up_count_source_ch1: GPTIMER_CH1_TRG_DISABLE, GPTIMER_CH1_TRG_EDGE_RISING, GPTIMER_CH1_TRG_EDGE_FALLING, GPTIMER_CH1_TRG_EDGE_BOTH
                  up_count_source_evsel0: GPTIMER_EVSEL0_TRG_DISABLE, GPTIMER_EVSEL0_TRG_ENABLE
                  up_count_source_evsel1: GPTIMER_EVSEL1_TRG_DISABLE, GPTIMER_EVSEL1_TRG_ENABLE
                  up_count_source_evsel2: GPTIMER_EVSEL2_TRG_DISABLE, GPTIMER_EVSEL2_TRG_ENABLE
                  up_count_source_evsel3: GPTIMER_EVSEL3_TRG_DISABLE, GPTIMER_EVSEL3_TRG_ENABLE
                  up_count_source_evsel4: GPTIMER_EVSEL4_TRG_DISABLE, GPTIMER_EVSEL4_TRG_ENABLE
                  up_count_source_evsel5: GPTIMER_EVSEL5_TRG_DISABLE, GPTIMER_EVSEL5_TRG_ENABLE
                  up_count_source_evsel6: GPTIMER_EVSEL6_TRG_DISABLE, GPTIMER_EVSEL6_TRG_ENABLE
                  up_count_source_evsel7: GPTIMER_EVSEL7_TRG_DISABLE, GPTIMER_EVSEL7_TRG_ENABLE
    \param[out] none
    \retval     none
*/
void gptimer_counter_up_source_config(uint32_t timer_periph,
                                      gptimer_counter_up_source_parameter_struct *counter_up_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(counter_up_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0012U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPTIMER_CUPEVSSEL(timer_periph) = (uint32_t)((uint32_t)(counter_up_source_para->up_count_source_eti0 & GPTIMER_CUPEVSSEL_ETI0CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_eti1 & GPTIMER_CUPEVSSEL_ETI1CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_eti2 & GPTIMER_CUPEVSSEL_ETI2CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_eti3 & GPTIMER_CUPEVSSEL_ETI3CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_ch0 & GPTIMER_CUPEVSSEL_CH0CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_ch1 & GPTIMER_CUPEVSSEL_CH1CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_evsel0 & GPTIMER_CUPEVSSEL_EVSEL0CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_evsel1 & GPTIMER_CUPEVSSEL_EVSEL1CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_evsel2 & GPTIMER_CUPEVSSEL_EVSEL2CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_evsel3 & GPTIMER_CUPEVSSEL_EVSEL3CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_evsel4 & GPTIMER_CUPEVSSEL_EVSEL4CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_evsel5 & GPTIMER_CUPEVSSEL_EVSEL5CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_evsel6 & GPTIMER_CUPEVSSEL_EVSEL6CUPS) |
                                                     (uint32_t)(counter_up_source_para->up_count_source_evsel7 & GPTIMER_CUPEVSSEL_EVSEL7CUPS));
    }
}

/*!
    \brief      initialize GPTIMER counter down source init parameter struct with a default value (API_ID(0x0013U))
    \param[in]  counter_down_source_para: counter down source init parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_counter_down_source_struct_para_init(gptimer_counter_down_source_parameter_struct
                                                  *counter_down_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(counter_down_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0013U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        counter_down_source_para->down_count_source_eti0 = GPTIMER_ETI0_TRG_DISABLE;
        counter_down_source_para->down_count_source_eti1 = GPTIMER_ETI1_TRG_DISABLE;
        counter_down_source_para->down_count_source_eti2 = GPTIMER_ETI2_TRG_DISABLE;
        counter_down_source_para->down_count_source_eti3 = GPTIMER_ETI3_TRG_DISABLE;
        counter_down_source_para->down_count_source_ch0 = GPTIMER_CH0_TRG_DISABLE;
        counter_down_source_para->down_count_source_ch1 = GPTIMER_CH1_TRG_DISABLE;
        counter_down_source_para->down_count_source_evsel0 = GPTIMER_EVSEL0_TRG_DISABLE;
        counter_down_source_para->down_count_source_evsel1 = GPTIMER_EVSEL1_TRG_DISABLE;
        counter_down_source_para->down_count_source_evsel2 = GPTIMER_EVSEL2_TRG_DISABLE;
        counter_down_source_para->down_count_source_evsel3 = GPTIMER_EVSEL3_TRG_DISABLE;
        counter_down_source_para->down_count_source_evsel4 = GPTIMER_EVSEL4_TRG_DISABLE;
        counter_down_source_para->down_count_source_evsel5 = GPTIMER_EVSEL5_TRG_DISABLE;
        counter_down_source_para->down_count_source_evsel6 = GPTIMER_EVSEL6_TRG_DISABLE;
        counter_down_source_para->down_count_source_evsel7 = GPTIMER_EVSEL7_TRG_DISABLE;
    }
}

/*!
    \brief      initialize GPTIMER counter down source (API_ID(0x0014U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  counter_down_source_para: counter down source init parameter struct
                  down_count_source_eti0: GPTIMER_ETI0_TRG_DISABLE, GPTIMER_ETI0_TRG_EDGE_RISING, GPTIMER_ETI0_TRG_EDGE_FALLING, GPTIMER_ETI0_TRG_EDGE_BOTH
                  down_count_source_eti1: GPTIMER_ETI1_TRG_DISABLE, GPTIMER_ETI1_TRG_EDGE_RISING, GPTIMER_ETI1_TRG_EDGE_FALLING, GPTIMER_ETI1_TRG_EDGE_BOTH
                  down_count_source_eti2: GPTIMER_ETI2_TRG_DISABLE, GPTIMER_ETI2_TRG_EDGE_RISING, GPTIMER_ETI2_TRG_EDGE_FALLING, GPTIMER_ETI2_TRG_EDGE_BOTH
                  down_count_source_eti3: GPTIMER_ETI3_TRG_DISABLE, GPTIMER_ETI3_TRG_EDGE_RISING, GPTIMER_ETI3_TRG_EDGE_FALLING, GPTIMER_ETI3_TRG_EDGE_BOTH
                  down_count_source_ch0: GPTIMER_CH0_TRG_DISABLE, GPTIMER_CH0_TRG_EDGE_RISING, GPTIMER_CH0_TRG_EDGE_FALLING, GPTIMER_CH0_TRG_EDGE_BOTH
                  down_count_source_ch1: GPTIMER_CH1_TRG_DISABLE, GPTIMER_CH1_TRG_EDGE_RISING, GPTIMER_CH1_TRG_EDGE_FALLING, GPTIMER_CH1_TRG_EDGE_BOTH
                  down_count_source_evsel0: GPTIMER_EVSEL0_TRG_DISABLE, GPTIMER_EVSEL0_TRG_ENABLE
                  down_count_source_evsel1: GPTIMER_EVSEL1_TRG_DISABLE, GPTIMER_EVSEL1_TRG_ENABLE
                  down_count_source_evsel2: GPTIMER_EVSEL2_TRG_DISABLE, GPTIMER_EVSEL2_TRG_ENABLE
                  down_count_source_evsel3: GPTIMER_EVSEL3_TRG_DISABLE, GPTIMER_EVSEL3_TRG_ENABLE
                  down_count_source_evsel4: GPTIMER_EVSEL4_TRG_DISABLE, GPTIMER_EVSEL4_TRG_ENABLE
                  down_count_source_evsel5: GPTIMER_EVSEL5_TRG_DISABLE, GPTIMER_EVSEL5_TRG_ENABLE
                  down_count_source_evsel6: GPTIMER_EVSEL6_TRG_DISABLE, GPTIMER_EVSEL6_TRG_ENABLE
                  down_count_source_evsel7: GPTIMER_EVSEL7_TRG_DISABLE, GPTIMER_EVSEL7_TRG_ENABLE
    \param[out] none
    \retval     none
*/
void gptimer_counter_down_source_config(uint32_t timer_periph,
                                        gptimer_counter_down_source_parameter_struct *counter_down_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(counter_down_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0014U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPTIMER_CDNEVSSEL(timer_periph) = (uint32_t)((uint32_t)(counter_down_source_para->down_count_source_eti0 & GPTIMER_CDNEVSSEL_ETI0CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_eti1 & GPTIMER_CDNEVSSEL_ETI1CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_eti2 & GPTIMER_CDNEVSSEL_ETI2CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_eti3 & GPTIMER_CDNEVSSEL_ETI3CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_ch0 & GPTIMER_CDNEVSSEL_CH0CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_ch1 & GPTIMER_CDNEVSSEL_CH1CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_evsel0 & GPTIMER_CDNEVSSEL_EVSEL0CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_evsel1 & GPTIMER_CDNEVSSEL_EVSEL1CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_evsel2 & GPTIMER_CDNEVSSEL_EVSEL2CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_evsel3 & GPTIMER_CDNEVSSEL_EVSEL3CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_evsel4 & GPTIMER_CDNEVSSEL_EVSEL4CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_evsel5 & GPTIMER_CDNEVSSEL_EVSEL5CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_evsel6 & GPTIMER_CDNEVSSEL_EVSEL6CDWS) |
                                                     (uint32_t)(counter_down_source_para->down_count_source_evsel7 & GPTIMER_CDNEVSSEL_EVSEL7CDWS));
    }
}

/*!
    \brief      select counter up input level source (API_ID(0x0015U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  input_source: counter up input level source
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_COUNTER_UP_DISABLE: counter up input source disable
      \arg        GPTIMER_COUNTER_UP_CH0_LOW: channel 0 low as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_CH0_HIGH: channel 0 high as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_CH1_LOW: channel 1 low as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_CH1_HIGH: channel 1 high as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_ETI0_LOW: eti0 low as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_ETI0_HIGH: eti0 high as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_ETI1_LOW: eti1 low as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_ETI1_HIGH: eti1 high as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_ETI2_LOW: eti2 low as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_ETI2_HIGH: eti2 high as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_ETI3_LOW: eti3 low as counter up input source enable
      \arg        GPTIMER_COUNTER_UP_ETI3_HIGH: eti3 high as counter up input source enable
    \param[out] none
    \retval     none
*/
void gptimer_counter_up_input_level_source_select(uint32_t timer_periph, uint32_t input_source)
{
    GPTIMER_CUPEVSSEL(timer_periph) &= ~(uint32_t)(GPTIMER_CUPEVSSEL_INTLCUPS);
    GPTIMER_CUPEVSSEL(timer_periph) |= (uint32_t)(input_source & GPTIMER_CUPEVSSEL_INTLCUPS);
}

/*!
    \brief      select counter down input level source (API_ID(0x0016U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  input_source: counter down input level source
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_COUNTER_DOWN_DISABLE: counter down input source disable
      \arg        GPTIMER_COUNTER_DOWN_CH0_LOW: channel 0 low as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_CH0_HIGH: channel 0 high as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_CH1_LOW: channel 1 low as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_CH1_HIGH: channel 1 high as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_ETI0_LOW: eti0 low as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_ETI0_HIGH: eti0 high as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_ETI1_LOW: eti1 low as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_ETI1_HIGH: eti1 high as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_ETI2_LOW: eti2 low as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_ETI2_HIGH: eti2 high as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_ETI3_LOW: eti3 low as counter down input source enable
      \arg        GPTIMER_COUNTER_DOWN_ETI3_HIGH: eti3 high as counter down input source enable
    \param[out] none
    \retval     none
*/
void gptimer_counter_down_input_level_source_select(uint32_t timer_periph, uint32_t input_source)
{
    GPTIMER_CDNEVSSEL(timer_periph) &= ~(uint32_t)(GPTIMER_CDNEVSSEL_INTLCDWS);
    GPTIMER_CDNEVSSEL(timer_periph) |= (uint32_t)(input_source & GPTIMER_CDNEVSSEL_INTLCDWS);
}

/*!
    \brief      enable GPTIMER (API_ID(0x0017U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_enable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) |= (uint32_t)GPTIMER_CTL0_CEN;
}

/*!
    \brief      disable GPTIMER (API_ID(0x0018U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_disable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) &= ~(uint32_t)GPTIMER_CTL0_CEN;
}

/*!
    \brief      enable the auto reload shadow function (API_ID(0x0019U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_auto_reload_shadow_enable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) |= (uint32_t)GPTIMER_CTL0_ARSE;
}

/*!
    \brief      disable the auto reload shadow function (API_ID(0x001AU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_auto_reload_shadow_disable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) &= ~(uint32_t)GPTIMER_CTL0_ARSE;
}

/*!
    \brief      enable the update event (API_ID(0x001BU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_update_event_enable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) &= ~(uint32_t)GPTIMER_CTL0_UPDIS;
}

/*!
    \brief      disable the update event (API_ID(0x001CU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_update_event_disable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) |= (uint32_t) GPTIMER_CTL0_UPDIS;
}

/*!
    \brief      set counter alignment mode (API_ID(0x001DU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  aligned:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_COUNTER_EDGE: edge-aligned mode
      \arg        GPTIMER_COUNTER_CENTER: center-aligned mode
    \param[out] none
    \retval     none
*/
void gptimer_counter_alignment(uint32_t timer_periph, uint16_t aligned)
{
    GPTIMER_CTL0(timer_periph) &= (uint32_t)(~GPTIMER_CTL0_CAM);
    GPTIMER_CTL0(timer_periph) |= (uint32_t)(aligned & GPTIMER_CTL0_CAM);
}

/*!
    \brief      set counter up direction (API_ID(0x001EU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_counter_up_direction(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) &= ~(uint32_t)GPTIMER_CTL0_DIR;
}

/*!
    \brief      set counter down direction (API_ID(0x001FU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_counter_down_direction(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) |= (uint32_t)GPTIMER_CTL0_DIR;
}

/*!
    \brief      enable counter direction force set (API_ID(0x0020U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_counter_direction_force_set_enable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) |= (uint32_t)GPTIMER_CTL0_FDIR;
}

/*!
    \brief      disable counter direction force set (API_ID(0x0021U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_counter_direction_force_set_disable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) &= ~(uint32_t)GPTIMER_CTL0_FDIR;
}

/*!
    \brief      select register global update source (API_ID(0x0022U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  source:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_GLOBAL_UPS_SEL_FLOW: global update event source select counter overflow / underflow event
      \arg        GPTIMER_GLOBAL_UPS_SEL_OVERFLOW: global update event source select counter overflow event
      \arg        GPTIMER_GLOBAL_UPS_SEL_UNDERFLOW: global update event source select counter underflow event
    \param[out] none
    \retval     none
*/
void gptimer_register_global_update_source_select(uint32_t timer_periph, uint32_t source)
{
    GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_GLBUPSEL;
    GPTIMER_UPSSEL(timer_periph) |= (uint32_t)(source & GPTIMER_UPSSEL_GLBUPSEL);
}

/*!
    \brief      select register local update source (API_ID(0x0023U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  reg:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_LOCAL_UP_CH0CV: CH0CV local update
      \arg        GPTIMER_LOCAL_UP_CH0COMV_ADD: CH0COMV_ADD local update
      \arg        GPTIMER_LOCAL_UP_CH1CV: CH1CV local update
      \arg        GPTIMER_LOCAL_UP_CH1COMV_ADD: CH1COMV_ADD local update
      \arg        GPTIMER_LOCAL_UP_ADCCR1: ADC triggered comparison value 1 local update
      \arg        GPTIMER_LOCAL_UP_ADCCR2: ADC triggered comparison value 2 local update
      \arg        GPTIMER_LOCAL_UP_CAR: car local update
      \arg        GPTIMER_LOCAL_UP_CH0: channel 0 output mode local update
      \arg        GPTIMER_LOCAL_UP_CH1: channel 1 output mode local update
    \param[in]  source:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_LOCAL_UPS_SEL_DISABLE: local update event source select disable
      \arg        GPTIMER_LOCAL_UPS_SEL_OVERFLOW: local update event source select counter overflow event
      \arg        GPTIMER_LOCAL_UPS_SEL_UNDERFLOW: local update event source select counter underflow event
      \arg        GPTIMER_LOCAL_UPS_SEL_FLOW: local update event source select counter flow event
      \arg        GPTIMER_LOCAL_UPS_SEL_CHCOM: local update event source select channel compare event(only GPTIMER_LOCAL_UP_CH0COMV_ADD
                                               and GPTIMER_LOCAL_UP_CH1COMV_ADD can be selected)
    \param[out] none
    \retval     none
*/
void gptimer_register_local_update_source_select(uint32_t timer_periph, uint32_t reg, uint32_t source)
{
    switch(reg) {
    case GPTIMER_LOCAL_UP_CH0CV:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_CH0CVUPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)(source & GPTIMER_UPSSEL_CH0CVUPSEL);
        break;
    case GPTIMER_LOCAL_UP_CH0COMV_ADD:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_CH0COMV_ADDUPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)((source << 2) & GPTIMER_UPSSEL_CH0COMV_ADDUPSEL);
        break;
    case GPTIMER_LOCAL_UP_CH1CV:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_CH1CVUPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)((source << 5) & GPTIMER_UPSSEL_CH1CVUPSEL);
        break;
    case GPTIMER_LOCAL_UP_CH1COMV_ADD:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_CH1COMV_ADDUPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)((source << 7) & GPTIMER_UPSSEL_CH1COMV_ADDUPSEL);
        break;
    case GPTIMER_LOCAL_UP_ADCCR1:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_ADCCR1UPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)((source << 10) & GPTIMER_UPSSEL_ADCCR1UPSEL);
        break;
    case GPTIMER_LOCAL_UP_ADCCR2:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_ADCCR1UPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)((source << 12) & GPTIMER_UPSSEL_ADCCR1UPSEL);
        break;
    case GPTIMER_LOCAL_UP_CAR:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_CARUPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)((source << 14) & GPTIMER_UPSSEL_CARUPSEL);
        break;
    case GPTIMER_LOCAL_UP_CH0:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_CH0UPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)((source << 24) & GPTIMER_UPSSEL_CH0UPSEL);
        break;
    case GPTIMER_LOCAL_UP_CH1:
        GPTIMER_UPSSEL(timer_periph) &= ~(uint32_t)GPTIMER_UPSSEL_CH1UPSEL;
        GPTIMER_UPSSEL(timer_periph) |= (uint32_t)((source << 26) & GPTIMER_UPSSEL_CH1UPSEL);
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief      configure prescaler (API_ID(0x0024U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  prescaler: prescaler value,0~65535
    \param[out] none
    \retval     none
*/
void gptimer_prescaler_config(uint32_t timer_periph, uint16_t prescaler)
{
    GPTIMER_PSC(timer_periph) = (uint32_t)prescaler;
}

/*!
    \brief      configure update repetition register value (API_ID(0x0025U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  repetition: the counter repetition value, 0~4095
    \param[in]  load_mode:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_UPREP_LOAD_IMMEDIATELY: repetition load immediately
      \arg        GPTIMER_UPREP_LOAD_NEXT_UPEVENT: repetition load at next update
    \param[out] none
    \retval     none
*/
void gptimer_update_repetition_value_config(uint32_t timer_periph, uint16_t repetition, uint32_t load_mode)
{
    GPTIMER_CREP(timer_periph) = (uint32_t)(repetition & GPTIMER_CREP_CREP);
    if(load_mode == GPTIMER_UPREP_LOAD_IMMEDIATELY) {
        GPTIMER_CREP(timer_periph) |= GPTIMER_CREP_RLD;
    }
}

/*!
    \brief      read update repetition register value (API_ID(0x0026U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     repetition value
*/
uint16_t gptimer_update_repetition_counter_read(uint32_t timer_periph)
{
    uint16_t repetition_counter = 0U;
    repetition_counter = (uint16_t)(((GPTIMER_CREP(timer_periph))&GPTIMER_CREP_CNT) >> 16);
    return repetition_counter;
}

/*!
    \brief      configure autoreload register value (API_ID(0x0027U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  autoreload: the counter auto-reload value,0~65535
    \param[out] none
    \retval     none
*/
void gptimer_autoreload_value_config(uint32_t timer_periph, uint32_t autoreload)
{
    GPTIMER_CAR(timer_periph) = (uint32_t)autoreload;
}

/*!
    \brief      configure counter register value (API_ID(0x0028U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  counter: the counter value, 0~65535
    \param[out] none
    \retval     none
*/
void gptimer_counter_value_config(uint32_t timer_periph, uint32_t counter)
{
    GPTIMER_CNT(timer_periph) = (uint32_t)counter;
}

/*!
    \brief      read counter value (API_ID(0x0029U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     counter value
*/
uint32_t gptimer_counter_read(uint32_t timer_periph)
{
    uint32_t count_value = 0U;
    count_value = GPTIMER_CNT(timer_periph);
    return count_value;
}

/*!
    \brief      read prescaler value (API_ID(0x002AU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     prescaler register value
*/
uint16_t gptimer_prescaler_read(uint32_t timer_periph)
{
    uint16_t prescaler_value = 0U;
    prescaler_value = (uint16_t)(GPTIMER_PSC(timer_periph));
    return prescaler_value;
}

/*!
    \brief      configure single pulse mode (API_ID(0x002BU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  spmode:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_SP_MODE_SINGLE: single pulse mode
      \arg        GPTIMER_SP_MODE_REPETITIVE: repetitive pulse mode
    \param[out] none
    \retval     none
*/
void gptimer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode)
{
    if(GPTIMER_SP_MODE_SINGLE == spmode) {
        GPTIMER_CTL0(timer_periph) |= (uint32_t)GPTIMER_CTL0_SPM;
    } else if(GPTIMER_SP_MODE_REPETITIVE == spmode) {
        GPTIMER_CTL0(timer_periph) &= ~((uint32_t)GPTIMER_CTL0_SPM);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable DMA (API_ID(0x002CU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  dma:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER_DMA_CH0D:channel 0 capture or compare DMA request
      \arg        GPTIMER_DMA_CH1D: channel 1 capture or compare DMA request
      \arg        GPTIMER_DMA_CH0COMADD: channel 0 additional compare DMA request
      \arg        GPTIMER_DMA_CH1COMADD: channel 1 additional compare DMA request
      \arg        GPTIMER_DMA_REPED: repetition count end DMA request
      \arg        GPTIMER_DMA_OVERFLOWD: counter overflow DMA request
      \arg        GPTIMER_DMA_UNDERFLOWD: counter underflow DMA request
      \arg        GPTIMER_DMA_OVUNFLOWD: counter overflow/underflow DMA request
    \param[out] none
    \retval     none
*/
void gptimer_dma_enable(uint32_t timer_periph, uint32_t dma)
{
    GPTIMER_DMAINTEN(timer_periph) |= (uint32_t)(dma & DMA_REQUEST_ENABLE_MASK);
}

/*!
    \brief      disable DMA (API_ID(0x002DU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  dma:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER_DMA_CH0D:channel 0 capture or compare DMA request
      \arg        GPTIMER_DMA_CH1D: channel 1 capture or compare DMA request
      \arg        GPTIMER_DMA_CH0COMADD: channel 0 additional compare DMA request
      \arg        GPTIMER_DMA_CH1COMADD: channel 1 additional compare DMA request
      \arg        GPTIMER_DMA_REPED: repetition count end DMA request
      \arg        GPTIMER_DMA_OVERFLOWD: counter overflow DMA request
      \arg        GPTIMER_DMA_UNDERFLOWD: counter underflow DMA request
      \arg        GPTIMER_DMA_OVUNFLOWD: counter overflow/underflow DMA request
    \param[out] none
    \retval     none
*/
void gptimer_dma_disable(uint32_t timer_periph, uint32_t dma)
{
    GPTIMER_DMAINTEN(timer_periph) &= (~(uint32_t)(dma & DMA_REQUEST_ENABLE_MASK));
}

/*!
    \brief      configure the DMA transfer (API_ID(0x002EU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  dma_baseaddr:
                only one parameter can be selected which is shown as below:
       \arg        GPTIMER_DMACFG_DMATA_WP: DMA transfer address is GPTIMER_WP
       \arg        GPTIMER_DMACFG_DMATA_SWEN: DMA transfer address is GPTIMER_SWEN
       \arg        GPTIMER_DMACFG_DMATA_SWDIS: DMA transfer address is GPTIMER_SWDIS
       \arg        GPTIMER_DMACFG_DMATA_SWRST: DMA transfer address is GPTIMER_SWRST
       \arg        GPTIMER_DMACFG_DMATA_ESSEL: DMA transfer address is GPTIMER_ESSEL
       \arg        GPTIMER_DMACFG_DMATA_DSSEL: DMA transfer address is GPTIMER_DSSEL
       \arg        GPTIMER_DMACFG_DMATA_RSSEL: DMA transfer address is GPTIMER_RSSEL
       \arg        GPTIMER_DMACFG_DMATA_CH0CSSEL: DMA transfer address is GPTIMER_CH0CSSEL
       \arg        GPTIMER_DMACFG_DMATA_CH1CSSEL: DMA transfer address is GPTIMER_CH0CSSEL
       \arg        GPTIMER_DMACFG_DMATA_CTL1: DMA transfer address is GPTIMER_CTL0
       \arg        GPTIMER_DMACFG_DMATA_UPSSR: DMA transfer address is GPTIMER_CUPEVSSEL
       \arg        GPTIMER_DMACFG_DMATA_DNSSR: DMA transfer address is GPTIMER_CDNEVSSEL
       \arg        GPTIMER_DMACFG_DMATA_CH0CTL: DMA transfer address is GPTIMER_CH0CTL
       \arg        GPTIMER_DMACFG_DMATA_CH1CTL: DMA transfer address is GPTIMER_CH1CTL
       \arg        GPTIMER_DMACFG_DMATA_CHCTL: DMA transfer address is GPTIMER_CHCTL
       \arg        GPTIMER_DMACFG_DMATA_DMAINTEN: DMA transfer address is GPTIMER_DMAINTEN
       \arg        GPTIMER_DMACFG_DMATA_INTF: DMA transfer address is GPTIMER_INTF
       \arg        GPTIMER_DMACFG_DMATA_UPSSEL: DMA transfer address is GPTIMER_UPSSEL
       \arg        GPTIMER_DMACFG_DMATA_CNT: DMA transfer address is GPTIMER_CNT
       \arg        GPTIMER_DMACFG_DMATA_PSC: DMA transfer address is GPTIMER_PSC
       \arg        GPTIMER_DMACFG_DMATA_CAR: DMA transfer address is GPTIMER_CAR
       \arg        GPTIMER_DMACFG_DMATA_CH0CV: DMA transfer address is GPTIMER_CH0CV
       \arg        GPTIMER_DMACFG_DMATA_CH1CV: DMA transfer address is GPTIMER_CH1CV
       \arg        GPTIMER_DMACFG_DMATA_CH0COMV_ADD: DMA transfer address is GPTIMER_CH0COMV_ADD
       \arg        GPTIMER_DMACFG_DMATA_CH1COMV_ADD: DMA transfer address is GPTIMER_CH1COMV_ADD
       \arg        GPTIMER_DMACFG_DMATA_DTCTL: DMA transfer address is GPTIMER_DTCTL
       \arg        GPTIMER_DMACFG_DMATA_ADCTL: DMA transfer address is GPTIMER_ADCTL
       \arg        GPTIMER_DMACFG_DMATA_ADCCR1: DMA transfer address is GPTIMER_ADCCR1
       \arg        GPTIMER_DMACFG_DMATA_ADCCR2: DMA transfer address is GPTIMER_ADCCR2
       \arg        GPTIMER_DMACFG_DMATA_ADCTRGS: DMA transfer address is GPTIMER_ADCTRGS
       \arg        GPTIMER_DMACFG_DMATA_ADDINTSCTL0: DMA transfer address is GPTIMER_ADDINTSCTL0
       \arg        GPTIMER_DMACFG_DMATA_ADDINTSCTL1: DMA transfer address is GPTIMER_ADDINTSCTL1
       \arg        GPTIMER_DMACFG_DMATA_IADCTSS: DMA transfer address is GPTIMER_IADCTSS
       \arg        GPTIMER_DMACFG_DMATA_CREP: DMA transfer address is GPTIMER_CREP
       \arg        GPTIMER_DMACFG_DMATA_SYNRSTCTL: DMA transfer address is GPTIMER_SYNRSTCTL
       \param[in]  dma_lenth:
                   only one parameter can be selected which is shown as below:
       \arg        GPTIMER_DMACFG_DMATC_xTRANSFER(x=1..35): DMA transfer x time
    \param[out] none
    \retval     none
*/
void gptimer_dma_transfer_config(uint32_t timer_periph, uint32_t dma_baseaddr, uint32_t dma_lenth)
{
    GPTIMER_DMACFG(timer_periph) &= (~(uint32_t)(GPTIMER_DMACFG_DMATA | GPTIMER_DMACFG_DMATC));
    GPTIMER_DMACFG(timer_periph) |= (uint32_t)((dma_baseaddr & GPTIMER_DMACFG_DMATA) | (dma_lenth & GPTIMER_DMACFG_DMATC));
}

/*!
    \brief      initialize GPTIMER channel output parameter struct with a default value (API_ID(0x002FU))
    \param[in]  ocpara: GPTIMER channel n output parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_channel_output_struct_para_init(gptimer_oc_parameter_struct *ocpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(ocpara)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x002FU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the channel output parameter struct member with the default value */
        ocpara->chxcv_up_output_level                   = GPTIMER_MATCH_OUTPUT_KEEP;
        ocpara->chxcv_down_output_level                 = GPTIMER_MATCH_OUTPUT_KEEP;
        ocpara->chxcomv_add_up_output_level             = GPTIMER_MATCH_OUTPUT_KEEP;
        ocpara->chxcomv_add_down_output_level           = GPTIMER_MATCH_OUTPUT_KEEP;
        ocpara->period_end_output_level                 = GPTIMER_PERIOD_END_OUTPUT_KEEP;
        ocpara->cnt_enable_disable_oc_en                = GPTIMER_CNT_ENABLE_DISABLE_OC_KEEP;
        ocpara->cnt_enable_output_level                 = GPTIMER_CNT_ENABLE_OUTPUT_LOW;
        ocpara->cnt_disable_output_level                = GPTIMER_CNT_DISABLE_OUTPUT_LOW;
        ocpara->output_stop_output_level                = GPTIMER_OUTPUT_STOP_OUTPUT_KEEP;
        ocpara->force_duty_output_mode                  = GPTIMER_COMPARE_DUTY_OUTPUT;
        ocpara->force_duty_output_time                  = GPTIMER_FORCE_DUTY_OUTPUT_NEXT_PERIOD;
        ocpara->force_duty_end_output_level             = GPTIMER_FORCE_DUTY_END_BASE_OUTPUT_KEEP;
        ocpara->compare_period_end_priority_control     = GPRIMER_PERIOD_END_OUTPUT_COMPARE;
    }
}

/*!
    \brief      configure channel output mode (API_ID(0x0030U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  ocpara: GPTIMER channel n output parameter struct
                  chxcv_down_output_level: GPTIMER_MATCH_OUTPUT_KEEP, GPTIMER_MATCH_OUTPUT_LOW, GPTIMER_MATCH_OUTPUT_HIGH, GPTIMER_MATCH_OUTPUT_TOGGLE
                  chxcv_up_output_level: GPTIMER_MATCH_OUTPUT_KEEP, GPTIMER_MATCH_OUTPUT_LOW, GPTIMER_MATCH_OUTPUT_HIGH, GPTIMER_MATCH_OUTPUT_TOGGLE
                  chxcomv_add_down_output_level: GPTIMER_MATCH_OUTPUT_KEEP, GPTIMER_MATCH_OUTPUT_LOW, GPTIMER_MATCH_OUTPUT_HIGH, GPTIMER_MATCH_OUTPUT_TOGGLE
                  chxcomv_add_up_output_level: GPTIMER_MATCH_OUTPUT_KEEP, GPTIMER_MATCH_OUTPUT_LOW, GPTIMER_MATCH_OUTPUT_HIGH, GPTIMER_MATCH_OUTPUT_TOGGLE
                  period_end_output_level: GPTIMER_PERIOD_END_OUTPUT_KEEP, GPTIMER_PERIOD_END_OUTPUT_LOW, GPTIMER_PERIOD_END_OUTPUT_HIGH, GPTIMER_PERIOD_END_OUTPUT_TOGGLE
                  cnt_enable_disable_oc_en: GPTIMER_CNT_ENABLE_DISABLE_OC_KEEP, GPTIMER_CNT_ENABLE_DISABLE_OC_CTL
                  cnt_enable_output_level: GPTIMER_CNT_ENABLE_OUTPUT_LOW, GPTIMER_CNT_ENABLE_OUTPUT_HIGH
                  cnt_disable_output_level: GPTIMER_CNT_DISABLE_OUTPUT_LOW, GPTIMER_CNT_DISABLE_OUTPUT_HIGH
                  output_stop_output_level: GPTIMER_OUTPUT_STOP_OUTPUT_KEEP, GPTIMER_OUTPUT_STOP_OUTPUT_HIZ, GPTIMER_OUTPUT_STOP_OUTPUT_LOW, GPTIMER_OUTPUT_STOP_OUTPUT_HIGH
                  force_duty_output_mode: GPTIMER_COMPARE_DUTY_OUTPUT, GPTIMER_FORCE_0_DUTY_OUTPUT,GPTIMER_FORCE_100_DUTY_OUTPUT
                  force_duty_output_time: GPTIMER_FORCE_DUTY_OUTPUT_NEXT_PERIOD, GPTIMER_FORCE_DUTY_OUTPUT_IMMEDIATELY
                  force_duty_end_output_level: GPTIMER_FORCE_DUTY_END_BASE_OUTPUT_KEEP, GPTIMER_FORCE_DUTY_END_BASE_OUTPUT_COMPARE
                  compare_period_end_priority_control: GPRIMER_PERIOD_END_OUTPUT_COMPARE, GPRIMER_PERIOD_END_OUTPUT_KEEP
    \param[out] none
    \retval     none
*/
void gptimer_channel_output_config(uint32_t timer_periph, uint16_t channel, gptimer_oc_parameter_struct *ocpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(ocpara)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0030U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(channel) {
        /* configure GPTIMER_CH0 */
        case GPTIMER_CH0:
            GPTIMER_CH0CTL(timer_periph) &= ~(uint32_t)(GPTIMER_CH0CTL_CH0COMDW | GPTIMER_CH0CTL_CH0COMUP | \
                                                        GPTIMER_CH0CTL_CH0ACOMDW | GPTIMER_CH0CTL_CH0ACOMUP | \
                                                        GPTIMER_CH0CTL_CH0EFF | GPTIMER_CH0CTL_CH0OUTM | \
                                                        GPTIMER_CH0CTL_CH0OUTCTL | GPTIMER_CH0CTL_CH0REDUTY | \
                                                        GPTIMER_CH0CTL_CH0ENDOUT | GPTIMER_CH0CTL_CH0ENOUT | \
                                                        GPTIMER_CH0CTL_CH0DISOUT | GPTIMER_CH0CTL_CH0OUT | GPTIMER_CH0CTL_CH0INVSOUT);
            GPTIMER_CH0CTL(timer_periph) |= (uint32_t)((ocpara->chxcv_down_output_level & OUTPUT_LEVEL_MASK) | ((ocpara->chxcv_up_output_level & OUTPUT_LEVEL_MASK) << 2) | \
                                                       ((ocpara->chxcomv_add_down_output_level & OUTPUT_LEVEL_MASK) << 4) | ((ocpara->chxcomv_add_up_output_level & OUTPUT_LEVEL_MASK) << 6) | \
                                                       (ocpara->period_end_output_level & GPTIMER_CH0CTL_CH0ENDOUT) | (ocpara->cnt_enable_disable_oc_en & GPTIMER_CH0CTL_CH0OUT) | \
                                                       (ocpara->cnt_enable_output_level & GPTIMER_CH0CTL_CH0ENOUT) | (ocpara->cnt_disable_output_level & GPTIMER_CH0CTL_CH0DISOUT) | \
                                                       (ocpara->output_stop_output_level & GPTIMER_CH0CTL_CH0INVSOUT) | (ocpara->force_duty_output_mode & GPTIMER_CH0CTL_CH0OUTM) | \
                                                       (ocpara->force_duty_output_time & GPTIMER_CH0CTL_CH0OUTCTL) | (ocpara->force_duty_end_output_level & GPTIMER_CH0CTL_CH0REDUTY) | \
                                                       (ocpara->compare_period_end_priority_control & GPTIMER_CH0CTL_CH0EFF));
            break;
        case GPTIMER_CH1:
            /* configure GPTIMER_CH1 */
            GPTIMER_CH1CTL(timer_periph) &= ~(uint32_t)(GPTIMER_CH1CTL_CH1COMDW | GPTIMER_CH1CTL_CH1COMUP | \
                                                        GPTIMER_CH1CTL_CH1ACOMDW | GPTIMER_CH1CTL_CH1ACOMUP | \
                                                        GPTIMER_CH1CTL_CH1EFF | GPTIMER_CH1CTL_CH1OUTM | \
                                                        GPTIMER_CH1CTL_CH1OUTCTL | GPTIMER_CH1CTL_CH1REDUTY | \
                                                        GPTIMER_CH1CTL_CH1ENDOUT | GPTIMER_CH1CTL_CH1ENOUT | \
                                                        GPTIMER_CH1CTL_CH1DISOUT | GPTIMER_CH1CTL_CH1OUT | GPTIMER_CH1CTL_CH1INVSOUT);
            GPTIMER_CH1CTL(timer_periph) |= (uint32_t)((ocpara->chxcv_down_output_level & OUTPUT_LEVEL_MASK) | ((ocpara->chxcv_up_output_level & OUTPUT_LEVEL_MASK) << 2) | \
                                                       ((ocpara->chxcomv_add_down_output_level & OUTPUT_LEVEL_MASK) << 4) | ((ocpara->chxcomv_add_up_output_level & OUTPUT_LEVEL_MASK) << 6) | \
                                                       (ocpara->period_end_output_level & GPTIMER_CH1CTL_CH1ENDOUT) | (ocpara->cnt_enable_disable_oc_en & GPTIMER_CH1CTL_CH1OUT) | \
                                                       (ocpara->cnt_enable_output_level & GPTIMER_CH1CTL_CH1ENOUT) | (ocpara->cnt_disable_output_level & GPTIMER_CH1CTL_CH1DISOUT) | \
                                                       (ocpara->output_stop_output_level & GPTIMER_CH1CTL_CH1INVSOUT) | (ocpara->force_duty_output_mode & GPTIMER_CH1CTL_CH1OUTM) | \
                                                       (ocpara->force_duty_output_time & GPTIMER_CH1CTL_CH1OUTCTL) | (ocpara->force_duty_end_output_level & GPTIMER_CH1CTL_CH1REDUTY) | \
                                                       (ocpara->compare_period_end_priority_control & GPTIMER_CH1CTL_CH1EFF));
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      configure channel output force duty (API_ID(0x0031U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  duty: GPTIMER_COMPARE_DUTY_OUTPUT, GPTIMER_FORCE_0_DUTY_OUTPUT, GPTIMER_FORCE_100_DUTY_OUTPUT
    \param[in]  output_time: GPTIMER_FORCE_DUTY_OUTPUT_IMMEDIATELY, GPTIMER_FORCE_DUTY_OUTPUT_NEXT_PERIOD
    \param[out] none
    \retval     none
*/
void gptimer_channel_output_force_duty_config(uint32_t timer_periph, uint16_t channel, uint32_t duty,
                                              uint32_t output_time)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CH0CTL(timer_periph) &= ~(uint32_t)GPTIMER_CH0CTL_CH0OUTM;
        GPTIMER_CH0CTL(timer_periph) |= (uint32_t)(duty & GPTIMER_CH0CTL_CH0OUTM);
        GPTIMER_CH0CTL(timer_periph) &= ~(uint32_t)GPTIMER_CH0CTL_CH0OUTCTL;
        GPTIMER_CH0CTL(timer_periph) |= (uint32_t)(output_time & GPTIMER_CH0CTL_CH0OUTCTL);
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CH1CTL(timer_periph) &= ~(uint32_t)GPTIMER_CH1CTL_CH1OUTM;
        GPTIMER_CH1CTL(timer_periph) |= (uint32_t)(duty & GPTIMER_CH1CTL_CH1OUTM);
        GPTIMER_CH1CTL(timer_periph) &= ~(uint32_t)GPTIMER_CH1CTL_CH1OUTCTL;
        GPTIMER_CH1CTL(timer_periph) |= (uint32_t)(output_time & GPTIMER_CH1CTL_CH1OUTCTL);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure channel output compare value (API_ID(0x0032U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  value: 0~65535
    \param[out] none
    \retval     none
*/
void gptimer_channel_output_compare_value_config(uint32_t timer_periph, uint16_t channel, uint16_t value)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CH0CV(timer_periph) = (uint32_t)value;
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CH1CV(timer_periph) = (uint32_t)value;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure channel output additional compare value (API_ID(0x0033U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  value: 0~65535
    \param[out] none
    \retval     none
*/
void gptimer_channel_output_additional_compare_value_config(uint32_t timer_periph, uint16_t channel, uint16_t value)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CH0COMV_ADD(timer_periph) = (uint32_t)value;
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CH1COMV_ADD(timer_periph) = (uint32_t)value;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure channel output shadow function (API_ID(0x0034U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  ocshadow: channel output compare shadow
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_OC_SHADOW_ENABLE: channel output compare shadow enable
      \arg        GPTIMER_OC_SHADOW_DISABLE: channel output compare shadow disable
    \param[out] none
    \retval     none
*/
void gptimer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH0COMSEN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(((uint32_t)(ocshadow) << 4U) & GPTIMER_CHCTL_CH0COMSEN);
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH1COMSEN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(((uint32_t)(ocshadow) << 12U) & GPTIMER_CHCTL_CH1COMSEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure channel output additional shadow function (API_ID(0x0035U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  ocshadow: channel output compare shadow
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_OC_SHADOW_ENABLE: channel output compare shadow enable
      \arg        GPTIMER_OC_SHADOW_DISABLE: channel output compare shadow disable
    \param[out] none
    \retval     none
*/
void gptimer_channel_output_additional_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH0COMADDSEN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(((uint32_t)(ocshadow) << 5U) & GPTIMER_CHCTL_CH0COMADDSEN);
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH1COMADDSEN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(((uint32_t)(ocshadow) << 13U) & GPTIMER_CHCTL_CH1COMADDSEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure channel output additional shadow function (API_ID(0x0036U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  ocshadow: channel output compare shadow
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_OC_SHADOW_ENABLE: channel output compare shadow enable
      \arg        GPTIMER_OC_SHADOW_DISABLE: channel output compare shadow disable
    \param[out] none
    \retval     none
*/
void gptimer_channel_output_control_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH0SEN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(((uint32_t)(ocshadow) << 6U) & GPTIMER_CHCTL_CH0SEN);
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH1SEN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(((uint32_t)(ocshadow) << 14U) & GPTIMER_CHCTL_CH1SEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable two channel simultaneous output high check function (API_ID(0x0037U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_two_channel_output_high_check_enable(uint32_t timer_periph)
{
    GPTIMER_DMAINTEN(timer_periph) |= (uint32_t)GPTIMER_DMAINTEN_CHHOUTDET;
}

/*!
    \brief      disable two channel simultaneous output high check function (API_ID(0x0038U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_two_channel_output_high_check_disable(uint32_t timer_periph)
{
    GPTIMER_DMAINTEN(timer_periph) &= ~(uint32_t)GPTIMER_DMAINTEN_CHHOUTDET;
}

/*!
    \brief      enable two channel simultaneous output low check function (API_ID(0x0039U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_two_channel_output_low_check_enable(uint32_t timer_periph)
{
    GPTIMER_DMAINTEN(timer_periph) |= (uint32_t)GPTIMER_DMAINTEN_CHLOUTDET;
}

/*!
    \brief      disable two channel simultaneous output low check function (API_ID(0x003AU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_two_channel_output_low_check_disable(uint32_t timer_periph)
{
    GPTIMER_DMAINTEN(timer_periph) &= ~(uint32_t)GPTIMER_DMAINTEN_CHLOUTDET;
}

/*!
    \brief      enable counter cycle synchronization signal output (API_ID(0x003BU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_period_signal_output_enable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) |= (uint32_t)GPTIMER_CTL0_CCSOEN;
}

/*!
    \brief      disable counter cycle synchronization signal output (API_ID(0x003CU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     none
*/
void gptimer_period_signal_output_disable(uint32_t timer_periph)
{
    GPTIMER_CTL0(timer_periph) &= ~((uint32_t)GPTIMER_CTL0_CCSOEN);
}

/*!
    \brief      configure stop output source (API_ID(0x003DU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  group:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_OUTPUT_STOP_GTOC0: output stop GTOC0
      \arg        GPTIMER_OUTPUT_STOP_GTOC1: output stop GTOC1
      \arg        GPTIMER_OUTPUT_STOP_GTOC2: output stop GTOC2
      \arg        GPTIMER_OUTPUT_STOP_GTOC3: output stop GTOC3
    \param[out] none
    \retval     none
*/
void gptimer_stop_output_set_select(uint32_t timer_periph, uint32_t group)
{
    GPTIMER_DMAINTEN(timer_periph) &= ~(uint32_t)GPTIMER_DMAINTEN_CLOSSEL;
    GPTIMER_DMAINTEN(timer_periph) |= (uint32_t)(group & GPTIMER_DMAINTEN_CLOSSEL);
}

/*!
    \brief      output stop recover time select (API_ID(0x003EU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  time:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_OUTPUT_RECOVER_PERIOD_END: output stop recover time is period end
      \arg        GPTIMER_OUTPUT_RECOVER_CREP_END: output stop recover time is crep end
    \param[out] none
    \retval     none
*/
void gptimer_stop_output_recover_time_select(uint32_t timer_periph, uint32_t time)
{
    GPTIMER_CHCTL(timer_periph) &= ~(uint32_t)GPTIMER_CHCTL_STORESEL;
    GPTIMER_CHCTL(timer_periph) |= (uint32_t)(time & GPTIMER_CHCTL_STORESEL);
}

/*!
    \brief      initialize GPTIMER complementary output parameter struct with a default value (API_ID(0x003FU))
    \param[in]  comocpara: GPTIMER complementary output parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_channel_complementary_output_struct_para_init(gptimer_com_oc_parameter_struct *comocpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(comocpara)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x003FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the channel output parameter struct member with the default value */
        comocpara->complementary_mode         = GPTIMER_CH1_MODE_INDEPENDENTLY;
        comocpara->deadtime_enable            = GPTIMER_DEADTIME_DISABLE;
        comocpara->deadtime_mode              = GPTIMER_DEADTIME_MODE_SYMMETRIC;
        comocpara->rising_deadtime_value      = 0U;
        comocpara->falling_deadtime_value     = 0U;
        comocpara->rising_deadtime_shadow     = GPTIMER_DT_RISING_SHADOW_DISABLE;
        comocpara->falling_deadtime_shadow    = GPTIMER_DT_FALLING_SHADOW_DISABLE;
    }
}

/*!
    \brief      configure GPTIMER channel complementary output function (API_ID(0x0040U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  comocpara: GPTIMER complementary output parameter struct
                  complementary_mode: GPTIMER_CH1_MODE_INDEPENDENTLY, GPTIMER_CH1_MODE_COMPLEMENTARY
                  deadtime_enable: GPTIMER_DEADTIME_DISABLE, GPTIMER_DEADTIME_ENABLE
                  deadtime_mode: GPTIMER_DEADTIME_MODE_SYMMETRIC, GPTIMER_DEADTIME_MODE_ASYMMETRIC
                  rising_deadtime_value: 0~255
                  falling_deadtime_value: 0~255
                  rising_deadtime_shadow: GPTIMER_DT_RISING_SHADOW_DISABLE, GPTIMER_DT_RISING_SHADOW_ENABLE
                  falling_deadtime_shadow: GPTIMER_DT_FALLING_SHADOW_DISABLE, GPTIMER_DT_FALLING_SHADOW_ENABLE
    \param[out] none
    \retval     none
*/
void gptimer_channel_complementary_output_config(uint32_t timer_periph, gptimer_com_oc_parameter_struct *comocpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(comocpara)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0040U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH1MSEL);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(comocpara->complementary_mode & GPTIMER_CHCTL_CH1MSEL);

        GPTIMER_DTCTL(timer_periph) &= (~(uint32_t)GPTIMER_DTCTL_DTASYEN);
        GPTIMER_DTCTL(timer_periph) |= (uint32_t)(comocpara->deadtime_mode & GPTIMER_DTCTL_DTASYEN);

        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_DTEN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(comocpara->deadtime_enable & GPTIMER_CHCTL_DTEN);

        GPTIMER_DTCTL(timer_periph) &= (~(uint32_t)GPTIMER_DTCTL_REDTCFG);
        GPTIMER_DTCTL(timer_periph) |= (uint32_t)(comocpara->rising_deadtime_value & GPTIMER_DTCTL_REDTCFG);

        GPTIMER_DTCTL(timer_periph) &= (~(uint32_t)GPTIMER_DTCTL_FEDTCFG);
        GPTIMER_DTCTL(timer_periph) |= (uint32_t)((comocpara->falling_deadtime_value << 16) & GPTIMER_DTCTL_FEDTCFG);

        GPTIMER_DTCTL(timer_periph) &= (~(uint32_t)GPTIMER_DTCTL_REDTSEN);
        GPTIMER_DTCTL(timer_periph) |= (uint32_t)(comocpara->rising_deadtime_shadow & GPTIMER_DTCTL_REDTSEN);

        GPTIMER_DTCTL(timer_periph) &= (~(uint32_t)GPTIMER_DTCTL_FEDTSEN);
        GPTIMER_DTCTL(timer_periph) |= (uint32_t)(comocpara->falling_deadtime_shadow & GPTIMER_DTCTL_FEDTSEN);
    }
}

/*!
    \brief      configure channel input or output (API_ID(0x0041U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  io_direction:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CHANNEL_OUTPUT: channel output
      \arg        GPTIMER_CHANNEL_INPUT: channel input
    \param[out] none
    \retval     none
*/
void gptimer_channel_io_direction_config(uint32_t timer_periph, uint16_t channel, uint32_t io_direction)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH0SEL);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)(io_direction & GPTIMER_CHCTL_CH0SEL);
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH1SEL);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)((io_direction << 8) & GPTIMER_CHCTL_CH1SEL);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure channel input or output enable state (API_ID(0x0042U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  state:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CHANNEL_ENABLE: channel enable
      \arg        GPTIMER_CHANNEL_DISABLE: channel disable
    \param[out] none
    \retval     none
*/
void gptimer_channel_io_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH0EN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)((state) & GPTIMER_CHCTL_CH0EN);
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CHCTL(timer_periph) &= (~(uint32_t)GPTIMER_CHCTL_CH1EN);
        GPTIMER_CHCTL(timer_periph) |= (uint32_t)((uint32_t)(state << 8U) & GPTIMER_CHCTL_CH1EN);
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize GPTIMER counter capture source init parameter struct with a default value (API_ID(0x0043U))
    \param[in]  counter_capture_source_para: counter capture source init parameter struct
    \param[out] none
    \retval     none
*/
void gptimer_capture_source_struct_para_init(gptimer_capture_source_parameter_struct *counter_capture_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(counter_capture_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0043U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        counter_capture_source_para->capture_source_eti0 = GPTIMER_ETI0_TRG_DISABLE;
        counter_capture_source_para->capture_source_eti1 = GPTIMER_ETI1_TRG_DISABLE;
        counter_capture_source_para->capture_source_eti2 = GPTIMER_ETI2_TRG_DISABLE;
        counter_capture_source_para->capture_source_eti3 = GPTIMER_ETI3_TRG_DISABLE;
        counter_capture_source_para->capture_source_ch0 = GPTIMER_CH0_TRG_DISABLE;
        counter_capture_source_para->capture_source_ch1 = GPTIMER_CH1_TRG_DISABLE;
        counter_capture_source_para->capture_source_evsel0 = GPTIMER_EVSEL0_TRG_DISABLE;
        counter_capture_source_para->capture_source_evsel1 = GPTIMER_EVSEL1_TRG_DISABLE;
        counter_capture_source_para->capture_source_evsel2 = GPTIMER_EVSEL2_TRG_DISABLE;
        counter_capture_source_para->capture_source_evsel3 = GPTIMER_EVSEL3_TRG_DISABLE;
        counter_capture_source_para->capture_source_evsel4 = GPTIMER_EVSEL4_TRG_DISABLE;
        counter_capture_source_para->capture_source_evsel5 = GPTIMER_EVSEL5_TRG_DISABLE;
        counter_capture_source_para->capture_source_evsel6 = GPTIMER_EVSEL6_TRG_DISABLE;
        counter_capture_source_para->capture_source_evsel7 = GPTIMER_EVSEL7_TRG_DISABLE;
    }
}

/*!
    \brief      initialize GPTIMER counter capture source (API_ID(0x0044U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  capture_source_para: counter capture source init parameter struct
                  capture_source_eti0: GPTIMER_ETI0_TRG_DISABLE, GPTIMER_ETI0_TRG_EDGE_RISING, GPTIMER_ETI0_TRG_EDGE_FALLING, GPTIMER_ETI0_TRG_EDGE_BOTH
                  capture_source_eti1: GPTIMER_ETI1_TRG_DISABLE, GPTIMER_ETI1_TRG_EDGE_RISING, GPTIMER_ETI1_TRG_EDGE_FALLING, GPTIMER_ETI1_TRG_EDGE_BOTH
                  capture_source_eti2: GPTIMER_ETI2_TRG_DISABLE, GPTIMER_ETI2_TRG_EDGE_RISING, GPTIMER_ETI2_TRG_EDGE_FALLING, GPTIMER_ETI2_TRG_EDGE_BOTH
                  capture_source_eti3: GPTIMER_ETI3_TRG_DISABLE, GPTIMER_ETI3_TRG_EDGE_RISING, GPTIMER_ETI3_TRG_EDGE_FALLING, GPTIMER_ETI3_TRG_EDGE_BOTH
                  capture_source_ch0: GPTIMER_CH0_TRG_DISABLE, GPTIMER_CH0_TRG_EDGE_RISING, GPTIMER_CH0_TRG_EDGE_FALLING, GPTIMER_CH0_TRG_EDGE_BOTH
                  capture_source_ch1: GPTIMER_CH1_TRG_DISABLE, GPTIMER_CH1_TRG_EDGE_RISING, GPTIMER_CH1_TRG_EDGE_FALLING, GPTIMER_CH1_TRG_EDGE_BOTH
                  capture_source_evsel0: GPTIMER_EVSEL0_TRG_DISABLE, GPTIMER_EVSEL0_TRG_ENABLE
                  capture_source_evsel1: GPTIMER_EVSEL1_TRG_DISABLE, GPTIMER_EVSEL1_TRG_ENABLE
                  capture_source_evsel2: GPTIMER_EVSEL2_TRG_DISABLE, GPTIMER_EVSEL2_TRG_ENABLE
                  capture_source_evsel3: GPTIMER_EVSEL3_TRG_DISABLE, GPTIMER_EVSEL3_TRG_ENABLE
                  capture_source_evsel4: GPTIMER_EVSEL4_TRG_DISABLE, GPTIMER_EVSEL4_TRG_ENABLE
                  capture_source_evsel5: GPTIMER_EVSEL5_TRG_DISABLE, GPTIMER_EVSEL5_TRG_ENABLE
                  capture_source_evsel6: GPTIMER_EVSEL6_TRG_DISABLE, GPTIMER_EVSEL6_TRG_ENABLE
                  capture_source_evsel7: GPTIMER_EVSEL7_TRG_DISABLE, GPTIMER_EVSEL7_TRG_ENABLE
    \param[out] none
    \retval     none
*/
void gptimer_capture_source_config(uint32_t timer_periph, uint16_t channel,
                                   gptimer_capture_source_parameter_struct *capture_source_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(capture_source_para)) {
        fw_debug_report_err(GPTIMER_MODULE_ID, API_ID(0x0044U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(channel == GPTIMER_CH0) {
            GPTIMER_CH0CSSEL(timer_periph) = (uint32_t)((uint32_t)(capture_source_para->capture_source_eti0 & GPTIMER_CH0CSSEL_ETI0CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_eti1 & GPTIMER_CH0CSSEL_ETI1CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_eti2 & GPTIMER_CH0CSSEL_ETI2CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_eti3 & GPTIMER_CH0CSSEL_ETI3CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_ch0 & GPTIMER_CH0CSSEL_CH0CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_ch1 & GPTIMER_CH0CSSEL_CH1CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel0 & GPTIMER_CH0CSSEL_EVSEL0CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel1 & GPTIMER_CH0CSSEL_EVSEL1CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel2 & GPTIMER_CH0CSSEL_EVSEL2CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel3 & GPTIMER_CH0CSSEL_EVSEL3CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel4 & GPTIMER_CH0CSSEL_EVSEL4CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel5 & GPTIMER_CH0CSSEL_EVSEL5CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel6 & GPTIMER_CH0CSSEL_EVSEL6CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel7 & GPTIMER_CH0CSSEL_EVSEL7CH0IC));
        } else if(channel == GPTIMER_CH1) {
            GPTIMER_CH1CSSEL(timer_periph) = (uint32_t)((uint32_t)(capture_source_para->capture_source_eti0 & GPTIMER_CH1CSSEL_ETI0CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_eti1 & GPTIMER_CH1CSSEL_ETI1CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_eti2 & GPTIMER_CH1CSSEL_ETI2CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_eti3 & GPTIMER_CH1CSSEL_ETI3CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_ch0 & GPTIMER_CH1CSSEL_CH0CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_ch1 & GPTIMER_CH1CSSEL_CH1CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel0 & GPTIMER_CH1CSSEL_EVSEL0CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel1 & GPTIMER_CH1CSSEL_EVSEL1CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel2 & GPTIMER_CH1CSSEL_EVSEL2CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel3 & GPTIMER_CH1CSSEL_EVSEL3CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel4 & GPTIMER_CH1CSSEL_EVSEL4CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel5 & GPTIMER_CH1CSSEL_EVSEL5CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel6 & GPTIMER_CH1CSSEL_EVSEL6CH0IC) |
                                                        (uint32_t)(capture_source_para->capture_source_evsel7 & GPTIMER_CH1CSSEL_EVSEL7CH0IC));
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      configure channel input capture filter (API_ID(0x0045U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  number: 0~15
    \param[out] none
    \retval     none
*/
void gptimer_channel_input_capture_filter_config(uint32_t timer_periph, uint32_t channel, uint32_t number)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CH0CTL(timer_periph) &= ~(uint32_t)GPTIMER_CH0CTL_CH0CAPFLT;
        GPTIMER_CH0CTL(timer_periph) |= (uint32_t)((number << 28) & GPTIMER_CH0CTL_CH0CAPFLT);
        break;
    case GPTIMER_CH1:
        /* configure GPTIMER_CH1 */
        GPTIMER_CH1CTL(timer_periph) &= ~(uint32_t)GPTIMER_CH1CTL_CH1CAPFLT;
        GPTIMER_CH1CTL(timer_periph) |= (uint32_t)((number << 28) & GPTIMER_CH1CTL_CH1CAPFLT);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure channel input capture prescaler (API_ID(0x0046U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[in]  prescaler: GPTIMER_IC_PSC_DIV1, GPTIMER_IC_PSC_DIV2, GPTIMER_IC_PSC_DIV4, GPTIMER_IC_PSC_DIV8
    \param[out] none
    \retval     none
*/
void gptimer_channel_input_capture_prescaler_config(uint32_t timer_periph, uint16_t channel, uint32_t prescaler)
{
    switch(channel) {
    /* configure GPTIMER_CH0 */
    case GPTIMER_CH0:
        GPTIMER_CH0CTL(timer_periph) &= (~(uint32_t)GPTIMER_CH0CTL_CH0CAPPSC);
        GPTIMER_CH0CTL(timer_periph) |= (uint32_t)(prescaler & GPTIMER_CH0CTL_CH0CAPPSC);
        break;
    /* configure GPTIMER_CH1 */
    case GPTIMER_CH1:
        GPTIMER_CH1CTL(timer_periph) &= (~(uint32_t)GPTIMER_CH1CTL_CH1CAPPSC);
        GPTIMER_CH1CTL(timer_periph) |= (uint32_t)(prescaler & GPTIMER_CH1CTL_CH1CAPPSC);
        break;
    default:
        break;
    }
}

/*!
    \brief      read channel capture compare register value (API_ID(0x0047U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  channel: GPTIMER channel
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CH0: channel 0
      \arg        GPTIMER_CH1: channel 1
    \param[out] none
    \retval     count value
*/
uint32_t gptimer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel)
{
    uint32_t count_value = 0U;
    switch(channel) {
    case GPTIMER_CH0:
        /* read GPTIMER_CH0 capture compare register value */
        count_value = GPTIMER_CH0CV(timer_periph);
        break;
    case GPTIMER_CH1:
        /* read GPTIMER_CH1 capture compare register value */
        count_value = GPTIMER_CH1CV(timer_periph);
        break;
    default:
        break;
    }
    return (count_value);
}

/*!
    \brief      select synchronization control set (API_ID(0x0048U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  set:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_SYNRSTCTL_SYNCSSEL_SET0: synchronization control set0
      \arg        GPTIMER_SYNRSTCTL_SYNCSSEL_SET1: synchronization control set1
    \param[out] none
    \retval     none
*/
void gptimer_counter_sync_control_select(uint32_t timer_periph, uint32_t set)
{
    GPTIMER_SYNRSTCTL(timer_periph) &= ~(uint32_t)GPTIMER_SYNRSTCTL_SYNCSSEL;
    GPTIMER_SYNRSTCTL(timer_periph) |= (uint32_t)(set & GPTIMER_SYNRSTCTL_SYNCSSEL);
}

/*!
    \brief      select counter sync reset source (API_ID(0x0049U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  source:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER_SYNC_RESET_CH0CV: ch0cv as counter sync reset source
      \arg        GPTIMER_SYNC_RESET_CH1CV: ch1cv as counter sync reset source
      \arg        GPTIMER_SYNC_RESET_CH0COMV_ADD: ch0comval_add as counter sync reset source
      \arg        GPTIMER_SYNC_RESET_CH1COMV_ADD: ch1comval_add as counter sync reset source
      \arg        GPTIMER_SYNC_RESET_OF: overflow as counter sync reset source
      \arg        GPTIMER_SYNC_RESET_UF: underflow as counter sync reset source
      \arg        GPTIMER_SYNC_RESET_CH: channel input as counter sync reset source
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void gptimer_counter_sync_reset_source_select(uint32_t timer_periph, uint32_t source, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        GPTIMER_SYNRSTCTL(timer_periph) |= (uint32_t)(source & COUNTER_SYNC_RESET_SOURCE_MASK);
    } else {
        GPTIMER_SYNRSTCTL(timer_periph) &= (~(uint32_t)(source & COUNTER_SYNC_RESET_SOURCE_MASK));
    }
}

/*!
    \brief  enable compare event produce a ADC converter trigger signal (API_ID(0x004AU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  compare_time:
                one or more parameter can be selected which is shown as below:
       \arg       GPTIMER_ADT1UEN: enable counter up ADTCV1[15:0] match event as adc trigger signal
       \arg       GPTIMER_ADT1DEN: enable counter down ADTCV1[15:0] match event as adc trigger signal
       \arg       GPTIMER_ADT2UEN: enable counter up ADTCV2[15:0] match event as adc trigger signal
       \arg       GPTIMER_ADT2DEN: enable counter down ADTCV2[15:0] match event as adc trigger signal
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_compare_enable(uint32_t timer_periph, uint32_t compare_time)
{
    GPTIMER_ADCTL(timer_periph) |= (uint32_t)(compare_time & COMPARISON_GENERATE_TRIGGER_MASK);
}

/*!
    \brief  disable compare event produce a ADC converter trigger signal (API_ID(0x004BU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  compare_time:
                one or more parameter can be selected which is shown as below:
       \arg       GPTIMER_ADT1UEN: enable counter up ADTCV1[15:0] match event as adc trigger signal
       \arg       GPTIMER_ADT1DEN: enable counter down ADTCV1[15:0] match event as adc trigger signal
       \arg       GPTIMER_ADT2UEN: enable counter up ADTCV2[15:0] match event as adc trigger signal
       \arg       GPTIMER_ADT2DEN: enable counter down ADTCV2[15:0] match event as adc trigger signal
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_compare_disable(uint32_t timer_periph, uint32_t compare_time)
{
    GPTIMER_ADCTL(timer_periph) &= (~(uint32_t)(compare_time & COMPARISON_GENERATE_TRIGGER_MASK));
}

/*!
    \brief  config trigger adc compare register value (API_ID(0x004CU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  compare:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADC_COMPARE1: select GPTIMERx_ADCCR1 ADTCV1
       \arg       GPTIMER_ADC_COMPARE2: select GPTIMERx_ADCCR2 ADTCV2
    \param[in]  value: 0~65535
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_compare_value_config(uint32_t timer_periph, uint32_t compare,  uint16_t value)
{
    switch(compare) {
    case GPTIMER_ADC_COMPARE1:
        GPTIMER_ADCCR1(timer_periph) = value;
        break;
    case GPTIMER_ADC_COMPARE2:
        GPTIMER_ADCCR2(timer_periph) = value;
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief  enable adc compare register shadow function (API_ID(0x004DU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  compare:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADC_COMPARE1: select GPTIMERx_ADCCR1 ADTCV1
       \arg       GPTIMER_ADC_COMPARE2: select GPTIMERx_ADCCR2 ADTCV2
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_compare_shadow_enable(uint32_t timer_periph, uint32_t compare)
{
    switch(compare) {
    case GPTIMER_ADC_COMPARE1:
        GPTIMER_ADCTL(timer_periph) |= (uint32_t)GPTIMER_ADCTL_ADTCV1SEN;
        break;
    case GPTIMER_ADC_COMPARE2:
        GPTIMER_ADCTL(timer_periph) |= (uint32_t)GPTIMER_ADCTL_ADTCV2SEN;
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief  disable adc compare register shadow function (API_ID(0x004EU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  compare:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADC_COMPARE1: select GPTIMERx_ADCCR1 ADTCV1
       \arg       GPTIMER_ADC_COMPARE2: select GPTIMERx_ADCCR2 ADTCV2
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_compare_shadow_disable(uint32_t timer_periph, uint32_t compare)
{
    switch(compare) {
    case GPTIMER_ADC_COMPARE1:
        GPTIMER_ADCTL(timer_periph) &= ~(uint32_t)GPTIMER_ADCTL_ADTCV1SEN;
        break;
    case GPTIMER_ADC_COMPARE2:
        GPTIMER_ADCTL(timer_periph) &= ~(uint32_t)GPTIMER_ADCTL_ADTCV2SEN;
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief  enable trigger adc adsm signal (API_ID(0x004FU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  adsm:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADCSM3: adc monitor signal 3
       \arg       GPTIMER_ADCSM4: adc monitor signal 4
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_adsm_enable(uint32_t timer_periph, uint32_t adsm)
{
    if(adsm == GPTIMER_ADCSM3) {
        GPTIMER_ADCTL(timer_periph) |= (uint32_t)GPTIMER_ADCTL_ADCMS3EN;
    } else if(adsm == GPTIMER_ADCSM4) {
        GPTIMER_ADCTL(timer_periph) |= (uint32_t)GPTIMER_ADCTL_ADCMS4EN;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief  disable trigger adc adsm signal (API_ID(0x0050U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  adsm:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADCSM3: adc monitor signal 3
       \arg       GPTIMER_ADCSM4: adc monitor signal 4
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_adsm_disable(uint32_t timer_periph, uint32_t adsm)
{
    if(adsm == GPTIMER_ADCSM3) {
        GPTIMER_ADCTL(timer_periph) &= ~(uint32_t)GPTIMER_ADCTL_ADCMS3EN;
    } else if(adsm == GPTIMER_ADCSM4) {
        GPTIMER_ADCTL(timer_periph) &= ~(uint32_t)GPTIMER_ADCTL_ADCMS4EN;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief  select trigger adc adsm signal (API_ID(0x0051U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  adsm:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADCSM3: adc monitor signal 3
       \arg       GPTIMER_ADCSM4: adc monitor signal 4
    \param[in]  trg_source:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADSM_ADTCV1: adc monitor signal ADTCV1
       \arg       GPTIMER_ADSM_ADTCV2: adc monitor signal ADTCV2
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_adsm_select(uint32_t timer_periph, uint32_t adsm, uint32_t trg_source)
{
    switch(adsm) {
    case GPTIMER_ADCSM3:
        GPTIMER_ADCTL(timer_periph) &= ~(uint32_t)GPTIMER_ADCTL_ADCMS3SEL;
        if(trg_source == GPTIMER_ADSM_ADTCV2) {
            GPTIMER_ADCTL(timer_periph) |= (uint32_t)GPTIMER_ADCTL_ADCMS3SEL;
        }
        break;
    case GPTIMER_ADCSM4:
        GPTIMER_ADCTL(timer_periph) &= ~(uint32_t)GPTIMER_ADCTL_ADCMS4SEL;
        if(trg_source == GPTIMER_ADSM_ADTCV2) {
            GPTIMER_ADCTL(timer_periph) |= (uint32_t)GPTIMER_ADCTL_ADCMS4SEL;
        }
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief  config trigger adc skipping value (API_ID(0x0052U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  skipping_count:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADC_SKIP_COUNT1: adc skipping counter 1
       \arg       GPTIMER_ADC_SKIP_COUNT2: adc skipping counter 2
    \param[in]  value: skipping value, 0~15
    \param[in]  initial_value: initial value, 0~15
    \param[in]  skipping_source:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADC_SKIP_NO: no counting, no skipping
       \arg       GPTIMER_ADC_SKIP_ADTCV1: the ADTCV1[15:0] comparison matching
       \arg       GPTIMER_ADC_SKIP_ADTCV2: the ADTCV2[15:0] comparison matching
       \arg       GPTIMER_ADC_SKIP_ADTCV1_OR_ADTCV2: the ADTCV1[15:0] or ADTCV2[15:0] comparison matching
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_skipping_config(uint32_t timer_periph, uint32_t skipping_count, uint32_t value, uint32_t initial_value,
                                         uint32_t skipping_source)
{
    switch(skipping_count) {
    case GPTIMER_ADC_SKIP_COUNT1:
        GPTIMER_ADCTRGS(timer_periph) &= ~(uint32_t)(GPTIMER_ADCTRGS_ADCC1SVAL | GPTIMER_ADCTRGS_ADCC1IVAL |
                                                     GPTIMER_ADCTRGS_ADCC1SKSEL);
        GPTIMER_ADCTRGS(timer_periph) |= (uint32_t)(((value & TRIGGER_ADC_SKIPPING_VALUE_MASK) << 4) |
                                                    ((initial_value & TRIGGER_ADC_SKIPPING_VALUE_MASK) << 8) | (skipping_source & GPTIMER_ADCTRGS_ADCC1SKSEL));
        break;
    case GPTIMER_ADC_SKIP_COUNT2:
        GPTIMER_ADCTRGS(timer_periph) &= ~(uint32_t)(GPTIMER_ADCTRGS_ADCC2SVAL | GPTIMER_ADCTRGS_ADCC2IVAL |
                                                     GPTIMER_ADCTRGS_ADCC2SKSEL);
        GPTIMER_ADCTRGS(timer_periph) |= (uint32_t)(((value & TRIGGER_ADC_SKIPPING_VALUE_MASK) << 20) |
                                                    ((initial_value & TRIGGER_ADC_SKIPPING_VALUE_MASK) << 24) | ((skipping_source << 16) & GPTIMER_ADCTRGS_ADCC2SKSEL));
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief  select trigger adc skipping function (API_ID(0x0053U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  compare:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADC_COMPARE1: select GPTIMERx_ADCCR1 ADTCV1
       \arg       GPTIMER_ADC_COMPARE2: select GPTIMERx_ADCCR2 ADTCV2
    \param[in]  skipping_time:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADC_REQ_NO: do not skipping
       \arg       GPTIMER_ADC_REQ_CNT1_ZERO: adc req source when skipping counter 1 equal 0
       \arg       GPTIMER_ADC_REQ_CNT2_ZERO: adc req source when skipping counter 2 equal 0
       \arg       GPTIMER_ADC_REQ_CNT1_OR_CNT2_ZERO: adc req source when skipping counter 1/2 equal 0
       \arg       GPTIMER_ADC_REQ_CNT1_SVAL: adc req source when skipping counter 1 equal skipping value
       \arg       GPTIMER_ADC_REQ_CNT2_SVAL: adc req source when skipping counter 2 equal skipping value
       \arg       GPTIMER_ADC_REQ_CNT1_OR_CNT2_SVAL: adc req source when skipping counter 1/2 equal skipping value
    \param[out] none
    \retval     none
*/
void gptimer_trigger_adc_skipping_time_select(uint32_t timer_periph, uint32_t compare,  uint32_t skipping_time)
{
    switch(compare) {
    case GPTIMER_ADC_COMPARE1:
        GPTIMER_ADCTL(timer_periph) &= ~(uint32_t)GPTIMER_ADCTL_ADTCV1SSEL;
        GPTIMER_ADCTL(timer_periph) |= (uint32_t)(skipping_time & GPTIMER_ADCTL_ADTCV1SSEL);
        break;
    case GPTIMER_ADC_COMPARE2:
        GPTIMER_ADCTL(timer_periph) &= ~(uint32_t)GPTIMER_ADCTL_ADTCV2SSEL;
        GPTIMER_ADCTL(timer_periph) |= (uint32_t)((skipping_time << 4) & GPTIMER_ADCTL_ADTCV2SSEL);
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief  read trigger adc skipping counter (API_ID(0x0054U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  skipping_count:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADC_SKIP_COUNT1: adc skipping counter 1
       \arg       GPTIMER_ADC_SKIP_COUNT2: adc skipping counter 2
    \param[out] none
    \retval     skipping counter
*/
uint16_t gptimer_trigger_adc_skipping_counter_read(uint32_t timer_periph, uint32_t skipping_count)
{
    uint16_t skipping_counter;
    switch(skipping_count) {
    case GPTIMER_ADC_SKIP_COUNT1:
        skipping_counter = (uint16_t)(((GPTIMER_ADCTRGS(timer_periph))&GPTIMER_ADCTRGS_ADCC1VAL) >> 12);
        break;
    case GPTIMER_ADC_SKIP_COUNT2:
        skipping_counter = (uint16_t)(((GPTIMER_ADCTRGS(timer_periph))&GPTIMER_ADCTRGS_ADCC2VAL) >> 28);
        break;
    default:
        /*illegal  parameter */
        break;
    }
    return skipping_counter;
}

/*!
    \brief  config additional interrupt skipping initial value (API_ID(0x0055U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  skipping_count:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADDINT_SKIP_COUNT1: additional interrupt skipping counter 1
       \arg       GPTIMER_ADDINT_SKIP_COUNT2: additional interrupt skipping counter 2
    \param[in]  value: skipping value, 0~15
    \param[in]  initial_value: initial value, 0~15
    \param[in]  skipping_source:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADDINT_SKIP_NO: no additional interrupt skipping counter source
       \arg       GPTIMER_ADDINT_SKIP_OVERFLOW: overflow as additional skipping counter source
       \arg       GPTIMER_ADDINT_SKIP_UNDERFLOW: underflow as additional skipping counter source
       \arg       GPTIMER_ADDINT_SKIP_FLOW: overflow and underflow as additional skipping counter source
    \param[out] none
    \retval     none
*/
void gptimer_additional_interrupt_skipping_config(uint32_t timer_periph, uint32_t skipping_count, uint32_t value,
                                                  uint32_t initial_value, uint32_t skipping_source)
{
    switch(skipping_count) {
    case GPTIMER_ADDINT_SKIP_COUNT1:
        GPTIMER_ADDINTSCTL0(timer_periph) &= ~(uint32_t)(GPTIMER_ADDINTSCTL0_ADDC1SVAL | GPTIMER_ADDINTSCTL0_ADDC1IVAL |
                                                         GPTIMER_ADDINTSCTL0_ADDC1SKSEL);
        GPTIMER_ADDINTSCTL0(timer_periph) |= (uint32_t)(((initial_value & TRIGGER_ADD_SKIPPING_VALUE_MASK) << 8) |
                                                        ((value & TRIGGER_ADD_SKIPPING_VALUE_MASK) << 4) | (skipping_source & GPTIMER_ADDINTSCTL0_ADDC1SKSEL));
        break;
    case GPTIMER_ADDINT_SKIP_COUNT2:
        GPTIMER_ADDINTSCTL0(timer_periph) &= ~(uint32_t)(GPTIMER_ADDINTSCTL0_ADDC2SVAL | GPTIMER_ADDINTSCTL0_ADDC2IVAL |
                                                         GPTIMER_ADDINTSCTL0_ADDC2SKSEL);
        GPTIMER_ADDINTSCTL0(timer_periph) |= (uint32_t)(((initial_value & TRIGGER_ADD_SKIPPING_VALUE_MASK) << 24) |
                                                        ((value & TRIGGER_ADD_SKIPPING_VALUE_MASK) << 20) | ((skipping_source << 16) & GPTIMER_ADDINTSCTL0_ADDC2SKSEL));
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief  select additional interrupt skipping function (API_ID(0x0056U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  event:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADDINT_SKIP_EVENT_CH0CV: additional interrupt skipping event ch0cv
       \arg       GPTIMER_ADDINT_SKIP_EVENT_CH1CV: additional interrupt skipping event ch1cv
       \arg       GPTIMER_ADDINT_SKIP_EVENT_CH0COMV_ADD: additional interrupt skipping event ch0comv_add
       \arg       GPTIMER_ADDINT_SKIP_EVENT_CH1COMV_ADD: additional interrupt skipping event ch1comv_add
       \arg       GPTIMER_ADDINT_SKIP_EVENT_UNDERFLOW: additional interrupt skipping event underflow
       \arg       GPTIMER_ADDINT_SKIP_EVENT_OVERFLOW: additional interrupt skipping event overflow
       \arg       GPTIMER_ADDINT_SKIP_EVENT_ADTCV1: additional interrupt skipping event adtcv1
       \arg       GPTIMER_ADDINT_SKIP_EVENT_ADTCV2: additional interrupt skipping event adtcv2
    \param[in]  skipping_time:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADDINT_REQ_NO: do not skipping
       \arg       GPTIMER_ADDINT_REQ_CNT1_ZERO: additional interrupt req source when skipping counter 1 equal 0
       \arg       GPTIMER_ADDINT_REQ_CNT2_ZERO: additional interrupt req source when skipping counter 2 equal 0
       \arg       GPTIMER_ADDINT_REQ_CNT1_OR_CNT2_ZERO: additional interrupt req source when skipping counter 1/2 equal 0
       \arg       GPTIMER_ADDINT_REQ_CNT1_SVAL: additional interrupt req source when skipping counter 1 equal skipping value
       \arg       GPTIMER_ADDINT_REQ_CNT2_SVAL: additional interrupt req source when skipping counter 2 equal skipping value
       \arg       GPTIMER_ADDINT_REQ_CNT1_OR_CNT2_SVAL: additional interrupt req source when skipping counter 1/2 equal skipping value
    \param[out] none
    \retval     none
*/
void gptimer_additional_interrupt_skipping_time_select(uint32_t timer_periph, uint32_t event,  uint32_t skipping_time)
{
    switch(event) {
    case GPTIMER_ADDINT_SKIP_EVENT_CH0CV:
        GPTIMER_ADDINTSCTL1(timer_periph) &= ~(uint32_t)GPTIMER_ADDINTSCTL1_CH0AISSEL;
        GPTIMER_ADDINTSCTL1(timer_periph) |= (uint32_t)(skipping_time & SKIPPING_TIME_MASK);
        break;
    case GPTIMER_ADDINT_SKIP_EVENT_CH1CV:
        GPTIMER_ADDINTSCTL1(timer_periph) &= ~(uint32_t)GPTIMER_ADDINTSCTL1_CH1AISSEL;
        GPTIMER_ADDINTSCTL1(timer_periph) |= (uint32_t)((skipping_time & SKIPPING_TIME_MASK) << 4);
        break;
    case GPTIMER_ADDINT_SKIP_EVENT_CH0COMV_ADD:
        GPTIMER_ADDINTSCTL1(timer_periph) &= ~(uint32_t)GPTIMER_ADDINTSCTL1_CH0ADDAISSEL;
        GPTIMER_ADDINTSCTL1(timer_periph) |= (uint32_t)((skipping_time & SKIPPING_TIME_MASK) << 8);
        break;
    case GPTIMER_ADDINT_SKIP_EVENT_CH1COMV_ADD:
        GPTIMER_ADDINTSCTL1(timer_periph) &= ~(uint32_t)GPTIMER_ADDINTSCTL1_CH1ADDAISSEL;
        GPTIMER_ADDINTSCTL1(timer_periph) |= (uint32_t)((skipping_time & SKIPPING_TIME_MASK) << 12);
        break;
    case GPTIMER_ADDINT_SKIP_EVENT_UNDERFLOW:
        GPTIMER_ADDINTSCTL1(timer_periph) &= ~(uint32_t)GPTIMER_ADDINTSCTL1_UFAISSEL;
        GPTIMER_ADDINTSCTL1(timer_periph) |= (uint32_t)((skipping_time & SKIPPING_TIME_MASK) << 16);
        break;
    case GPTIMER_ADDINT_SKIP_EVENT_OVERFLOW:
        GPTIMER_ADDINTSCTL1(timer_periph) &= ~(uint32_t)GPTIMER_ADDINTSCTL1_OFAISSEL;
        GPTIMER_ADDINTSCTL1(timer_periph) |= (uint32_t)((skipping_time & SKIPPING_TIME_MASK) << 20);
        break;
    case GPTIMER_ADDINT_SKIP_EVENT_ADTCV1:
        GPTIMER_ADDINTSCTL1(timer_periph) &= ~(uint32_t)GPTIMER_ADDINTSCTL1_ADT1AISSEL;
        GPTIMER_ADDINTSCTL1(timer_periph) |= (uint32_t)((skipping_time & SKIPPING_TIME_MASK) << 24);
        break;
    case GPTIMER_ADDINT_SKIP_EVENT_ADTCV2:
        GPTIMER_ADDINTSCTL1(timer_periph) &= ~(uint32_t)GPTIMER_ADDINTSCTL1_ADT2AISSEL;
        GPTIMER_ADDINTSCTL1(timer_periph) |= (uint32_t)((skipping_time & SKIPPING_TIME_MASK) << 28);
        break;
    default:
        /*illegal  parameter */
        break;
    }
}

/*!
    \brief  read additional interrupt skipping counter (API_ID(0x0057U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  skipping_count:
                only one parameter can be selected which is shown as below:
       \arg       GPTIMER_ADDINT_SKIP_COUNT1: additional interrupt skipping counter 1
       \arg       GPTIMER_ADDINT_SKIP_COUNT2: additional interrupt skipping counter 2
    \param[out] none
    \retval     skipping counter
*/
uint16_t gptimer_additional_interrupt_skipping_counter_read(uint32_t timer_periph, uint32_t skipping_count)
{
    uint16_t skipping_counter;
    switch(skipping_count) {
    case GPTIMER_ADDINT_SKIP_COUNT1:
        skipping_counter = (uint16_t)(((GPTIMER_ADDINTSCTL0(timer_periph))&GPTIMER_ADDINTSCTL0_ADDC1VAL) >> 12);
        break;
    case GPTIMER_ADDINT_SKIP_COUNT2:
        skipping_counter = (uint16_t)(((GPTIMER_ADDINTSCTL0(timer_periph))&GPTIMER_ADDINTSCTL0_ADDC2VAL) >> 28);
        break;
    default:
        /*illegal  parameter */
        break;
    }
    return skipping_counter;
}

/*!
    \brief      select flow interrupt skipping source (API_ID(0x0058U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  skipping_source:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_FLOW_SKIP_SOURCE_NO: no flow skipping
      \arg        GPTIMER_FLOW_SKIP_SOURCE_OVERFLOW: overflow as flow skipping source
      \arg        GPTIMER_FLOW_SKIP_SOURCE_UNDERFLOW: underflow as flow skipping source
      \arg        GPTIMER_FLOW_SKIP_SOURCE_FLOW: overflow / underflow as flow skipping source
    \param[out] none
    \retval     none
*/
void gptimer_flow_interrupt_skipping_source_select(uint32_t timer_periph, uint32_t skipping_source)
{
    GPTIMER_IADCTSS(timer_periph) &= ~(uint32_t)(GPTIMER_IADCTSS_OUFINTSSEL);
    GPTIMER_IADCTSS(timer_periph) |= (uint32_t)(skipping_source & GPTIMER_IADCTSS_OUFINTSSEL);
}

/*!
    \brief      enable flow interrupt skipping link function (API_ID(0x0059U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  skipping_link_source:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER_SKIP_LINK_CH0CV: interrupt skipping link channel 0 input capture/compare match
      \arg        GPTIMER_SKIP_LINK_CH1CV: interrupt skipping link channel 1 input capture/compare match
      \arg        GPTIMER_SKIP_LINK_CH0COMV_ADD: interrupt skipping link channel 0 additional value compare match
      \arg        GPTIMER_SKIP_LINK_CH1COMV_ADD: interrupt skipping link channel 1 additional value compare match
      \arg        GPTIMER_SKIP_LINK_ADCCR1: interrupt skipping link trigger signal generated by ADTCV1[15:0]
      \arg        GPTIMER_SKIP_LINK_ADCCR2: interrupt skipping link trigger signal generated by ADTCV2[15:0]
    \param[out] none
    \retval     none
*/
void gptimer_flow_interrupt_skipping_link_enable(uint32_t timer_periph, uint32_t skipping_link_source)
{
    GPTIMER_IADCTSS(timer_periph) |= (uint32_t)(skipping_link_source & FLOW_SKIPPING_LINK_MASK);
}

/*!
    \brief      disable flow interrupt skipping link function (API_ID(0x005AU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  skipping_link_source:
                one or more parameter can be selected which is shown as below:
      \arg        GPTIMER_SKIP_LINK_CH0CV: interrupt skipping link channel 0 input capture/compare match
      \arg        GPTIMER_SKIP_LINK_CH1CV: interrupt skipping link channel 1 input capture/compare match
      \arg        GPTIMER_SKIP_LINK_CH0COMV_ADD: interrupt skipping link channel 0 additional value compare match
      \arg        GPTIMER_SKIP_LINK_CH1COMV_ADD: interrupt skipping link channel 1 additional value compare match
      \arg        GPTIMER_SKIP_LINK_ADCCR1: interrupt skipping link trigger signal generated by ADTCV1[15:0]
      \arg        GPTIMER_SKIP_LINK_ADCCR2: interrupt skipping link trigger signal generated by ADTCV2[15:0]
    \param[out] none
    \retval     none
*/
void gptimer_flow_interrupt_skipping_link_disable(uint32_t timer_periph, uint32_t skipping_link_source)
{
    GPTIMER_IADCTSS(timer_periph) &= ~(uint32_t)(skipping_link_source & FLOW_SKIPPING_LINK_MASK);
}

/*!
    \brief      configure flow interrupt repetition skipping number (API_ID(0x005BU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  number: the interrupt skipping value, 0~7
    \param[out] none
    \retval     none
*/
void gptimer_flow_interrupt_skipping_num_config(uint32_t timer_periph, uint32_t number)
{
    GPTIMER_IADCTSS(timer_periph) &= ~(uint32_t)(GPTIMER_IADCTSS_OUFINTSVAL);
    GPTIMER_IADCTSS(timer_periph) |= (uint32_t)((number << 8) & GPTIMER_IADCTSS_OUFINTSVAL);
}

/*!
    \brief      read flow interrupt skipping counter value (API_ID(0x005CU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[out] none
    \retval     skipping counter
*/
uint16_t gptimer_flow_interrupt_skipping_counter_read(uint32_t timer_periph)
{
    uint16_t skipping_counter = 0U;
    skipping_counter = (uint16_t)(((GPTIMER_IADCTSS(timer_periph))&GPTIMER_IADCTSS_OUFINTSC) >> 16);
    return skipping_counter;
}

/*!
    \brief      configure write CHxVAL register selection (API_ID(0x005DU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  ccsel:
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_CHVSEL_DISABLE: no effect
      \arg        GPTIMER_CHVSEL_ENABLE: when write the CHxVAL register, if the write value is same as the CHxVAL value, the write access is ignored
    \param[out] none
    \retval     none
*/
void gptimer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel)
{
    if(GPTIMER_CHVSEL_ENABLE == ccsel) {
        GPTIMER_CFG(timer_periph) |= (uint32_t)GPTIMER_CFG_CHVSEL;
    } else if(GPTIMER_CHVSEL_DISABLE == ccsel) {
        GPTIMER_CFG(timer_periph) &= ~(uint32_t)GPTIMER_CFG_CHVSEL;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      get GPTIMER flags (API_ID(0x005EU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  flag: the gptimer flags
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_FLAG_CH0: GPTIMER channel 0 capture or compare flag
      \arg        GPTIMER_FLAG_CH1: GPTIMER channel 1 capture or compare flag
      \arg        GPTIMER_FLAG_OVERFLOW: GPTIMER counter overflow flag
      \arg        GPTIMER_FLAG_UNDERFLOW: GPTIMER counter underflow flag
      \arg        GPTIMER_FLAG_CH0COMADD: GPTIMER additional channel 0 compare flag
      \arg        GPTIMER_FLAG_CH1COMADD: GPTIMER additional channel 1 compare flag
      \arg        GPTIMER_FLAG_RS: GPTIMER counter reset flag
      \arg        GPTIMER_FLAG_ADT1CMU: GPTIMER adc trigger 1 up count compare match flag
      \arg        GPTIMER_FLAG_ADT1CMD: GPTIMER adc trigger 1 down count compare match flag
      \arg        GPTIMER_FLAG_ADT2CMU: GPTIMER adc trigger 2 up count compare match flag
      \arg        GPTIMER_FLAG_ADT2CMD: GPTIMER adc trigger 2 down count compare match flag
      \arg        GPTIMER_FLAG_CHHOUT: GPTIMER output simultaneous high error flag
      \arg        GPTIMER_FLAG_CHLOUT: GPTIMER output simultaneous low error flag
      \arg        GPTIMER_FLAG_RCEND: GPTIMER repetition count end flag
      \arg        GPTIMER_FLAG_DIR: GPTIMER counter direction flag
      \arg        GPTIMER_FLAG_OST: GPTIMER output stop flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus gptimer_flag_get(uint32_t timer_periph, uint32_t flag)
{
    FlagStatus reval = RESET;
    if(RESET != (GPTIMER_INTF(timer_periph) & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear GPTIMER flags (API_ID(0x005FU))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  flag: the gptimer flags
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_FLAG_CH0: GPTIMER channel 0 capture or compare flag
      \arg        GPTIMER_FLAG_CH1: GPTIMER channel 1 capture or compare flag
      \arg        GPTIMER_FLAG_OVERFLOW: GPTIMER counter overflow flag
      \arg        GPTIMER_FLAG_UNDERFLOW: GPTIMER counter underflow flag
      \arg        GPTIMER_FLAG_CH0COMADD: GPTIMER additional channel 0 compare flag
      \arg        GPTIMER_FLAG_CH1COMADD: GPTIMER additional channel 1 compare flag
      \arg        GPTIMER_FLAG_RS: GPTIMER counter reset flag
      \arg        GPTIMER_FLAG_ADT1CMU: GPTIMER adc trigger 1 up count compare match flag
      \arg        GPTIMER_FLAG_ADT1CMD: GPTIMER adc trigger 1 down count compare match flag
      \arg        GPTIMER_FLAG_ADT2CMU: GPTIMER adc trigger 2 up count compare match flag
      \arg        GPTIMER_FLAG_ADT2CMD: GPTIMER adc trigger 2 down count compare match flag
      \arg        GPTIMER_FLAG_CHHOUT: GPTIMER output simultaneous high error flag
      \arg        GPTIMER_FLAG_CHLOUT: GPTIMER output simultaneous low error flag
      \arg        GPTIMER_FLAG_RCEND: GPTIMER repetition count end flag
      \arg        GPTIMER_FLAG_DIR: GPTIMER counter direction flag
      \arg        GPTIMER_FLAG_OST: GPTIMER output stop flag
    \param[out] none
    \retval     none
*/
void gptimer_flag_clear(uint32_t timer_periph, uint32_t flag)
{
    GPTIMER_INTF(timer_periph) = (~(uint32_t)flag);
}

/*!
    \brief      enable the GPTIMER interrupt (API_ID(0x0060U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  interrupt: gptimer interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_INT_CH0: GPTIMER channel 1 capture or compare interrupt
      \arg        GPTIMER_INT_CH1: GPTIMER channel 2 capture or compare interrupt
      \arg        GPTIMER_INT_OVERFLOW: GPTIMER counter overflow interrupt
      \arg        GPTIMER_INT_UNDERFLOW: GPTIMER counter underflow interrupt
      \arg        GPTIMER_INT_CH0COMADD: GPTIMER additional channel 1 compare interrupt
      \arg        GPTIMER_INT_CH1COMADD: GPTIMER additional channel 2 compare interrupt
      \arg        GPTIMER_INT_RS: GPTIMER counter reset interrupt
      \arg        GPTIMER_INT_CREP: GPTIMER repetition count end interrupt
    \param[out] none
    \retval     none
*/
void gptimer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt)
{
    GPTIMER_DMAINTEN(timer_periph) |= (uint32_t)(interrupt & INTERRUPT_ENABLE_MASK);
}

/*!
    \brief      disable the GPTIMER interrupt (API_ID(0x0061U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  interrupt: gptimer interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_INT_CH0: GPTIMER channel 1 capture or compare interrupt
      \arg        GPTIMER_INT_CH1: GPTIMER channel 2 capture or compare interrupt
      \arg        GPTIMER_INT_OVERFLOW: GPTIMER counter overflow interrupt
      \arg        GPTIMER_INT_UNDERFLOW: GPTIMER counter underflow interrupt
      \arg        GPTIMER_INT_CH0COMADD: GPTIMER additional channel 1 compare interrupt
      \arg        GPTIMER_INT_CH1COMADD: GPTIMER additional channel 2 compare interrupt
      \arg        GPTIMER_INT_RS: GPTIMER counter reset interrupt
      \arg        GPTIMER_INT_CREP: GPTIMER repetition count end interrupt
    \param[out] none
    \retval     none
*/
void gptimer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt)
{
    GPTIMER_DMAINTEN(timer_periph) &= (~(uint32_t)(interrupt & INTERRUPT_ENABLE_MASK));
}

/*!
    \brief      get gptimer interrupt flag (API_ID(0x0062U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  int_flag: the gptimer interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_INT_FLAG_CH0: GPTIMER channel 0 capture or compare interrupt flag
      \arg        GPTIMER_INT_FLAG_CH1: GPTIMER channel 1 capture or compare interrupt flag
      \arg        GPTIMER_INT_FLAG_OVERFLOW: GPTIMER counter overflow interrupt flag
      \arg        GPTIMER_INT_FLAG_UNDERFLOW: GPTIMER counter underflow interrupt flag
      \arg        GPTIMER_INT_FLAG_CH0COMADD: GPTIMER additional channel 0 compare interrupt flag
      \arg        GPTIMER_INT_FLAG_CH1COMADD: GPTIMER additional channel 1 compare interrupt flag
      \arg        GPTIMER_INT_FLAG_RS: GPTIMER counter reset interrupt flag
      \arg        GPTIMER_INT_FLAG_CREP: GPTIMER repetition count end interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus gptimer_interrupt_flag_get(uint32_t timer_periph, uint32_t int_flag)
{
    FlagStatus reval = RESET;
    uint32_t val;
    val = (GPTIMER_DMAINTEN(timer_periph) & int_flag);
    if((RESET != (GPTIMER_INTF(timer_periph) & int_flag)) && (RESET != val)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear gptimer interrupt flag (API_ID(0x0063U))
    \param[in]  timer_periph: GPTIMERx(x=0,1)
    \param[in]  int_flag: the gptimer interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        GPTIMER_INT_FLAG_CH0: GPTIMER channel 0 capture or compare interrupt flag
      \arg        GPTIMER_INT_FLAG_CH1: GPTIMER channel 1 capture or compare interrupt flag
      \arg        GPTIMER_INT_FLAG_OVERFLOW: GPTIMER counter overflow interrupt flag
      \arg        GPTIMER_INT_FLAG_UNDERFLOW: GPTIMER counter underflow interrupt flag
      \arg        GPTIMER_INT_FLAG_CH0COMADD: GPTIMER additional channel 0 compare interrupt flag
      \arg        GPTIMER_INT_FLAG_CH1COMADD: GPTIMER additional channel 1 compare interrupt flag
      \arg        GPTIMER_INT_FLAG_RS: GPTIMER counter reset interrupt flag
      \arg        GPTIMER_INT_FLAG_CREP: GPTIMER repetition count end interrupt flag
    \param[out] none
    \retval     none
*/
void gptimer_interrupt_flag_clear(uint32_t timer_periph, uint32_t int_flag)
{
    GPTIMER_INTF(timer_periph) = (~(uint32_t)(int_flag & INTERRUPT_FLAG_MASK));
}
