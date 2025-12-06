/*!
    \file    gd32h75e_esc_intc.h
    \brief   definitions for the ESC intc

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

#ifndef GD32H75E_ESC_INTC_H
#define GD32H75E_ESC_INTC_H

#include "gd32h75e.h"

/* INTC definitions */
#define ESC_INTC                           ((uint32_t)0x00003A00U)                     /*!< INTC base address */

/* registers definitions */
#define INTC_CTL                           ((uint32_t)(ESC_INTC + 0x00000000U))        /*!< INTC control register */
#define INTC_FLAG                          ((uint32_t)(ESC_INTC + 0x00000004U))        /*!< INTC flag register */
#define INTC_EN                            ((uint32_t)(ESC_INTC + 0x00000008U))        /*!< INTC enable register */

/* bits definitions */
/* INTC_CTL */
#define INTC_CTL_IRQMODE                   BIT(0)                      /*!< IRQ pin output mode */
#define INTC_CTL_IRQCKOUT                  BIT(1)                      /*!< IRQ clock output */
#define INTC_CTL_IRQPOL                    BIT(4)                      /*!< IRQ pin output polarity */
#define INTC_CTL_IRQEN                     BIT(8)                      /*!< IRQ pin output enable */
#define INTC_CTL_IRQSTAT                   BIT(12)                     /*!< internal IRQ line status */
#define INTC_CTL_DEASSTAT                  BIT(13)                     /*!< interrupt de-assertion interval status */
#define INTC_CTL_DEASC                     BIT(14)                     /*!< interrupt de-assertion interval clear */
#define INTC_CTL_DEAS                      BITS(24,31)                 /*!< interrupt de-assertion interval */

/* INTC_FLAG */
#define INTC_FLAG_ECATIF                   BIT(0)                      /*!< etherCAT interrupt flag */
#define INTC_FLAG_AHB2OPBIF                BIT(14)                     /*!< AHB2OPB bridge interrupt flag */
#define INTC_FLAG_PMEIF                    BIT(17)                     /*!< PME interrupt flag */
#define INTC_FLAG_TIMIF                    BIT(19)                     /*!< timer interrupt flag */
#define INTC_FLAG_PHYAIF                   BIT(26)                     /*!< ethernet PHY A interrupt flag */
#define INTC_FLAG_PHYBIF                   BIT(27)                     /*!< ethernet PHY B interrupt flag */
#define INTC_FLAG_READYIF                  BIT(30)                     /*!< device ready interrupt flag */
#define INTC_FLAG_SWIF                     BIT(31)                     /*!< software interrupt flag */

/* INTC_EN */
#define INTC_EN_ECATIE                     BIT(0)                      /*!< etherCAT interrupt enable */
#define INTC_EN_AHB2OPBIE                  BIT(14)                     /*!< AHB2OPB bridge interrupt enable */
#define INTC_EN_PMEIE                      BIT(17)                     /*!< PME interrupt enable */
#define INTC_EN_TIMIE                      BIT(19)                     /*!< timer interrupt enable */
#define INTC_EN_PHYAIE                     BIT(26)                     /*!< ethernet PHY A interrupt enable */
#define INTC_EN_PHYBIE                     BIT(27)                     /*!< ethernet PHY B interrupt enable */
#define INTC_EN_READYIE                    BIT(30)                     /*!< device ready interrupt enable */
#define INTC_EN_SWIE                       BIT(31)                     /*!< software interrupt enable */

/* interrupt enable */
typedef enum {
    SW_INT_ENABLE                          = INTC_EN_SWIE,             /*!< enable software interrupt */
    READY_INT_ENABLE                       = INTC_EN_READYIE,          /*!< enable device ready interrupt */
    PHYB_INT_ENABLE                        = INTC_EN_PHYBIE,           /*!< enable ethernet PHY B interrupt */
    PHYA_INT_ENABLE                        = INTC_EN_PHYAIE,           /*!< enable ethernet PHY A interrupt */
    TIM_INT_ENABLE                         = INTC_EN_TIMIE,            /*!< enable timer interrupt */
    PME_INT_ENABLE                         = INTC_EN_PMEIE,            /*!< enable PME interrupt */
    AHB2OPB_INT_ENABLE                     = INTC_EN_AHB2OPBIE,        /*!< enable AHB2OPB bridge interrupt */
    ECAT_INT_ENABLE                        = INTC_EN_ECATIE            /*!< enable etherCAT interrupt */
} intc_enable_enum;

