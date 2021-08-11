#include <Windows.h>
#include <iostream>

typedef void (*NetIOCounters)(DWORD[]); 

int main() {
  HINSTANCE handle = LoadLibrary("NetIOForWindows.dll");

  auto f = (NetIOCounters) GetProcAddress(handle, "NetIOCounters");
  DWORD result1[2];
  DWORD result2[2];
  for (int i = 0;  i < 100; i++ ) {
      f(result1);shiyong
      Sleep(1000);
      f(result2);
      printf("sendRate: %d KB/s\trecvRate: %d KB/s\n", (result2[0] - result1[0]) / 1000,
          (result2[1] - result1[1] ) / 1000 );
  }
  
  FreeLibrary(handle);
  return 0; 
}