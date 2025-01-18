#pragma once
#include "glad/glad.h"


enum gl_bool_value {
    gl_false = GL_FALSE,
    gl_true = GL_TRUE
};

enum gl_primitive {
    gl_triangles = GL_TRIANGLES
};

enum gl_data_type {
    gl_float = GL_FLOAT,
    gl_uint = GL_UNSIGNED_INT,
    gl_int = GL_INT
};

enum gl_shader_type {
    gl_vert_shader = GL_VERTEX_SHADER,
    gl_frag_shader = GL_FRAGMENT_SHADER,
    gl_comp_shader = GL_COMPUTE_SHADER,
    gl_geom_shader = GL_GEOMETRY_SHADER,
    gl_tesscontrol_shader = GL_TESS_CONTROL_SHADER,
    gl_tesseval_shader = GL_TESS_EVALUATION_SHADER
};

enum gl_buffer_usage {
    static_draw = GL_STATIC_DRAW,
    dynamic_draw = GL_DYNAMIC_DRAW,
    stream_draw = GL_STREAM_DRAW
};

enum gl_bit {
    gl_color_buffer = GL_COLOR_BUFFER_BIT,
    stencil_buffer = GL_STENCIL_BUFFER_BIT
};