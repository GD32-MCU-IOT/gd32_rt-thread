/*!
    \file    gd32e51x_libopt.h
    \brief   library optional for gd32e51x

    \version 2024-12-30, V1.2.0, firmware for GD32E51x
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#ifndef GD32E51X_LIBOPT_H
#define GD32E51X_LIBOPT_H

#ifndef GD32EPRTxxA

#include "gd32e51x_adc.h"
#include "gd32e51x_bkp.h"
#include "gd32e51x_can.h"
#include "gd32e51x_crc.h"
#include "gd32e51x_ctc.h"
#include "gd32e51x_dac.h"
#include "gd32e51x_dbg.h"
#include "gd32e51x_dma.h"
#include "gd32e51x_exmc.h"
#include "gd32e51x_exti.h"
#include "gd32e51x_fmc.h"
#include "gd32e51x_fwdgt.h"
#include "gd32e51x_gpio.h"
#include "gd32e51x_shrtimer.h"
#include "gd32e51x_i2c.h"
#include "gd32e51x_misc.h"
#include "gd32e51x_pmu.h"
#include "gd32e51x_rcu.h"
#include "gd32e51x_rtc.h"
#include "gd32e51x_spi.h"
#include "gd32e51x_timer.h"
#include "gd32e51x_usart.h"
#include "gd32e51x_wwdgt.h"
#include "gd32e51x_sqpi.h"
#include "gd32e51x_sdio.h"
#include "gd32e51x_tmu.h"
#include "gd32e51x_cmp.h"

#if defined (GD32E51X_CL)
#include "gd32e51x_enet.h"
#endif /* GD32E51X_CL*/

#else /* GD32EPRTxxA */
#include "gd32e51x_adc.h"
#include "gd32e51x_bkp.h"
#include "gd32e51x_crc.h"
#include "gd32e51x_ctc.h"
#include "gd32e51x_dac.h"
#include "gd32e51x_dbg.h"
#include "gd32e51x_dma.h"
#include "gd32e51x_enet.h"
#include "gd32e51x_exmc.h"
#include "gd32e51x_exti.h"
#include "gd32e51x_fmc.h"
#include "gd32e51x_fwdgt.h"
#include "gd32e51x_gpio.h"
#include "gd32e51x_i2c.h"
#include "gd32e51x_misc.h"
#include "gd32e51x_pmu.h"
#include "gd32e51x_rcu.h"
#include "gd32e51x_rtc.h"
#include "gd32e51x_spi.h"
#include "gd32e51x_timer.h"
#include "gd32e51x_usart.h"
#include "gd32e51x_wwdgt.h"
#include "gd32e51x_sqpi.h"

#endif /* GD32EPRTxxA */

#endif /* GD32E51X_LIBOPT_H */
