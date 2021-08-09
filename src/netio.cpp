#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <netioapi.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

using namespace std;

bool GetNetWorkBandwithByMibTable() {
  DWORD dwBuffer = 0;
  GetIfTable(NULL, &dwBuffer, 0);

  PMIB_IFTABLE pMibIfTable = (MIB_IFTABLE *)malloc(dwBuffer);

  DWORD dwRet = GetIfTable(pMibIfTable, &dwBuffer, 0);
  if(NO_ERROR != dwRet) {
    // std::cout << "ERROR" << dwRet << std::endl;
    free(pMibIfTable);
    return false;
  }

  int iMbsBandwidth = INT_MAX;

	for (int i = 0; i != pMibIfTable->dwNumEntries; ++i) {
		if (pMibIfTable->table[i].dwType <= 23) {
			int iTmp = static_cast<int>(pMibIfTable->table[i].dwSpeed / 1000 / 1000);
			if (iTmp != 0 && iTmp < iMbsBandwidth) {
				iMbsBandwidth = iTmp;
			}
			cout << "***************** Sent: " << pMibIfTable->table[i].dwOutOctets << "***************** Rev: " << 	pMibIfTable->table[i].dwInOctets << "*******" << iTmp << endl;
		}
	}

	free(pMibIfTable);
	if (iMbsBandwidth == INT_MAX) {
		return false;
	}
	return true;
}


bool GetStatisticOfSysNetworkFlow(DWORD &dwbitTotalRecv, DWORD &dwbitTotalSend) {
  DWORD dwBuffer = 0;
  GetIfTable(NULL, &dwBuffer, 0);

  PMIB_IFTABLE pMibIfTable = (MIB_IFTABLE *)malloc(dwBuffer);

  DWORD dwRet = GetIfTable(pMibIfTable, &dwBuffer, 0);
  if(NO_ERROR != dwRet) {
    // std::cout << "ERROR" << dwRet << std::endl;
    free(pMibIfTable);
    return false;
  }

	dwbitTotalRecv = dwbitTotalSend = 0;

	for (int i = 0; i != pMibIfTable->dwNumEntries; ++i) {
		if (pMibIfTable->table[i].dwType <= 23) {
			dwbitTotalRecv += pMibIfTable->table[i].dwInOctets;
			dwbitTotalSend += pMibIfTable->table[i].dwOutOctets;
		}
	}

	dwbitTotalRecv *= 8;
	dwbitTotalSend *= 8;

	free(pMibIfTable);

	return true;
}

bool GetSysNetworkFlowByMidTable(DWORD &dwbpsRecv, DWORD &dwbpsSend) {
	DWORD dwTotalRecv1 = 0, dwTotalSend1 = 0;
	if (!GetStatisticOfSysNetworkFlow(dwTotalRecv1, dwTotalSend1)) {
		return false;
	}

	Sleep(1000);

	DWORD dwTotalRecv2 = 0, dwTotalSend2 = 0;
	if (!GetStatisticOfSysNetworkFlow(dwTotalRecv2, dwTotalSend2)) {
		return false;
	}

	dwbpsRecv = dwTotalRecv2 - dwTotalRecv1;
	dwbpsSend = dwTotalSend2 - dwTotalSend1;
	return true;
}
int main(int argc, char *argv[])
{
  GetNetWorkBandwithByMibTable();

	DWORD recv, send;
	GetStatisticOfSysNetworkFlow(recv, send);
	cout << "recvTotal:" << recv << "***sendTotal:" << send << endl;
	for (int i = 0; i < 100; i++) {
		DWORD recvbps, sendbps;
		GetSysNetworkFlowByMidTable(recvbps, sendbps);
		cout << "recv bps:" << recvbps << "***send bps:" << sendbps << endl;
	}
	
	return 0;
}