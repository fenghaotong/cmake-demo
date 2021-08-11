cmake_minimum_required(VERSION 3.16) 

PROJECT(demo)

# 添加子项目
ADD_SUBDIRECTORY(lib)

# 设置源码路径
SET(LIBHELLO_SRC ./src/main.cpp)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # 设置输出路径
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./bin)

# add_library(common STATIC main.cpp) #生成静态库
add_library(main SHARED ${LIBHELLO_SRC}) #生成动态库或共享库

# INSTALL(TARGETS main) 

# 设置dll的输出位置
SET_TARGET_PROPERTIES(main PROPERTIES LINKER_LANGUAGE C 
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} 
      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} 
      OUTPUT_NAME "main" 
      PREFIX "")

# # 头文件路径
# INCLUDE_DIRECTORIES("include", "./")
# # 枚举头文件
# file(GLOB_RECURSE INCLUDES "include/*.h" "include/*.hpp" "include/*.cpp")


# # 指定引用的外部库的搜索路径
# LINK_DIRECTORIES("../lib/lib_out/Release/")

# # 枚举源文件
# aux_source_directory("./" SOURCES)

# 输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(${PROJECT_NAME} ${LIBHELLO_SRC})

# TARGET_LINK_LIBRARIES(${PROJECT_NAME}
# my_dll.dll
# )



