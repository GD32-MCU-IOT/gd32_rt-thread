/*!
    \file    gd32m53x_tmu.h
    \brief   definitions for the TMU

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

#ifndef GD32M53X_TMU_H
#define GD32M53X_TMU_H

#include "gd32m53x.h"

/* TMU definitions */
#define TMU                         TMU_BASE

/* registers definitions */
#define TMU_CS                      REG32(TMU + 0x00000000U)          /*!< TMU control and status register */

#define TMU_IDATA                   REG32(TMU + 0x00000004U)          /*!< TMU input data register */

#define TMU_ODATA                   REG32(TMU + 0x00000008U)          /*!< TMU output data register */

/* bits definitions */
/* TMU_CS */
#define TMU_CS_MODE                 BITS(0,3)                   /*!< TMU operation mode selection */
#define TMU_CS_FACTOR               BITS(8,10)                  /*!< scaling factor */
#define TMU_CS_OFLTEN               BIT(14)                     /*!< output floating point format enable */
#define TMU_CS_IFLTEN               BIT(15)                     /*!< input floating point format enable */
#define TMU_CS_RIE                  BIT(16)                     /*!< read TMU_ODATA interrupt enable */
#define TMU_CS_RDEN                 BIT(17)                     /*!< read TMU_ODATA DMA request enable */
#define TMU_CS_WDEN                 BIT(18)                     /*!< write TMU_IDATA DMA request enable */
#define TMU_CS_ONUM                 BIT(19)                     /*!< times the TMU_ODATA needs to be read */
#define TMU_CS_INUM                 BIT(20)                     /*!< times the TMU_IDATA needs to be write */
#define TMU_CS_OWIDTH               BIT(21)                     /*!< width of output data */
#define TMU_CS_IWIDTH               BIT(22)                     /*!< width of input data */
#define TMU_CS_OVRIE                BIT(29)                     /*!< overflow error interrupt enable */
#define TMU_CS_OVRF                 BIT(30)                     /*!< overflow error flag */
#define TMU_CS_ENDF                 BIT(31)                     /*!< end of TMU operation flag */

/* TMU_IDATA */
#define TMU_IDATA_IDATA             BITS(0,31)                  /*!< the input data of TMU operation */

/* TMU_ODATA */
#define TMU_ODATA_ODATA             BITS(0,31)                  /*!< the output data of TMU operation */

/* constants definitions */
/* TMU init parameter struct definitions */
typedef struct {
    uint32_t mode;                                              /*!< mode of TMU operation */
    uint32_t scale;                                             /*!< scaling factor */
    uint32_t output_floating;                                   /*!< TMU_ODATA format */
    uint32_t input_floating;                                    /*!< TMU_IDATA format */
    uint32_t dma_read;                                          /*!< DMA request to read TMU_ODATA */
    uint32_t dma_write;                                         /*!< DMA request to write TMU_IDATA */
    uint32_t read_times;                                        /*!< times the TMU_ODATA needs to be read */
    uint32_t write_times;                                       /*!< times the TMU_IDATA needs to be write */
    uint32_t output_width;                                      /*!< width of output data */
    uint32_t input_width;                                       /*!< width of input data */
} tmu_parameter_struct;

/* TMU mode definitions */
#define TMU_MODE(regval)            (BITS(0,3) & ((uint32_t)(regval) << 0))
#define TMU_MODE_COS                TMU_MODE(0)                 /*!< mode0: m*cos(x) */
#define TMU_MODE_SIN                TMU_MODE(1)                 /*!< mode1: m*sin(x) */
#define TMU_MODE_ATAN2              TMU_MODE(2)                 /*!< mode2: atan2(y,x) */
#define TMU_MODE_MODULUS            TMU_MODE(3)                 /*!< mode3: sqrt(x^2+y^2) */
#define TMU_MODE_SQRT               TMU_MODE(4)                 /*!< mode4: sqrt(x) */

