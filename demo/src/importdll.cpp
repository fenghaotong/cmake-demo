#include <iostream>
#include <stdio.h>

typedef int (*add)(int, int); 

int main() {
  HINSTANCE handle = LoadLibrary("my_dll.dll"); 
  
  std::cout << handle << std::endl; 
  auto f = (add) GetProcAddress(handle, "add"); 
  std::cout << f(1, 32) << std::endl; 
  FreeLibrary(handle);
  std::cout << "hello world" << std::endl;

  return 0; 
}