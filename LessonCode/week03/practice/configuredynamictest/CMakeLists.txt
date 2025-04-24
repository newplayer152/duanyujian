cmake_minimum_required(VERSION 3.10)

project(ConfigureTest)

add_executable(${PROJECT_NAME})

find_package(GTest CONFIG REQUIRED)

#向工程添加源码
target_sources(${PROJECT_NAME} PRIVATE
    configuretest.cpp
)

#向工程添加头文件路径 -I
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../configuredynamiclib
)

# 链接 Google Test 到测试目标
target_link_libraries(${PROJECT_NAME} PRIVATE
    ConfigureDynamicLib
    GTest::gmock 
    GTest::gtest 
  )
