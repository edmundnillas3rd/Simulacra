cmake_minimum_required(VERSION 3.22)
project(Test C CXX)

add_executable(${PROJECT_NAME} "src/Main.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Simulacra")
target_link_libraries(${PROJECT_NAME} PUBLIC Simulacra)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)