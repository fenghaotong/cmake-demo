cmake_minimum_required(VERSION 3.16) 

PROJECT(encryt)

# # 生成unicode工程
# add_definitions(-DUNICODE -D_UNICODE)

# 添加所有源文件
# SET(MAIN_PATH ${PROJECT_SOURCE_DIR}/)
# aux_source_directory(${MAIN_PATH}/ sourceList)


# 设置变量 
SET(ALL_SRCS ./src/encrypt.cpp) 

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定使用的头文件路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../include/)
# # 指定静态链接库路径pPp
LINK_LIBRARIES(
  ${PROJECT_SOURCE_DIR}/../lib/${TAG}/*.lib
)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(${PROJECT_NAME} ${ALL_SRCS})
