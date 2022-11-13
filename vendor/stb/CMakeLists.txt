cmake_minimum_required(VERSION 3.20)
project(stb)

set(STB_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp")
set(STB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "")

add_library(${PROJECT_NAME} STATIC 
            "${STB_SOURCE_DIR}" 
            "${STB_INCLUDE_DIR}"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${STB_INCLUDE_DIR}")