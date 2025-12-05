/*!
    \file    gd32h75e_ospi.c
    \brief   OSPI driver

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

#include "gd32h75e_ospi.h"

static void ospi_config(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct, ospi_regular_cmd_struct* cmd_struct);

/*!
    \brief      reset the OSPI peripheral (API_ID: 0x0001U)
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void ospi_deinit(uint32_t ospi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else
#endif
    {
        switch(ospi_periph){
        case OSPI0:
            /* reset OSPI0 */
            rcu_periph_reset_enable(RCU_OSPI0RST);
            rcu_periph_reset_disable(RCU_OSPI0RST);
            break;
        case OSPI1:
            /* reset OSPI1 */
            rcu_periph_reset_enable(RCU_OSPI1RST);
            rcu_periph_reset_disable(RCU_OSPI1RST);
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      initialize the parameters of OSPI struct with default values
    \param[in]  none
    \param[out] ospi_struct: the initialized struct ospi_parameter_struct pointer
    \retval     none
*/
void ospi_struct_init(ospi_parameter_struct *ospi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(ospi_struct)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the structure with default value */
        ospi_struct->prescaler          = 2U;
        ospi_struct->sample_shift       = OSPI_SAMPLE_SHIFTING_NONE;
        ospi_struct->fifo_threshold     = OSPI_FIFO_THRESHOLD_4;
        ospi_struct->device_size        = OSPI_MESZ_512_MBS;
        ospi_struct->wrap_size          = OSPI_DIRECT;
        ospi_struct->cs_hightime        = OSPI_CS_HIGH_TIME_3_CYCLE;
        ospi_struct->memory_type        = OSPI_MICRON_MODE;
        ospi_struct->delay_hold_cycle   = OSPI_DELAY_HOLD_NONE;
    }
}

/*!
    \brief      initialize OSPI parameter
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
void ospi_init(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct) 
{
    uint32_t reg = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(ospi_struct)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else if(NOT_OSPI_PSC(ospi_struct->prescaler)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_OSPI_FIFO_THRESHOLD(ospi_struct->fifo_threshold)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_OSPI_SAMPLE_SHIFTING(ospi_struct->sample_shift)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_OSPI_MESZ(ospi_struct->device_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_OSPI_CS_HIGH_TIME(ospi_struct->cs_hightime)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_OSPI_MEMORY_TYPE(ospi_struct->memory_type)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_OSPI_WRAP_SIZE(ospi_struct->wrap_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_OSPI_DELAY_HOLD_CYCLE(ospi_struct->delay_hold_cycle)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure memory type, device size, chip select high time, delay block bypass, free running clock, clock mode */    
        reg = OSPI_DCFG0(ospi_periph);
        
        reg &= ~(OSPI_DCFG0_DTYSEL | OSPI_DCFG0_MESZ | OSPI_DCFG0_CSHC);
        
        reg |= (ospi_struct->memory_type | ospi_struct->device_size | ospi_struct->cs_hightime);
        
        OSPI_DCFG0(ospi_periph) = reg;
         
        /* configure wrap size */
        OSPI_DCFG1(ospi_periph) = (OSPI_DCFG1(ospi_periph) & ~OSPI_DCFG1_WPSZ) | ospi_struct->wrap_size;
        
        /* configure FIFO threshold */
        OSPI_CTL(ospi_periph) = (OSPI_CTL(ospi_periph) & ~OSPI_CTL_FTL) | ospi_struct->fifo_threshold;
        
        /* wait till BUSY flag reset */
        while(RESET != (OSPI_STAT(ospi_periph) & OSPI_FLAG_BUSY)){
        }
         
        /* configure clock prescaler */
        OSPI_DCFG1(ospi_periph) = (OSPI_DCFG1(ospi_periph) & ~OSPI_DCFG1_PSC) | OSPI_PSC(ospi_struct->prescaler);

        /* configure sample shifting and delay hold quarter cycle */
        OSPI_TIMCFG(ospi_periph) = (OSPI_TIMCFG(ospi_periph) & ~(OSPI_TIMCFG_SSAMPLE | OSPI_TIMCFG_DEHQC)) | (ospi_struct->sample_shift | ospi_struct->delay_hold_cycle);
    }
}

/*!
    \brief      enable OSPI
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void ospi_enable(uint32_t ospi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_CTL(ospi_periph) |= (uint32_t)OSPI_CTL_OSPIEN;
    }
}

/*!
    \brief      disable OSPI
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void ospi_disable(uint32_t ospi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_CTL(ospi_periph) &= (uint32_t)(~OSPI_CTL_OSPIEN);
    }
}

/*!
    \brief      configure device memory type
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dtysel: OSPI device type select
                only one parameter can be selected which is shown as below:
      \arg        OSPI_MICRON_MODE: micron mode
      \arg        OSPI_MACRONIX_MODE: micronix mode
      \arg        OSPI_STANDARD_MODE: standard mode
      \arg        OSPI_MACRONIX_RAM_MODE: micronix ram mode
    \param[out] none
    \retval     none
*/
void ospi_device_memory_type_config(uint32_t ospi_periph, uint32_t dtysel)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else if(NOT_OSPI_MEMORY_TYPE(dtysel)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_DCFG0(ospi_periph) &= (uint32_t)(~OSPI_RESERVE_MODE);
        OSPI_DCFG0(ospi_periph) |= (uint32_t)dtysel;
    }
}

/*!
    \brief      configure device memory size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  mesz: device memory size
                only one parameter can be selected which is shown as below:
                  OSPI_MESZ_x_BYTES (x = 2, 4, 8, ..., 512, 1024)
                  OSPI_MESZ_x_KBS (x = 2, 4, 8, ..., 512, 1024)
                  OSPI_MESZ_x_MBS (x = 2, 4, 8, ..., 2048, 4096)
    \param[out] none
    \retval     none
*/
void ospi_device_memory_size_config(uint32_t ospi_periph, uint32_t mesz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else if(NOT_OSPI_MESZ(mesz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_DCFG0(ospi_periph) &= (uint32_t)(~OSPI_DCFG0_MESZ);
        OSPI_DCFG0(ospi_periph) |= (uint32_t)mesz;
    }
}

/*!
    \brief      select functional mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  fmod: OSPI functional mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INDIRECT_WRITE: OSPI indirect write mode
      \arg        OSPI_INDIRECT_READ: OSPI indirect read mode
      \arg        OSPI_STATUS_POLLING: OSPI status polling mode
      \arg        OSPI_MEMORY_MAPPED: OSPI memory mapped mode
    \param[out] none
    \retval     none
*/
void ospi_functional_mode_config(uint32_t ospi_periph, uint32_t fmod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else if(NOT_OSPI_MODE(fmod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_CTL(ospi_periph) &= (uint32_t)(~OSPI_CTL_FMOD);
        OSPI_CTL(ospi_periph) |= (uint32_t)fmod;
    }
}

/*!
    \brief      configure status polling mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  stop: OSPI automatic stop
      \arg        OSPI_AUTOMATIC_STOP_MATCH: status polling mode stop in match
    \param[in]  mode: OSPI match mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_MATCH_MODE_AND: status polling match mode and
      \arg        OSPI_MATCH_MODE_OR: status polling match mode or
    \param[out] none
    \retval     none
*/
void ospi_status_polling_config(uint32_t ospi_periph, uint32_t stop, uint32_t mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else if(NOT_OSPI_AUTOMATIC_STOP_MATCH(stop)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else if(NOT_OSPI_MATCH_MODE(mode)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_CTL(ospi_periph) &= (uint32_t)(~(OSPI_CTL_SPS | OSPI_CTL_SPMOD));
           
        OSPI_CTL(ospi_periph) |= (uint32_t)(stop | mode);
    }
}

/*!
    \brief      configure status mask
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  mask: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_status_mask_config(uint32_t ospi_periph, uint32_t mask)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_STATMK(ospi_periph) &= (uint32_t)(~OSPI_STATMK_MASK);
        OSPI_STATMK(ospi_periph) |= (uint32_t)mask;
    }
}

/*!
    \brief      configure status match
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  match: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_status_match_config(uint32_t ospi_periph, uint32_t match)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0000BU), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_STATMATCH(ospi_periph) &= (uint32_t)(~OSPI_STATMATCH_MATCH);
        OSPI_STATMATCH(ospi_periph) |= (uint32_t)match;
    }
}

/*!
    \brief      configure interval cycle
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  interval: between 0 and 0xFFFF
    \param[out] none
    \retval     none
*/
void ospi_interval_cycle_config(uint32_t ospi_periph, uint16_t interval)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_INTERVAL(ospi_periph) &= (uint32_t)(~OSPI_INTERVAL_INTERVAL);
        OSPI_INTERVAL(ospi_periph) |= (uint32_t)interval;
    }
}

/*!
    \brief      configure OSPI fifo threshold level
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  ftl: FIFO threshold level
                only one parameter can be selected which is shown as below:
                  OSPI_FIFO_THRESHOLD_x (x = 1, 2, ..., 31, 32)
    \param[out] none
    \retval     none
*/
void ospi_fifo_level_config(uint32_t ospi_periph, uint32_t ftl)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    } else if(NOT_OSPI_FIFO_THRESHOLD(ftl)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_CTL(ospi_periph) &= (uint32_t)(~OSPI_CTL_FTL);
        OSPI_CTL(ospi_periph) |= (uint32_t)ftl;
    }
}

