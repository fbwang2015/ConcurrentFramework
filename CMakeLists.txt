cmake_minimum_required(VERSION 3.0)

project(concurrent_framework)

add_definitions(-std=c++11)

include_directories(
	include
)

set(src_list main.cpp
    src/agent.cpp
    src/environment.cpp
    src/workflow.cpp
)

add_executable(${PROJECT_NAME} ${src_list})