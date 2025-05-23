cmake_minimum_required(VERSION 3.26)
project(Sandbox)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
    "${SRC_DIR}/Sandbox.cpp"
    "${SRC_DIR}/Terrain/Terrain.cpp"
    "${SRC_DIR}/Terrain/CellularAutomataGen.cpp"
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
)

target_link_options(
    ${PROJECT_NAME} PRIVATE
    /debug:fastlink
    /incremental
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    /MP4
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/$<CONFIG>"
)

target_link_libraries(${PROJECT_NAME} PUBLIC Simulacra)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE /wd4312)
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})