/*!
    \brief      configure chip select high cycle
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  cshc: OSPI chip select high cycle
                only one parameter can be selected which is shown as below:
      \arg        OSPI_CS_HIGH_TIME_x_CYCLE (x = 1, 2, ..., 63, 64)
    \param[out] none
    \retval     none
*/
void ospi_chip_select_high_cycle_config(uint32_t ospi_periph, uint32_t cshc)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    } else if(NOT_OSPI_CS_HIGH_TIME(cshc)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_DCFG0(ospi_periph) &= (uint32_t)(~OSPI_DCFG0_CSHC);
        OSPI_DCFG0(ospi_periph) |= (uint32_t)cshc;
    }
}

/*!
    \brief      configure OSPI prescaler 
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  psc: between 0 and 0xFF
    \param[out] none
    \retval     none
*/
void ospi_prescaler_config(uint32_t ospi_periph, uint32_t psc)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    } else if(NOT_OSPI_PSC(psc)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_DCFG1(ospi_periph) &= (uint32_t)(~OSPI_DCFG1_PSC);
        OSPI_DCFG1(ospi_periph) |= (uint32_t)(psc & (uint32_t)0xFFU);
    }
}

/*!
    \brief      configure dummy cycles number
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dumyc: number of dummy cycles
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DUMYC_CYCLES_x (x = 0, 1, 2, ..., 30, 31)
    \param[out] none
    \retval     none
*/
void ospi_dummy_cycles_config(uint32_t ospi_periph, uint32_t dumyc)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    } else if(NOT_OSPI_DUMYC_CYCLES(dumyc)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_TIMCFG(ospi_periph) &= (uint32_t)(~OSPI_TIMCFG_DUMYC); 
        OSPI_TIMCFG(ospi_periph) |= (uint32_t)dumyc ;
    }
}

/*!
    \brief      delay hold 1/4 cycle
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dehqc: OSPI delay hold quarter cycle
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DELAY_HOLD_NONE: OSPI no delay hold cycle
      \arg        OSPI_DELAY_HOLD_QUARTER_CYCLE: OSPI delay hold 1/4 cycle
    \param[out] none
    \retval     none
*/
void ospi_delay_hold_cycle_config(uint32_t ospi_periph, uint32_t dehqc)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else if(NOT_OSPI_DELAY_HOLD_CYCLE(dehqc)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_TIMCFG(ospi_periph) &= (uint32_t)(~OSPI_TIMCFG_DEHQC);
        OSPI_TIMCFG(ospi_periph) |= (uint32_t)dehqc;
    }
}

/*!
    \brief      configure sample shift
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  ssample: OSPI sample shift
                only one parameter can be selected which is shown as below:
      \arg        OSPI_SAMPLE_SHIFTING_NONE: OSPI no sample shift
      \arg        OSPI_SAMPLE_SHIFTING_HALF_CYCLE: OSPI have 1/2 cycle sample shift
    \param[out] none
    \retval     none
*/
void ospi_sample_shift_config(uint32_t ospi_periph, uint32_t ssample)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else if(NOT_OSPI_SAMPLE_SHIFTING(ssample)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_TIMCFG(ospi_periph) &= (uint32_t)(~OSPI_TIMCFG_SSAMPLE);
        OSPI_TIMCFG(ospi_periph) |= (uint32_t)ssample;
    }
}

/*!
    \brief      configure data length
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dtlen: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_data_length_config(uint32_t ospi_periph, uint32_t dtlen)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_DTLEN(ospi_periph) &= (uint32_t)(~OSPI_DTLEN_DTLEN);
        OSPI_DTLEN(ospi_periph) |= (uint32_t)dtlen;
    }
}

/*!
    \brief      configure OSPI instruction
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  instruction: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_instruction_config(uint32_t ospi_periph, uint32_t instruction)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_INS(ospi_periph) = (uint32_t)instruction;
    }
}

/*!
    \brief      configure OSPI instruction mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  imod: OSPI instruction mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INSTRUCTION_NONE: no instruction mode
      \arg        OSPI_INSTRUCTION_1_LINE: instruction mode on a single line
      \arg        OSPI_INSTRUCTION_2_LINES: instruction mode on two lines
      \arg        OSPI_INSTRUCTION_4_LINES: instruction mode on four lines
      \arg        OSPI_INSTRUCTION_8_LINES: instruction mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_instruction_mode_config(uint32_t ospi_periph, uint32_t imod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    } else if(NOT_OSPI_INSTRUCTION_MODE(imod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_IMOD);
        OSPI_TCFG(ospi_periph) |= (uint32_t)imod;
    }
}

/*!
    \brief      configure OSPI instruction size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  inssz: OSPI instruction size
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INSTRUCTION_8_BITS: instruction size on 8-bit address
      \arg        OSPI_INSTRUCTION_16_BITS: instruction size on 16-bit address
      \arg        OSPI_INSTRUCTION_24_BITS: instruction size on 24-bit address
      \arg        OSPI_INSTRUCTION_32_BITS: instruction size on 32-bit address
    \param[out] none
    \retval     none
*/
void ospi_instruction_size_config(uint32_t ospi_periph, uint32_t inssz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    } else if(NOT_OSPI_INSTRUCTION_SIZE(inssz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_INSSZ);
        OSPI_TCFG(ospi_periph) |= (uint32_t)inssz;
    }
}

/*!
    \brief      configure OSPI address
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addr: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_address_config(uint32_t ospi_periph, uint32_t addr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_ADDR(ospi_periph) = (uint32_t)addr;
    }
}

/*!
    \brief      configure OSPI address mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrmod: OSPI address mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRESS_NONE: no address mode
      \arg        OSPI_ADDRESS_1_LINE: address mode on a single line
      \arg        OSPI_ADDRESS_2_LINES: address mode on two lines
      \arg        OSPI_ADDRESS_4_LINES: address mode on four lines
      \arg        OSPI_ADDRESS_8_LINES: address mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_address_mode_config(uint32_t ospi_periph, uint32_t addrmod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRESS_MODE(addrmod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_ADDRMOD);
        OSPI_TCFG(ospi_periph) |= (uint32_t)addrmod;
    }
}

/*!
    \brief      configure OSPI address dtr
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrdtr: OSPI address double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRDTR_MODE_DISABLE: address double transfer rate mode disable
      \arg        OSPI_ADDRDTR_MODE_ENABLE: address double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_address_dtr_config(uint32_t ospi_periph, uint32_t addrdtr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRDTR_MODE(addrdtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_ADDRDTR);
        OSPI_TCFG(ospi_periph) |= (uint32_t)addrdtr;
    }
}

/*!
    \brief      configure OSPI address size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrsz: OSPI address size
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRESS_8_BITS: address size on 8-bit address
      \arg        OSPI_ADDRESS_16_BITS: address size on 16-bit address
      \arg        OSPI_ADDRESS_24_BITS: address size on 24-bit address
      \arg        OSPI_ADDRESS_32_BITS: address size on 32-bit address
    \param[out] none
    \retval     none
*/
void ospi_address_size_config(uint32_t ospi_periph, uint32_t addrsz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRESS_SIZE(addrsz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_ADDRSZ);
        OSPI_TCFG(ospi_periph) |= (uint32_t)addrsz;
    }
}

