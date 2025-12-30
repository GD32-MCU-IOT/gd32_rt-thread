/*!
    \file    gd32g5x3_fft.h
    \brief   definitions for the FFT
    
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

#ifndef GD32G5X3_FFT_H
#define GD32G5X3_FFT_H

#include "gd32g5x3.h"

/* FFT definitions */
#define FFT                       FFT_BASE                        /*!< FFT base address */

/* registers definitions */
#define FFT_CSR                   REG32((FFT) + 0x00000000U)      /*!< FFT control and status register */
#define FFT_RESADDR               REG32((FFT) + 0x00000004U)      /*!< FFT real start address register */
#define FFT_IMSADDR               REG32((FFT) + 0x00000008U)      /*!< FFT image start address register */
#define FFT_WSADDR                REG32((FFT) + 0x0000000CU)      /*!< FFT window start address register */
#define FFT_OSADDR                REG32((FFT) + 0x00000010U)      /*!< FFT output start address register */
#define FFT_LOOPLEN               REG32((FFT) + 0x00000014U)      /*!< FFT loop length register */

/* bits definitions */
/* FFT_CSR */
#define FFT_CSR_FFTEN             BIT(0)                          /*!< FFT calculation enable*/
#define FFT_CSR_NUMPT             BITS(1,3)                       /*!< FFT point number selection */
#define FFT_CSR_IFFTMODE          BIT(4)                          /*!< IFFT mode enable */
#define FFT_CSR_WINEN             BIT(8)                          /*!< Window function enable */
#define FFT_CSR_DOWNSAMP          BITS(9,12)                      /*!< input data down sample selection */
#define FFT_CSR_IMSEL             BITS(13,14)                     /*!< image input source selection */
#define FFT_CSR_TAEIE             BIT(27)                         /*!< FFT transfer access error interrupt enable */
#define FFT_CSR_TAEIF             BIT(28)                         /*!< FFT transfer access error flag */
#define FFT_CSR_CCIE              BIT(29)                         /*!< FFT calculation completion interrupt enable */
#define FFT_CSR_CCF               BIT(30)                         /*!< FFT calculation completion flag */
#define FFT_CSR_DMABSY            BIT(31)                         /*!< FFT DMA busy status bit */

/* FFT_RESADDR */
#define FFT_RESADDR_RESADDR       BITS(0,31)                      /*!< FFT real part start address */

/* FFT_IMSADDR */
#define FFT_IMSADDR_IMSADDR       BITS(0,31)                      /*!< FFT image part start address */

/* FFT_IMSADDR */
#define FFT_WSADDR_WSADDR         BITS(0,31)                      /*!< FFT window function start address */

/* FFT_OSADDR */
#define FFT_OSADDR_OSADDR         BITS(0,31)                      /*!< FFT output start address */

/* FFT_LOOPLEN */
#define FFT_LOOPLEN_LENGTH        BITS(0,15)                      /*!< DMA loop buffer length of the FFT input data */
#define FFT_LOOPLEN_INDEX         BITS(16,31)                     /*!< Index of DMA loop buffer */

/* constants definitions */
/* FFT init parameter struct definitions*/
typedef struct
{
    uint32_t mode_sel;                                            /*!< FFT mode configure */
    uint8_t point_num;                                            /*!< FFT point number select */
    uint8_t window_enable;                                        /*!< FFT window function enable */
    uint8_t downsamp_sel;                                         /*!< FFT input data down sample selection */
    uint8_t image_source;                                         /*!< FFT image input source select */
    uint16_t loopbuf_len;                                         /*!< FFT loop buffer length */
    uint16_t loopbuf_index;                                       /*!< FFT loop buffer index, 0~loopbuf_len. it can not more than loopbuf_len */
    uint32_t real_addr;                                           /*!< FFT real start address */
    uint32_t image_addr;                                          /*!< FFT image start address */
    uint32_t window_addr;                                         /*!< FFT window start address */
    uint32_t output_addr;                                         /*!< FFT output start address */
}fft_parameter_struct;

/* FFT mode configure */
#define FFT_MODE                         ((uint32_t)0x00000000U)                      /*!< excute FFT operation */
#define IFFT_MODE                        FFT_CSR_IFFTMODE                             /*!< excute IFFT operation */

/* FFT point number select */
#define CSR_NUMPT(regval)                (BITS(1,3) & ((uint32_t)(regval) << 1U))     /*!< number of FFT point */
#define FFT_POINT_32                     ((uint8_t)0x00U)                             /*!< number of FFT point is 32 */
#define FFT_POINT_64                     ((uint8_t)0x01U)                             /*!< number of FFT point is 64 */
#define FFT_POINT_128                    ((uint8_t)0x02U)                             /*!< number of FFT point is 128 */
#define FFT_POINT_256                    ((uint8_t)0x03U)                             /*!< number of FFT point is 256 */
#define FFT_POINT_512                    ((uint8_t)0x04U)                             /*!< number of FFT point is 512 */
#define FFT_POINT_1024                   ((uint8_t)0x05U)                             /*!< number of FFT point is 1024 */

/* FFT window function enable */
#define FFT_WINDOW_DISABLE               ((uint8_t)0x00U)                             /*!< no window function */
#define FFT_WINDOW_ENABLE                ((uint8_t)0x01U)                             /*!< window function from FFT_WSADDR */

