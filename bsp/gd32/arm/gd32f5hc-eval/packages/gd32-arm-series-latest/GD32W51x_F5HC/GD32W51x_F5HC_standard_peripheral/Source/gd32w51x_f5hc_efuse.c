/*!
    \file    gd32w51x_f5hc_efuse.c
    \brief   EFUSE driver

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

#include "gd32w51x_f5hc_efuse.h"

/*!
    \brief      read EFUSE value (API_ID: 0x0001U)
    \param[in]  ef_addr: EFUSE address
      \arg        0~0xf8
    \param[in]  size: size of EFUSE
      \arg        1~0x40
    \param[out] buf: the buffer for storing read-out EFUSE register value
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_read(uint32_t ef_addr, uint32_t size, uint32_t buf[])
{
    uint32_t i = 0U;
    uint32_t timeout = 0xFFFFU;
    uint32_t reg_addr = 0U;
    uint32_t number = size / 4U;
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(buf)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0001U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(0U == number){
            number = 1U;
        }

        /* assert EFUSE address and size parameter */
        if((RESERVED_ADDR < ef_addr) || (EFUSE_MAX_SIZE < size)){
            status = ERROR;
        }else{
            /* get the register address corresponding to EFUSE */
            if(0x4U > ef_addr){
                reg_addr = (uint32_t)(EFUSE + 0x08U + (ef_addr * 4U));
            }else{
                /* when EFUSE address is greater than 4, it must be an integral multiple of 4 */
                if(0U == (ef_addr % 4U)){
                    reg_addr = (uint32_t)(EFUSE + 0x14U + ef_addr);
                }else{
                    status = ERROR;
                }
            }

            if(SUCCESS == status){
                /* EFUSE read operation */
                EFUSE_CS &= (~EFUSE_CS_EFRW);
                if((RF_DATA_ADDR <= ef_addr) && (USER_DATA_ADDR > ef_addr)){
                    for(i = 0U; i < size; i++){
                        timeout = 0xFFFFU;
                        efuse_flag_clear(EFUSE_RDIC);
                        
                        EFUSE_ADDR = (uint32_t)((1U << 8U) | ((uint32_t)ef_addr + i));

                        /* start read EFUSE operation */
                        EFUSE_CS |= EFUSE_CS_EFSTR;

                        /* wait for the operation to complete */
                        do{
                            timeout--;
                        }while((RESET == efuse_flag_get(EFUSE_RDIF)) && (0x00U != timeout));
                        if(0x00U == timeout){
                            status = ERROR;
                            break;
                        }
                    }
                }else{
                    efuse_flag_clear(EFUSE_RDIC);
                    
                    /* write EFUSE address and size */
                    EFUSE_ADDR = (uint32_t)((size << 8U) | ef_addr);

                    /* start read EFUSE operation */
                    EFUSE_CS |= EFUSE_CS_EFSTR; 

                    /* wait for the operation to complete */
                    do{
                        timeout--;
                    }while((RESET == efuse_flag_get(EFUSE_RDIF)) && (0x00U != timeout));
                    if(0x00U == timeout){
                        status = ERROR;
                    }
                }

                if(SUCCESS == status){
                    /* read EFUSE */
                    for(i = 0U; i < number; i++){
                        buf[i] = REG32(reg_addr + (4U * i));
                    }
                }
            }
        }
    }

    return status;
}

