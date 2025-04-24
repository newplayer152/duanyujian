cmake_minimum_required(VERSION 3.10)  #cmake版本最低3.10

project(CircleDynamicMain)  #添加当前项目名称

#默认可执行文件
add_executable(${PROJECT_NAME})

#向工程添加源码
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

#向工程添加多个特定头文件和库的搜索路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../circledynamiclib
)

#链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    CircleDynamicLib)