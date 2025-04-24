cmake_minimum_required(VERSION 3.10)  #cmake版本最低3.10

project(ConfigureDynamicLib)  #添加当前项目名称


#默认生成动态库
add_library(${PROJECT_NAME} SHARED)

#向工程添加源码
target_sources(${PROJECT_NAME} PRIVATE
    configure.cpp
    configure.h
)

#针对特定的目标,定义宏
target_compile_definitions(${PROJECT_NAME} PRIVATE CONFIGURE_DLL)

# 设置库的输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "configuredynamiclib"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
