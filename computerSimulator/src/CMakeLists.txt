cmake_minimum_required(VERSION 3.27)

add_executable(ComputerSimulator main2.cpp
                ${MY_INCLUDE_DIR}/cpu.h
                ${MY_INCLUDE_DIR}/disk.h
                ${MY_INCLUDE_DIR}/gpu.h
                ${MY_INCLUDE_DIR}/kbd.h
                ${MY_INCLUDE_DIR}/ram.h
                ${MY_INCLUDE_DIR}/utils.h)

target_include_directories(ComputerSimulator PUBLIC ${MY_INCLUDE_DIR})