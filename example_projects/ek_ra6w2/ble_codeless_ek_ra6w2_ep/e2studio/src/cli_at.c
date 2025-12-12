/***********************************************************************************************************************
 * File Name    : cli_at.c
 * Description  : AT command implementation
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

/**
 * \addtogroup REFERENCE_APPS
 * \{
 */
#if CFG_CLI
#include "rm_cli_w_debug_utils.h"

extern volatile bool rm_atcmd_w_core_handle_rx_overflow;

#define CLI_AT_ONOFF_PARAM_ON     "on"
#define CLI_AT_ONOFF_PARAM_OFF    "off"

static bool cmd_at_set_binmod_overflow_handler (int argc, char * argv[])
{
    bool rc = false;

    if (argc == 2)
    {
        if (!strncmp(argv[1], CLI_AT_ONOFF_PARAM_ON, sizeof(CLI_AT_ONOFF_PARAM_ON)))
        {
#if (ATCMD_DA14XXX_CODELESS == 1)
            rm_atcmd_w_core_handle_rx_overflow = true;
#endif
            rc = true;
        }
        else if (!strncmp(argv[1], CLI_AT_ONOFF_PARAM_OFF, sizeof(CLI_AT_ONOFF_PARAM_OFF)))
        {
#if (ATCMD_DA14XXX_CODELESS == 1)
            rm_atcmd_w_core_handle_rx_overflow = false;
#endif
            rc = true;
        }
    }

    return rc;
}

static const debug_handler_t at_handlers[] =
{
    {"rx_overflow", "Enable/disable binary mode overflow detection and handling",
     (debug_callback_t) cmd_at_set_binmod_overflow_handler},
    {NULL},
};

bool at_command (int argc, const char * argv[], void * user_data)
{
    return debug_handle_message(argc, argv, at_handlers);
}

#endif                                 // CFG_CLI

/**
 * \}
 */