/*!
    \brief      configure OSPI alternate byte
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  alte: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_alternate_byte_config(uint32_t ospi_periph, uint32_t alte)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_ALTE(ospi_periph) = (uint32_t)alte;
    }
}

/*!
    \brief      configure OSPI alternate byte mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  atlemod: OSPI alternate bytes mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ALTERNATE_BYTES_NONE: no alternate bytes mode
      \arg        OSPI_ALTERNATE_BYTES_1_LINE: alternate mode on a single line
      \arg        OSPI_ALTERNATE_BYTES_2_LINES: alternate bytes mode on two lines
      \arg        OSPI_ALTERNATE_BYTES_4_LINES: alternate bytes mode on four lines
      \arg        OSPI_ALTERNATE_BYTES_8_LINES: alternate bytes mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_alternate_byte_mode_config(uint32_t ospi_periph, uint32_t atlemod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    } else if(NOT_OSPI_ALTERNATE_BYTES_MODE(atlemod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_ALTEMOD );
        OSPI_TCFG(ospi_periph) |= (uint32_t)atlemod;
    }
}

/*!
    \brief      configure OSPI alternate byte dtr
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  abdtr: OSPI alternate bytes double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ABDTR_MODE_DISABLE: alternate bytes double transfer rate mode disable
      \arg        OSPI_ABDTR_MODE_ENABLE: alternate bytes double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_alternate_byte_dtr_config(uint32_t ospi_periph, uint32_t abdtr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    } else if(NOT_OSPI_ABDTR_MODE(abdtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_ABDTR);
        OSPI_TCFG(ospi_periph) |= (uint32_t)abdtr;
    }
}

/*!
    \brief      configure OSPI alternate byte size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  altesz: OSPI alternate bytes size
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ALTERNATE_BYTES_8_BITS: alternate bytes size on 8-bit address
      \arg        OSPI_ALTERNATE_BYTES_16_BITS: alternate bytes size on 16-bit address
      \arg        OSPI_ALTERNATE_BYTES_24_BITS: alternate bytes size on 24-bit address
      \arg        OSPI_ALTERNATE_BYTES_32_BITS: alternate bytes size on 32-bit address
    \param[out] none
    \retval     none
*/
void ospi_alternate_byte_size_config(uint32_t ospi_periph, uint32_t altesz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    } else if(NOT_OSPI_ALTERNATE_BYTES_SIZE(altesz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_ABDTR);
        OSPI_TCFG(ospi_periph) |= (uint32_t)altesz;
    }
}

/*!
    \brief      configure data mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  datamod: OSPI data mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DATA_NONE: no data mode
      \arg        OSPI_DATA_1_LINE: data mode on a single line
      \arg        OSPI_DATA_2_LINES: data mode on two lines
      \arg        OSPI_DATA_4_LINES: data mode on four lines
      \arg        OSPI_DATA_8_LINES: data mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_data_mode_config(uint32_t ospi_periph, uint32_t datamod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    } else if(NOT_OSPI_DATA_MODE(datamod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_DATAMOD);
        OSPI_TCFG(ospi_periph) |= (uint32_t)datamod;
    }
}

/*!
    \brief      configure data dtr
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dadtr: OSPI data double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DADTR_MODE_DISABLE: data double transfer rate mode disable
      \arg        OSPI_DADTR_MODE_ENABLE: data double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_data_dtr_config(uint32_t ospi_periph, uint32_t dadtr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0020U), ERR_PERIPH);
    } else if(NOT_OSPI_DADTR_MODE(dadtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0020U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_TCFG(ospi_periph) &= (uint32_t)~(OSPI_TCFG_DADTR);
        OSPI_TCFG(ospi_periph) |= (uint32_t)dadtr;
    }
}

/*!
    \brief      OSPI transmit data
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  data: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_data_transmit(uint32_t ospi_periph, uint32_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0021U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_DATA(ospi_periph) = (uint32_t)data;
    }
}

/*!
    \brief      OSPI receive data
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] none
    \retval     between 0 and 0xFFFFFFFF
*/
uint32_t ospi_data_receive(uint32_t ospi_periph)
{
    uint32_t reval = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0022U), ERR_PERIPH);
    } else
#endif
    {
        reval = ((uint32_t)OSPI_DATA(ospi_periph));
    }
    return reval;
}

/*!
    \brief      enable OSPI DMA
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void ospi_dma_enable(uint32_t ospi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0023U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_CTL(ospi_periph) |= (uint32_t)OSPI_CTL_DMAEN;
    }
}

/*!
    \brief      disable OSPI DMA
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void ospi_dma_disable(uint32_t ospi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0024U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_CTL(ospi_periph) &= (uint32_t)(~OSPI_CTL_DMAEN);
    }
}

/*!
    \brief      configure wrap size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  wpsz: OSPI wrap size set
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DIRECT: external memory indirect device does not support wrap read
      \arg        OSPI_WRAP_16BYTES: external memory device supports wrap size of 16 bytes
      \arg        OSPI_WRAP_32BYTES: external memory device supports wrap size of 32 bytes
      \arg        OSPI_WRAP_64BYTES: external memory device supports wrap size of 64 bytes
      \arg        OSPI_WRAP_128BYTES: external memory device supports wrap size of 128 bytes
    \param[out] none
    \retval     none
*/
void ospi_wrap_size_config(uint32_t ospi_periph, uint32_t wpsz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0025U), ERR_PERIPH);
    } else if(NOT_OSPI_WRAP_SIZE(wpsz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0025U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_DCFG1(ospi_periph) &= (uint32_t)(~OSPI_DCFG1_WPSZ);
        OSPI_DCFG1(ospi_periph) |= (uint32_t)wpsz;
    }
}

/*!
    \brief      configure wrap instruction mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  instruction: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_wrap_instruction_config(uint32_t ospi_periph, uint32_t instruction)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0026U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPINS(ospi_periph) = (uint32_t)instruction;
    }
}

/*!
    \brief      configure wrap instruction mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  imod: OSPI instruction mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INSTRUCTION_NONE: no instruction mode
      \arg        OSPI_INSTRUCTION_1_LINE: instruction mode on a single line
      \arg        OSPI_INSTRUCTION_2_LINES: instruction mode on two lines
      \arg        OSPI_INSTRUCTION_4_LINES: instruction mode on four lines
      \arg        OSPI_INSTRUCTION_8_LINES: instruction mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_wrap_instruction_mode_config(uint32_t ospi_periph, uint32_t imod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0027U), ERR_PERIPH);
    } else if(NOT_OSPI_INSTRUCTION_MODE(imod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0027U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_IMOD);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)imod;
    }
}

/*!
    \brief      configure wrap instruction size
    \param[in]  ospi_periph: OSPIx(x=0,1)
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INSTRUCTION_8_BITS: instruction size on 8-bit address
      \arg        OSPI_INSTRUCTION_16_BITS: instruction size on 16-bit address
      \arg        OSPI_INSTRUCTION_24_BITS: instruction size on 24-bit address
      \arg        OSPI_INSTRUCTION_32_BITS: instruction size on 32-bit address
    \param[out] none
    \retval     none
*/
void ospi_wrap_instruction_size_config(uint32_t ospi_periph, uint32_t inssz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0028U), ERR_PERIPH);
    } else if(NOT_OSPI_INSTRUCTION_SIZE(inssz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0028U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_INSSZ);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)inssz;
    }
}

/*!
    \brief      configure wrap address
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addr: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_wrap_address_config(uint32_t ospi_periph, uint32_t addr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0029U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_ADDR(ospi_periph) = (uint32_t)addr;
    }
}

/*!
    \brief      configure wrap address mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrmod: OSPI address mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRESS_NONE: no address mode
      \arg        OSPI_ADDRESS_1_LINE: address mode on a single line
      \arg        OSPI_ADDRESS_2_LINES: address mode on two lines
      \arg        OSPI_ADDRESS_4_LINES: address mode on four lines
      \arg        OSPI_ADDRESS_8_LINES: address mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_wrap_address_mode_config(uint32_t ospi_periph, uint32_t addrmod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002AU), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRESS_MODE(addrmod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002AU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_ADDRMOD);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)addrmod;
    }
}

/*!
    \brief      configure wrap address dtr
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrdtr: OSPI address double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRDTR_MODE_DISABLE: address double transfer rate mode disable
      \arg        OSPI_ADDRDTR_MODE_ENABLE: address double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_wrap_address_dtr_config(uint32_t ospi_periph, uint32_t addrdtr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002BU), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRDTR_MODE(addrdtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002BU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_ADDRDTR);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)addrdtr;
    }
}

/*!
    \brief      configure wrap address size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrsz: OSPI address size
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRESS_8_BITS: address size on 8-bit address
      \arg        OSPI_ADDRESS_16_BITS: address size on 16-bit address
      \arg        OSPI_ADDRESS_24_BITS: address size on 24-bit address
      \arg        OSPI_ADDRESS_32_BITS: address size on 32-bit address
    \param[out] none
    \retval     none
*/
void ospi_wrap_address_size_config(uint32_t ospi_periph, uint32_t addrsz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002CU), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRESS_SIZE(addrsz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002CU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_ADDRSZ);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)addrsz;
    }
}

