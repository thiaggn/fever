#pragma once
#include "glad/glad.h"
#include "shader.h"
#include "shared/aliases.h"
#include "texture.h"
#include <glm/matrix.hpp>
#include <variant>
#include <vector>

namespace gl {
    struct texture_descriptor {
        const char *name;
        uint unit;
        texture tex;

        texture_descriptor(uint unit, const char *name, texture tex)
            : name(name), unit(unit), tex(tex) {}
    };

    struct uniform {
        int location;

        void update(float v) const;
        void update(float v1, float v2) const;
        void update(float v1, float v2, float v3) const;
        void update(float v1, float v2, float v3, float v4) const;

        void update(int v) const;
        void update(int v1, int v2) const;
        void update(int v1, int v2, int v3) const;
        void update(int v1, int v2, int v3, int v4) const;

        void update(const glm::mat<4, 4, float> &data) const;
    };

    struct program {
        uint handle;
        std::vector<texture_descriptor> textures;

        program();
        void add_shader(shader_type type, const char *path) const;
        void add_shader(shader s) const;

        void add_texture(uint unit, const char *name, texture t);

        uniform set_uniform(const char *name, float v) const;
        uniform set_uniform(const char *name, float v1, float v2) const;
        uniform set_uniform(const char *name, float v1, float v2, float v3) const;
        uniform set_uniform(const char *name, float v1, float v2, float v3, float v4) const;

        uniform set_uniform(const char *name, int v) const;
        uniform set_uniform(const char *name, int v1, int v2) const;
        uniform set_uniform(const char *name, int v1, int v2, int v3) const;
        uniform set_uniform(const char *name, int v1, int v2, int v3, int v4) const;

        uniform set_uniform(const char *name, const glm::mat<4, 4, float> &data) const;

        void save() const;
        void use() const;
        int linking_succeded() const;
    };
}// namespace gl