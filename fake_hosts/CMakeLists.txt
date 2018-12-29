cmake_minimum_required(VERSION 3.5)
project(fake_hosts)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRCS ./fake_hosts.cpp)
add_library(${PROJECT_NAME} SHARED ${SRCS})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
