cmake_minimum_required(VERSION 3.0.0)
project(opengl_test VERSION 0.1.0)

include(CTest)
enable_testing()

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

link_directories(lib)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/")

add_executable(opengl_test src/EBO.cpp src/glad.c src/main.cpp src/shaderClass.cpp src/stb.cpp src/texture.cpp src/VAO.cpp src/VBO.cpp)

TARGET_LINK_LIBRARIES(opengl_test libglfw3dll.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)