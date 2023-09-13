cmake_minimum_required(VERSION 3.26)
project(stb)

set(STB_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp")
set(STB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_library(
    ${PROJECT_NAME} STATIC
    ${STB_SOURCE_DIR}
)

target_include_directories(
    ${PROJECT_NAME} SYSTEM
    PUBLIC ${STB_INCLUDE_DIR}
)