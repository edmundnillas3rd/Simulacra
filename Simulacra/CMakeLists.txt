cmake_minimum_required(VERSION 3.26)
project(Simulacra)

set(SOURCE_FILES 
    "src/Core/Application.cpp"
    "src/Core/FileManager.cpp"
    "src/Core/Logger.cpp"

    "src/Platform/OpenGL/OpenGLBuffer.cpp" 
    "src/Platform/OpenGL/OpenGLDebug.cpp" 
    "src/Platform/OpenGL/OpenGLRenderer.cpp" 
    "src/Platform/OpenGL/OpenGLShader.cpp" 
    "src/Platform/OpenGL/OpenGLTexture.cpp" 

    "src/Platform/Windows/Win32FileManager.cpp" 
    "src/Platform/Windows/Win32Window.cpp" 

    "src/Renderer/OrthographicCamera.cpp"
    "src/Renderer/Renderer2D.cpp"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imguizmo")

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(stb CONFIG REQUIRED)

add_library(
    ${PROJECT_NAME} STATIC
    ${SOURCE_FILES}
)

set(LIBRARIES
    # Static libraries
    SDL2::SDL2
    SDL2::SDL2main
    glad::glad
    spdlog::spdlog
    glm::glm
    stb::stb

    # Header libraries
    imgui
    imguizmo
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
target_link_options(${PROJECT_NAME} PRIVATE /incremental /debug:fastlink)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE /MP4)

target_precompile_headers(
    ${PROJECT_NAME}
    PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/spch.h>"
)
