cmake_minimum_required(VERSION 3.0.0)
project(opengl_test VERSION 0.1.0)

include(CTest)
enable_testing()

INCLUDE_DIRECTORIES(include)

link_directories(lib)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/")

add_executable(opengl_test src/main.cpp src/glad.c)

TARGET_LINK_LIBRARIES(opengl_test libglfw3dll.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)