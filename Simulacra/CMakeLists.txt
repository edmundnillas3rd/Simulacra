cmake_minimum_required(VERSION 3.26)
project(Simulacra)

set(API_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
    "${API_DIR}/src/Simulacra/Application.cpp"
    "${API_DIR}/src/Simulacra/Input.cpp"
    "${API_DIR}/src/Platform/Windows/SDL2Windows.cpp"
    "${API_DIR}/src/Platform/Windows/SDL2WindowsTime.cpp"
    "${API_DIR}/src/Platform/OpenGL/Shaders.cpp"
    "${API_DIR}/src/Platform/OpenGL/Buffers.cpp"
    "${API_DIR}/src/Platform/OpenGL/Texture.cpp"
    "${API_DIR}/src/Platform/OpenGL/RendererAPI.cpp"
    "${API_DIR}/src/Platform/OpenGL/Framebuffer.cpp"
    "${API_DIR}/spch.cpp"
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

    # Header libraries
    imgui
    imguizmo
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_precompile_headers(
    ${PROJECT_NAME}
    PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/spch.h>"
)
