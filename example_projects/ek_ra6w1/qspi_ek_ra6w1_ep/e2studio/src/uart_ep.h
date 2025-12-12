/***********************************************************************************************************************
 * File Name    : uart_ep.h
 * Description  : Contains function declaration of uart_ep.c and Macros.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#ifndef UART_EP_H_
#define UART_EP_H_

#include "r_uart_api.h"
#include "hal_data.h"

#define ENABLE_UART_LOG

/* Macro definition */
#define CARRIAGE_ASCII            (13u)     /* Carriage return */
#define DATA_LENGTH               (4u)      /* Expected Input Data length */
#define UART_ERROR_EVENTS         (UART_EVENT_BREAK_DETECT | UART_EVENT_ERR_OVERFLOW | UART_EVENT_ERR_FRAMING | \
                                   UART_EVENT_ERR_PARITY)    /* UART Error event bits mapped in registers */

#ifdef ENABLE_UART_LOG

/* Function declaration */
fsp_err_t uart_ep_demo(void);
fsp_err_t uart_print_user_msg(uint8_t *p_msg);
fsp_err_t uart_initialize(void);
void deinit_uart(void);
void uart_log(char *p_msg);

#endif

#endif /* UART_EP_H_ */

