cmake_minimum_required(VERSION 3.26)
project(imguizmo)

add_library(
    ${PROJECT_NAME} STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/GraphEditor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ImCurveEdit.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ImGradient.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ImSequencer.cpp"
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    imgui
)

target_link_options(
    ${PROJECT_NAME} PRIVATE
    /incremental
    /debug:fastlink
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    /MP4
)

target_include_directories(
    ${PROJECT_NAME} SYSTEM
    PUBLIC 
    "${CMAKE_SOURCE_DIR}/vendor/imgui"
)