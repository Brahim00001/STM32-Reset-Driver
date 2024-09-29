/*
 * reset.c
 *
 *  Created on: Apr 5, 2020
 *      Author: Brahim Ben Sedrine
 */

#include <string.h>
#include "reset.h"
#include "uart.h"


static char gs_pcReset_iSystemResume[128] = {};

static T_eReset_eType gs_eReset_iType = C_eReset_eHardware;

T_eError_eErrorType eReset_eDisplayType_Cmd(UART_HandleTypeDef *in_pstUartHandle) {

	/* Get from what the system has resumed */
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST) != RESET) {
    	strcat(gs_pcReset_iSystemResume, "Software Reset\r\n");
    	eReset_eType_Set(C_eReset_eSoftware);
    }
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET){
    	strcat(gs_pcReset_iSystemResume, "WWDG Reset\r\n");
    	eReset_eType_Set(C_eReset_eWatchdog);
	}
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
	{
		strcat(gs_pcReset_iSystemResume, "IWDG Reset\r\n");
		eReset_eType_Set(C_eReset_eWatchdog);
	}
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_FWRST) != RESET)
	{
		strcat(gs_pcReset_iSystemResume, "Firewall Reset\r\n");
		eReset_eType_Set(C_eReset_eHardware);
	}
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_OBLRST) != RESET)
	{
		strcat(gs_pcReset_iSystemResume, "Option Byte Loader Reset\r\n");
		eReset_eType_Set(C_eReset_eHardware);
	}
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET)
	{
		strcat(gs_pcReset_iSystemResume, "Pin Reset\r\n"); /* pin reset occurs with all types */
	}
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) != RESET)
	{
		strcat(gs_pcReset_iSystemResume, "BOR Reset\r\n");
		eReset_eType_Set(C_eReset_eHardware);
	}
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST) != RESET)
	{
		strcat(gs_pcReset_iSystemResume, "Low Power Reset\r\n");
		eReset_eType_Set(C_eReset_eHardware);
	}
	/* Clear reset flags in any case */
	__HAL_RCC_CLEAR_RESET_FLAGS();

	eUart_eSend_Cmd(in_pstUartHandle, "System was resumed from:\r\n");
	eUart_eSend_Cmd(in_pstUartHandle, gs_pcReset_iSystemResume);

	return Success;
}


T_eError_eErrorType eReset_eType_Set(T_eReset_eType in_eResetType) {

	gs_eReset_iType = in_eResetType;

	return Success;
}

T_eError_eErrorType eReset_eType_Get(T_eReset_eType *out_peResetType) {

	*out_peResetType = gs_eReset_iType;

	return Success;
}
