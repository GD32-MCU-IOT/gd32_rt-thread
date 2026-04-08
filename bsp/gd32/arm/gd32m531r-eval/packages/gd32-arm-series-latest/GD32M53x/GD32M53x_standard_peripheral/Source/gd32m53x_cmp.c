/*!
    \file    gd32m53x_cmp.c
    \brief   CMP driver

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


#include "gd32m53x_cmp.h"

/*!
    \brief      CMP deinit (API_ID(0x0001U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     none
*/
void cmp_deinit(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph) {
        CMP0_CS &= ((uint32_t)0x00000000U);
        CMP_IFC |= ((uint32_t)0x00010000U);
        CMP_IFC &= ((uint32_t)0xFFFEFFFFU);
    } else if(CMP1 == cmp_periph) {
        CMP1_CS &= ((uint32_t)0x00000000U);
        CMP_IFC |= ((uint32_t)0x00020000U);
        CMP_IFC &= ((uint32_t)0xFFFDFFFFU);
    } else if(CMP2 == cmp_periph) {
        CMP2_CS &= ((uint32_t)0x00000000U);
        CMP_IFC |= ((uint32_t)0x00040000U);
        CMP_IFC &= ((uint32_t)0xFFFBFFFFU);
    } else if(CMP3 == cmp_periph) {
        CMP3_CS &= ((uint32_t)0x00000000U);
        CMP_IFC |= ((uint32_t)0x00080000U);
        CMP_IFC &= ((uint32_t)0xFFF7FFFFU);
    } else {
    }

}

/*!
    \brief      CMP mode init (API_ID(0x0002U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  inverting_input
      \arg        CMP_INVERTING_INPUT_NONE: No input for CMP0 to CMP3
      \arg        CMP_INVERTING_INPUT_PC11: PC11 for CMP0 to CMP3
      \arg        CMP_INVERTING_INPUT_PC12: PC12 for CMP0 to CMP3
      \arg        CMP_INVERTING_INPUT_DAC0_OUT0: CMP inverting input DAC0_OUT0
      \arg        CMP_INVERTING_INPUT_DAC0_OUT1: CMP inverting input DAC0_OUT1
    \param[in]  output_hysteresis
      \arg        CMP_HYSTERESIS_NO: output no hysteresis
      \arg        CMP_HYSTERESIS_LOW: output low hysteresis
      \arg        CMP_HYSTERESIS_MIDDLE: output middle hysteresis
      \arg        CMP_HYSTERESIS_HIGH: output high hysteresis
    \param[out] none
    \retval     none
*/
void cmp_mode_init(cmp_enum cmp_periph, uint32_t inverting_input, uint32_t output_hysteresis)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph) {
        /* initialize comparator 0 mode */
        temp = CMP0_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXMISEL | CMP_CS_CMPXHST);
        temp |= (uint32_t)((inverting_input & CMP_CS_CMPXMISEL) | (output_hysteresis & CMP_CS_CMPXHST));
        CMP0_CS = temp;
    } else if(CMP1 == cmp_periph) {
        /* initialize comparator 1 mode */
        temp = CMP1_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXMISEL | CMP_CS_CMPXHST);
        temp |= (uint32_t)((inverting_input & CMP_CS_CMPXMISEL) | (output_hysteresis & CMP_CS_CMPXHST));
        CMP1_CS = temp;
    } else if(CMP2 == cmp_periph) {
        /* initialize comparator 2 mode */
        temp = CMP2_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXMISEL | CMP_CS_CMPXHST);
        temp |= (uint32_t)((inverting_input & CMP_CS_CMPXMISEL) | (output_hysteresis & CMP_CS_CMPXHST));
        CMP2_CS = temp;
    } else if(CMP3 == cmp_periph) {
        /* initialize comparator 3 mode */
        temp = CMP3_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXMISEL | CMP_CS_CMPXHST);
        temp |= (uint32_t)((inverting_input & CMP_CS_CMPXMISEL) | (output_hysteresis & CMP_CS_CMPXHST));
        CMP3_CS = temp;
    } else {
    }
}

