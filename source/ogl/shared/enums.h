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
    gl_ubyte = GL_UNSIGNED_BYTE,
    gl_int = GL_INT
};

enum gl_bit {
    gl_color_buffer = GL_COLOR_BUFFER_BIT,
    stencil_buffer = GL_STENCIL_BUFFER_BIT
};