/*!
    \brief      write EFUSE (API_ID: 0x0002U)
    \param[in]  ef_addr: EFUSE address, when ef_addr is greater than 4, the ef_addr must be an integral multiple of 4
      \arg        0~0xf8
    \param[in]  size: size of EFUSE(byte)
      \arg        1~0x40
    \param[in]  buf: the buffer of data written to EFUSE
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_write(uint32_t ef_addr, uint32_t size, uint32_t buf[])
{
    uint32_t i = 0U;
    uint32_t timeout = 0xFFFFU;
    uint32_t reg_addr = 0U;
    uint32_t number = size / 4U;
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(buf)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(0U == number){
            number = 1U;
        }

        /* assert EFUSE address and size parameter */
        if((RESERVED_ADDR < ef_addr) || (EFUSE_MAX_SIZE < size)){
            status = ERROR;
        }

        /* PUID and HUK are not modifiable */
        if((MCU_UID_ADDR < ef_addr) && (RF_DATA_ADDR > ef_addr)){
            status = ERROR;
        }

        if(SUCCESS == status){
            /* get the register address corresponding to EFUSE */
            if(0x4U > ef_addr){
                reg_addr = (uint32_t)(EFUSE + 0x08U + (ef_addr * 4U));
            }else{
                /* when EFUSE address is greater than 4, it must be an integral multiple of 4 */
                if(0U != (ef_addr % 4U)){
                    status = ERROR;
                }else{
                    reg_addr = (uint32_t)(EFUSE + 0x14U + ef_addr);
                }
            }
        }

        if(SUCCESS == status){
#if defined (GD32W515)
            /* EFUSE power on */
            RCU_CFG1 |= RCU_CFG1_BGPU;
#endif
            /* EFUSE write operation */
            EFUSE_CS |= EFUSE_CS_EFRW;

            /* RF data can only be written in byte */
            if((RF_DATA_ADDR <= ef_addr) && (USER_DATA_ADDR > ef_addr)){
                for(i = 0U ; i < size; i++){
                    timeout = 0xFFFFU;
                    efuse_flag_clear(EFUSE_PGIC);
                    
                    EFUSE_ADDR = (uint32_t)((1U << 8U) | (ef_addr + i));
                    REG32(reg_addr + ((i / 4U) * 4U)) = buf[i / 4U];
                    /* start write EFUSE operation */
                    EFUSE_CS |= EFUSE_CS_EFSTR;

                    /* wait for the operation to complete */
                    do{
                        timeout--;
                    }while((RESET == efuse_flag_get(EFUSE_PGIF)) && (0x00U != timeout));
                    if(0x00U == timeout){
                        status = ERROR;
                        break;
                    }
                }
            }else{
                efuse_flag_clear(EFUSE_PGIC);
                
                /* write EFUSE address and size */
                EFUSE_ADDR = (uint32_t)((size << 8U) | ef_addr);

                /* write EFUSE */
                for(i = 0U; i < number; i++){
                    REG32(reg_addr + (4U * i)) = buf[i];
                }

                /* start write EFUSE operation */
                EFUSE_CS |= EFUSE_CS_EFSTR;

                /* wait for the operation to complete */
                do{
                    timeout--;
                }while((RESET == efuse_flag_get(EFUSE_PGIF)) && (0x00U != timeout));
                if(0x00U == timeout){
                    status = ERROR;
                }
            }
        }

        if(SUCCESS == status){
            /* clear EFUSE write operation flag */
            EFUSE_CS &= (~EFUSE_CS_EFRW);
#if defined (GD32W515)
            /* EFUSE power off */
            RCU_CFG1 &= (~RCU_CFG1_BGPU);
#endif
        }
    }

    return status;
}

/*!
    \brief      boot configuration (API_ID: 0x0003U)
    \param[in]  size: size of data(byte)
      \arg        the size must be 1
    \param[in]  bt_value: the value of boot configuration
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_boot_config(uint32_t size, uint8_t bt_value[])
{
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(bt_value)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(1U != size){
            status = ERROR;
        } else {
            status = efuse_write(EFUSE_CTL_ADDR, size, (uint32_t *)bt_value);
        }
    }

    return status;
}

/*!
    \brief      trustzone control configuration (API_ID: 0x0004U)
    \param[in]  size: size of data(byte)
      \arg        the size must be 1
    \param[in]  tz_ctl: trustzone control value
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_tz_control_config(uint32_t size, uint8_t tz_ctl[])
{
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(tz_ctl)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(1U != size){
            status = ERROR;
        } else {
            status = efuse_write(TZ_CTL_ADDR, size, (uint32_t *)tz_ctl);
        }
    }

    return status;
}

/*!
    \brief      flash protection configuration (API_ID: 0x0005U)
    \param[in]  size: size of data(byte)
      \arg        the size must be 1
    \param[in]  fp_value: flash protection value
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_fp_config(uint32_t size, uint8_t fp_value[])
{
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(fp_value)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0005U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(1U != size){
            status = ERROR;
        } else {
            status = efuse_write(FP_ADDR, size, (uint32_t *)fp_value);
        }
    }

    return status;
}

/*!
    \brief      write AES key (API_ID: 0x0006U)
    \param[in]  size: size of data(byte)
      \arg        the size must be 16
    \param[in]  buf: the buffer of data written to efuse
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_aes_key_write(uint32_t size, uint8_t buf[])
{
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(buf)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0006U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(16U != size){
            status = ERROR;
        } else {
            status = efuse_write(AES_KEY_ADDR, size, (uint32_t *)buf);
        }
    }

    return status;
}

/*!
    \brief      write ROTPK key (API_ID: 0x0007U)
    \param[in]  size: size of data(byte)
      \arg        the size must be 32
    \param[in]  buf: the buffer of data written to efuse
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_rotpk_key_write(uint32_t size, uint8_t buf[])
{
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(buf)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(32U != size){
            status = ERROR;
        } else {
            status = efuse_write(ROTPK_ADDR, size, (uint32_t *)buf);
        }
    }

    return status;
}

/*!
    \brief      write debug password (API_ID: 0x0008U)
    \param[in]  size: size of data(byte)
      \arg        the size must be 8
    \param[in]  buf: the buffer of data written to efuse
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_dp_write(uint32_t size, uint8_t buf[])
{
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(buf)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0008U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(8U != size){
            status = ERROR;
        } else {
            status = efuse_write(DP_ADDR, size, (uint32_t *)buf);
        }
    }

    return status;
}

/*!
    \brief      write IAK key (API_ID: 0x0009U)
    \param[in]  size: size of data(byte)
      \arg        the size must be 64
    \param[in]  buf: the buffer of data written to efuse
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_iak_write(uint32_t size, uint8_t buf[])
{
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(buf)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x0009U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(64U != size){
            status = ERROR;
        } else {
            status = efuse_write(IAK_ADDR, size, (uint32_t *)buf);
        }

    }

    return status;
}

/*!
    \brief      write user data (API_ID: 0x000AU)
    \param[in]  size: size of data(byte)
      \arg        the size must be 32
    \param[in]  buf: the buffer of data written to efuse
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus efuse_user_data_write(uint32_t size, uint8_t buf[])
{
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(buf)) {
        fw_debug_report_err(EFUSE_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else
#endif
    {
        if(32U != size){
            status = ERROR;
        } else {
            status = efuse_write(USER_DATA_ADDR, size, (uint32_t *)buf);
        }
    }

    return status;
}

/*!
    \brief      enable trustzone by software (API_ID: 0x000BU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void efuse_software_trustzone_enable(void)
{
    EFUSE_PRE_TZEN |= EFUSE_PRE_TZEN_STZEN;
}

/*!
    \brief      disable trustzone by software (API_ID: 0x000CU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void efuse_software_trustzone_disable(void)
{
    EFUSE_PRE_TZEN &= (~EFUSE_PRE_TZEN_STZEN);
}

/*!
    \brief      get boot address information (API_ID: 0x000DU)
    \param[in]  tz: specifies the current trustzone state
    \param[out] none
    \retval     current boot address
*/
uint32_t efuse_boot_address_get(efuse_tz_enum tz)
{
    uint32_t boot_address;

    if(EFUSE_TZ == tz){
        boot_address = EFUSE_TZ_BOOT_ADDR;
    }else{
        boot_address = EFUSE_NTZ_BOOT_ADDR;
    }

    return boot_address;
}

