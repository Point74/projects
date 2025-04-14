cmake_minimum_required(VERSION 3.27)

add_executable(ElectronicDigitalSignature main.cpp
        ${MY_INCLUDE_DIR}/DSAKeyGenerator.h
        ${MY_INCLUDE_DIR}/DSASigner.h
        ${MY_INCLUDE_DIR}/DSAVerifier.h
        ${MY_INCLUDE_DIR}/utils.h)

target_include_directories(ElectronicDigitalSignature PUBLIC ${MY_INCLUDE_DIR})