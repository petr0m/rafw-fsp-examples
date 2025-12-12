/***********************************************************************************************************************
 * File Name    : wpa_ent_example.h
 * Description  : the header of WPA enterprise example.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#ifndef WPA_ENT_EXAMPLE_H
#define WPA_ENT_EXAMPLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "rm_wifi_api.h"
#include "rm_wifi.h"
#include "r_rtc_w.h"
#include "rm_vee_flash_w_rrq_nvram.h"
#include "rm_map_persistant_w.h"

#include "os.h"
#include "common_utils.h"

typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

void print_ep_info();
char *wpa_ent_connect_info();
void wpa_ent_ping(const char *target_ip);

#endif /* WPA_ENT_EXAMPLE_H */