/* TMU scaling factor definitions */
#define SCALE(regval)               (BITS(8,10) & ((uint32_t)(regval) << 8))
#define TMU_SCALING_FACTOR_1        SCALE(0)                    /*!< scaling factor = 1 */
#define TMU_SCALING_FACTOR_2        SCALE(1)                    /*!< scaling factor = 2 */
#define TMU_SCALING_FACTOR_4        SCALE(2)                    /*!< scaling factor = 4 */
#define TMU_SCALING_FACTOR_8        SCALE(3)                    /*!< scaling factor = 8 */
#define TMU_SCALING_FACTOR_16       SCALE(4)                    /*!< scaling factor = 16 */
#define TMU_SCALING_FACTOR_32       SCALE(5)                    /*!< scaling factor = 32 */
#define TMU_SCALING_FACTOR_64       SCALE(6)                    /*!< scaling factor = 64 */
#define TMU_SCALING_FACTOR_128      SCALE(7)                    /*!< scaling factor = 128 */

/* TMU_ODATA format definitions */
#define TMU_OUTPUT_FLOAT_DISABLE    ((uint32_t)0x00000000U)     /*!< disable TMU_ODATA floating point format */
#define TMU_OUTPUT_FLOAT_ENABLE     TMU_CS_OFLTEN               /*!< enable TMU_ODATA floating point format */

/* TMU_IDATA format definitions */
#define TMU_INPUT_FLOAT_DISABLE     ((uint32_t)0x00000000U)     /*!< disable TMU_IDATA floating point format */
#define TMU_INPUT_FLOAT_ENABLE      TMU_CS_IFLTEN               /*!< enable TMU_IDATA floating point format */

/* TMU DMA read enable definitions */
#define TMU_READ_DMA_DISABLE        ((uint32_t)0x00000000U)     /*!< disable DMA request to read TMU_ODATA */
#define TMU_READ_DMA_ENABLE         TMU_CS_RDEN                 /*!< enable DMA request to read TMU_ODATA */

/* TMU DMA write enable definitions */
#define TMU_WRITE_DMA_DISABLE       ((uint32_t)0x00000000U)     /*!< disable DMA request to write TMU_IDATA */
#define TMU_WRITE_DMA_ENABLE        TMU_CS_WDEN                 /*!< enable DMA request to write TMU_IDATA */

/* TMU_ODATA read times definitions */
#define TMU_READ_TIMES_1            ((uint32_t)0x00000000U)     /*!< one 32-bit read operation */
#define TMU_READ_TIMES_2            TMU_CS_ONUM                 /*!< two 32-bit read operation */

/* TMU_IDATA write times definitions */
#define TMU_WRITE_TIMES_1           ((uint32_t)0x00000000U)     /*!< one 32-bit write operation */
#define TMU_WRITE_TIMES_2           TMU_CS_INUM                 /*!< two 32-bit write operation */

/* TMU output data width definitions */
#define TMU_OUTPUT_WIDTH_32         ((uint32_t)0x00000000U)     /*!< TMU_ODATA contains the output data in q1.31 format */
#define TMU_OUTPUT_WIDTH_16         TMU_CS_OWIDTH               /*!< TMU_ODATA contains the output data in q1.15 format */

/* TMU input data width definitions */
#define TMU_INPUT_WIDTH_32          ((uint32_t)0x00000000U)     /*!< TMU_IDATA contains the input data in q1.31 format */
#define TMU_INPUT_WIDTH_16          TMU_CS_IWIDTH               /*!< TMU_IDATA contains the input data in q1.15 format */

/* TMU flag */
#define TMU_FLAG_OVRF               TMU_CS_OVRF                 /*!< TMU overflow flag */
#define TMU_FLAG_END                TMU_CS_ENDF                 /*!< end of TMU operation flag */

/* TMU interrupt enable or disable */
#define TMU_INT_OVRF                TMU_CS_OVRIE                /*!< TMU overflow interrupt */
#define TMU_INT_END                 TMU_CS_RIE                  /*!< TMU request to read TMU_ODATA interrupt */

