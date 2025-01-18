cmake_minimum_required(VERSION 3.28)
project(fever_renderer)
set(CMAKE_CXX_STANDARD 17)

# Definições

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/bin")

# Executável
add_executable(fever_renderer
        source/main.cc
        source/ctx/context.cc
        source/ctx/context.h
        source/ogl/opengl.h
        source/rsc/resource.cc
        source/rsc/resource.h
        source/rsc/resource.h
        source/ogl/opengl.cc
        source/ogl/shared/enums.h
        source/ogl/program.cc
        source/ogl/program.cc
        source/ogl/shader.cc
        source/ogl/shader.cc
        source/ogl/buffer.cc
        source/ogl/buffer.h
        source/ogl/buffer.h
        source/ogl/buffer.cc
        source/ogl/shared/aliases.h
        source/ogl/shared/aliases.h
        source/ogl/shared/aliases.cc
        source/ogl/shared/aliases.cc
        source/ogl/program.h
        source/ogl/program.h
        source/ogl/shader.h
)
target_include_directories(fever_renderer PRIVATE "./source")

# Dependencias
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(fever_renderer PRIVATE glfw)

target_sources(fever_renderer PRIVATE "./vendor/glad/src/glad.c")
target_include_directories(fever_renderer PRIVATE "./vendor/glad/include")

