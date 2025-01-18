#pragma once
#include "buffer.h"
#include "shader.h"
#include "program.h"
#include "shared/aliases.h"
#include "shared/enums.h"
#include <glad/glad.h>

struct gl_state {
    uint handle;

    gl_state();
    void recover() const;
    void add(const gl_vertex_buffer & b) const;
};

struct gl_instance {
    void clear_color(float r, float g, float b, float a) const;
    void clear(gl_bit b) const;
    void draw_buffer(gl_primitive p, int first, int many_vertices) const;
    void draw_elements(gl_primitive p, int count, gl_data_type index_dtype, void *offset) const;
    gl_state create_state() const;
};

extern const gl_instance gl;