/*!
    \brief      configure wrap alternate byte
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  alte: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_wrap_alternate_byte_config(uint32_t ospi_periph, uint32_t alte)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002DU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPALTE(ospi_periph) = (uint32_t)alte;
    }
}

/*!
    \brief      configure wrap alternate byte mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  atlemod: OSPI alternate bytes mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ALTERNATE_BYTES_NONE: no alternate bytes mode
      \arg        OSPI_ALTERNATE_BYTES_1_LINE: alternate mode on a single line
      \arg        OSPI_ALTERNATE_BYTES_2_LINES: alternate bytes mode on two lines
      \arg        OSPI_ALTERNATE_BYTES_4_LINES: alternate bytes mode on four lines
      \arg        OSPI_ALTERNATE_BYTES_8_LINES: alternate bytes mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_wrap_alternate_byte_mode_config(uint32_t ospi_periph, uint32_t atlemod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002EU), ERR_PERIPH);
    } else if(NOT_OSPI_ALTERNATE_BYTES_MODE(atlemod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002EU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_ALTEMOD);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)atlemod;
    }
}

/*!
    \brief      configure wrap alternate byte dtr
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  abdtr: OSPI alternate bytes double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ABDTR_MODE_DISABLE: alternate bytes double transfer rate mode disable
      \arg        OSPI_ABDTR_MODE_ENABLE: alternate bytes double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_wrap_alternate_byte_dtr_config(uint32_t ospi_periph, uint32_t abdtr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002FU), ERR_PERIPH);
    } else if(NOT_OSPI_ABDTR_MODE(abdtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x002FU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_ABDTR);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)abdtr;
    }
}

/*!
    \brief      configure wrap alternate byte size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  altesz: OSPI alternate bytes size
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ALTERNATE_BYTES_8_BITS: alternate bytes size on 8-bit address
      \arg        OSPI_ALTERNATE_BYTES_16_BITS: alternate bytes size on 16-bit address
      \arg        OSPI_ALTERNATE_BYTES_24_BITS: alternate bytes size on 24-bit address
      \arg        OSPI_ALTERNATE_BYTES_32_BITS: alternate bytes size on 32-bit address
    \param[out] none
    \retval     none
*/
void ospi_wrap_alternate_byte_size_config(uint32_t ospi_periph, uint32_t altesz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0030U), ERR_PERIPH);
    } else if(NOT_OSPI_ALTERNATE_BYTES_SIZE(altesz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0030U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_ABDTR);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)altesz;
    }
}

/*!
    \brief      configure wrap data mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  datamod: OSPI data mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DATA_NONE: no data mode
      \arg        OSPI_DATA_1_LINE: data mode on a single line
      \arg        OSPI_DATA_2_LINES: data mode on two lines
      \arg        OSPI_DATA_4_LINES: data mode on four lines
      \arg        OSPI_DATA_8_LINES: data mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_wrap_data_mode_config(uint32_t ospi_periph, uint32_t datamod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0031U), ERR_PERIPH);
    } else if(NOT_OSPI_DATA_MODE(datamod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0031U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_DATAMOD);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)datamod;
    }
}

/*!
    \brief      configure wrap data mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dadtr: OSPI data double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DADTR_MODE_DISABLE: data double transfer rate mode disable
      \arg        OSPI_DADTR_MODE_ENABLE: data double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_wrap_data_dtr_config(uint32_t ospi_periph, uint32_t dadtr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0032U), ERR_PERIPH);
    } else if(NOT_OSPI_DADTR_MODE(dadtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0032U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WPTCFG(ospi_periph) &= (uint32_t)~(OSPI_WPTCFG_DADTR);
        OSPI_WPTCFG(ospi_periph) |= (uint32_t)dadtr;
    }
}

/*!
    \brief      configure wrap dummy cycles number
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dumyc: number of dummy cycles
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DUMYC_CYCLES_x (x = 0, 1, 2, ..., 30, 31)
    \param[out] none
    \retval     none
*/
void ospi_wrap_dummy_cycles_config(uint32_t ospi_periph, uint32_t dumyc)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0033U), ERR_PERIPH);
    } else if(NOT_OSPI_DUMYC_CYCLES(dumyc)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0033U), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_WPTIMCFG(ospi_periph) &= (uint32_t)(~OSPI_WPTIMCFG_DUMYC);
        OSPI_WPTIMCFG(ospi_periph) |= (uint32_t)(dumyc << 0U);
    }
}

/*!
    \brief      delay hold 1/4 cycle in wrap
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dehqc: OSPI delay hold quarter cycle
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DELAY_HOLD_NONE: OSPI no delay hold cycle
      \arg        OSPI_DELAY_HOLD_QUARTER_CYCLE: OSPI delay hold 1/4 cycle
    \param[out] none
    \retval     none
*/
void ospi_wrap_delay_hold_cycle_config(uint32_t ospi_periph, uint32_t dehqc)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0034U), ERR_PERIPH);
    } else if(NOT_OSPI_DELAY_HOLD_CYCLE(dehqc)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0034U), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_WPTIMCFG(ospi_periph) &= (uint32_t)(~OSPI_WPTIMCFG_DEHQC);
        OSPI_WPTIMCFG(ospi_periph) |= (uint32_t)dehqc;
    }
}

/*!
    \brief      configure sample shift in wrap
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  ssample: OSPI sample shift
                only one parameter can be selected which is shown as below:
      \arg        OSPI_SAMPLE_SHIFTING_NONE: OSPI no sample shift
      \arg        OSPI_SAMPLE_SHIFTING_HALF_CYCLE: OSPI have 1/2 cycle sample shift
    \param[out] none
    \retval     none
*/
void ospi_wrap_sample_shift_config(uint32_t ospi_periph, uint32_t ssample)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0035U), ERR_PERIPH);
    } else if(NOT_OSPI_SAMPLE_SHIFTING(ssample)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0035U), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_WPTIMCFG(ospi_periph) &= (uint32_t)(~OSPI_WPTIMCFG_SSAMPLE);
        OSPI_WPTIMCFG(ospi_periph) |= (uint32_t)ssample;
    }
}

/*!
    \brief      configure write instruction
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  instruction: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_write_instruction_config(uint32_t ospi_periph, uint32_t instruction)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0036U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WINS(ospi_periph) = (uint32_t)instruction;
    }
}

/*!
    \brief      configure write instruction mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  imod: OSPI instruction mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INSTRUCTION_NONE: no instruction mode
      \arg        OSPI_INSTRUCTION_1_LINE: instruction mode on a single line
      \arg        OSPI_INSTRUCTION_2_LINES: instruction mode on two lines
      \arg        OSPI_INSTRUCTION_4_LINES: instruction mode on four lines
      \arg        OSPI_INSTRUCTION_8_LINES: instruction mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_write_instruction_mode_config(uint32_t ospi_periph, uint32_t imod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0037U), ERR_PERIPH);
    } else if(NOT_OSPI_INSTRUCTION_MODE(imod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0037U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_IMOD);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)imod;
    }
}

/*!
    \brief      configure write instruction size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  inssz: OSPI instruction size
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INSTRUCTION_8_BITS: instruction size on 8-bit address
      \arg        OSPI_INSTRUCTION_16_BITS: instruction size on 16-bit address
      \arg        OSPI_INSTRUCTION_24_BITS: instruction size on 24-bit address
      \arg        OSPI_INSTRUCTION_32_BITS: instruction size on 32-bit address
    \param[in]  instruction: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_write_instruction_size_config(uint32_t ospi_periph, uint32_t inssz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0038U), ERR_PERIPH);
    } else if(NOT_OSPI_INSTRUCTION_SIZE(inssz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0038U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_INSSZ);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)inssz;
    }
}

/*!
    \brief      configure write address
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addr: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_write_address_config(uint32_t ospi_periph, uint32_t addr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0039U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_ADDR(ospi_periph) = (uint32_t)addr;
    }
}

/*!
    \brief      configure write address mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrmod: OSPI address mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRESS_NONE: no address mode
      \arg        OSPI_ADDRESS_1_LINE: address mode on a single line
      \arg        OSPI_ADDRESS_2_LINES: address mode on two lines
      \arg        OSPI_ADDRESS_4_LINES: address mode on four lines
      \arg        OSPI_ADDRESS_8_LINES: address mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_write_address_mode_config(uint32_t ospi_periph, uint32_t addrmod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003AU), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRESS_MODE(addrmod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003AU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_ADDRMOD);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)addrmod;
    }
}

/*!
    \brief      configure write address dtr
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrdtr: OSPI address double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRDTR_MODE_DISABLE: address double transfer rate mode disable
      \arg        OSPI_ADDRDTR_MODE_ENABLE: address double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_write_address_dtr_config(uint32_t ospi_periph, uint32_t addrdtr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003BU), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRDTR_MODE(addrdtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003BU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_ADDRDTR);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)addrdtr;
    }
}

/*!
    \brief      configure write address size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  addrsz: OSPI address size
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ADDRESS_8_BITS: address size on 8-bit address
      \arg        OSPI_ADDRESS_16_BITS: address size on 16-bit address
      \arg        OSPI_ADDRESS_24_BITS: address size on 24-bit address
      \arg        OSPI_ADDRESS_32_BITS: address size on 32-bit address
    \param[out] none
    \retval     none
*/
void ospi_write_address_size_config(uint32_t ospi_periph, uint32_t addrsz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003CU), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRESS_SIZE(addrsz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003CU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_ADDRSZ);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)addrsz;
    }
}