/*!
    \brief      CMP noninverting input select (API_ID(0x0003U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  noninverting_input
      \arg        CMP_NONINVERTING_INPUT_NONE: No input for CMP0 to CMP3
      \arg        CMP_NONINVERTING_INPUT_PC0_PC1_PC2_PC3: PC0 for CMP0 or PC1 for CMP1 or PC2 for CMP2 or PC3 for CMP3
      \arg        CMP_NONINVERTING_INPUT_PC4_PC5_PC6_PD2: PC4 for CMP0 or PC5 for CMP1 or PC6 for CMP2 or PD2 for CMP3
      \arg        CMP_NONINVERTING_INPUT_PC10_PC11_PC12_PD4: PC10 for CMP0 or PC11 for CMP1 or PC12 for CMP2 or PD4 for CMP3
      \arg        CMP_NONINVERTING_INPUT_PC7_PC0_PC3_PD5: PC7 for CMP0 or PC0 for CMP1 or PC3 for CMP2 or PD5 for CMP3
      \arg        CMP_NONINVERTING_INPUT_PC10_PC9: reserved for CMP0 or reserved for CMP1 or PC10 for CMP2 or PC9 for CMP3
    \param[out] none
    \retval     none
*/
void cmp_noninverting_input_select(cmp_enum cmp_periph, uint32_t noninverting_input)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph) {
        temp = CMP0_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXPSEL;
        temp |= (uint32_t)(noninverting_input & CMP_CS_CMPXPSEL);
        CMP0_CS = temp;
    } else if(CMP1 == cmp_periph) {
        temp = CMP1_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXPSEL;
        temp |= (uint32_t)(noninverting_input & CMP_CS_CMPXPSEL);
        CMP1_CS = temp;
    } else if(CMP2 == cmp_periph) {
        temp = CMP2_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXPSEL;
        temp |= (uint32_t)(noninverting_input & CMP_CS_CMPXPSEL);
        CMP2_CS = temp;
    } else if(CMP3 == cmp_periph) {
        temp = CMP3_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXPSEL;
        temp |= (uint32_t)(noninverting_input & CMP_CS_CMPXPSEL);
        CMP3_CS = temp;
    } else {
    }
}

/*!
    \brief      CMP output init (API_ID(0x0004U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  output_polarity
      \arg        CMP_OUTPUT_POLARITY_INVERTED: output is inverted
      \arg        CMP_OUTPUT_POLARITY_NONINVERTED: output is not inverted
    \param[out] none
    \retval     none
*/
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_polarity)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph) {
        /* initialize comparator 0 output */
        temp = CMP0_CS;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity) {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        } else {
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP0_CS = temp;
    } else if(CMP1 == cmp_periph) {
        /* initialize comparator 1 output */
        temp = CMP1_CS;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity) {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        } else {
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP1_CS = temp;
    } else if(CMP2 == cmp_periph) {
        /* initialize comparator 2 output */
        temp = CMP2_CS;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity) {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        } else {
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP2_CS = temp;
    } else if(CMP3 == cmp_periph) {
        /* initialize comparator 3 output */
        temp = CMP3_CS;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity) {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        } else {
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP3_CS = temp;
    } else {
    }
}

