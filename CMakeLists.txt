cmake_minimum_required(VERSION 3.0)
project(helloopengl)

set(CMAKE_CXX_STANDARD 17)

add_executable(helloopengl main.cpp src/glad.c)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(helloopengl  ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)