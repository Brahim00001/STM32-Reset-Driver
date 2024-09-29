/**
 * \file uart.c
 * \brief UART driver.
 * \author Brahim Ben Sedrine
 * \version 0.1
 * \date 25 May 2024
 *
 * Source file containing UART functions driver that can be used.
 *
 */

#include <string.h>
#include "uart.h"


/**
 * \fn T_eError_eErrorType eUart_eSend_Cmd (UART_HandleTypeDef* in_pstUartHandle, char* in_pucString)
 * \brief see uart.h for more details on this function.
 */
T_eError_eErrorType eUart_eSend_Cmd (UART_HandleTypeDef* in_pstUartHandle, char* in_pucString) {

	uint32_t l_uiCnt;

	for(l_uiCnt=0; l_uiCnt<strlen(in_pucString); l_uiCnt++) {
		in_pstUartHandle->Instance->TDR = in_pucString[l_uiCnt];
		while(__HAL_UART_GET_FLAG(in_pstUartHandle, UART_FLAG_TC) == 0);
	}
	return Success;
}



/**
 * \fn T_eError_eErrorType eUart_eReceive_Cmd (UART_HandleTypeDef* in_pstUartHandle, uint32_t *out_puiNbrRxChars, char* out_pucString)
 * \brief see uart.h for more details on this function.
 */
T_eError_eErrorType eUart_eReceive_Cmd (UART_HandleTypeDef* in_pstUartHandle, uint32_t *out_puiNbrRxChars, char* out_pucString) {

	uint32_t l_uiNbrRxChars;
	uint32_t l_uiCnt;

	l_uiNbrRxChars = __HAL_UART_GET_FLAG(in_pstUartHandle, UART_FLAG_RXNE);

	for(l_uiCnt=0; l_uiCnt<l_uiNbrRxChars; l_uiCnt++) {
		out_pucString[l_uiCnt] = in_pstUartHandle->Instance->RDR;
	}

	*out_puiNbrRxChars = l_uiNbrRxChars;

	return Success;
}


/**
 * \fn T_eError_eErrorType eUart_eAbort_Cmd(UART_HandleTypeDef* in_pstUartHandle)
 * \brief see uart.h for more details on this function.
 */
T_eError_eErrorType eUart_eAbort_Cmd(UART_HandleTypeDef* in_pstUartHandle) {

	HAL_UART_Abort(in_pstUartHandle);

	return Success;
}


/**
 * \fn T_eError_eErrorType eUart_eStartRxDma_Cmd (UART_HandleTypeDef* in_pstUartHandle, uint8_t *in_pucRxBuffer, uint32_t in_uiLength)
 * \brief see uart.h for more details on this function.
 */
T_eError_eErrorType eUart_eStartRxDma_Cmd (UART_HandleTypeDef* in_pstUartHandle, uint8_t *in_pucRxBuffer, uint32_t in_uiLength) {

	memset(in_pucRxBuffer, '\0', in_uiLength);

	/* Discard any pending UART transaction */
	__HAL_UART_FLUSH_DRREGISTER(in_pstUartHandle);
	HAL_UART_Abort(in_pstUartHandle);

	/* Start Rx DMA */
//	HAL_UART_Receive_IT(in_pstUartHandle, in_pucRxBuffer, in_uiLength);
	HAL_UART_Receive_DMA(in_pstUartHandle, in_pucRxBuffer, in_uiLength);

	return Success;
}




/**
 * \fn void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 * \brief see uart.h for more details on this function.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

  /* NOTE : In this function should be called the different module's functions callback. */

	/* Module Tracking */
	eTracking_eUartRxCplt_Isr(huart);

	/* Module IAP UART */
	eIapUart_eUartRxCplt_Isr(huart);
}
