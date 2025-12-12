/***********************************************************************************************************************
 * File Name    : sntp_example.h
 * Description  : the header of SNTP example.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#ifndef SNTP_EXAMPLE_H
#define SNTP_EXAMPLE_H

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
#include "lwip/netif.h"
#include "net_sntp_client.h"
#include "common_utils.h"

typedef unsigned long long uint64_t;
typedef unsigned long uint32_t;

void print_ep_info();
void print_current_time(void);
void sntp_example(void);

#endif /* SNTP_EXAMPLE_H */
