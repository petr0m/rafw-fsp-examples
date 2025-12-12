/***********************************************************************************************************************
 * File Name    : sntp_example.c
 * Description  : Example of SNTP.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#include "sntp_example.h"
#include "config.h"

extern int sntp_get_period(void);
extern unsigned int get_sntp_use(void);
extern unsigned int set_sntp_use(int use);
extern u8_t sntp_get_use(void);
extern void get_sntp_server(char *svraddr, unsigned int index);

void print_ep_info()
{
    fsp_pack_version_t version;
    R_FSP_VersionGet(&version);
    APP_PRINT(BANNER_1);
    APP_PRINT(BANNER_2);
    APP_PRINT(BANNER_3, EP_VERSION);
    APP_PRINT(BANNER_4, version.version_id_b.major, version.version_id_b.minor, version.version_id_b.patch);
    APP_PRINT(BANNER_5);
    APP_PRINT(BANNER_6);
}

void print_current_time(void)
{
    rtc_w_instance_ctrl_t *rtc_w_ctrl = R_RTC_W_GetCtrl();
    struct tm ts;
    char buf[32];

    if (rtc_w_ctrl != NULL)
    {
        R_RTC_W_CalendarTimeGet(rtc_w_ctrl, &ts);
        R_RTC_W_Time2Str(rtc_w_ctrl, &ts, buf, sizeof(buf), "%Y-%m-%d %H:%M:%S");
    }
    else
    {
        snprintf(buf, sizeof(buf), "RTC-NA");
    }

    APP_PRINT("\n>>> Current time : %s\n", buf);
}

void sntp_example(void)
{
    UINT8 status;

    /* Configure SNTP server domain */
    APP_PRINT("\n>>> Set SNTP configuration...\n");

    status = set_sntp_server((unsigned char*) SNTP_SERVER_DOMAIN_0, 0);
    if (status == pdTRUE)
    {
        APP_PRINT("\tSNTP Server 0 : %s\n", SNTP_SERVER_DOMAIN_0);
    }

    status = set_sntp_server((unsigned char*) SNTP_SERVER_DOMAIN_1, 1);
    if (status == pdTRUE)
    {
        APP_PRINT("\tSNTP Server 1 : %s\n", SNTP_SERVER_DOMAIN_1);
    }

    status = set_sntp_server((unsigned char*) SNTP_SERVER_DOMAIN_2, 2);
    if (status == pdTRUE)
    {
        APP_PRINT("\tSNTP Server 2 : %s\n", SNTP_SERVER_DOMAIN_2);
    }

    /* Configure SNTP sync period: seconds */
    status = set_sntp_period((int) SNTP_SYNC_PERIOD);
    if (status == pdTRUE)
    {
        APP_PRINT("\tSNTP Sync Period : %d seconds\n", SNTP_SYNC_PERIOD);
    }

    /* Configure SNTP time zone: seconds */
    set_time_zone((long) SNTP_TIME_ZONE);

    /* Set SNTP client */
    set_sntp_use(pdTRUE);

    if (get_sntp_use())
    {
        APP_PRINT("\n>>> SNTP client is started\n");
    }

    /* Check SNTP sync status */
    while (1)
    {
        if (is_sntp_sync() == TRUE)
        {
            APP_PRINT("\n>>> SNTP client is sync\n");
            break;

        }
        vTaskDelay(200);
    }
}
