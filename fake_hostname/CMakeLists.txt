cmake_minimum_required(VERSION 3.5)
project(fake_hostname)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
link_libraries(-ldl)

set(SRCS ./fake_gethostname.cpp)
add_library(${PROJECT_NAME} SHARED ${SRCS})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