/*!
    \brief      configure write alternate byte
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  alte: between 0 and 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void ospi_write_alternate_byte_config(uint32_t ospi_periph, uint32_t alte)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003DU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WALTE(ospi_periph) = (uint32_t)alte;
    }
}

/*!
    \brief      configure write alternate bytes mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  atlemod: OSPI alternate bytes mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ALTERNATE_BYTES_NONE: no alternate bytes mode
      \arg        OSPI_ALTERNATE_BYTES_1_LINE: alternate mode on a single line
      \arg        OSPI_ALTERNATE_BYTES_2_LINES: alternate bytes mode on two lines
      \arg        OSPI_ALTERNATE_BYTES_4_LINES: alternate bytes mode on four lines
      \arg        OSPI_ALTERNATE_BYTES_8_LINES: alternate bytes mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_write_alternate_byte_mode_config(uint32_t ospi_periph, uint32_t atlemod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003EU), ERR_PERIPH);
    } else if(NOT_OSPI_ALTERNATE_BYTES_MODE(atlemod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003EU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_ALTEMOD);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)atlemod;
    }
}

/*!
    \brief      configure write alternate byte dtr
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  abdtr: OSPI alternate bytes double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ABDTR_MODE_DISABLE: alternate bytes double transfer rate mode disable
      \arg        OSPI_ABDTR_MODE_ENABLE: alternate bytes double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_write_alternate_byte_dtr_config(uint32_t ospi_periph, uint32_t abdtr)
{ 
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003FU), ERR_PERIPH);
    } else if(NOT_OSPI_ABDTR_MODE(abdtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x003FU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_ABDTR);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)abdtr;
    }
}

/*!
    \brief      configure write alternate byte size
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  altesz: OSPI alternate bytes size
                only one parameter can be selected which is shown as below:
      \arg        OSPI_ALTERNATE_BYTES_8_BITS: alternate bytes size on 8-bit address
      \arg        OSPI_ALTERNATE_BYTES_16_BITS: alternate bytes size on 16-bit address
      \arg        OSPI_ALTERNATE_BYTES_24_BITS: alternate bytes size on 24-bit address
      \arg        OSPI_ALTERNATE_BYTES_32_BITS: alternate bytes size on 32-bit address
    \param[out] none
    \retval     none
*/
void ospi_write_alternate_byte_size_config(uint32_t ospi_periph, uint32_t altesz)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0040U), ERR_PERIPH);
    } else if(NOT_OSPI_ALTERNATE_BYTES_SIZE(altesz)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0040U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_ALTESZ);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)altesz;
    }
}

/*!
    \brief      configure write data mode
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  datamod: OSPI data mode
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DATA_NONE: no data mode
      \arg        OSPI_DATA_1_LINE: data mode on a single line
      \arg        OSPI_DATA_2_LINES: data mode on two lines
      \arg        OSPI_DATA_4_LINES: data mode on four lines
      \arg        OSPI_DATA_8_LINES: data mode on eight lines
    \param[out] none
    \retval     none
*/
void ospi_write_data_mode_config(uint32_t ospi_periph, uint32_t datamod)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0041U), ERR_PERIPH);
    } else if(NOT_OSPI_DATA_MODE(datamod)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0041U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~OSPI_WTCFG_DATAMOD;
        OSPI_WTCFG(ospi_periph) |= (uint32_t)datamod;
    }
}

/*!
    \brief      configure write data dtr
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dadtr: OSPI data double transfer rate
                only one parameter can be selected which is shown as below:
      \arg        OSPI_DADTR_MODE_DISABLE: data double transfer rate mode disable
      \arg        OSPI_DADTR_MODE_ENABLE: data double transfer rate mode enable
    \param[out] none
    \retval     none
*/
void ospi_write_data_dtr_config(uint32_t ospi_periph, uint32_t dadtr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0042U), ERR_PERIPH);
    } else if(NOT_OSPI_DADTR_MODE(dadtr)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0042U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_WTCFG(ospi_periph) &= (uint32_t)~(OSPI_WTCFG_DADTR);
        OSPI_WTCFG(ospi_periph) |= (uint32_t)dadtr;
    }
}

/*!
    \brief      configure write dummy cycles number
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  dumyc: number of dummy cycles
      \arg        OSPI_DUMYC_CYCLES_x (x = 0, 1, 2, ..., 30, 31)
    \param[out] none
    \retval     none
*/
void ospi_write_dummy_cycles_config(uint32_t ospi_periph, uint32_t dumyc)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0043U), ERR_PERIPH);
    } else if(NOT_OSPI_DUMYC_CYCLES(dumyc)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0043U), ERR_PERIPH);
    } else 
#endif
    {
        OSPI_WTIMCFG(ospi_periph) &= (uint32_t)(~OSPI_WTIMCFG_DUMYC);
        OSPI_WTIMCFG(ospi_periph) |= (uint32_t)dumyc;
    }
}

