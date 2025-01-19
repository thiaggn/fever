#include "program.h"
#include "shader.h"
#include "opengl.h"
#include "shared/aliases.h"
#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <glm/gtc/type_ptr.hpp>

namespace gl {
    static int get_location(uint prog_handle, const char *name) {
        int location = glGetUniformLocation(prog_handle, name);

        if (location == -1) {
            fprintf(stderr, "error: gl::program::get_location: uniform \"%s\" not found.\n", name);
            exit(EXIT_FAILURE);
        }

        return location;
    }

    program::program() {
        handle = glCreateProgram();
        glUseProgram(handle);
    }

    void program::add_shader(shader_type type, const char *path) const {
        shader s(type, path);
        glAttachShader(handle, s.handle);
        glDeleteShader(s.handle);
    }

    void program::add_shader(shader s) const {
        glAttachShader(handle, s.handle);
        glDeleteShader(s.handle);
    }

    void program::add_texture(uint unit, const char *name, texture t) {
        textures.emplace_back(unit, name, t);
    }

    void program::save() const {
        glLinkProgram(handle);
        glUseProgram(handle);

        if (!linking_succeded()) {
            exit(EXIT_FAILURE);
        }

        for (const texture_descriptor &t: textures) {
            set_uniform(t.name, int(t.unit));
        }
    }

    void program::use() const {
        for (const texture_descriptor &t: textures) {
            t.tex.use(t.unit);
        }
        glUseProgram(handle);
    }

    int program::linking_succeded() const {
        int success;
        glGetProgramiv(handle, GL_LINK_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetProgramInfoLog(handle, 512, nullptr, info_log);
            fprintf(stderr, "error: gl::program::link: failed to save shader.\n");
            fprintf(stderr, "%s", info_log);
        }

        return success;
    }

    uniform program::set_uniform(const char *name, int v) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(v);
        return u;
    }

    uniform program::set_uniform(const char *name, int v1, int v2) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(v1, v2);
        return u;
    }

    uniform program::set_uniform(const char *name, int v1, int v2, int v3) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(v1, v2, v3);
        return u;
    }

    uniform program::set_uniform(const char *name, int v1, int v2, int v3, int v4) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(v1, v2, v3, v4);
        return u;
    }

    uniform program::set_uniform(const char *name, float v) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(v);
        return u;
    }

    uniform program::set_uniform(const char *name, float v1, float v2) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(v1, v2);
        return u;
    }

    uniform program::set_uniform(const char *name, float v1, float v2, float v3) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(v1, v2, v3);
        return u;
    }

    uniform program::set_uniform(const char *name, float v1, float v2, float v3, float v4) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(v1, v2, v3, v4);
        return u;
    }

    uniform program::set_uniform(const char *name, const glm::mat<4, 4, float> &data) const {
        uniform u {};
        u.location = get_location(handle, name);
        u.update(data);
        return u;
    }

    void uniform::update(float v) const {
        glUniform1f(location, v);
    }

    void uniform::update(float v1, float v2) const {
        glUniform2f(location, v1, v2);
    }

    void uniform::update(float v1, float v2, float v3) const {
        glUniform3f(location, v1, v2, v3);
    }

    void uniform::update(float v1, float v2, float v3, float v4) const {
        glUniform4f(location, v1, v2, v3, v4);
    }

    void uniform::update(int v) const {
        glUniform1i(location, v);
    }

    void uniform::update(int v1, int v2) const {
        glUniform2i(location, v1, v2);
    }

    void uniform::update(int v1, int v2, int v3) const {
        glUniform3i(location, v1, v2, v3);
    }

    void uniform::update(int v1, int v2, int v3, int v4) const {
        glUniform4i(location, v1, v2, v3, v4);
    }

    void uniform::update(const glm::mat<4, 4, float> &data) const {
        glUniformMatrix4fv(location, 1, gl::no, glm::value_ptr(data));
    }
}