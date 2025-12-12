/***********************************************************************************************************************
 * File Name    : wpa_ent_example.c
 * Description  : Example of WPA enterprise.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "app_task.h"
#include "lwip/sockets.h"
#include "lwip/icmp.h"
#include "lwip/ip_addr.h"
#include "lwip/inet_chksum.h"
#include "lwip/sys.h"
#include "os.h"
#include "wpa_ent_example.h"

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

char *wpa_ent_connect_info()
{
	struct netif *iface_sta = WIFI_GetNetIf(eWiFiModeStation);

	APP_PRINT("\n>>> WPA Enterprise AP Connect: Success\n")
	APP_PRINT("IP assigned: %s\n", ipaddr_ntoa(&iface_sta->ip_addr));
	APP_PRINT("Net Mask: %s\n", ipaddr_ntoa(&iface_sta->netmask));
	APP_PRINT("Gateway IP: %s\n", ipaddr_ntoa(&iface_sta->gw));

	return ipaddr_ntoa(&iface_sta->gw);
}

void wpa_ent_ping(const char *target_ip)
{
    struct sockaddr_in targetAddr;
    int sock;
    char sendBuf[64];
    char recvBuf[128];
    int sentBytes, receivedBytes;
    struct timeval timeout;
    fd_set readSet;

    memset(&targetAddr, 0, sizeof(targetAddr));
    targetAddr.sin_family = AF_INET;

    /* Use the passed-in target IP address */
    targetAddr.sin_addr.s_addr = inet_addr(target_ip);

    /* Create a raw ICMP socket. */
    sock = lwip_socket(AF_INET, SOCK_RAW, IP_PROTO_ICMP);
    if (sock < 0)
    {
    	APP_PRINT("Ping Test: Failed to create socket\n");
        return;
    }

    /* Set a 1-second receive timeout. */
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    lwip_setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    for (int i = 0; i < PING_COUNT; i++)
    {
        memset(sendBuf, 0, sizeof(sendBuf));
        struct icmp_echo_hdr *icmpHdr = (struct icmp_echo_hdr *)sendBuf;
        icmpHdr->type = ICMP_ECHO;
        icmpHdr->code = 0;
        icmpHdr->chksum = 0;  /* To be calculated. */
        icmpHdr->id = LWIP_RAND() & 0xFFFF;
        icmpHdr->seqno = htons(i + 1);
        icmpHdr->chksum = inet_chksum(icmpHdr, sizeof(sendBuf));
        sentBytes = lwip_sendto(sock, sendBuf, sizeof(sendBuf), 0, (struct sockaddr *)&targetAddr, sizeof(targetAddr));

        if (sentBytes < 0)
        {
            APP_PRINT("Ping Test: Failed to send ping %d\n", i + 1);
            continue;
        }
        APP_PRINT("Ping Test: Ping %d sent to %s\n", i + 1, target_ip);

        if (lwip_select(sock + 1, &readSet, NULL, NULL, &timeout) > 0)
        {
            receivedBytes = lwip_recv(sock, recvBuf, sizeof(recvBuf), 0);
            if (receivedBytes > 0)
            {
            	APP_PRINT("Ping Test: Ping %d response received!\n", i + 1);
            }
            else
            {
            	APP_PRINT("Ping Test: Ping %d received no data\n", i + 1);
            }
        }
        else
        {
        	APP_PRINT("Ping Test: Ping %d timed out\n", i + 1);
        }
        sys_msleep(PING_INTERVAL_MS);
    }
    lwip_close(sock);
}