/*!
    \brief      configure OSPI regular command parameter
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
                               OSPI_MACRONIX_RAM_MODE
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                             OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES    
    \param[in]  cmd_struct: structure that contains the command configuration information
                            and the member values are shown as below:
                  operation_type: OSPI_OPTYPE_COMMON_CFG, OSPI_OPTYPE_READ_CFG
                                  OSPI_OPTYPE_WRITE_CFG, OSPI_OPTYPE_WRAP_CFG
                  instruction: between 0 and 0xFFFFFFFF
                  ins_mode: OSPI_INSTRUCTION_NONE, OSPI_INSTRUCTION_1_LINE, OSPI_INSTRUCTION_2_LINES
                            OSPI_INSTRUCTION_4_LINES, OSPI_INSTRUCTION_8_LINES
                  ins_size: OSPI_INSTRUCTION_8_BITS, OSPI_INSTRUCTION_16_BITS
                            OSPI_INSTRUCTION_24_BITS, OSPI_INSTRUCTION_32_BITS
                  address: between 0 and 0xFFFFFFFF
                  addr_mode: OSPI_ADDRESS_NONE, OSPI_ADDRESS_1_LINE, OSPI_ADDRESS_2_LINES
                             OSPI_ADDRESS_4_LINES, OSPI_ADDRESS_8_LINES
                  address_size: OSPI_ADDRESS_8_BITS, OSPI_ADDRESS_16_BITS
                                OSPI_ADDRESS_24_BITS, OSPI_ADDRESS_32_BITS
                  addr_dtr_mode: OSPI_ADDRDTR_MODE_DISABLE, OSPI_ADDTR_MODE_ENABLE
                  alter_bytes: between 0 and 0xFFFFFFFF
                  alter_bytes_mode: OSPI_ALTERNATE_BYTES_NONE, OSPI_ALTERNATE_BYTES_1_LINE
                                    OSPI_ALTERNATE_BYTES_2_LINES, OSPI_ALTERNATE_BYTES_4_LINES
                                    OSPI_ALTERNATE_BYTES_8_LINES
                  alter_bytes_size: OSPI_ALTERNATE_BYTES_8_BITS, OSPI_ALTERNATE_BYTES_16_BITS
                                    OSPI_ALTERNATE_BYTES_24_BITS, OSPI_ALTERNATE_BYTES_32_BITS
                  alter_bytes_dtr_mode: OSPI_ABDTR_MODE_DISABLE, OSPI_ABDTR_MODE_ENABLE
                  data_mode: OSPI_DATA_NONE, OSPI_DATA_1_LINE, OSPI_DATA_2_LINES
                             OSPI_DATA_4_LINES, OSPI_DATA_8_LINES
                  nbdata: between 1 and 0xFFFFFFFF
                  data_dtr_mode: OSPI_DADTR_MODE_DISABLE, OSPI_DADTR_MODE_ENABLE
                  dummy_cycles: OSPI_DUMYC_CYCLES_x (x = 0, 1, 2, ..., 30, 31)
    \param[out] none
    \retval     none
*/
void ospi_command_config(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct, ospi_regular_cmd_struct *cmd_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(ospi_struct)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PARAM_POINTER);
    } else if(NOT_VALID_POINTER(cmd_struct)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PARAM_POINTER);
    }else if(NOT_OSPI_PSC(ospi_struct->prescaler)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_FIFO_THRESHOLD(ospi_struct->fifo_threshold)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_SAMPLE_SHIFTING(ospi_struct->sample_shift)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_MESZ(ospi_struct->device_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_CS_HIGH_TIME(ospi_struct->cs_hightime)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_MEMORY_TYPE(ospi_struct->memory_type)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_WRAP_SIZE(ospi_struct->wrap_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_DELAY_HOLD_CYCLE(ospi_struct->delay_hold_cycle)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_OPTYPE(cmd_struct->operation_type)) {
         fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_INSTRUCTION_MODE(cmd_struct->ins_mode)) {
         fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_INSTRUCTION_SIZE(cmd_struct->ins_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRESS_MODE(cmd_struct->addr_mode)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRESS_SIZE(cmd_struct->addr_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_ADDRDTR_MODE(cmd_struct->addr_dtr_mode)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_ALTERNATE_BYTES_MODE(cmd_struct->alter_bytes)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_ALTERNATE_BYTES_SIZE(cmd_struct->alter_bytes_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_ABDTR_MODE(cmd_struct->alter_bytes_dtr_mode)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_DATA_MODE(cmd_struct->data_mode)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else if(NOT_OSPI_DADTR_MODE(cmd_struct->data_dtr_mode)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    }  else if(NOT_OSPI_DUMYC_CYCLES(cmd_struct->dummy_cycles)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(((cmd_struct->operation_type == OSPI_OPTYPE_WRITE_CFG) || (cmd_struct->operation_type == OSPI_OPTYPE_WRAP_CFG)) ||
            ((cmd_struct->operation_type == OSPI_OPTYPE_READ_CFG) || (cmd_struct->operation_type == OSPI_OPTYPE_COMMON_CFG))){
            /* wait till busy flag is reset */
              while(RESET != (OSPI_STAT(ospi_periph) & OSPI_FLAG_BUSY)){
              }

            /* configure the registers */
            ospi_config(ospi_periph, ospi_struct, cmd_struct);

            if(cmd_struct->data_mode == OSPI_DATA_NONE){
                /* when there is no data phase, the transfer start as soon as the configuration is done
                so wait until TC flag is set to go back in idle state */
              while(RESET == (OSPI_STAT(ospi_periph) & OSPI_FLAG_TC)){
              }

                OSPI_STATC(ospi_periph) = OSPI_STATC_TCC;
            }
        }
    }
}

/*!
    \brief      transmit data (this function is used only in indirect write mode)
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  pdata: pointer to data buffer
    \param[out] none
    \retval     none
*/ 
void ospi_transmit(uint32_t ospi_periph, uint8_t *pdata)
{ 
    uint32_t txcounter;
    uint32_t address;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0045U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(pdata)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0045U), ERR_PERIPH);
    } else
#endif
    {
        /* configure counters and size */
        txcounter = OSPI_DTLEN(ospi_periph) + 1U;
        address = (uint32_t)pdata;

        /* configure CTL register with functional mode as indirect write */
        OSPI_CTL(ospi_periph) = (OSPI_CTL(ospi_periph) & ~OSPI_CTL_FMOD) | OSPI_INDIRECT_WRITE;

        do{
            /* wait till fifo threshold flag is set to send data */
          while(RESET != (OSPI_STAT(ospi_periph) & OSPI_FLAG_FT)){
          }
            *((__IO uint8_t *)&OSPI_DATA(ospi_periph)) = *(uint8_t *)address;
            address++;
            txcounter--;
        }while(txcounter > 0U);

        /* wait till transfer complete flag is set to go back in idle state */
        while(RESET == (OSPI_STAT(ospi_periph) & OSPI_FLAG_TC)){
        }

        /* clear transfer complete flag */
        OSPI_STATC(ospi_periph) = OSPI_STATC_TCC;
    }
}

/*!
    \brief      receive data (this function is used only in indirect read mode)
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  pdata: pointer to data buffer
    \param[out] none
    \retval     none
*/
void ospi_receive(uint32_t ospi_periph, uint8_t *pdata)
{
    uint32_t rxcounter;
    uint32_t address;
    uint32_t addr_reg = OSPI_ADDR(ospi_periph);
    uint32_t ins_reg = OSPI_INS(ospi_periph);

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0046U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(pdata)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0046U), ERR_PERIPH);
    } else
#endif
    {
        /* configure counters and size */
        rxcounter = OSPI_DTLEN(ospi_periph) + 1U;
        address = (uint32_t)pdata;

        /* configure CTL register with functional mode as indirect read */
        OSPI_CTL(ospi_periph) = (OSPI_CTL(ospi_periph) & ~OSPI_CTL_FMOD) | OSPI_INDIRECT_READ;

        /* trigger the transfer by re-writing address or instruction register */
        if((OSPI_TCFG(ospi_periph) & OSPI_TCFG_ADDRMOD) != OSPI_ADDRESS_NONE){
            OSPI_ADDR(ospi_periph) = addr_reg;
        }else{
            OSPI_INS(ospi_periph) = ins_reg;
        }

        do{
            /* wait till fifo threshold or transfer complete flags are set to read received data */
          while(RESET == (OSPI_STAT(ospi_periph) & (OSPI_FLAG_FT | OSPI_FLAG_TC))){
          }
            
            *(uint8_t *)address = *((__IO uint8_t *)&OSPI_DATA(ospi_periph));
            address++;
            rxcounter--;
            
        }while(rxcounter > 0U);

        /* wait till transfer complete flag is set to go back in idle state */
        while(RESET == (OSPI_STAT(ospi_periph) & OSPI_FLAG_TC)){
        }

        /* clear transfer complete flag */
        OSPI_STATC(ospi_periph) = OSPI_STATC_TCC;
    }
}

