#pragma once
#include <glad/glad.h>
#include "shared/aliases.h"
#include <stdio.h>
#include <stdlib.h>

namespace gl {
    enum wrap_mode {
        repeat = GL_REPEAT,
        clamp_to_edge = GL_CLAMP_TO_EDGE,
        clamp_to_border = GL_CLAMP_TO_BORDER,
        clamp_to_edge_mirror = GL_MIRROR_CLAMP_TO_EDGE,
    };
    
    enum tex_dimensions {
        dim_2d = GL_TEXTURE_2D,
        dim_3d = GL_TEXTURE_3D,
    };

    enum tex_filtering {
        nearest = GL_NEAREST,
        linear = GL_LINEAR,
    };

    struct tex_wrapping {
        wrap_mode s;
        wrap_mode t;
        wrap_mode r;

        tex_wrapping() : s(repeat), t(repeat), r(repeat) {}
    };

    struct filtering {
        tex_filtering min;
        tex_filtering mag;

        filtering() : min(nearest), mag(nearest) {}
    };

    struct texture_create_info {
        tex_dimensions dimension;
        tex_wrapping wrap;
        filtering filter;
        struct { filtering filter; } mipmap;

        explicit texture_create_info(tex_dimensions d) : dimension(d) {};
    };

    struct texture {
        uint handle;
        uint target;

        explicit texture (const texture_create_info &p, const char *path);
        void use(uint unit) const;
    };
}