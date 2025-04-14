cmake_minimum_required(VERSION 3.27)
project("Electronic Digital Signature" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)