/*!
    \brief      configure the OSPI automatic polling mode (this function is used only in automatic polling mode)
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
                               OSPI_MACRONIX_RAM_MODE
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                             OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
    \param[in]  autopl_cfg_struct: OSPI autopolling stuct members of the structure
                             and the member values are shown as below:
                  match: between 0 and 0xFFFFFFFF
                  mask: between 0 and 0xFFFFFFFF
                  interval: between 0 and 0xFFFF
                  match_mode: OSPI_MATCH_MODE_AND, OSPI_MATCH_MODE_OR
                  automatic_stop: OSPI_AUTOMATIC_STOP_MATCH
    \param[out] none
    \retval     none
*/
void ospi_autopolling_mode(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct, ospi_autopolling_struct *autopl_cfg_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(ospi_struct)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PARAM_POINTER);
    } else if(NOT_VALID_POINTER(autopl_cfg_struct)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PARAM_POINTER);
    }else if(NOT_OSPI_PSC(ospi_struct->prescaler)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_FIFO_THRESHOLD(ospi_struct->fifo_threshold)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_SAMPLE_SHIFTING(ospi_struct->sample_shift)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_MESZ(ospi_struct->device_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_CS_HIGH_TIME(ospi_struct->cs_hightime)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_MEMORY_TYPE(ospi_struct->memory_type)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_WRAP_SIZE(ospi_struct->wrap_size)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_DELAY_HOLD_CYCLE(ospi_struct->delay_hold_cycle)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_INTERVAL_NUM(autopl_cfg_struct->interval)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_MATCH_MODE(autopl_cfg_struct->match_mode)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_OSPI_AUTOMATIC_STOP_MATCH(autopl_cfg_struct->automatic_stop)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t addr_reg = OSPI_ADDR(ospi_periph);
        uint32_t ins_reg = OSPI_INS(ospi_periph);
     
        if(autopl_cfg_struct->automatic_stop == OSPI_AUTOMATIC_STOP_MATCH){
            /* wait till busy flag is reset */
          while(RESET != (OSPI_STAT(ospi_periph) & OSPI_FLAG_BUSY)){
          }

            /* configure registers */
            OSPI_STATMATCH(ospi_periph) = autopl_cfg_struct->match;
            OSPI_STATMK(ospi_periph) = autopl_cfg_struct->mask;
            OSPI_INTERVAL(ospi_periph) = autopl_cfg_struct->interval;
            OSPI_CTL(ospi_periph) = (OSPI_CTL(ospi_periph) & (~OSPI_CTL_SPMOD | ~OSPI_CTL_SPS | ~OSPI_CTL_FMOD)) | 
                                    (autopl_cfg_struct->match_mode | autopl_cfg_struct->automatic_stop | OSPI_STATUS_POLLING);

            /* trig the transfer by re-writing address or instruction register */
            if((OSPI_TCFG(ospi_periph) & OSPI_TCFG_ADDRMOD) != OSPI_ADDRESS_NONE){   
                OSPI_ADDR(ospi_periph) = addr_reg;
            }else{
                OSPI_INS(ospi_periph) = ins_reg;
            }

            /* wait till status match flag is set to go back in idle state */
            while(RESET == (OSPI_STAT(ospi_periph) & OSPI_FLAG_SM)){
            }

            /* clear status match flag */
            OSPI_STATC(ospi_periph) = OSPI_STATC_SMC;
        }
    }
}

/*!
    \brief      configure the registers for the regular command mode
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
                               OSPI_MACRONIX_RAM_MODE
                  wrap_size: OSPI_DIRECT, OSPI_WRAP_16BYTES, OSPI_WRAP_32BYTES
                             OSPI_WRAP_64BYTES, OSPI_WRAP_128BYTES
    \param[in]  cmd_struct: structure that contains the command configuration information
                            and the member values are shown as below:
                  operation_type: OSPI_OPTYPE_COMMON_CFG, OSPI_OPTYPE_READ_CFG
                                  OSPI_OPTYPE_WRITE_CFG, OSPI_OPTYPE_WRAP_CFG
                  instruction: between 0 and 0xFFFFFFFF
                  ins_mode: OSPI_INSTRUCTION_NONE, OSPI_INSTRUCTION_1_LINE, OSPI_INSTRUCTION_2_LINES
                            OSPI_INSTRUCTION_4_LINES, OSPI_INSTRUCTION_8_LINES
                  ins_size: OSPI_INSTRUCTION_8_BITS, OSPI_INSTRUCTION_16_BITS
                            OSPI_INSTRUCTION_24_BITS, OSPI_INSTRUCTION_32_BITS
                  address: between 0 and 0xFFFFFFFF
                  addr_mode: OSPI_ADDRESS_NONE, OSPI_ADDRESS_1_LINE, OSPI_ADDRESS_2_LINES
                             OSPI_ADDRESS_4_LINES, OSPI_ADDRESS_8_LINES
                  address_size: OSPI_ADDRESS_8_BITS, OSPI_ADDRESS_16_BITS
                                OSPI_ADDRESS_24_BITS, OSPI_ADDRESS_32_BITS
                  addr_dtr_mode: OSPI_ADDRDTR_MODE_DISABLE, OSPI_ADDTR_MODE_ENABLE
                  alter_bytes: between 0 and 0xFFFFFFFF
                  alter_bytes_mode: OSPI_ALTERNATE_BYTES_NONE, OSPI_ALTERNATE_BYTES_1_LINE
                                    OSPI_ALTERNATE_BYTES_2_LINES, OSPI_ALTERNATE_BYTES_4_LINES
                                    OSPI_ALTERNATE_BYTES_8_LINES
                  alter_bytes_size: OSPI_ALTERNATE_BYTES_8_BITS, OSPI_ALTERNATE_BYTES_16_BITS
                                    OSPI_ALTERNATE_BYTES_24_BITS, OSPI_ALTERNATE_BYTES_32_BITS
                  alter_bytes_dtr_mode: OSPI_ABDTR_MODE_DISABLE, OSPI_ABDTR_MODE_ENABLE
                  data_mode: OSPI_DATA_NONE, OSPI_DATA_1_LINE, OSPI_DATA_2_LINES
                             OSPI_DATA_4_LINES, OSPI_DATA_8_LINES
                  nbdata: between 1 and 0xFFFFFFFF
                  data_dtr_mode: OSPI_DADTR_MODE_DISABLE, OSPI_DADTR_MODE_ENABLE
                  dummy_cycles: OSPI_DUMYC_CYCLES_x (x = 0, 1, 2, ..., 30, 31)
    \param[out] none
    \retval     none
*/
static void ospi_config(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct, ospi_regular_cmd_struct* cmd_struct)
{
    __IO uint32_t *tcfg_reg, *timcfg_reg, *ins_reg, *alte_reg;
    
    /* re-initialize the value of the functional mode */
    OSPI_CTL(ospi_periph) &= ~OSPI_CTL_FMOD;

    if(cmd_struct->operation_type == OSPI_OPTYPE_WRITE_CFG){
        tcfg_reg = &(OSPI_WTCFG(ospi_periph));
        timcfg_reg = &(OSPI_WTIMCFG(ospi_periph));
        ins_reg  = &(OSPI_WINS(ospi_periph));
        alte_reg = &(OSPI_WALTE(ospi_periph));
    }else if(cmd_struct->operation_type == OSPI_OPTYPE_WRAP_CFG){
        tcfg_reg = &(OSPI_WPTCFG(ospi_periph));
        timcfg_reg = &(OSPI_WPTIMCFG(ospi_periph));
        ins_reg  = &(OSPI_WPINS(ospi_periph));
        alte_reg = &(OSPI_WPALTE(ospi_periph));
    }else{
        tcfg_reg = &(OSPI_TCFG(ospi_periph));
        timcfg_reg = &(OSPI_TIMCFG(ospi_periph));
        ins_reg  = &(OSPI_INS(ospi_periph));
        alte_reg = &(OSPI_ALTE(ospi_periph));
    }

    if(cmd_struct->alter_bytes_mode != OSPI_ALTERNATE_BYTES_NONE){
        /* configure the ALTE register with alternate bytes value */
        *alte_reg = cmd_struct->alter_bytes;

        /* configure the TCFG register with alternate bytes communication parameters */
        *tcfg_reg = (*tcfg_reg & ~(OSPI_TCFG_ALTEMOD | OSPI_TCFG_ABDTR | OSPI_TCFG_ALTESZ)) | 
                    (cmd_struct->alter_bytes_mode | cmd_struct->alter_bytes_dtr_mode | cmd_struct->alter_bytes_size);
    }        
    
    /* configure the TIMCFG register with the number of dummy cycles */
    *timcfg_reg = (*timcfg_reg & ~OSPI_TIMCFG_DUMYC) | cmd_struct->dummy_cycles;
 
    if(cmd_struct->data_mode != OSPI_DATA_NONE){
        if(cmd_struct->operation_type == OSPI_OPTYPE_COMMON_CFG){
            /* configure the DTLEN register with the number of data */
            OSPI_DTLEN(ospi_periph) = (cmd_struct->nbdata - 1U);
        }
    }
    if(cmd_struct->ins_mode != OSPI_INSTRUCTION_NONE){
        if(cmd_struct->addr_mode != OSPI_ADDRESS_NONE){
            if(cmd_struct->data_mode != OSPI_DATA_NONE){
                /* command with instruction, address and data */
                /* configure the TCFG register with all communication parameters */
                *tcfg_reg &= ~(OSPI_TCFG_IMOD | OSPI_TCFG_INSSZ | 
                            OSPI_TCFG_ADDRMOD | OSPI_TCFG_ADDRDTR | OSPI_TCFG_ADDRSZ |
                            OSPI_TCFG_DATAMOD | OSPI_TCFG_DADTR);
                
                *tcfg_reg |= cmd_struct->ins_mode | cmd_struct->ins_size |
                            cmd_struct->addr_mode | cmd_struct->addr_dtr_mode | cmd_struct->addr_size |
                            cmd_struct->data_mode | cmd_struct->data_dtr_mode;
            }else{
                /* command with instruction and address */
                /* configure the TCFG register with all communication parameters */
                *tcfg_reg &= ~(OSPI_TCFG_IMOD | OSPI_TCFG_INSSZ | 
                            OSPI_TCFG_ADDRMOD | OSPI_TCFG_ADDRDTR | OSPI_TCFG_ADDRSZ |
                            OSPI_TCFG_DATAMOD | OSPI_TCFG_DADTR);

                *tcfg_reg |= cmd_struct->ins_mode | cmd_struct->ins_size |
                            cmd_struct->addr_mode | cmd_struct->addr_dtr_mode | cmd_struct->addr_size;

                /* the DHQC bit is linked with DDTR bit which should be activated */
                if((ospi_struct->delay_hold_cycle == OSPI_DELAY_HOLD_QUARTER_CYCLE) ){
                    *tcfg_reg = (*tcfg_reg & ~OSPI_DADTR_MODE_ENABLE) | OSPI_DADTR_MODE_ENABLE;
                }
            }

            /* configure the INS register with the instruction value */
            *ins_reg = cmd_struct->instruction;

            /* configure the ADDR register with the address value */
            OSPI_ADDR(ospi_periph) = cmd_struct->address;
        }else{
            if(cmd_struct->data_mode != OSPI_DATA_NONE){
                /* command with instruction and data */
                /* configure the TCFG register with all communication parameters */
                *tcfg_reg &= ~(OSPI_TCFG_IMOD | OSPI_TCFG_INSSZ | 
                            OSPI_TCFG_DATAMOD | OSPI_TCFG_DADTR);

                *tcfg_reg = cmd_struct->ins_mode | cmd_struct->ins_size |
                            cmd_struct->data_mode | cmd_struct->data_dtr_mode;
            }else{
                /* command with only instruction */
                /* configure the TCFG register with all communication parameters */
                *tcfg_reg &= ~(OSPI_TCFG_IMOD | OSPI_TCFG_INSSZ);
                
                *tcfg_reg = cmd_struct->ins_mode | cmd_struct->ins_size;

                /* the DEHQC bit is linked with DDTR bit which should be activated */
                if((ospi_struct->delay_hold_cycle == OSPI_DELAY_HOLD_QUARTER_CYCLE)){
                    *tcfg_reg = (*tcfg_reg & ~OSPI_DADTR_MODE_ENABLE) | OSPI_DADTR_MODE_ENABLE;
                }
            }

            /* configure the INS register with the instruction value */
            *ins_reg = cmd_struct->instruction;           
        }
    }else{
        if(cmd_struct->addr_mode != OSPI_ADDRESS_NONE){
            if(cmd_struct->data_mode != OSPI_DATA_NONE){
                /* command with address and data */

                /* configure the TCFG register with all communication parameters */
                *tcfg_reg &= ~(OSPI_TCFG_ADDRMOD | OSPI_TCFG_ADDRDTR | OSPI_TCFG_ADDRSZ |
                               OSPI_TCFG_DATAMOD | OSPI_TCFG_DADTR);
                
                *tcfg_reg = cmd_struct->addr_mode | cmd_struct->addr_dtr_mode | cmd_struct->addr_size |
                            cmd_struct->data_mode | cmd_struct->data_dtr_mode;              
            }else{
                /* command with only address */

                /* configure the TCFG register with all communication parameters */
                *tcfg_reg &= ~(OSPI_TCFG_ADDRMOD | OSPI_TCFG_ADDRDTR | OSPI_TCFG_ADDRSZ);
                
                *tcfg_reg = cmd_struct->addr_mode | cmd_struct->addr_dtr_mode | cmd_struct->addr_size;                 
            }

            /* configure the ADDR register with the instruction value */
            OSPI_ADDR(ospi_periph) = cmd_struct->address;
        }
    }
}

