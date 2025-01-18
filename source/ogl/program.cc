#include "program.h"
#include "shader.h"
#include "shared/aliases.h"
#include "shared/enums.h"
#include <stdio.h>
#include <stdlib.h>

gl_program::gl_program() {
    handle = glCreateProgram();
    glUseProgram(handle);
}

void gl_program::add(gl_shader_type type, const char *path) const {
    struct gl_shader s = gl_shader(type, path);
    glAttachShader(handle, s.handle);
    glDeleteShader(s.handle);
}

void gl_program::add(gl_shader s) const {
    glAttachShader(handle, s.handle);
    glDeleteShader(s.handle);
}

void gl_program::link() const {
    glLinkProgram(handle);
    glUseProgram(handle);
    if (!linking_succeded()) {
        exit(EXIT_FAILURE);
    }
}

void gl_program::use() const {
    glUseProgram(handle);
}

int gl_program::linking_succeded() const {
    int success;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(handle, 512, nullptr, info_log);
        fprintf(stderr, "error: gl_program::link: failed to link shader.\n");
        fprintf(stderr, "%s", info_log);
    }

    return success;
}

static int get_location(uint prog_handle, const char*name) {
    int location = glGetUniformLocation(prog_handle, name);
    if (location == -1) {
        fprintf(stderr, "error: gl_program::get_location: uniform %s not found.\n", name);
        exit(EXIT_FAILURE);
    }

    return location;
}

struct gl_uniform gl_program::set_uniform(const char *name, int v) const {
    struct gl_uniform u {};
    u.location = get_location(handle, name);
    u.update(v);
    return u;
}

struct gl_uniform gl_program::set_uniform(const char *name, int v1, int v2) const {
    struct gl_uniform u {};
    u.location = get_location(handle, name);
    u.update(v1, v2);
    return u;
}

struct gl_uniform gl_program::set_uniform(const char *name, int v1, int v2, int v3) const {
    struct gl_uniform u {};
    u.location = get_location(handle, name);
    u.update(v1, v2, v3);
    return u;
}

struct gl_uniform gl_program::set_uniform(const char *name, int v1, int v2, int v3, int v4) const {
    struct gl_uniform u {};
    u.location = get_location(handle, name);
    u.update(v1, v2, v3, v4);
    return u;
}

struct gl_uniform gl_program::set(const char *name, float v) const {
    struct gl_uniform u {};
    u.location = get_location(handle, name);
    u.update(v);
    return u;
}

struct gl_uniform gl_program::set_uniform(const char *name, float v1, float v2) const {
    struct gl_uniform u {};
    u.location = get_location(handle, name);
    u.update(v1, v2);
    return u;
}

struct gl_uniform gl_program::set_uniform(const char *name, float v1, float v2, float v3) const {
    struct gl_uniform u {};
    u.location = get_location(handle, name);
    u.update(v1, v2, v3);
    return u;
}

struct gl_uniform gl_program::set_uniform(const char *name, float v1, float v2, float v3, float v4) const {
    struct gl_uniform u {};
    u.location = get_location(handle, name);
    u.update(v1, v2, v3, v4);
    return u;
}

void gl_uniform::update(float v) const {
    glUniform1f(location, v);
}

void gl_uniform::update(float v1, float v2) const {
    glUniform2f(location, v1, v2);
}

void gl_uniform::update(float v1, float v2, float v3) const {
    glUniform3f(location, v1, v2, v3);
}

void gl_uniform::update(float v1, float v2, float v3, float v4) const {
    glUniform4f(location, v1, v2, v3, v4);
}

void gl_uniform::update(int v) const {
    glUniform1i(location, v);
}

void gl_uniform::update(int v1, int v2) const {
    glUniform2i(location, v1, v2);
}

void gl_uniform::update(int v1, int v2, int v3) const {
    glUniform3i(location, v1, v2, v3);
}

void gl_uniform::update(int v1, int v2, int v3, int v4) const {
    glUniform4i(location, v1, v2, v3, v4);
}
