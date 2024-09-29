/*
 * reset.h
 *
 *  Created on: April 5, 2024
 *      Author: Brahim Ben Sedrine
 */

#ifndef RESET_H_
#define RESET_H_

#include "error.h"
#include "main.h"

/**
 *\enum T_eReset_eType
 *\brief Enumeration containg the type of occured reset
 */
typedef enum {
	/* Reset Events */
	C_eReset_eHardware = 0,       	/* Hardware Reset Event */
	C_eReset_eSoftware,       		/* Software Reset Event */
	C_eReset_eWatchdog,       		/* Watchdog Reset Event */
}T_eReset_eType;

T_eError_eErrorType eReset_eDisplayType_Cmd(UART_HandleTypeDef *in_pstUartHandle);

T_eError_eErrorType eReset_eType_Set(T_eReset_eType in_eResetType);

T_eError_eErrorType eReset_eType_Get(T_eReset_eType *out_peResetType);

#endif /* RESET_H_ */