/*!
    \brief      CMP digital filter init (API_ID(0x0005U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  sampling_frequency
      \arg        CMP_DIGITAL_FILTER_NOT_USED: digital filter is not used
      \arg        CMP_SAMPLING_FREQUENCY_DIV8: digital filter is used and sampling frequency is fCK_CMP/8
      \arg        CMP_SAMPLING_FREQUENCY_DIV16: digital filter is used and sampling frequency is fCK_CMP/16
      \arg        CMP_SAMPLING_FREQUENCY_DIV32: digital filter is used and sampling frequency is fCK_CMP/32
    \param[in]  sampling_number
      \arg        CMP_SAMPLING_NUM_3_TIMES: digital filter sampling number is three times
      \arg        CMP_SAMPLING_NUM_4_TIMES: digital filter sampling number is four times
    \param[out] none
    \retval     none
*/
void cmp_digital_filter_init(cmp_enum cmp_periph, uint32_t sampling_frequency, uint32_t sampling_number)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph) {
        /* initialize comparator 0 mode */
        temp = CMP0_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXDFSCDIV | CMP_CS_CMPXDFSNUM);
        temp |= (uint32_t)((sampling_frequency & CMP_CS_CMPXDFSCDIV) | (sampling_number & CMP_CS_CMPXDFSNUM));
        CMP0_CS = temp;
    } else if(CMP1 == cmp_periph) {
        /* initialize comparator 1 mode */
        temp = CMP1_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXDFSCDIV | CMP_CS_CMPXDFSNUM);
        temp |= (uint32_t)((sampling_frequency & CMP_CS_CMPXDFSCDIV) | (sampling_number & CMP_CS_CMPXDFSNUM));
        CMP1_CS = temp;
    } else if(CMP2 == cmp_periph) {
        /* initialize comparator 2 mode */
        temp = CMP2_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXDFSCDIV | CMP_CS_CMPXDFSNUM);
        temp |= (uint32_t)((sampling_frequency & CMP_CS_CMPXDFSCDIV) | (sampling_number & CMP_CS_CMPXDFSNUM));
        CMP2_CS = temp;
    } else if(CMP3 == cmp_periph) {
        /* initialize comparator 3 mode */
        temp = CMP3_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXDFSCDIV | CMP_CS_CMPXDFSNUM);
        temp |= (uint32_t)((sampling_frequency & CMP_CS_CMPXDFSCDIV) | (sampling_number & CMP_CS_CMPXDFSNUM));
        CMP3_CS = temp;
    } else {
    }
}

/*!
    \brief      enable CMP (API_ID(0x0006U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     none
*/
void cmp_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph) {
        CMP0_CS |= (uint32_t)CMP_CS_CMPXEN;
    } else if(CMP1 == cmp_periph) {
        CMP1_CS |= (uint32_t)CMP_CS_CMPXEN;
    } else if(CMP2 == cmp_periph) {
        CMP2_CS |= (uint32_t)CMP_CS_CMPXEN;
    } else if(CMP3 == cmp_periph) {
        CMP3_CS |= (uint32_t)CMP_CS_CMPXEN;
    } else {
    }
}

/*!
    \brief      disable CMP (API_ID(0x0007U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     none
*/
void cmp_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph) {
        CMP0_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    } else if(CMP1 == cmp_periph) {
        CMP1_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    } else if(CMP2 == cmp_periph) {
        CMP2_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    } else if(CMP3 == cmp_periph) {
        CMP3_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    } else {
    }
}

/*!
    \brief      lock the comparator (API_ID(0x0008U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     none
*/
void cmp_lock_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph) {
        /* lock CMP0 */
        CMP0_CS |= (uint32_t)CMP_CS_CMPXLK;
    } else if(CMP1 == cmp_periph) {
        /* lock CMP1 */
        CMP1_CS |= (uint32_t)CMP_CS_CMPXLK;
    } else if(CMP2 == cmp_periph) {
        /* lock CMP2 */
        CMP2_CS |= (uint32_t)CMP_CS_CMPXLK;
    } else if(CMP3 == cmp_periph) {
        /* lock CMP3 */
        CMP3_CS |= (uint32_t)CMP_CS_CMPXLK;
    } else {
    }
}

/*!
    \brief      enable CMP output to pin (API_ID(0x0009U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     none
*/
void cmp_output_to_pin_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph) {
        CMP0_CS |= (uint32_t)CMP_CS_CMPXPOE;
    } else if(CMP1 == cmp_periph) {
        CMP1_CS |= (uint32_t)CMP_CS_CMPXPOE;
    } else if(CMP2 == cmp_periph) {
        CMP2_CS |= (uint32_t)CMP_CS_CMPXPOE;
    } else if(CMP3 == cmp_periph) {
        CMP3_CS |= (uint32_t)CMP_CS_CMPXPOE;
    } else {
    }
}

