cmake_minimum_required(VERSION 3.20)
project(Simulacra)

set(API_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
    "${SRC_DIR}/Application.cpp"
    "${SRC_DIR}/Log.cpp"
    "${SRC_DIR}/Window.cpp"
    "${SRC_DIR}/Platform/SDL2/SDL2.cpp"
    "${API_DIR}/spch.cpp"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad")
# add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/stb")

find_package(SDL2 CONFIG REQUIRED)
find_package(spdlog REQUIRED)

add_library(
    ${PROJECT_NAME} STATIC
    ${SOURCE_FILES}
)
        
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${BIN_DIR}/$<CONFIG>"
)

target_include_directories(
    ${PROJECT_NAME} 
    SYSTEM
    PUBLIC 
    ${SRC_DIR}
    ${API_DIR}
)

set(LIBRARIES
    SDL2::SDL2
    SDL2::SDL2main
    glad
    spdlog::spdlog
    # stb
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_precompile_headers(
    ${PROJECT_NAME}
    PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/spch.h>"
)