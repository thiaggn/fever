#pragma once
#include "glad/glad.h"


namespace gl {
    enum boolean {
        no = GL_FALSE,
        yes = GL_TRUE
    };

    enum primitive {
        triangles = GL_TRIANGLES
    };

    enum data_type {
        float32 = GL_FLOAT,
        uint32 = GL_UNSIGNED_INT,
        ubyte = GL_UNSIGNED_BYTE,
        int32 = GL_INT
    };

    enum buffer_bit {
        color_buffer_bit = GL_COLOR_BUFFER_BIT,
        stencil_buffer_bit = GL_STENCIL_BUFFER_BIT
    };
}