/* interrupt disable */
typedef enum {
    SW_INT_DISABLE                         = INTC_EN_SWIE,             /*!< disable software interrupt */
    READY_INT_DISABLE                      = INTC_EN_READYIE,          /*!< disable device ready interrupt */
    PHYB_INT_DISABLE                       = INTC_EN_PHYBIE,           /*!< disable ethernet PHY B interrupt */
    PHYA_INT_DISABLE                       = INTC_EN_PHYAIE,           /*!< disable ethernet PHY A interrupt */
    TIM_INT_DISABLE                        = INTC_EN_TIMIE,            /*!< disable timer interrupt */
    PME_INT_DISABLE                        = INTC_EN_PMEIE,            /*!< disable PME interrupt */
    AHB2OPB_INT_DISABLE                    = INTC_EN_AHB2OPBIE,        /*!< disable AHB2OPB bridge interrupt */
    ECAT_INT_DISABLE                       = INTC_EN_ECATIE            /*!< disable etherCAT interrupt */
} intc_disable_enum;

/* get interrupt flag */
typedef enum {
    SW_INT_FLAG_GET                        = INTC_FLAG_SWIF,           /*!< get software interrupt flag */
    READY_INT_FLAG_GET                     = INTC_FLAG_READYIF,        /*!< get device ready interrupt flag */
    PHYB_INT_FLAG_GET                      = INTC_FLAG_PHYBIF,         /*!< get ethernet PHY B interrupt flag */
    PHYA_INT_FLAG_GET                      = INTC_FLAG_PHYAIF,         /*!< get ethernet PHY A interrupt flag */
    TIM_INT_FLAG_GET                       = INTC_FLAG_TIMIF,          /*!< get timer interrupt flag */
    PME_INT_FLAG_GET                       = INTC_FLAG_PMEIF,          /*!< get PME interrupt flag */
    AHB2OPB_INT_FLAG_GET                   = INTC_FLAG_AHB2OPBIF,      /*!< get AHB2OPB bridge interrupt flag */
    ECAT_INT_FLAG_GET                      = INTC_FLAG_ECATIF          /*!< get etherCAT interrupt flag */
} intc_get_flag_enum;

/* clear interrupt flag */
typedef enum {
    SW_INT_FLAG_CLEAR                      = INTC_FLAG_SWIF,           /*!< clear software interrupt flag */
    READY_INT_FLAG_CLEAR                   = INTC_FLAG_READYIF,        /*!< clear device ready interrupt flag */
    TIM_INT_FLAG_CLEAR                     = INTC_FLAG_TIMIF,          /*!< clear timer interrupt flag */
    PME_INT_FLAG_CLEAR                     = INTC_FLAG_PMEIF           /*!< clear PME interrupt flag */
} intc_clear_flag_enum;

/* Interrupt de-assertion interval */
#define INTC_DEAS                          ((uint32_t)0x00000000U)     /*!< no effect */
#define INTC_DEAS_CLEAR                    INTC_CTL_DEASC              /*!< clear interrupt de-assertion interval */

/* IRQ pin output enable */
#define IRQ_DISABLE                        ((uint32_t)0x00000000U)     /*!< disable IRQ pin output */
#define IRQ_ENABLE                         INTC_CTL_IRQEN              /*!< enable IRQ pin output */

/* IRQ pin output polarity */
#define IRQ_POL_LOW                        ((uint32_t)0x00000000U)     /*!< IRQ pin output activation level is low */
#define IRQ_POL_HIGH                       INTC_CTL_IRQPOL             /*!< IRQ pin output activation level is high */

/* IRQ clock output */
#define IRQ_NO_CKOUT                       ((uint32_t)0x00000000U)     /*!< No clock output */
#define IRQ_CKOUT                          INTC_CTL_IRQCKOUT           /*!< IRQ pin output crystal oscillator clock */

