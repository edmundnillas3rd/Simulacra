cmake_minimum_required(VERSION 3.20)
project(Simulacra)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
    "${SRC_DIR}/Main.cpp"
    "${SRC_DIR}/Core/Application.cpp"
    "${SRC_DIR}/Platform/Windows/Window.cpp"
    "${SRC_DIR}/Platform/OpenGL/OpenGL.cpp"
    "${SRC_DIR}/Platform/OpenGL/GLDebug.cpp"
    "${SRC_DIR}/Platform/OpenGL/GLBuffer.cpp"
    "${SRC_DIR}/Platform/OpenGL/GLBufferLayout.cpp"
    "${SRC_DIR}/Platform/OpenGL/GLShader.cpp"
    "${SRC_DIR}/Platform/OpenGL/GLTexture.cpp"
)

set(HEADER_FILES
    "${SRC_DIR}/Simulacra.h"
    "${SRC_DIR}/Core/Application.h"
    "${SRC_DIR}/Platform/Windows/Window.h"
    "${SRC_DIR}/Platform/OpenGL/OpenGL.h"
    "${SRC_DIR}/Platform/OpenGL/GLDebug.h"
    "${SRC_DIR}/Platform/OpenGL/GLBuffer.h"
    "${SRC_DIR}/Platform/OpenGL/GLBufferLayout.h"
    "${SRC_DIR}/Platform/OpenGL/GLShader.h"
    "${SRC_DIR}/Platform/OpenGL/GLTexture.h"
)

add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/glad")
add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/stb")

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
               "${SOURCE_FILES}"
               "${HEADER_FILES}"
)
        
set_target_properties(${PROJECT_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/$<CONFIG>"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${SRC_DIR}" "${GLAD_INCLUDE_DIRS}")

set(LIBRARIES
    SDL2::SDL2
    SDL2::SDL2main
    glad
    stb
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)