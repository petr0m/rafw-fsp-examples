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
#include "sntp_example.h"

void wifi_init();
void netif_status_callback(struct netif *netif);

#if defined(__SUPPORT_FACTORY_RESET_BTN__)
#include "rm_wifi_user_app_gpio_handle.h"
#endif

#define WIFI_EVENT_CONNECTED 5
TaskHandle_t g_app_main_task_handle = NULL;
uint32_t notified_value = EVENT_VAL;

WIFINetworkParams_t net_params =
{
    .ucChannel = CHANNEL,
    .xPassword.xWPA.cPassphrase = PSWD,
    .ucSSID = SSID,
    .xPassword.xWPA.ucLength = PSWD_LEN,
    .ucSSIDLength = SSID_LEN,
    .xSecurity = eWiFiSecurityWPA2,
};

void netif_status_callback(struct netif *netif)
{
    if (netif_is_up(netif) && !ip_addr_isany_val(netif->ip_addr))
    {
        APP_PRINT("\n>>> WIFI ConnectAP: Success\n");
        APP_PRINT("IP assigned: %s\n", ipaddr_ntoa(&netif->ip_addr));
        xTaskNotify(g_app_main_task_handle, WIFI_EVENT_CONNECTED, eSetBits);
    }
}

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

    /* Init CC312 HW engine and psa crypto */
    RM_WIFI_mbedtls_setup_psa_crypto();

#ifdef RM_MAP_PERSISTANT_W
    /* Initialize and open the peristant storage.
     * Before any Read/Write/Erase open in persistant storage
     * RM_MAP_PERSISTANT_W_Open should be called
     * */
    RM_MAP_PERSISTANT_W_Open(&g_map_persistant_w_ctrl);
#endif

    WIFI_On();
 
    /* setting callback for netif status */
    netif_set_status_callback(netif_default, netif_status_callback);

    wifi_err = WIFI_SetMode(eWiFiModeStation);
    assert(eWiFiSuccess == wifi_err);
    wifi_err = WIFI_ConnectAP(&net_params);
    assert(eWiFiSuccess == wifi_err);
#endif
}

void app_task_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    g_app_main_task_handle = xTaskGetCurrentTaskHandle();

    print_ep_info();
    wifi_init();

    while(notified_value != WIFI_EVENT_CONNECTED)
    {
        xTaskNotifyWait(0, 0xFFFFFFFF, &notified_value, portMAX_DELAY);
    }

    sntp_example();
    print_current_time();

    while (1)
    	vTaskDelay (200);
	
    WIFI_Off();
}
