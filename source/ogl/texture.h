#pragma once
#include <glad/glad.h>
#include "shared/aliases.h"
#include <stdio.h>
#include <stdlib.h>

enum gl_wrap_mode {
    gl_repeat = GL_REPEAT,
    gl_clamp_to_edge = GL_CLAMP_TO_EDGE,
    gl_clamp_to_border = GL_CLAMP_TO_BORDER,
    gl_mirror_clamp_to_edge = GL_MIRROR_CLAMP_TO_EDGE,
};

enum gl_tex_dimensions {
    gl_2D = GL_TEXTURE_2D,
    gl_texture_3d = GL_TEXTURE_3D,
};

enum gl_tex_filtering {
    gl_nearest = GL_NEAREST,
    gl_linear = GL_LINEAR,
};

struct gl_tex_wrapping {
    gl_wrap_mode s;
    gl_wrap_mode t;
    gl_wrap_mode r;

    gl_tex_wrapping() : s(gl_repeat), t(gl_repeat), r(gl_repeat) {}
};

struct gl_filtering {
    gl_tex_filtering min;
    gl_tex_filtering mag;

    gl_filtering() : min(gl_nearest), mag(gl_nearest) {}
};

struct gl_texture_params {
    gl_tex_dimensions dimension;
    gl_tex_wrapping wrap;
    gl_filtering filter;
    struct { gl_filtering filter; } mipmap;

    explicit gl_texture_params(gl_tex_dimensions d) : dimension(d) {};

};

struct gl_texture {
    uint handle;
    uint target;

    explicit gl_texture (const gl_texture_params &p, const char *path);
    void use() const;
};
