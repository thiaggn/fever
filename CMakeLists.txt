cmake_minimum_required(VERSION 3.28)
project(fever_renderer)

set(CMAKE_CXX_STANDARD 17)



add_executable(fever_renderer
        source/main.cc
        source/ctx/context.cc
        source/ctx/context.h
        source/ogl/buffer.cc
        source/ogl/buffer.h
        source/ogl/shader.cc
        source/ogl/shader.h
)
target_include_directories(fever_renderer PRIVATE "./source")

# Dependencias

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(fever_renderer PRIVATE glfw)

target_sources(fever_renderer PRIVATE "./vendor/glad/src/glad.c")
target_include_directories(fever_renderer PRIVATE "./vendor/glad/include")

