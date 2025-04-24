cmake_minimum_required(VERSION 3.10)  #cmake版本最低3.10


project(VideoDownloadPlay)  #添加当前项目名称

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


add_executable(${PROJECT_NAME})

#向工程添加源码
target_sources(${PROJECT_NAME} PRIVATE
    videodownloadplay.cpp
)