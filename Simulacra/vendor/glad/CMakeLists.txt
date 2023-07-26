cmake_minimum_required(VERSION 3.20)
project(glad)

set(GLAD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")
set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_library(
    ${PROJECT_NAME} STATIC
    ${GLAD_SOURCE_DIR}
)

target_include_directories(
        ${PROJECT_NAME} SYSTEM
        PUBLIC ${GLAD_INCLUDE_DIR}
)