#define TMU_INT_FLAG_OVRF           TMU_CS_OVRF                 /*!< TMU overflow interrupt flag */
#define TMU_INT_FLAG_END            TMU_CS_ENDF                 /*!< TMU request to read TMU_ODATA interrupt flag */

/* function declarations */
/* initialization functions */
/* reset the TMU registers */
void tmu_deinit(void);
/* initialize the parameters of TMU struct with the default values */
void tmu_struct_para_init(tmu_parameter_struct *init_struct);
/* initialize TMU */
void tmu_init(tmu_parameter_struct *init_struct);

/* DMA configuration */
/* enable TMU DMA read request */
void tmu_dma_read_enable(void);
/* disable TMU DMA read request */
void tmu_dma_read_disable(void);
/* enable TMU DMA write request */
void tmu_dma_write_enable(void);
/* disable TMU DMA write request */
void tmu_dma_write_disable(void);

/* TMU data write and read */
/* write one data in q1.31 format */
void tmu_one_q31_write(uint32_t data);
/* write two data in q1.31 format */
void tmu_two_q31_write(uint32_t data1, uint32_t data2);
/* write two data in q1.15 format */
void tmu_two_q15_write(uint16_t data1, uint16_t data2);
/* write one data in floating point format */
void tmu_one_f32_write(float data);
/* write two data in floating point format */
void tmu_two_f32_write(float data1, float data2);
/* read one data in q1.31 format */
void tmu_one_q31_read(uint32_t *p);
/* read two data in q1.31 format */
void tmu_two_q31_read(uint32_t *p1, uint32_t *p2);
/* read two data in q1.15 format */
void tmu_two_q15_read(uint16_t *p1, uint16_t *p2);
/* read one data in floating point format */
void tmu_one_f32_read(float *p);
/* read two data in floating point format */
void tmu_two_f32_read(float *p1, float *p2);

/* TMU interrupt and flag */
/* get TMU flag */
FlagStatus tmu_flag_get(uint32_t flag);
/* clear TMU flag */
void tmu_flag_clear(uint32_t flag);
/* enable TMU interrupt */
void tmu_interrupt_enable(uint32_t interrupt);
/* disable TMU interrupt */
void tmu_interrupt_disable(uint32_t interrupt);
/* get TMU interrupt flag */
FlagStatus tmu_interrupt_flag_get(uint32_t int_flag);
/* clear TMU interrupt flag */
void tmu_interrupt_flag_clear(uint32_t int_flag);

/* TMU coprocessor instruction macro functions */
/* general write/read functions */
/*!
    \brief      configure the TMU_CS through coprocessor instruction
    \param[in]  REG_VALUE: the value to be written
    \param[out] none
    \retval     none
*/
#define TMU_CP_CS_WRITE(REG_VALUE)                 __asm volatile("MCR p0, 0, %[value], c0, c0, 0" : : [value] "r" (REG_VALUE))

/*!
    \brief      read out the TMU_CS through coprocessor instruction
    \param[in]  none
    \param[out] REG_VALUE: the value of TMU_CS
    \retval     none
*/
#define TMU_CP_CS_READ(REG_VALUE)                  __asm volatile("MRC p0, 0, %[value], c0, c0, 0" : [value] "=r" (REG_VALUE))

/*!
    \brief      write one data through coprocessor instruction
    \param[in]  DATA: the first input data only
    \param[out] none
    \retval     none
*/
#define TMU_CP_ONE_DATA_WRITE(DATA)                __asm volatile("MCR p0, 0, %[value], c0, c1, 0" : : [value] "r" (DATA))

/*!
    \brief      write two data through coprocessor instruction
    \param[in]  DATA1: the first input data
    \param[in]  DATA2: the second input data
    \param[out] none
    \retval     none
*/
#define TMU_CP_TWO_DATA_WRITE(DATA1, DATA2)        __asm volatile("MCRR p0, 0, %[value1], %[value2], c1" : : [value1] "r" (DATA1), [value2] "r" (DATA2))

