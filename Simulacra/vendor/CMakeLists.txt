cmake_minimum_required(VERSION 3.26)
project(ProjectDeps_Lib)

find_package(SDL2 CONFIG REQUIRED)

add_library(${PROJECT_NAME}
    "glad/src/glad.c"
    "stb/stb_image.cpp"

    "imgui/imgui.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"

    "imgui/backends/imgui_impl_opengl3.cpp"
    "imgui/backends/imgui_impl_sdl2.cpp"
)

target_link_options(${PROJECT_NAME} PRIVATE /incremental /debug:fastlink)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

target_compile_options(${PROJECT_NAME} PRIVATE /MP4)

target_include_directories(${PROJECT_NAME} PUBLIC "glad/include" "stb" "imgui" "imgui/backends")