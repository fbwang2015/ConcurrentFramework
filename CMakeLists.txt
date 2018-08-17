cmake_minimum_required(VERSION 3.0)

project(concurrent_framework)



include_directories(
	include
)

set(src_list main.cpp
	src/agent.cpp
	src/environment.cpp
)

add_executable(${concurrent_framework} ${src_list})
	 