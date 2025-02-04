#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using glfw_context = GLFWwindow;

struct ctx_context {
    glfw_context *handle;

    void swap_buffers() const;

    void terminate() const;

    double get_time() const;

    [[nodiscard]] bool available() const;
};

struct ctx_context ctx_create(int width, int height, const char *title);