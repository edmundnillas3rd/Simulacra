cmake_minimum_required(VERSION 3.26)
project(Sandbox)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
)

target_link_options(${PROJECT_NAME} PRIVATE /debug:fastlink)
target_link_options(${PROJECT_NAME} PRIVATE /incremental)

target_link_libraries(${PROJECT_NAME} PUBLIC Simulacra)

target_compile_options(${PROJECT_NAME} PRIVATE /MP4)
target_compile_options(${PROJECT_NAME} PRIVATE /wd4312)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})