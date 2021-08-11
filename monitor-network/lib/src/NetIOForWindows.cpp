#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include "NetIOForWindows.h"

// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")

#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

using namespace std;


/**
 * 
 * 获取所有网卡接收和发送的字节数
 * 
 * */
void NetIOCounters(DWORD result[2]) {

    /* Declare and initialize variables */
    DWORD dwRetVal = 0, recvTotal = 0, sendTotal = 0;

    // 声明一个MIB_IFROW指针，用来指向网卡
    MIB_IFROW *pIfRow = NULL;
    pIfRow = (MIB_IFROW *) malloc(sizeof(MIB_IFROW));
    if (pIfRow == NULL) {
      printf("Error allocation memory\n");
      exit(1);
    }
    SecureZeroMemory((PVOID)pIfRow, sizeof(MIB_IFROW));

    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
    GetAddresses(pAddresses);

    // If successful, output some information from the data we received
    pCurrAddresses = pAddresses;
    unsigned int i = 0;
    while (pCurrAddresses) {
      pIfRow->dwIndex = pCurrAddresses->IfIndex;
      dwRetVal = GetIfEntry(pIfRow);
      if (dwRetVal == NO_ERROR) {
        recvTotal += pIfRow->dwInOctets;
        sendTotal += pIfRow->dwOutOctets;
        // PrintInterfaceInfo(pIfRow, i);
      }
      pCurrAddresses = pCurrAddresses->Next;
      i++;
    }

    if (pAddresses) FREE(pAddresses);
    if (pIfRow) FREE(pIfRow);

    result[0] = sendTotal;
    result[1] = recvTotal;

    return;
}

/**
 *  获取网卡信息
 * */
void GetAddresses(PIP_ADAPTER_ADDRESSES &pAddresses) {
    DWORD dwRetVal = 0;

    // Set the flags to pass to GetAdaptersAddresses
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

    ULONG outBufLen = 0;
    ULONG Iterations = 0;
    // Allocate a 15 KB buffer to start with.
    outBufLen = WORKING_BUFFER_SIZE;

    LPVOID lpMsgBuf = NULL;

    do {
      pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(outBufLen);
      if (pAddresses == NULL) {
        printf("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
        exit(1);
      }

      dwRetVal =
          GetAdaptersAddresses(AF_UNSPEC, flags, NULL, pAddresses, &outBufLen);

      if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
        FREE(pAddresses);
        pAddresses = NULL;
      } else {
        break;
      }

      Iterations++;

    } while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (Iterations < MAX_TRIES));

    if (dwRetVal != NO_ERROR)  {
      printf("Call to GetAdaptersAddresses failed with error: %d\n", dwRetVal);
      if (dwRetVal == ERROR_NO_DATA)
        printf("\tNo addresses were found for the requested parameters\n");
      else {
        if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
              FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
              NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),   
              // Default language
              (LPTSTR) & lpMsgBuf, 0, NULL)) {
          printf("\tError: %s", lpMsgBuf);
          LocalFree(lpMsgBuf);
          if (pAddresses) FREE(pAddresses);
          exit(1);
        }
      }
    }
}

void PrintInterfaceInfo(MIB_IFROW * pIfRow, unsigned int i) {
    printf("\tIndex:\t %ld\n", pIfRow->dwIndex);
    printf("\tInterfaceName[%d]:\t ", i);
    if (pIfRow->wszName != NULL)
        printf("%ws", pIfRow->wszName);
    printf("\n");

    printf("\tDescription[%d]:\t ", i);
    for (unsigned int j = 0; j < pIfRow->dwDescrLen; j++)
        printf("%c", pIfRow->bDescr[j]);
    printf("\n");

    printf("\tIndex[%d]:\t\t %d\n", i, pIfRow->dwIndex);

    printf("\tType[%d]:\t\t ", i);
    switch (pIfRow->dwType) {
    case IF_TYPE_OTHER:
        printf("Other\n");
        break;
    case IF_TYPE_ETHERNET_CSMACD:
        printf("Ethernet\n");
        break;
    case IF_TYPE_ISO88025_TOKENRING:
        printf("Token Ring\n");
        break;
    case IF_TYPE_PPP:
        printf("PPP\n");
        break;
    case IF_TYPE_SOFTWARE_LOOPBACK:
        printf("Software Lookback\n");
        break;
    case IF_TYPE_ATM:
        printf("ATM\n");
        break;
    case IF_TYPE_IEEE80211:
        printf("IEEE 802.11 Wireless\n");
        break;
    case IF_TYPE_TUNNEL:
        printf("Tunnel type encapsulation\n");
        break;
    case IF_TYPE_IEEE1394:
        printf("IEEE 1394 Firewire\n");
        break;
    default:
        printf("Unknown type %ld\n", pIfRow->dwType);
        break;
    }

    printf("\tMtu[%d]:\t\t %ld\n", i, pIfRow->dwMtu);

    printf("\tSpeed[%d]:\t\t %ld\n", i, pIfRow->dwSpeed);

    printf("\tPhysical Addr:\t\t ");
    if (pIfRow->dwPhysAddrLen == 0)
        printf("\n");
//                    for (j = 0; j < (int) pIfRow->dwPhysAddrLen; j++) {
    for (unsigned int j = 0; j < pIfRow->dwPhysAddrLen; j++) {
        if (j == (pIfRow->dwPhysAddrLen - 1))
            printf("%.2X\n", (int) pIfRow->bPhysAddr[j]);
        else
            printf("%.2X-", (int) pIfRow->bPhysAddr[j]);
    }
    printf("\tAdmin Status[%d]:\t %ld\n", i,
            pIfRow->dwAdminStatus);

    printf("\tOper Status[%d]:\t ", i);
    switch (pIfRow->dwOperStatus) {
    case IF_OPER_STATUS_NON_OPERATIONAL:
        printf("Non Operational\n");
        break;
    case IF_OPER_STATUS_UNREACHABLE:
        printf("Unreasonable\n");
        break;
    case IF_OPER_STATUS_DISCONNECTED:
        printf("Disconnected\n");
        break;
    case IF_OPER_STATUS_CONNECTING:
        printf("Connecting\n");
        break;
    case IF_OPER_STATUS_CONNECTED:
        printf("Connected\n");
        break;
    case IF_OPER_STATUS_OPERATIONAL:
        printf("Operational\n");
        break;
    default:
        printf("Unknown status %ld\n", 
            pIfRow->dwOperStatus);
        break;
    }

    printf("***************recv: [%d] Bytes\n*****************send: [%d] Bytes\n",
           pIfRow->dwInOctets, pIfRow->dwOutOctets);
    printf("\n");
}