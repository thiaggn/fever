#pragma once
#include "glad/glad.h"
#include "shared/aliases.h"
#include "shared/enums.h"

enum gl_shader_type {
    gl_fragment_shader = GL_FRAGMENT_SHADER,
    gl_vertex_shader = GL_VERTEX_SHADER,
    gl_comp_shader = GL_COMPUTE_SHADER,
    gl_geom_shader = GL_GEOMETRY_SHADER,
    gl_tesscontrol_shader = GL_TESS_CONTROL_SHADER,
    gl_tesseval_shader = GL_TESS_EVALUATION_SHADER
};

struct gl_shader {
    uint handle;

    gl_shader(gl_shader_type type, const char *path);
    int compilation_succeded(uint shader);
};