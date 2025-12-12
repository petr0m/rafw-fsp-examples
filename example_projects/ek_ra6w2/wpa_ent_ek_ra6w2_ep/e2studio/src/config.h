/***********************************************************************************************************************
 * File Name    : config.h
 * Description  : Contains macros, data structures and functions used  common to the EP
 ***********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#include "common_utils.h"

/* WPA enterprise setting */
#define BAND 0 /* 0:2.4G, 1:5G */
#define SSID "SSID"
#define ENT_AUTH 1
#define AUTH_PRO 1
#define WPA_ID "WPAID"
#define WPA_PW "WPAPASSWORD"
#define SSID_LEN strlen(SSID)
#define WPA_ID_LEN strlen(WPA_ID)
#define WPA_PW_LEN strlen(WPA_PW)

/* Ping test setting */
#define IP_PROTO_ICMP     1
#define PING_COUNT        10
#define PING_INTERVAL_MS  1000

/* Event status */
#define EVENT_VAL -1
#define WIFI_STATUS_EVENT 1
#define WIFI_EVENT_CONNECTED 5