//
// Created by @thiaggn on 12/01/2025.
//

#include "context.h"
#include <stdio.h>
#include <stdlib.h>

static void handle_glfw_error(int code, const char *desc) {
    printf("error: glfw: \"%d\" %s\n", code, desc);
}

static bool has_started_glfw = false;

static bool has_loaded_glad = false;

static void glfw_setup() {
    if (!has_started_glfw) {
        has_started_glfw = true;

        if (!glfwInit()) {
            printf("error: glfw: failed to start\n");
            exit(EXIT_FAILURE);
        }
        else printf("info: glfw: success to start\n");
        glfwSetErrorCallback(handle_glfw_error);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }
}

struct ctx_context ctx_create(int width, int height, const char *title) {
    glfw_setup();

    ctx_context c {};
    c.handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(c.handle);

    if (c.handle == nullptr) {
        printf("error: ctx_context: glfw: failed to create context");
        exit(EXIT_FAILURE);
    }

    if(!has_loaded_glad) {
        has_loaded_glad = true;

        int version = gladLoadGL();
        printf("info: glad: loaded GL %d\n", version);
    }

    return c;
}

void ctx_context::swap_buffers() const {
    glfwPollEvents();
    glfwSwapBuffers(handle);
}

void ctx_context::terminate() const {
    glfwDestroyWindow(handle);
    glfwTerminate();
}

bool ctx_context::available() const {
    return !glfwWindowShouldClose(handle);
}
