/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: TcpIpw_Cfg.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This configuration information to the TcpIpw                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
********************************************************************************
** 1.0.1     12-Jen-2021   JYS          Redmine #27644                        **
*******************************************************************************/

#ifndef TCPIPW_CFG_H
#define TCPIPW_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Macro for defining main function periodicity */
#define TCPIPW_MAIN_FUNC_PERIOD                                               1u

/* TCP Configuration */
#define TCPIPW_TCP                                                        STD_ON

/* UDP protocol configuration */
#define TCPIPW_UDP                                                        STD_ON

/* Configuration for number of sockets Identifiers */
#define TCPIPW_SOCKID_COUNT                                                   6u

/* Configuration for number of TCP socket */
#define TCPIPW_TCP_SOCKID_COUNT                                               4u

/* Configuration for number of UDP socket */
#define TCPIPW_UDP_SOCKID_COUNT                                               2u

/* Configuration for number of IP address Identifiers */
#define TCPIPW_IP_ADDR_ID_COUNT                                               3u

/* Configuration for number of available TCP buffers */
#define TCPIPW_TCP_BUFFER_COUNT                                               4u

/* Maximum segment size for the TCP segments */
#define TCPIPW_TCP_MSS                                                     1460u

/* Configuration for maximum size of TCP buffer */
#define TCPIPW_TCP_BUFFER_MAX_SIZE                                TCPIPW_TCP_MSS

/* Configuration for number of available UDP buffers */
#define TCPIPW_UDP_BUFFER_COUNT                                               2u

/* Configuration for maximum size of UDP buffer */
#define TCPIPW_UDP_BUFFER_MAX_SIZE                                          576u

/* Make both DHCP and AUTOIP zero when using static IP address assignment */

/* Configuration for Enabling and disabling DHCP */
#define TCPIPW_DHCP                                                      STD_OFF

/* Configuration for Enabling and disabling AUTOIP */
#define TCPIPW_AUTOIP                                                    STD_OFF

/* Number of DHCP discovery messages before switching to AUTOIP IP address */
#define TCPIPW_DHCP_AUTOIP_COOP_TRIES                                         5U

/* MACRO to enable hostname in TCPIP wrapper */
#define TCPIPW_NETIF_HOSTNAME                                             STD_ON

/* Configuration for maximum size of the DHCP host name buffer */
#define TCPIPW_DHCP_HOST_NAME_MAX_LENGTH                                    100u

/* Configuration for keepalive feature */
#define TCPIPW_TCP_KEEPALIVE                                              STD_ON

/* Host name option for the DHCP */
#define TCPIPW_DHCP_HOSTNAME_OPTION                                          12u

/* Default Keepalive probe count */
#define TCPIPW_TCP_KEEPCNT_DEFAULT                                            9u

/* AUTOIP CONFIGURATION USING ISO STANDARD */
/* Second (initial random delay) */
#define TCPIPW_PROBE_WAIT                                                     1u

/* second   (minimum delay till repeated probe) */
#define TCPIPW_PROBE_MIN                                                      1u

/* seconds  (maximum delay till repeated probe) */
#define TCPIPW_PROBE_MAX                                                      1u

/* (number of probe packets) */
#define TCPIPW_PROBE_NUM                                                      1u

/* (number of announcement packets) */
#define TCPIPW_ANNOUNCE_NUM                                                   1u

 /* seconds  (time between announcement packets) */
#define TCPIPW_ANNOUNCE_INTERVAL                                              1u

 /* seconds  (delay before announcing) */
#define TCPIPW_ANNOUNCE_WAIT                                                  1u

/* ARP queuing */
/* Allocate ARP queue of length equal to the number of socket configured 
  by the user in the system */
#define TCPIPW_ARP_QUEUE_LEN                                 TCPIPW_SOCKID_COUNT

/* Unicast  IP address identifier */
#define TCPIPW_UNICAST_IP_ADDR_ID                                             0u

/* Broadcast IP address identifier */
#define TCPIPW_BROADCAST_IP_ADDR_ID                                           1u

/* Enable/Disable the ARP queue. Where STD_ON indicates Enable and STD_OFF
  indicates Disable */
#define TCPIPW_ARP_QUEUEING                                               STD_ON

/* Configuration for the Memory alignment */
#define TCPIPW_MEM_ALIGNMENT                                  (CPU_TYPE_32 / 8U)

/* The TCP timer interval in milliseconds. */
#define TCPIPW_TCP_TMR_INTERVAL                          TCPIPW_MAIN_FUNC_PERIOD

/* Turn off checksum verification of fuzzed data */
#define TCPIPW_CHECKSUM_CHECK_IP                                          STD_ON
#define TCPIPW_CHECKSUM_CHECK_UDP                                         STD_ON
#define TCPIPW_CHECKSUM_CHECK_TCP                                         STD_ON
#define TCPIPW_CHECKSUM_CHECK_ICMP                                        STD_ON

/* Queue length for the out of sequence data */
#define TCPIPW_TCP_OOSEQ_MAX_PBUFS                                            6U

/* Memory for RAM PBUFS */
#define TCPIPW_MEM_SIZE                                                (1024*16)

/* Multiplication factor which decides the TCP window size */
#define TCPIPW_WND_SIZE_MUL_FACTOR                                            4U

/* Multiplication factor which decides the TCP send buffer size */
#define TCPIPW_SEND_BUF_SIZE_MUL_FACTOR                                       8U

/* Configuration for Pbuf pool memory size */
#define TCPIPW_PBUF_POOL_SIZE                                                 8U

/* Configuration for endianness of communication stack */
#if(CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
#define TCPIPW_BYTE_ORDER                                             BIG_ENDIAN
#else
#define TCPIPW_BYTE_ORDER                                          LITTLE_ENDIAN
#endif

/* Configuration for type of CPU type */
#define TCPIPW_BITS_IN_INT                                           CPU_TYPE_32

/* Configuration to enable or disable the memory stats */
#define TCPIPW_MEMP_STATS                                                STD_OFF

/* Configuration to enable or disable processing of multiple Received data */
#define TCPIPW_MULTIPLE_RX_PROCESSING                                    STD_OFF

/* Following definition is used to skip structure padding check in lwip_init() */
#define TCPIPW_SKIP_PACKING_CHECK                                         STD_ON

#endif /* TCPIPW_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