/*!
    \brief      disable CMP output to pin (API_ID(0x000aU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     none
*/
void cmp_output_to_pin_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph) {
        CMP0_CS &= ~(uint32_t)CMP_CS_CMPXPOE;
    } else if(CMP1 == cmp_periph) {
        CMP1_CS &= ~(uint32_t)CMP_CS_CMPXPOE;
    } else if(CMP2 == cmp_periph) {
        CMP2_CS &= ~(uint32_t)CMP_CS_CMPXPOE;
    } else if(CMP3 == cmp_periph) {
        CMP3_CS &= ~(uint32_t)CMP_CS_CMPXPOE;
    } else {
    }
}

/*!
    \brief      enable CMP output (API_ID(0x000bU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     none
*/
void cmp_output_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph) {
        CMP0_CS |= (uint32_t)CMP_CS_CMPXOE;
    } else if(CMP1 == cmp_periph) {
        CMP1_CS |= (uint32_t)CMP_CS_CMPXOE;
    } else if(CMP2 == cmp_periph) {
        CMP2_CS |= (uint32_t)CMP_CS_CMPXOE;
    } else if(CMP3 == cmp_periph) {
        CMP3_CS |= (uint32_t)CMP_CS_CMPXOE;
    } else {
    }
}

/*!
    \brief      disable CMP output (API_ID(0x000cU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     none
*/
void cmp_output_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph) {
        CMP0_CS &= ~(uint32_t)CMP_CS_CMPXOE;
    } else if(CMP1 == cmp_periph) {
        CMP1_CS &= ~(uint32_t)CMP_CS_CMPXOE;
    } else if(CMP2 == cmp_periph) {
        CMP2_CS &= ~(uint32_t)CMP_CS_CMPXOE;
    } else if(CMP3 == cmp_periph) {
        CMP3_CS &= ~(uint32_t)CMP_CS_CMPXOE;
    } else {
    }
}

/*!
    \brief      get output level (API_ID(0x000dU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[out] none
    \retval     the output level
*/
uint32_t cmp_output_level_get(cmp_enum cmp_periph)
{
    uint32_t reval = CMP_OUTPUTLEVEL_LOW;

    if(CMP0 == cmp_periph) {
        /* get output level of CMP0 */
        if((uint32_t)RESET != (CMP_STAT & CMP_STAT_CMP0O)) {
            reval = CMP_OUTPUTLEVEL_HIGH;
        } else {
            reval = CMP_OUTPUTLEVEL_LOW;
        }
    } else if(CMP1 == cmp_periph) {
        /* get output level of CMP1 */
        if((uint32_t)RESET != (CMP_STAT & CMP_STAT_CMP1O)) {
            reval = CMP_OUTPUTLEVEL_HIGH;
        } else {
            reval = CMP_OUTPUTLEVEL_LOW;
        }
    } else if(CMP2 == cmp_periph) {
        /* get output level of CMP2 */
        if((uint32_t)RESET != (CMP_STAT & CMP_STAT_CMP2O)) {
            reval = CMP_OUTPUTLEVEL_HIGH;
        } else {
            reval = CMP_OUTPUTLEVEL_LOW;
        }
    } else if(CMP3 == cmp_periph) {
        /* get output level of CMP3 */
        if((uint32_t)RESET != (CMP_STAT & CMP_STAT_CMP3O)) {
            reval = CMP_OUTPUTLEVEL_HIGH;
        } else {
            reval = CMP_OUTPUTLEVEL_LOW;
        }
    } else {
    }
    return reval;
}

