cmake_minimum_required(VERSION 3.16) 

# 设置变量 
SET(LIBHELLO_SRC ./src/NetIOForWindows.cpp ./src/NetIOForWindows.h) 
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/) # 第一个参数为你需要构建的dll的名字，第二个为类型 

ADD_LIBRARY(NetIOForWindows SHARED ${LIBHELLO_SRC}) 

INSTALL(TARGETS NetIOForWindows) 

# 为dll设置linker 
# 指定dll的生成目录，这里是：./bin
SET_TARGET_PROPERTIES(NetIOForWindows PROPERTIES LINKER_LANGUAGE C 
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} 
      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} 
      OUTPUT_NAME "NetIOForWindows" 
      PREFIX "")