/* IRQ clock output mode */
#define IRQ_OPEN_DRAIN_MODE                ((uint32_t)0x00000000U)     /*!< Output open-drain mode */
#define IRQ_PUSH_PULL_MODE                 INTC_CTL_IRQMODE            /*!< Output push-pull mode */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check INTC control deasc */
#define NOT_INTC_CTL_DEASC(deasc_detect)            (((deasc_detect) != INTC_DEAS) && ((deasc_detect) != INTC_DEAS_CLEAR))

/* check INTC control irqen */
#define NOT_INTC_CTL_IRQEN(irqen)                   (((irqen) != IRQ_DISABLE) && ((irqen) != IRQ_ENABLE))

/* check INTC control irqpol */
#define NOT_INTC_CTL_IRPOL(irqpol)                  (((irqpol) != IRQ_POL_LOW) && ((irqpol) != IRQ_POL_HIGH))

/* check INTC control irqckout */
#define NOT_INTC_CTL_IRQCKOUT(irqckout)             (((irqckout) != IRQ_NO_CKOUT) && ((irqckout) != IRQ_CKOUT))

/* check INTC control irqmode */
#define NOT_INTC_CTL_IRQMODE(irqmode)               (((irqmode) != IRQ_OPEN_DRAIN_MODE) && ((irqmode) != IRQ_PUSH_PULL_MODE))

/* check INTC flag type */
#define NOT_INTC_FLAG_GET(interupt_flag_type)       (((interupt_flag_type) != SW_INT_FLAG_GET) && \
                                                     ((interupt_flag_type) != READY_INT_FLAG_GET) && \
                                                     ((interupt_flag_type) != PHYB_INT_FLAG_GET) && \
                                                     ((interupt_flag_type) != PHYA_INT_FLAG_GET) && \
                                                     ((interupt_flag_type) != TIM_INT_FLAG_GET) && \
                                                     ((interupt_flag_type) != PME_INT_FLAG_GET) && \
                                                     ((interupt_flag_type) != AHB2OPB_INT_FLAG_GET) && \
                                                     ((interupt_flag_type) != ECAT_INT_FLAG_GET))

/* check INTC flag clear type */
#define NOT_INTC_FLAG_CLEAR(interupt_flag_type)     (((interupt_flag_type) != SW_INT_FLAG_CLEAR) && \
                                                     ((interupt_flag_type) != READY_INT_FLAG_CLEAR) && \
                                                     ((interupt_flag_type) != TIM_INT_FLAG_CLEAR) && \
                                                     ((interupt_flag_type) != PME_INT_FLAG_CLEAR))

/* check INTC interrupt enable type */
#define NOT_INTC_ENABLE(interrupt_enable_type)      (((interrupt_enable_type) != INTC_EN_SWIE) && \
                                                     ((interrupt_enable_type) != INTC_EN_READYIE) && \
                                                     ((interrupt_enable_type) != INTC_EN_PHYBIE) && \
                                                     ((interrupt_enable_type) != INTC_EN_PHYAIE) && \
                                                     ((interrupt_enable_type) != INTC_EN_TIMIE) && \
                                                     ((interrupt_enable_type) != INTC_EN_PMEIE) && \
                                                     ((interrupt_enable_type) != INTC_EN_AHB2OPBIE) && \
                                                     ((interrupt_enable_type) != INTC_EN_ECATIE))
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* configure INTC interrupt de-assertion interval */
void intc_deas_config(uint8_t deas);
/* configure INTC interrupt de-assertion interval clear */
void intc_deasc_config(uint32_t deasc);
/* configure IRQ pin out enable, polarity, clock and mode */
void intc_irq_config(uint32_t irqen, uint32_t irqpol, uint32_t irqckout, uint32_t irqmode);
/* enable INTC interrupt */
void intc_interrupt_enable(intc_enable_enum int_type);
/* disable INTC interrupt */
void intc_interrupt_disable(intc_disable_enum int_type);
/* get INTC interrupt flag */
FlagStatus intc_interrupt_flag_get(intc_get_flag_enum flag_type);
/* clear INTC interrupt flag */
void intc_interrupt_flag_clear(intc_clear_flag_enum flag_type);
/* get interrupt de-assertion interval status */
FlagStatus intc_deasstat_get(void);
/* get internal IRQ line status */
FlagStatus intc_irqstat_get(void);

#endif /* GD32H75E_ESC_INTC_H */
