#ifndef CPP_LEARN_MY_DLL_H 
#define CPP_LEARN_MY_DLL_H 

#define EXPORT_DLL __declspec(dllexport) 

extern "C" EXPORT_DLL void NetIOCounters(DWORD result[2]); 
void GetAddresses(PIP_ADAPTER_ADDRESSES &pAddresses);
void PrintInterfaceInfo(MIB_IFROW * pIfRow, unsigned int i);

#endif //CPP_LEARN_MY_DLL_H