/*!
    \brief      read one data through coprocessor instruction
    \param[in]  none
    \param[out] DATA: the first output data only
    \retval     none
*/
#define TMU_CP_ONE_DATA_READ(DATA)                 __asm volatile("MRC p0, 0, %[value], c0, c2, 0" : [value] "=r" (DATA))

/*!
    \brief      read two data through coprocessor instruction
    \param[in]  none
    \param[out] DATA1: the first output data only
    \param[out] DATA2: the second output data only
    \retval     none
*/
#define TMU_CP_TWO_DATA_READ(DATA1, DATA2)         __asm volatile("MRRC p0, 0, %[value1], %[value2], c2" : [value1] "=r" (DATA1), [value2] "=r" (DATA2))

/* fast write functions */
/*!
    \brief      configure mode0 (m*cos(��)) while writing one data through coprocessor instruction
    \param[in]  DATA: the first input data(��) only
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE0_ONE_DATA_WRITE(DATA)          __asm volatile("MCR p0, 0, %[value], c0, c9, 0" : : [value] "r" (DATA))

/*!
    \brief      configure mode0 (m*cos(��)) while writing two data through coprocessor instruction
    \param[in]  DATA1: the first input data(��)
    \param[in]  DATA2: the second input data(m)
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE0_TWO_DATA_WRITE(DATA1, DATA2)  __asm volatile("MCRR p0, 0, %[value1], %[value2], c9" : : [value1] "r" (DATA1), [value2] "r" (DATA2))

/*!
    \brief      configure mode1 (m*sin(��)) while writing one data through coprocessor instruction
    \param[in]  DATA: the first input data(��) only
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE1_ONE_DATA_WRITE(DATA)          __asm volatile("MCR p0, 0, %[value], c0, c9, 1" : : [value] "r" (DATA))

/*!
    \brief      configure mode1 (m*sin(��)) while writing two data through coprocessor instruction
    \param[in]  DATA1: the first input data(��)
    \param[in]  DATA2: the second input data(m)
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE1_TWO_DATA_WRITE(DATA1, DATA2)  __asm volatile("MCRR p0, 1, %[value1], %[value2], c9" : : [value1] "r" (DATA1), [value2] "r" (DATA2))

/*!
    \brief      configure mode2 (atan2(y,x)) while writing one data through coprocessor instruction
    \param[in]  DATA: the first input data only(x)
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE2_ONE_DATA_WRITE(DATA)          __asm volatile("MCR p0, 0, %[value], c0, c9, 2" : : [value] "r" (DATA))

/*!
    \brief      configure mode2 (atan2(y,x)) while writing two data through coprocessor instruction
    \param[in]  DATA1: the first input data(x)
    \param[in]  DATA2: the second input data(y)
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE2_TWO_DATA_WRITE(DATA1, DATA2)  __asm volatile("MCRR p0, 2, %[value1], %[value2], c9" : : [value1] "r" (DATA1), [value2] "r" (DATA2))

/*!
    \brief      configure mode3 (sqrt(x^2+y^2)) while writing one data through coprocessor instruction
    \param[in]  DATA: the first input data only(x)
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE3_ONE_DATA_WRITE(DATA)          __asm volatile("MCR p0, 0, %[value], c0, c9, 3" : : [value] "r" (DATA))

/*!
    \brief      configure mode3 (sqrt(x^2+y^2)) while writing two data through coprocessor instruction
    \param[in]  DATA1: the first input data(x)
    \param[in]  DATA2: the second input data(y)
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE3_TWO_DATA_WRITE(DATA1, DATA2)  __asm volatile("MCRR p0, 3, %[value1], %[value2], c9" : : [value1] "r" (DATA1), [value2] "r" (DATA2))

/*!
    \brief      configure mode4 (sqrt(x)) while writing one data through coprocessor instruction
    \param[in]  DATA: the first input data only(x)
    \param[out] none
    \retval     none
*/
#define TMU_CP_MODE4_ONE_DATA_WRITE(DATA)          __asm volatile("MCR p0, 0, %[value], c0, c9, 4" : : [value] "r" (DATA))

#endif /* GD32M53X_TMU_H */