/*!
    \brief      get EFUSE flag is set or not (API_ID: 0x000EU)
    \param[in]  efuse_flag: specifies to get a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_PGIF: programming operation completion flag
      \arg        EFUSE_RDIF: read operation completion flag
      \arg        EFUSE_OBERIF: overstep boundary error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus efuse_flag_get(efuse_flag_enum efuse_flag)
{
    FlagStatus flag_status = RESET;

    if(EFUSE_CS & (uint32_t)efuse_flag){
        flag_status = SET;
    }
    return flag_status;
}

/*!
    \brief      clear EFUSE pending flag (API_ID: 0x000FU)
    \param[in]  efuse_cflag: specifies to clear a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_PGIC: clear programming operation completion flag
      \arg        EFUSE_RDIC: clear read operation completion flag
      \arg        EFUSE_OBERIC: clear overstep boundary error flag
    \param[out] none
    \retval     none
*/
void efuse_flag_clear(efuse_clear_flag_enum efuse_cflag)
{
    EFUSE_CS |= (uint32_t)efuse_cflag;
}

/*!
    \brief      enable EFUSE interrupt (API_ID: 0x0010U)
    \param[in]  source: specifies an interrupt to enbale
                one or more parameters can be selected which are shown as below:
      \arg        EFUSE_INTEN_PG: programming operation completion interrupt
      \arg        EFUSE_INTEN_RD: read operation completion interrupt
      \arg        EFUSE_INTEN_OBER: overstep boundary error interrupt
    \param[out] none
    \retval     none
*/
void efuse_interrupt_enable(efuse_int_enum source)
{
    EFUSE_CS |= (uint32_t)source;
}

/*!
    \brief      disable EFUSE interrupt (API_ID: 0x0011U)
    \param[in]  source: specifies an interrupt to disbale
                one or more parameters can be selected which are shown as below:
      \arg        EFUSE_INTEN_PG: programming operation completion interrupt
      \arg        EFUSE_INTEN_RD: read operation completion interrupt
      \arg        EFUSE_INTEN_OBER: overstep boundary error interrupt
    \param[out] none
    \retval     none
*/
void efuse_interrupt_disable(efuse_int_enum source)
{
    EFUSE_CS &= (~(uint32_t)source);
}

/*!
    \brief      get EFUSE interrupt flag is set or not (API_ID: 0x0012U)
    \param[in]  int_flag: specifies to get a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_INT_PGIF: programming operation completion interrupt flag
      \arg        EFUSE_INT_RDIF: read operation completion interrupt flag
      \arg        EFUSE_INT_OBERIF: overstep boundary error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus efuse_interrupt_flag_get(efuse_int_flag_enum int_flag)
{
    FlagStatus ret = RESET;
    if(EFUSE_CS & (uint32_t)int_flag){
        ret = SET;
    }else{
        ret = RESET;
    }
    return ret;
}

/*!
    \brief      clear EFUSE pending interrupt flag (API_ID: 0x0013U)
    \param[in]  int_cflag: specifies to clear a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_INT_PGIC: clear programming operation completion interrupt flag
      \arg        EFUSE_INT_RDIC: clear operation completion interrupt flag
      \arg        EFUSE_INT_OBERIC: clear overstep boundary error interrupt flag
    \param[out] none
    \retval     none
*/
void efuse_interrupt_flag_clear(efuse_clear_int_flag_enum int_cflag)
{
    EFUSE_CS |= ((uint32_t)int_cflag);
}
