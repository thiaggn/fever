#pragma once
#include "buffer.h"
#include "program.h"
#include "shader.h"
#include "shared/aliases.h"
#include "shared/enums.h"
#include "texture.h"
#include <glad/glad.h>

namespace gl {
    struct state {
        friend struct instance;
        uint handle;

        void recover() const;
        void add(const vertex_buffer &b) const;
        void add(const index_buffer &b) const;

    private:
        state();
    };

    struct instance {
        void clear_color(float r, float g, float b, float a) const;
        void clear(buffer_bit b) const;
        void draw_buffer(primitive p, int first, int many_vertices) const;
        void draw_elements(primitive p, int count, data_type index_dtype, void *offset) const;
        state create_state() const;
    };

    void check_error();
}

extern const gl::instance GL;
