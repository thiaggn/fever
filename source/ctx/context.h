#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using glfw_context = GLFWwindow;

struct ctx_context {
    glfw_context *handle;

    void render() const;

    void terminate() const;

    [[nodiscard]] bool available() const;
};

struct ctx_context ctx_create(int width, int height, const char *title);