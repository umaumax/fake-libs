cmake_minimum_required(VERSION 3.5)
project(fake_SSL_write)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
link_libraries(-ldl -lssl)

find_package(OpenSSL REQUIRED)
if(NOT OPENSSL_FOUND)
  message(SEND_ERROR "Fail to find OpenSSL")
endif()
message(STATUS "OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
include_directories(${OPENSSL_INCLUDE_DIR})

set(SRCS ./fake_SSL_write.cpp)
add_library(${PROJECT_NAME} SHARED ${SRCS})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
