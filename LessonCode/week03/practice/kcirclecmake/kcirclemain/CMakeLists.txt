cmake_minimum_required(VERSION 3.10)

project(KCircleMain)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include(../kcircle/kcircle.cmake)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES_FILE})

# 向工程添加多个特定头文件的搜索路径  -I
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS_DIR})

# 显式添加头文件，使其在IDE中可见
target_sources(${PROJECT_NAME} PRIVATE ${HEADERS_FILE})