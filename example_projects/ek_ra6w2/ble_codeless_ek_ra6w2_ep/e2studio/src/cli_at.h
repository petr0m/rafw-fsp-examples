/***********************************************************************************************************************
 * File Name    : cli_at.h
 * Description  : AT command implementation
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#include "stdbool.h"

/**
 * \addtogroup REFERENCE_APPS
 * \{
 */
#ifndef CLI_AT_H_
 #define CLI_AT_H_

bool at_command(int argc, const char * argv[], void * user_data);

#endif                                 /* CLI_AT_H_ */

/**
 * \}
 */
