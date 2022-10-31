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
    "${SRC_DIR}/Platform/OpenGL/GLShader.cpp"
)

set(HEADER_FILES
    "${SRC_DIR}/Simulacra.h"
    "${SRC_DIR}/Core/Application.h"
    "${SRC_DIR}/Platform/Windows/Window.h"
    "${SRC_DIR}/Platform/OpenGL/OpenGL.h"
    "${SRC_DIR}/Platform/OpenGL/GLDebug.h"
    "${SRC_DIR}/Platform/OpenGL/GLShader.h"
)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
               "${SOURCE_FILES}"
               "${HEADER_FILES}"
)
        
set_target_properties(${PROJECT_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/$<CONFIG>"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${SRC_DIR}")

set(LIBRARIES
    SDL2::SDL2
    SDL2::SDL2main
    glad::glad
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)