#pragma once
#include "buffer.h"
#include "program.h"
#include "shader.h"
#include "shared/aliases.h"
#include "shared/enums.h"
#include "texture.h"
#include <glad/glad.h>

struct gl_state {
    friend struct gl_instance;
    uint handle;

    void recover() const;
    void add(const gl_vertex_buffer &b) const;
    void add(const gl_index_buffer &b) const;

private:
    gl_state();
};

struct gl_instance {
    void clear_color(float r, float g, float b, float a) const;
    void clear(gl_bit b) const;
    void draw_buffer(gl_primitive p, int first, int many_vertices) const;
    void draw_elements(gl_primitive p, int count, gl_data_type index_dtype, void *offset) const;
    gl_state create_state() const;
};

extern const gl_instance gl;
