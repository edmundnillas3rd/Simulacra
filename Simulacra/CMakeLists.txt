cmake_minimum_required(VERSION 3.26)
project(Simulacra)

set(SOURCE_FILES 
    "src/Core/Application.cpp"
    "src/Core/Logger.cpp"
    "src/Core/Threads.cpp"

    "src/Renderer/RendererAPI.cpp"

    "src/Platform/FileSystem.cpp" 
    "src/Platform/Window.cpp"
    "src/Platform/OpenGL/OpenGLRenderer.cpp" 
    "src/Platform/OpenGL/OpenGLShader.cpp" 
    "src/Platform/OpenGL/OpenGLTexture.cpp" 
)

find_package(imgui  CONFIG REQUIRED)
find_package(SDL2   CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm    CONFIG REQUIRED)

add_subdirectory("vendor")

if (SDL2_FOUND)
    set(SOURCE_FILES 
        ${SOURCE_FILES}
        "src/Platform/SDL/SDLWindow.cpp" 
        "src/Platform/SDL/SDLOpenGLContext.cpp" 
    )
    list(APPEND SIMULACRA_DEFINITIONS SIMULACRA_SDL)
else()
    message(ERROR "Platform not supported!")
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(SOURCE_FILES
        ${SOURCE_FILES}
        "src/Platform/Windows/WindowsFileSystem.cpp" 
    )
    list(APPEND SIMULACRA_DEFINITIONS SIMULACRA_WINDOWS)
endif()

add_library(
    ${PROJECT_NAME} STATIC
    ${SOURCE_FILES}
)


set(LIBRARIES
    imgui::imgui
    SDL2::SDL2
    SDL2::SDL2main
    spdlog::spdlog
    glm::glm

    ProjectDeps_Lib
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
target_link_options(${PROJECT_NAME} PRIVATE /incremental /debug:fastlink)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE /MP4)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${SIMULACRA_DEFINITIONS})

target_precompile_headers(
    ${PROJECT_NAME}
    PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/spch.h>"
)
