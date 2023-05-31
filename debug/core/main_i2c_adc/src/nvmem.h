/*****************************************************************************
*
*  nvmem.h  - CC3000 Host Driver Implementation.
*  Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/
#ifndef __NVRAM_H__
#define __NVRAM_H__

#include "cc3000_common.h"


//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef  __cplusplus
extern "C" {
#endif


//*****************************************************************************
//
//! \addtogroup nvmem_api
//! @{
//
//*****************************************************************************

/****************************************************************************
**
**	Definitions for File IDs
**	
****************************************************************************/
/* NVMEM file ID */
#define NVMEM_NVS_FILEID 							(0)
#define NVMEM_NVS_SHADOW_FILEID 					(1)
#define NVMEM_WLAN_CONFIG_FILEID 					(2)
#define NVMEM_WLAN_CONFIG_SHADOW_FILEID 			(3)
#define NVMEM_WLAN_DRIVER_SP_FILEID					(4)
#define NVMEM_WLAN_FW_SP_FILEID						(5)
#define NVMEM_MAC_FILEID 							(6)
#define NVMEM_FRONTEND_VARS_FILEID 					(7)
#define NVMEM_IP_CONFIG_FILEID 						(8)
#define NVMEM_IP_CONFIG_SHADOW_FILEID 				(9)
#define NVMEM_BOOTLOADER_SP_FILEID 					(10)
#define NVMEM_RM_FILEID			 					(11)

/*  max entry in order to invalid nvmem              */
#define NVMEM_MAX_ENTRY                              (14)


/*****************************************************************************
 * \brief Read data from nvmem
 *
 * Reads data from the file referred by the ulFileId parameter. 
 * Reads data from file ulOffset till len. Err if the file can't
 * be used, is invalid, or if the read is out of bounds. 
 *
 *
 * \param[in] ulFileId   nvmem file id:\n
 * NVMEM_NVS_FILEID, NVMEM_NVS_SHADOW_FILEID,
 * NVMEM_WLAN_CONFIG_FILEID, NVMEM_WLAN_CONFIG_SHADOW_FILEID,
 * NVMEM_WLAN_DRIVER_SP_FILEID, NVMEM_WLAN_FW_SP_FILEID,
 * NVMEM_MAC_FILEID, NVMEM_FRONTEND_VARS_FILEID,
 * NVMEM_IP_CONFIG_FILEID, NVMEM_IP_CONFIG_SHADOW_FILEID,
 * NVMEM_BOOTLOADER_SP_FILEID or NVMEM_RM_FILEID.
 * \param[in] ulLength   number of bytes to read  
 * \param[in] ulOffset   ulOffset in file from where to read  
 * \param[out] buff    output buffer pointer
 *
 * \return	    number of bytes read.
 *
 * \sa
 * \note
 * \warning
 *
 *****************************************************************************/

extern signed long nvmem_read(unsigned long file_id, unsigned long length, unsigned long offset, unsigned char *buff);


/*****************************************************************************
 * \brief Write data to nvmem.
 *  
 * writes data to file referred by the ulFileId parameter. 
 * Writes data to file  ulOffset till ulLength. The file id will be 
 * marked invalid till the write is done. The file entry doesn't
 * need to be valid - only allocated.
 *  
 * \param[in] ulFileId   nvmem file id:\n
 * NVMEM_NVS_FILEID, NVMEM_NVS_SHADOW_FILEID,
 * NVMEM_WLAN_CONFIG_FILEID, NVMEM_WLAN_CONFIG_SHADOW_FILEID,
 * NVMEM_WLAN_DRIVER_SP_FILEID, NVMEM_WLAN_FW_SP_FILEID,
 * NVMEM_MAC_FILEID, NVMEM_FRONTEND_VARS_FILEID,
 * NVMEM_IP_CONFIG_FILEID, NVMEM_IP_CONFIG_SHADOW_FILEID,
 * NVMEM_BOOTLOADER_SP_FILEID or NVMEM_RM_FILEID.
 * \param[in] ulLength    number of bytes to write   
 * \param[in] ulEntryOffset  offset in file to start write operation from    
 * \param[in] buff      data to write 
 *
 * \return	  on succes 0, error otherwise.
 *
 * \sa
 * \note
 * \warning
 *
 *****************************************************************************/
extern signed long nvmem_write(unsigned long file_id, unsigned long length, unsigned long entry_offset, 
            unsigned char *buff);



//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


#ifdef  __cplusplus
}
#endif // __cplusplus

#endif // __NVRAM_H__