/*!
    \brief      enable OSPI interrupt 
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  interrupt: OSPI interrupt
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INT_TERR: transfer error interrupt 
      \arg        OSPI_INT_TC: transfer complete interrupt
      \arg        OSPI_INT_FT: fifo threshold interrupt
      \arg        OSPI_INT_SM: status match interrupt
    \param[out] none
    \retval     none
*/
void ospi_interrupt_enable(uint32_t ospi_periph, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0048U), ERR_PERIPH);
    } else if(NOT_OSPI_INTERRUPT(interrupt)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0048U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_CTL(ospi_periph) |= interrupt;
    }
}

/*!
    \brief      disable OSPI interrupt 
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  interrupt: OSPI interrupt
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INT_TERR: transfer error interrupt 
      \arg        OSPI_INT_TC: transfer complete interrupt
      \arg        OSPI_INT_FT: fifo threshold interrupt
      \arg        OSPI_INT_SM: status match interrupt
    \param[out] none
    \retval     none
*/
void ospi_interrupt_disable(uint32_t ospi_periph, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0049U), ERR_PERIPH);
    } else if(NOT_OSPI_INTERRUPT(interrupt)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x0049U), ERR_PERIPH);
    } else
#endif
    {
        OSPI_CTL(ospi_periph) &= ~interrupt;
    }
}

/*!  
    \brief      get OSPI fifo level
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] none
    \retval     6-bit fifo level
*/
uint32_t ospi_fifo_level_get(uint32_t ospi_periph)
{
    uint32_t fl = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x004AU), ERR_PERIPH);
    } else
#endif
    {
        fl = (OSPI_STAT(ospi_periph) & (uint32_t)OSPI_STAT_FL) >> 8U;
    }
    return fl;
}

/*!
    \brief      get OSPI flag status
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  flag: OSPI flag status
                only one parameter can be selected which is shown as below:
      \arg        OSPI_FLAG_TERR: transfer error flag
      \arg        OSPI_FLAG_TC: transfer complete flag
      \arg        OSPI_FLAG_FT: fifo threshold flag
      \arg        OSPI_FLAG_SM: status match flag
      \arg        OSPI_FLAG_BUSY: busy flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ospi_flag_get(uint32_t ospi_periph, uint32_t flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x004BU), ERR_PERIPH);
    } else if(NOT_OSPI_FLAG(flag)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x004BU), ERR_PERIPH);
    } else
#endif
    {
        if(RESET != (OSPI_STAT(ospi_periph) & flag)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear OSPI flag status
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  flag: OSPI flag status
                only one parameter can be selected which is shown as below:
      \arg        OSPI_FLAG_TERR: transfer error flag
      \arg        OSPI_FLAG_TC: transfer complete flag
      \arg        OSPI_FLAG_SM: status match flag
    \param[out] none
    \retval     none
*/
void ospi_flag_clear(uint32_t ospi_periph, uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x004CU), ERR_PERIPH);
    } else if(NOT_OSPI_FLAG(flag)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x004CU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_STATC(ospi_periph) = (uint32_t)flag;
    }
}

/*!
    \brief      get OSPI interrupt flag status
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  int_flag: OSPI interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INT_FLAG_TERR: transfer error interrupt flag
      \arg        OSPI_INT_FLAG_TC: transfer complete interrupt flag
      \arg        OSPI_INT_FLAG_FT: fifo threshold interrupt flag
      \arg        OSPI_INT_FLAG_SM: status match interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ospi_interrupt_flag_get(uint32_t ospi_periph, ospi_interrupt_flag_enum int_flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x004DU), ERR_PERIPH);
    } else
#endif
    {
        /* get the status of interrupt enable bit */
        ret1 = (OSPI_REG_VAL(ospi_periph, int_flag) & BIT(OSPI_BIT_POS(int_flag)));
        /* get the status of interrupt flag */
        ret2 = (OSPI_REG_VAL2(ospi_periph, int_flag) & BIT(OSPI_BIT_POS2(int_flag)));
        if(ret1 && ret2) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear OSPI interrupt flag status
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[in]  int_flag: OSPI interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        OSPI_INT_FLAG_TERR: transfer error interrupt flag
      \arg        OSPI_INT_FLAG_TC: transfer complete interrupt flag
      \arg        OSPI_INT_FLAG_SM: status match interrupt flag
    \param[out] none
    \retval     none
*/
void ospi_interrupt_flag_clear(uint32_t ospi_periph, ospi_interrupt_flag_enum int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OSPI_PERIPH(ospi_periph)) {
        fw_debug_report_err(OSPI_MODULE_ID, API_ID(0x004EU), ERR_PERIPH);
    } else
#endif
    {
        OSPI_STATC(ospi_periph) |= BIT(OSPI_BIT_POS2(int_flag));
    }
}
