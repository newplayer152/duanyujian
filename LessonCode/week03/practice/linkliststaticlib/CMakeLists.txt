cmake_minimum_required(VERSION 3.10)  #cmake版本最低3.10

project(LinklistStaticLib)  #添加当前项目名称



#默认生成静态库
add_library(${PROJECT_NAME} STATIC)

#向工程添加源码
target_sources(${PROJECT_NAME} PRIVATE
    linklistnode.h
    linklistnode.cpp
    linklist.h
    linklist.cpp
)

#向工程添加多个特定头文件的搜索路径—— -I参数
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}
)