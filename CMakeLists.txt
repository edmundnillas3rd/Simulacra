cmake_minimum_required(VERSION 3.20)
project(Simulacra)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
    "${SRC_DIR}/Main.cpp"
)

set(HEADER_FILES
)

add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/glad")
# add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/stb")

find_package(SDL2 CONFIG REQUIRED)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
)
        
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/$<CONFIG>"
)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC ${SRC_DIR}
)

set(LIBRARIES
    SDL2::SDL2
    SDL2::SDL2main
    glad
    # stb
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)