cmake_minimum_required(VERSION 3.26)
project(Simulacra)

set(API_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
    "${SRC_DIR}/Application.cpp"
    "${SRC_DIR}/Window.cpp"
    "${SRC_DIR}/Logger.cpp"
    "${SRC_DIR}/FileManager.cpp"
    "${SRC_DIR}/Platform/Windows/Win32Window.cpp"
    "${SRC_DIR}/Platform/Windows/Win32FileManager.cpp"
    "${SRC_DIR}/Platform/OpenGL/OpenGLRenderer.cpp"
    "${SRC_DIR}/Platform/OpenGL/OpenGLDebug.cpp"
    "${SRC_DIR}/Platform/OpenGL/OpenGLBuffer.cpp"
    "${SRC_DIR}/Platform/OpenGL/OpenGLShader.cpp"
    "${SRC_DIR}/Platform/OpenGL/OpenGLTexture.cpp"
    "${SRC_DIR}/Renderer/Renderer2D.cpp"
    "${SRC_DIR}/Renderer/OrthographicCamera.cpp"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imguizmo")

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(stb CONFIG REQUIRED)
find_package(lua CONFIG REQUIRED)

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
    glad::glad
    spdlog::spdlog
    glm::glm
    stb::stb
    lua::lua

    # Header libraries
    imgui
    imguizmo
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})

target_link_options(
    ${PROJECT_NAME} PRIVATE
    /incremental
    /debug:fastlink
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    /MP4
)

target_precompile_headers(
    ${PROJECT_NAME}
    PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/spch.h>"
)
