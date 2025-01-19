#pragma once
#include "glad/glad.h"
#include "shared/aliases.h"
#include "shared/enums.h"

namespace gl {
    enum shader_type {
        fragment_shader = GL_FRAGMENT_SHADER,
        vertex_shader = GL_VERTEX_SHADER,
        comp_shader = GL_COMPUTE_SHADER,
        geom_shader = GL_GEOMETRY_SHADER,
        tesscontrol_shader = GL_TESS_CONTROL_SHADER,
        tesseval_shader = GL_TESS_EVALUATION_SHADER
    };

    struct shader {
        uint handle;

        shader(shader_type type, const char *path);
        int compilation_succeded(uint shader);
    };
}