/*!
    \brief      get CMP flag (API_ID(0x000eU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  flag: CMP flags
      \arg        CMP_FLAG_COMPARE: CMP compare flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cmp_flag_get(cmp_enum cmp_periph, uint32_t flag)
{
    FlagStatus reval = RESET;

    if(CMP0 == cmp_periph) {
        if(CMP_FLAG_COMPARE == flag) {
            if(0U != (CMP_STAT & CMP_STAT_CMP0IF)) {
                reval = SET;
            } else {
            }
        } else {
        }
    } else if(CMP1 == cmp_periph) {
        if(CMP_FLAG_COMPARE == flag) {
            if(0U != (CMP_STAT & CMP_STAT_CMP1IF)) {
                reval = SET;
            } else {
            }
        } else {
        }
    } else if(CMP2 == cmp_periph) {
        if(CMP_FLAG_COMPARE == flag) {
            if(0U != (CMP_STAT & CMP_STAT_CMP2IF)) {
                reval = SET;
            } else {
            }
        } else {
        }
    } else if(CMP3 == cmp_periph) {
        if(CMP_FLAG_COMPARE == flag) {
            if(0U != (CMP_STAT & CMP_STAT_CMP3IF)) {
                reval = SET;
            } else {
            }
        } else {
        }
    } else {
    }
    return reval;
}

/*!
    \brief      clear CMP flag (API_ID(0x000fU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  flag: CMP flags
      \arg        CMP_FLAG_COMPARE: CMP compare flag
    \param[out] none
    \retval     none
*/
void cmp_flag_clear(cmp_enum cmp_periph, uint32_t flag)
{
    if(CMP0 == cmp_periph) {
        if(CMP_FLAG_COMPARE == flag) {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP0IC;
        } else {
        }
    } else if(CMP1 == cmp_periph) {
        if(CMP_FLAG_COMPARE == flag) {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP1IC;
        } else {
        }
    } else if(CMP2 == cmp_periph) {
        if(CMP_FLAG_COMPARE == flag) {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP2IC;
        } else {
        }
    } else if(CMP3 == cmp_periph) {
        if(CMP_FLAG_COMPARE == flag) {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP3IC;
        } else {
        }
    } else {
    }
}

/*!
    \brief      enable CMP interrupt (API_ID(0x0010U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  trigger_mode
      \arg        CMP_INT_RISING_EDGE: CMP generate interrupt request when rising edge come
      \arg        CMP_INT_FALLING_EDGE: CMP generate interrupt request when failing edge come
      \arg        CMP_INT_BOTH_EDGE: CMP generate interrupt request when both edge come
    \param[in]  interrupt: CMP interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        CMP_INT_COMPARE: CMP compare interrupt
    \param[out] none
    \retval     none
*/
void cmp_interrupt_enable(cmp_enum cmp_periph, uint32_t trigger_mode, uint32_t interrupt)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph) {
        /* enable CMP0 interrupt */
        temp = CMP0_CS;
        temp &= ~(uint32_t)(interrupt & CMP_CS_CMPXINTEN);
        temp |= (uint32_t)(trigger_mode & CMP_CS_CMPXINTEN);
        CMP0_CS = temp;
    } else if(CMP1 == cmp_periph) {
        /* enable CMP1 interrupt */
        temp = CMP1_CS;
        temp &= ~(uint32_t)(interrupt & CMP_CS_CMPXINTEN);
        temp |= (uint32_t)(trigger_mode & CMP_CS_CMPXINTEN);
        CMP1_CS = temp;
    } else if(CMP2 == cmp_periph) {
        /* enable CMP2 interrupt */
        temp = CMP2_CS;
        temp &= ~(uint32_t)(interrupt & CMP_CS_CMPXINTEN);
        temp |= (uint32_t)(trigger_mode & CMP_CS_CMPXINTEN);
        CMP2_CS = temp;
    } else if(CMP3 == cmp_periph) {
        /* enable CMP3 interrupt */
        temp = CMP3_CS;
        temp &= ~(uint32_t)(interrupt & CMP_CS_CMPXINTEN);
        temp |= (uint32_t)(trigger_mode & CMP_CS_CMPXINTEN);
        CMP3_CS = temp;
    } else {
    }
}

