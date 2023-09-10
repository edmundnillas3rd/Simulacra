cmake_minimum_required(VERSION 3.26)
project(imgui)

find_package(SDL2 REQUIRED)

add_library(
    ${PROJECT_NAME} STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui_demo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp"
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC 
    SDL2::SDL2
    SDL2::SDL2main
)

target_include_directories(
    ${PROJECT_NAME} SYSTEM
    PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/backends"
)