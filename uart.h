#ifndef UART_UART_H_
#define UART_UART_H_


/**
 * \file uart.h
 * \brief UART driver header.
 * \author Brahim Ben Sedrine
 * \version 0.1
 * \date 24 May 2024
 *
 * Header file containing the useful Functions to communicate with the UART module.
 *
 */


#include "main.h"
#include "error.h"



/**
 * \fn T_eError_eErrorType eUart_eSend_Cmd (UART_HandleTypeDef* in_pstUartHandle, char* in_pucString)
 * \brief Send characters over UART.
 *
 * \param in_pstUartHandle UART Handler.
 * \param in_pucString Characters to send through UART.
 * \return Success.
 */
T_eError_eErrorType eUart_eSend_Cmd (UART_HandleTypeDef* in_pstUartHandle, char* in_pucString);



/**
 * \fn T_eError_eErrorType eUart_eReceive_Cmd (UART_HandleTypeDef* in_pstUartHandle, uint32_t *out_puiNbrRxChars, char* out_pucString)
 * \brief Receive characters from UART.
 *
 * \param in_pstUartHandle UART Handler.
 * \param out_puiNbrRxChars Number of Characters received from UART.
 * \param out_pucString Characters received from UART.
 * \return Success.
 */
T_eError_eErrorType eUart_eReceive_Cmd (UART_HandleTypeDef* in_pstUartHandle, uint32_t *out_puiNbrRxChars, char* out_pucString);



/**
 * \fn T_eError_eErrorType eUart_eAbort_Cmd(UART_HandleTypeDef* in_pstUartHandle)
 * \brief Abort any pending UART action.
 *
 * \param in_pstUartHandle UART Handler.
 * \return Success.
 */
T_eError_eErrorType eUart_eAbort_Cmd(UART_HandleTypeDef* in_pstUartHandle);



/**
 * \fn T_eError_eErrorType eUart_eStartRxDma_Cmd (UART_HandleTypeDef* in_pstUartHandle, uint8_t *in_pucRxBuffer, uint32_t in_uiLength)
 * \brief Launch DMA on UART Rx.
 *
 * \param in_pstUartHandle UART Handler.
 * \param in_pucRxBuffer Pointer to the buffer that will receive data.
 * \param in_uiLength Number of Characters to received from UART.
 * \return Success.
 */
T_eError_eErrorType eUart_eStartRxDma_Cmd (UART_HandleTypeDef* in_pstUartHandle, uint8_t *in_pucRxBuffer, uint32_t in_uiLength);



/**
 * \fn void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 * \brief Rx Transfer completed callback. The weak of this function is defined in stm32l4xx_hal_uart.c
 *
 * \param in_pstUartHandle UART Handler.
 * \return none.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#endif /* UART_UART_H_ */
