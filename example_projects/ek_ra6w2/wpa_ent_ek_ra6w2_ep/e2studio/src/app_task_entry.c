/***********************************************************************************************************************
 * File Name    : app_task_entry.c
 * Description  : Initialize Wi-Fi and run SNTP example.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#include "app_task.h"
#include "config.h"
#include "lwip/netif.h"
#include "wpa_ent_example.h"

void wifi_init();
void netif_status_callback(struct netif *netif);

TaskHandle_t g_app_main_task_handle = NULL;
uint32_t notified_value = EVENT_VAL;

/* WPA enterprise configuration */
WIFINetworkParamsExt_t net_params =
{
    .ucBand = BAND,
    .xNetworkParams.ucSSID = SSID,
    .xNetworkParams.ucSSIDLength = SSID_LEN,
    .xNetworkParams.xSecurity = eWiFiSecurityWPA2_ent,
    .xEntNetParams.ucEntAuthType = ENT_AUTH,
    .xEntNetParams.ucEntAuthProto = AUTH_PRO,
    .xEntNetParams.ucID = WPA_ID,
    .xEntNetParams.ucIDLength = WPA_ID_LEN,
    .xEntNetParams.ucPassword = WPA_PW,
    .xEntNetParams.ucPasswordLength = WPA_PW_LEN
};

/* Network connection status callback */
void netif_status_callback(struct netif *netif)
{
    if (netif_is_up(netif) && !ip_addr_isany_val(netif->ip_addr))
    {
        xTaskNotify(g_app_main_task_handle, WIFI_EVENT_CONNECTED, eSetBits);
    }
}

/* Wi-Fi module initialization */
void wifi_init()
{
#if CFG_WIFI
    WIFIReturnCode_t wifi_err;

#if WIFI_CFG_WATCHDOG_SERVICE_ENABLE
    g_wifi_cfg.p_watchdog_service->p_api->open(g_wifi_cfg.p_watchdog_service->p_ctrl, g_wifi_cfg.p_watchdog_service->p_cfg);
#else
    g_wifi_cfg.p_watchdog_service->p_cfg->p_wdt->p_api->open(g_wifi_cfg.p_watchdog_service->p_cfg->p_wdt->p_ctrl, g_wifi_cfg.p_watchdog_service->p_cfg->p_wdt->p_cfg);
    R_WDOG_W_Freeze(g_wifi_cfg.p_watchdog_service->p_cfg->p_wdt->p_ctrl, true);
    R_WDOG_W_TimeoutSet(g_wifi_cfg.p_watchdog_service->p_cfg->p_wdt->p_ctrl, dg_configWDOG_IDLE_RESET_VALUE);
    g_wifi_cfg.p_watchdog_service->p_cfg->p_wdt->p_api->refresh(g_wifi_cfg.p_watchdog_service->p_cfg->p_wdt->p_ctrl);
#endif

    RM_WIFI_mbedtls_setup_psa_crypto();

#ifdef RM_MAP_PERSISTANT_W
    /* Initialize and open the persistant storage */
    RM_MAP_PERSISTANT_W_Open(&g_map_persistant_w_ctrl);
#endif

    WIFI_On();

    /* Setting callback for NETIF status */
    netif_set_status_callback(netif_default, netif_status_callback);

    /* Setting station mode */
    wifi_err = WIFI_SetMode(eWiFiModeStation);
    if (wifi_err)
    {
        APP_PRINT("\n%s: WIFI_SetMode failed with wifi_err=%d\n", __func__, wifi_err);
    }

    /* Connect WAP enterprise AP */
    wifi_err = WIFI_ConnectAPExt(&net_params);
    if (wifi_err)
    {
        APP_PRINT("\n%s: WIFI_ConnectAPExt failed with wifi_err=%d\n", __func__, wifi_err);
    }
#endif
}

void app_task_entry(void *pvParameters)
{
    char *wpa_ent_ip = NULL;

    FSP_PARAMETER_NOT_USED (pvParameters);
    g_app_main_task_handle = xTaskGetCurrentTaskHandle();

    print_ep_info();
    wifi_init();

    while(notified_value != WIFI_EVENT_CONNECTED)
    {
        xTaskNotifyWait(0, 0xFFFFFFFF, &notified_value, portMAX_DELAY);
    }

    wpa_ent_ip = wpa_ent_connect_info();
    wpa_ent_ping((const char *) wpa_ent_ip);

    while (1)
        vTaskDelay (200);
	
    WIFI_Off();
}
