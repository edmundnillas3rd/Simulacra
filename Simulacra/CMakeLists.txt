cmake_minimum_required(VERSION 3.20)
project(Simulacra)

set(API_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
    "${SRC_DIR}/Core/Application.cpp"
    "${SRC_DIR}/Core/Log.cpp"
    "${SRC_DIR}/Core/Window.cpp"
    "${SRC_DIR}/Core/Input.cpp"
    "${SRC_DIR}/Platform/SDL2/SDL2.cpp"
    "${SRC_DIR}/Platform/Linux/FileSystem.cpp"
    "${SRC_DIR}/Platform/OpenGL/Shader.cpp"
    "${SRC_DIR}/Platform/OpenGL/Framebuffer.cpp"
    "${SRC_DIR}/Platform/OpenGL/Texture.cpp"
    "${SRC_DIR}/ImGui/ImGui.cpp"
    "${SRC_DIR}/Scene/Scene.cpp"
    "${API_DIR}/spch.cpp"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imguizmo")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb")

find_package(SDL2 CONFIG REQUIRED)
find_package(spdlog REQUIRED)
find_package(glm REQUIRED)

add_library(
    ${PROJECT_NAME} STATIC
    ${SOURCE_FILES}
)
        
# set_target_properties(
#     ${PROJECT_NAME}
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${BIN_DIR}/$<CONFIG>"
#     LIBRARY_OUTPUT_DIRECTORY "${BIN_DIR}/$<CONFIG>"
# )

target_include_directories(
    ${PROJECT_NAME} 
    SYSTEM
    PUBLIC 
    ${SRC_DIR}
    ${API_DIR}
)

set(LIBRARIES
    # Static libraries
    SDL2::SDL2
    SDL2::SDL2main
    spdlog::spdlog
    glm::glm

    # Header only libraries
    glad
    imgui
    imguizmo
    stb
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_precompile_headers(
    ${PROJECT_NAME}
    PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/spch.h>"
)
