#pragma once
#include "glad/glad.h"
#include "shader.h"
#include "shared/aliases.h"
#include "shared/enums.h"

struct gl_uniform {
    int location;

    void update(float v) const;
    void update(float v1, float v2) const;
    void update(float v1, float v2, float v3) const;
    void update(float v1, float v2, float v3, float v4) const;

    void update(int v) const;
    void update(int v1, int v2) const;
    void update(int v1, int v2, int v3) const;
    void update(int v1, int v2, int v3, int v4) const;
};

struct gl_program {
    uint handle;

    gl_program();
    void add(gl_shader_type type, const char *path) const;
    void attach_shader(gl_shader s) const;

    gl_uniform set_uniform(const char *name, float v) const;
    gl_uniform set_uniform(const char *name, float v1, float v2) const;
    gl_uniform set_uniform(const char *name, float v1, float v2, float v3) const;
    gl_uniform set_uniform(const char *name, float v1, float v2, float v3, float v4) const;

    gl_uniform set_uniform(const char *name, int v) const;
    gl_uniform set_uniform(const char *name, int v1, int v2) const;
    gl_uniform set_uniform(const char *name, int v1, int v2, int v3) const;
    gl_uniform set_uniform(const char *name, int v1, int v2, int v3, int v4) const;

    void link() const;
    void use() const;
    int linking_succeded() const;
};