/*!
    \brief      disable CMP interrupt (API_ID(0x0011U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  interrupt: CMP interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        CMP_INT_COMPARE: CMP compare interrupt
    \param[out] none
    \retval     none
*/
void cmp_interrupt_disable(cmp_enum cmp_periph, uint32_t interrupt)
{
    if(CMP0 == cmp_periph) {
        /* disable CMP0 interrupt */
        CMP0_CS &= ~(uint32_t)(interrupt & CMP_CS_CMPXINTEN);
    } else if(CMP1 == cmp_periph) {
        /* disable CMP1 interrupt */
        CMP1_CS &= ~(uint32_t)(interrupt & CMP_CS_CMPXINTEN);
    } else if(CMP2 == cmp_periph) {
        /* disable CMP2 interrupt */
        CMP2_CS &= ~(uint32_t)(interrupt & CMP_CS_CMPXINTEN);
    } else if(CMP3 == cmp_periph) {
        /* disable CMP3 interrupt */
        CMP3_CS &= ~(uint32_t)(interrupt & CMP_CS_CMPXINTEN);
    } else {
    }
}

/*!
    \brief      get CMP interrupt flag (API_ID(0x0012U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  flag: CMP interrupt flags
      \arg        CMP_INT_FLAG_COMPARE: CMP compare interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cmp_interrupt_flag_get(cmp_enum cmp_periph, uint32_t flag)
{
    uint32_t intstatus = 0U, flagstatus = 0U;
    FlagStatus retval = RESET;

    if(CMP0 == cmp_periph) {
        if(CMP_INT_FLAG_COMPARE == flag) {
            /* get the corresponding flag bit status */
            flagstatus = CMP_STAT & CMP_STAT_CMP0IF;
            /* get the interrupt enable bit status */
            intstatus = CMP0_CS & CMP_CS_CMPXINTEN;
        } else {
        }
    } else if(CMP1 == cmp_periph) {
        if(CMP_INT_FLAG_COMPARE == flag) {
            /* get the corresponding flag bit status */
            flagstatus = CMP_STAT & CMP_STAT_CMP1IF;
            /* get the interrupt enable bit status */
            intstatus = CMP1_CS & CMP_CS_CMPXINTEN;
        } else {
        }
    } else if(CMP2 == cmp_periph) {
        if(CMP_INT_FLAG_COMPARE == flag) {
            /* get the corresponding flag bit status */
            flagstatus = CMP_STAT & CMP_STAT_CMP2IF;
            /* get the interrupt enable bit status */
            intstatus = CMP2_CS & CMP_CS_CMPXINTEN;
        } else {
        }
    } else if(CMP3 == cmp_periph) {
        if(CMP_INT_FLAG_COMPARE == flag) {
            /* get the corresponding flag bit status */
            flagstatus = CMP_STAT & CMP_STAT_CMP3IF;
            /* get the interrupt enable bit status */
            intstatus = CMP3_CS & CMP_CS_CMPXINTEN;
        } else {
        }
    } else {
    }

    if((0U != flagstatus) && (0U != intstatus)) {
        retval = SET;
    } else {
        retval = RESET;
    }

    return retval;
}

/*!
    \brief      clear CMP interrupt flag (API_ID(0x0013U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
      \arg        CMP2: comparator 2
      \arg        CMP3: comparator 3
    \param[in]  flag: CMP interrupt flags
      \arg        CMP_INT_FLAG_COMPARE: CMP compare interrupt flag
    \param[out] none
    \retval     none
*/
void cmp_interrupt_flag_clear(cmp_enum cmp_periph, uint32_t flag)
{
    /* clear CMP interrupt flag */
    if(CMP0 == cmp_periph) {
        if(CMP_INT_FLAG_COMPARE == flag) {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP0IC;
        } else {
        }
    } else if(CMP1 == cmp_periph) {
        if(CMP_INT_FLAG_COMPARE == flag) {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP1IC;
        } else {
        }
    } else if(CMP2 == cmp_periph) {
        if(CMP_INT_FLAG_COMPARE == flag) {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP2IC;
        } else {
        }
    } else if(CMP3 == cmp_periph) {
        if(CMP_INT_FLAG_COMPARE == flag) {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP3IC;
        } else {
        }
    } else {
    }
}
