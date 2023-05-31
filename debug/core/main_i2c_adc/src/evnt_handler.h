/*****************************************************************************
*
*  evnt_handler.h  - CC3000 Host Driver Implementation.
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
#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__
#include "hci.h"
#include "socket.h"

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
// Prototypes for the APIs.
//
//*****************************************************************************
extern unsigned char *hci_event_handler(void *pRetParams, unsigned char *from, unsigned char *fromlen);
extern long hci_unsol_event_handler(hci_evnt_hdr_t *event_hdr);
extern long hci_unsolicited_event_handler(void);

#define M_BSD_RESP_PARAMS_OFFSET(hci_event_hdr)(bsd_resp_params_t *)((char *)(hci_event_hdr) + sizeof(hci_evnt_hdr_t))

#define SOCKET_STATUS_ACTIVE       0
#define SOCKET_STATUS_INACTIVE     1
/* Init socket_active_status = 'all ones': init all sockets with SOCKET_STATUS_INACTIVE.
   Will be changed by 'set_socket_active_status' upon 'connect' and 'accept' calls */
#define SOCKET_STATUS_INIT_VAL  0xFFFF
#define M_IS_VALID_SD(sd) ((0 <= (sd)) && ((sd) <= 7))
#define M_IS_VALID_STATUS(status) (((status) == SOCKET_STATUS_ACTIVE)||((status) == SOCKET_STATUS_INACTIVE))

extern unsigned long socket_active_status;

extern void set_socket_active_status(long Sd, long Status);
extern long get_socket_active_status(long Sd);


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//packed is used for preventing padding before sending the structure over the SPI                       ///
//for every IDE, exist different syntax:          1.   __MSP430FR5739__ for CCS v5                      ///
//                                                2.  __IAR_SYSTEMS_ICC__ for IAR Embedded Workbench    ///
// THIS COMMENT IS VALID FOR EVERY STRUCT DEFENITION!                                                   ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __CCS__
typedef struct __attribute__ ((__packed__)) _bsd_accept_return_t
#elif __IAR_SYSTEMS_ICC__
#pragma pack(1)
typedef struct _bsd_accept_return_t
#endif
{
    long             iSocketDescriptor;
    long             iStatus;
    sockaddr   		tSocketAddress;
    
} tBsdReturnParams;


#ifdef __CCS__
typedef struct __attribute__ ((__packed__)) _bsd_read_return_t
#elif __IAR_SYSTEMS_ICC__
#pragma pack(1)
typedef struct _bsd_read_return_t
#endif
{
    long             iSocketDescriptor;
    long             iNumberOfBytes;
    unsigned long	uiFlags;
} tBsdReadReturnParams;


#ifdef __CCS__
typedef struct __attribute__ ((__packed__)) _bsd_recvfrom_data_return_t
#elif __IAR_SYSTEMS_ICC__
#pragma pack(1)
typedef struct _bsd_recvfrom_data_return_t
#endif
{
    long             iSocketDescriptor;
	long             iFromLen;
    long             iNumberOfBytes;
    unsigned long	uiStatus;
	long 			iFrom;
} tBsdRecvFromDataParams;


#ifdef __CCS__
typedef struct __attribute__ ((__packed__)) _bsd_select_return_t
#elif __IAR_SYSTEMS_ICC__
#pragma pack(1)
typedef struct _bsd_select_return_t
#endif
{
    long						iStatus;
	unsigned long 			uiRdfd;
	unsigned long 			uiWrfd;
	unsigned long 			uiExfd;
} tBsdSelectRecvParams;


#ifdef __CCS__
typedef struct __attribute__ ((__packed__)) _bsd_getsockopt_return_t
#elif __IAR_SYSTEMS_ICC__
#pragma pack(1)
typedef struct _bsd_getsockopt_return_t
#endif
{
	unsigned char			ucOptValue[4];
	char						iStatus;
} tBsdGetSockOptReturnParams;


#ifdef __CCS__
typedef struct __attribute__ ((__packed__)) _bsd_gethostbyname_return_t
#elif __IAR_SYSTEMS_ICC__
#pragma pack(1)
typedef struct _bsd_gethostbyname_return_t
#endif
{
    long             retVal;
    long             outputAddress;
} tBsdGethostbynameParams;

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef  __cplusplus
}
#endif // __cplusplus

#endif // __EVENT_HANDLER_H__
