#include "texture.h"
#include <rsc/resource.h>
#include "shared/enums.h"

static void bind_min_filter(const gl_texture_params &p) {
    if(p.filter.min == gl_linear && p.mipmap.filter.min == gl_linear) {
        glTexParameteri(p.dimension, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else if(p.filter.min == gl_nearest && p.mipmap.filter.min == gl_nearest) {
        glTexParameteri(p.dimension, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    }
    else if(p.filter.min == gl_linear && p.mipmap.filter.min == gl_nearest) {
        glTexParameteri(p.dimension, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    }
    else if(p.filter.min == gl_nearest && p.mipmap.filter.min == gl_linear) {
        glTexParameteri(p.dimension, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    }
    else {
        fprintf(stderr, "error: gl_texture: invalid texture filtering parameters\n");
        exit(EXIT_FAILURE);
    }
}

static void bind_mag_filter(const gl_texture_params &p) {
    if (p.filter.mag == gl_linear && p.mipmap.filter.mag == gl_linear) {
        glTexParameteri(p.dimension, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else if (p.filter.mag == gl_nearest && p.mipmap.filter.mag == gl_nearest) {
        glTexParameteri(p.dimension, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    }
    else if (p.filter.mag == gl_linear && p.mipmap.filter.mag == gl_nearest) {
        glTexParameteri(p.dimension, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    }
    else if (p.filter.mag == gl_nearest && p.mipmap.filter.mag == gl_linear) {
        glTexParameteri(p.dimension, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    }
    else {
        fprintf(stderr, "error: gl_texture: invalid texture filtering parameters\n");
        exit(EXIT_FAILURE);
    }
}

gl_texture::gl_texture(const gl_texture_params &p, const char *path): handle(0), target(p.dimension) {
    rsc_image img = rsc_read_image(path);
    glGenTextures(1, &handle);
    glBindTexture(p.dimension, handle);

    int ch_count = img.channels_count == 4 ? GL_RGBA : GL_RGB;

    switch (p.dimension) {
        case gl_2D:
            glTexImage2D(gl_2D, 0, ch_count, img.width, img.height, 0, ch_count,gl_ubyte, img.bytes);
            glGenerateMipmap(gl_2D);
            break;

        default:
            fprintf(stderr, "error: gl_texture: unhandled texture dimension\n");
            exit(EXIT_FAILURE);
    }

    glTexParameteri(p.dimension, GL_TEXTURE_WRAP_S, p.wrap.s);
    glTexParameteri(p.dimension, GL_TEXTURE_WRAP_T, p.wrap.t);
    glTexParameteri(p.dimension, GL_TEXTURE_WRAP_R, p.wrap.r);

    bind_min_filter(p);
    bind_mag_filter(p);
    img.release();
}

void gl_texture::use() const {
    glBindTexture(target, handle);
}