/* FFT input data down sample selection */
#define CSR_DOWNSAMP(regval)             (BITS(9,12) & ((uint32_t)(regval) << 9U))    /*!< value of FFT down sample */
#define FFT_DOWNSAMPLE_1                 ((uint8_t)0x00U)                             /*!< value of FFT down sample is 1 */
#define FFT_DOWNSAMPLE_2                 ((uint8_t)0x01U)                             /*!< value of FFT down sample is 2 */
#define FFT_DOWNSAMPLE_3                 ((uint8_t)0x02U)                             /*!< value of FFT down sample is 3 */
#define FFT_DOWNSAMPLE_4                 ((uint8_t)0x03U)                             /*!< value of FFT down sample is 4 */
#define FFT_DOWNSAMPLE_5                 ((uint8_t)0x04U)                             /*!< value of FFT down sample is 5 */
#define FFT_DOWNSAMPLE_6                 ((uint8_t)0x05U)                             /*!< value of FFT down sample is 6 */
#define FFT_DOWNSAMPLE_7                 ((uint8_t)0x06U)                             /*!< value of FFT down sample is 7 */
#define FFT_DOWNSAMPLE_8                 ((uint8_t)0x07U)                             /*!< value of FFT down sample is 8 */
#define FFT_DOWNSAMPLE_9                 ((uint8_t)0x08U)                             /*!< value of FFT down sample is 9 */
#define FFT_DOWNSAMPLE_10                ((uint8_t)0x09U)                             /*!< value of FFT down sample is 10 */
#define FFT_DOWNSAMPLE_11                ((uint8_t)0x0AU)                             /*!< value of FFT down sample is 11 */
#define FFT_DOWNSAMPLE_12                ((uint8_t)0x0BU)                             /*!< value of FFT down sample is 12 */
#define FFT_DOWNSAMPLE_13                ((uint8_t)0x0CU)                             /*!< value of FFT down sample is 13 */
#define FFT_DOWNSAMPLE_14                ((uint8_t)0x0DU)                             /*!< value of FFT down sample is 14 */
#define FFT_DOWNSAMPLE_15                ((uint8_t)0x0EU)                             /*!< value of FFT down sample is 15 */
#define FFT_DOWNSAMPLE_16                ((uint8_t)0x0FU)                             /*!< value of FFT down sample is 16 */

/* FFT image input source select */
#define CSR_IMSEL(regval)                (BITS(13,14) & ((uint32_t)(regval) << 13U))  /*!< image input source select */
#define FFT_IM_MEMORY                    ((uint8_t)0x00U)                             /*!< image input is from FFT_IMSADDR */
#define FFT_IM_ZERO                      ((uint8_t)0x01U)                             /*!< image input is 0 */
#define FFT_IM_MEMORY_OPPOSITE           ((uint8_t)0x02U)                             /*!< image input is the opposite number of image data from FFT_IMSADDR */

/* FFT status flag */
#define FFT_FLAG_DMABSY                  FFT_CSR_DMABSY                               /*!< DMA busy flag */
#define FFT_FLAG_CCF                     FFT_CSR_CCF                                  /*!< FFT calculation completion flag */
#define FFT_FLAG_TAEIF                   FFT_CSR_TAEIF                                /*!< FFT transfer access error flag */

/* FFT interrupt */
#define FFT_INT_CCF                      FFT_CSR_CCIE                                 /*!< FFT calculation completion interrupt enable */
#define FFT_INT_TAEIF                    FFT_CSR_TAEIE                                /*!< FFT transfer access error interrupt enable */

/* FFT interrupt flag */
#define FFT_INT_FLAG_CCF                 FFT_CSR_CCF                                  /*!< FFT calculation completion interrupt flag */
#define FFT_INT_FLAG_TAEIF               FFT_CSR_TAEIF                                /*!< FFT transfer access error interrupt flag */

/* function declarations */
/* initialization functions */
/* reset the FFT peripheral */
void fft_deinit(void);
/* initialize the parameters of FFT struct with the default values */
void fft_struct_para_init(fft_parameter_struct* fft_parameter);
/* initialize the FFT peripheral for calculation */
void fft_init(fft_parameter_struct* fft_parameter);

/* configuration functions */
/* start FFT calculation */
void fft_calculation_start(void);
/* stop FFT calculation */
void fft_calculation_stop(void);
/* configure FFT calculation point number */
void fft_point_number_config(uint8_t point_num);
/* configure FFT mode */
void fft_mode_config(uint32_t mode);
/* enable FFT window function */
void fft_window_enable(void);
/* disable FFT window function */
void fft_window_disable(void);
/* configure FFT down sample value */
void fft_downsample_config(uint8_t sample_value);
/* configure FFT image part source */
void fft_image_source_config(uint8_t im_src);
/* configure real part start address */
void fft_real_addr_config(uint32_t addr);
/* configure image part start address */
void fft_image_addr_config(uint32_t addr);
/* configure window function start address */
void fft_window_addr_config(uint32_t addr);
/* configure output start address */
void fft_output_addr_config(uint32_t addr);
/* configure loop buffer length */
void fft_loop_buffer_length_config(uint16_t length);
/* configure loop buffer index */
void fft_loop_buffer_index_config(uint16_t index);

/* interrupt & flag functions */
/* get FFT flag status */
FlagStatus fft_flag_get(uint32_t flag);
/* clear FFT flag bit */
void fft_flag_clear(uint32_t flag);
/* enable FFT interrupt */
void fft_interrupt_enable(uint32_t fft_interrupt);
/* disable FFT interrupt */
void fft_interrupt_disable(uint32_t fft_interrupt);
/* get FFT interrupt flag status */
FlagStatus fft_interrupt_flag_get(uint32_t int_flag);
/* clear FFT interrupt flag bit */
void fft_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32G5X3_FFT_H */
