cmake_minimum_required(VERSION 3.20)
project(glad)

set(GLAD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")
set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE INTERNAL "")

add_library(${PROJECT_NAME} STATIC
            "${GLAD_SOURCE_DIR}"
            "${GLAD_INCLUDE_DIRS}"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${GLAD_INCLUDE_DIR}")