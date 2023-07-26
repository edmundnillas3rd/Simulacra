cmake_minimum_required(VERSION 3.26)
project(Super-Mario)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
    "${SRC_DIR}/Main.cpp"
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/$<CONFIG>"
)

target_link_libraries(${PROJECT_NAME} PUBLIC Simulacra)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)