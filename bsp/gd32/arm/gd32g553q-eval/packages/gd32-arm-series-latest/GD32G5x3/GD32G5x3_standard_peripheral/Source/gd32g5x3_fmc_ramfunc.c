/*!
    \file    gd32g5x3_fmc_ramfunc.c
    \brief   FMC RAMFUNC driver

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

#include "gd32g5x3_fmc_ramfunc.h"

/*!
    \brief      flash enter power down mode when MCU run mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
__attribute__((section("RAMCODE"))) void fmc_pd_mode_enter(void)
{
    uint32_t ws;
    
    /* write the FMC RUN_MDSEL unlock key */
    FMC_RUNKEY = RUN_MDSEL_UNLOCK_KEY0;
    FMC_RUNKEY = RUN_MDSEL_UNLOCK_KEY1;

    ws = FMC_WS;

    /* set the RUN_MDSEL bit */
    ws |= FMC_WS_RUN_MDSEL;

    FMC_WS = ws;
}

/*!
    \brief      flash exit power down mode when MCU run mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
__attribute__((section("RAMCODE"))) void fmc_pd_mode_exit(void)
{
    uint32_t ws;
    
    /* write the FMC RUN_MDSEL unlock key */
    FMC_RUNKEY = RUN_MDSEL_UNLOCK_KEY0;
    FMC_RUNKEY = RUN_MDSEL_UNLOCK_KEY1;

    ws = FMC_WS;

    /* clear the RUN_MDSEL bit */
    ws &= ~FMC_WS_RUN_MDSEL; 

    FMC_WS = ws;
}

/*!
    \brief      configure the option byte bank mode
    \param[in]  bank_mode: bank mode
                only one parameter can be selected which is shown as below:
      \arg        OB_SINGLE_BANK_MODE: single-bank mode
      \arg        OB_DUAL_BANK_MODE: dual-bank mode
    \param[out] none
    \retval     none
*/
__attribute__((section("RAMCODE"))) ErrStatus ob_bank_mode_config(uint32_t bank_mode)
{
    uint32_t start_area;
    uint32_t end_area;
    uint32_t timeout = FMC_TIMEOUT_COUNT;

    /* DCRP area should be disabled when configure bank mode */

    start_area = (FMC_DCRP_SADDR0 & FMC_DCRP_SADDR0_DCRP0_SADDR) >> DCRP_SADDR_DCRP_SADDR_OFFSET;
    end_area = (FMC_DCRP_EADDR0 & FMC_DCRP_EADDR0_DCRP0_EADDR) >> DCRP_EADDR_DCRP_EADDR_OFFSET;    
    /* DCRP0 area is enabled */
    if(start_area <= end_area){
        return ERROR;
    }

    start_area = (FMC_DCRP_SADDR1 & FMC_DCRP_SADDR1_DCRP1_SADDR) >> DCRP_SADDR_DCRP_SADDR_OFFSET;
    end_area = (FMC_DCRP_EADDR1 & FMC_DCRP_EADDR1_DCRP1_EADDR) >> DCRP_EADDR_DCRP_EADDR_OFFSET;
    /* DCRP1 area is enabled */
    if(start_area <= end_area){
        return ERROR;
    }

    /* disable FMC prefetch */
    FMC_WS &= ~FMC_WS_PFEN;

    /* disable icache */
    if(FMC_WS & FMC_WS_ICEN){
        FMC_WS &= ~FMC_WS_ICEN;
        FMC_WS |= FMC_WS_ICRST;
    }

    /* disable dcache */
    if(FMC_WS & FMC_WS_DCEN){
        FMC_WS &= ~FMC_WS_DCEN;
        FMC_WS |= FMC_WS_DCRST;
    }

    /* disable BK0WP_AREA0 if it is enabled */
    start_area = (FMC_BK0WP0 & FMC_BK0WP0_BK0WP0_SADDR) >> BKWP_BKWP_SADDR_OFFSET;
    end_area = (FMC_BK0WP0 & FMC_BK0WP0_BK0WP0_EADDR) >> BKWP_BKWP_EADDR_OFFSET; 
    if(start_area <= end_area){
        FMC_BK0WP0 &= ~(FMC_BK0WP0_BK0WP0_SADDR|FMC_BK0WP0_BK0WP0_EADDR);
        FMC_BK0WP0 |= FMC_BK0WP0_BK0WP0_SADDR;
    }

    /* disable BK0WP_AREA1 if it is enabled */
    start_area = (FMC_BK0WP1 & FMC_BK0WP1_BK0WP1_SADDR) >> BKWP_BKWP_SADDR_OFFSET;
    end_area = (FMC_BK0WP1 & FMC_BK0WP1_BK0WP1_EADDR) >> BKWP_BKWP_EADDR_OFFSET;
    if(start_area <= end_area){
        FMC_BK0WP1 &= ~(FMC_BK0WP1_BK0WP1_SADDR|FMC_BK0WP1_BK0WP1_EADDR);
        FMC_BK0WP1 |= FMC_BK0WP1_BK0WP1_SADDR;
    }

    /* disable BK1WP_AREA0 if it is enabled */
    start_area = (FMC_BK1WP0 & FMC_BK1WP0_BK1WP0_SADDR) >> BKWP_BKWP_SADDR_OFFSET;
    end_area = (FMC_BK1WP0 & FMC_BK1WP0_BK1WP0_EADDR) >> BKWP_BKWP_EADDR_OFFSET; 
    if(start_area <= end_area){
        FMC_BK1WP0 &= ~(FMC_BK1WP0_BK1WP0_SADDR|FMC_BK1WP0_BK1WP0_EADDR);
        FMC_BK1WP0 |= FMC_BK1WP0_BK1WP0_SADDR;
    }

    /* disable BK1WP_AREA1 if it is enabled */
    start_area = (FMC_BK1WP1 & FMC_BK1WP1_BK1WP1_SADDR) >> BKWP_BKWP_SADDR_OFFSET;
    end_area = (FMC_BK1WP1 & FMC_BK1WP1_BK1WP1_EADDR) >> BKWP_BKWP_EADDR_OFFSET; 
    if(start_area <= end_area){
        FMC_BK1WP1 &= ~(FMC_BK1WP1_BK1WP1_SADDR|FMC_BK1WP1_BK1WP1_EADDR);
        FMC_BK1WP1 |= FMC_BK1WP1_BK1WP1_SADDR;
    }

    /* configure option byte bank mode */
    FMC_OBCTL &= ~FMC_OBCTL_DBS;
    FMC_OBCTL |= bank_mode;

    FMC_CTL |= FMC_CTL_OBSTART;

    do{
        timeout--;
    }while((RESET != (FMC_STAT & FMC_STAT_BUSY)) && (0x00U != timeout));

    /* return the result */
    if(0x00U != timeout){
        return SUCCESS;
    }
    else {
        return ERROR;
    }


}
