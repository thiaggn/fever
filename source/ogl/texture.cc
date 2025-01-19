#include "texture.h"
#include "shared/enums.h"
#include <rsc/resource.h>
#include <stdio.h>
#include <stdlib.h>

namespace gl {
    static void bind_min_filter(const texture_create_info &p) {
        if (p.filter.min == linear && p.mipmap.filter.min == linear) {
            glTexParameteri(p.dimension, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        } else if (p.filter.min == nearest && p.mipmap.filter.min == nearest) {
            glTexParameteri(p.dimension, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        } else if (p.filter.min == linear && p.mipmap.filter.min == nearest) {
            glTexParameteri(p.dimension, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        } else if (p.filter.min == nearest && p.mipmap.filter.min == linear) {
            glTexParameteri(p.dimension, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        } else {
            fprintf(stderr, "error: texture: invalid texture filtering parameters\n");
            exit(EXIT_FAILURE);
        }
    }

    static void bind_mag_filter(const texture_create_info &p) {
        if (p.filter.mag == linear && p.mipmap.filter.mag == linear) {
            glTexParameteri(p.dimension, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        } else if (p.filter.mag == nearest && p.mipmap.filter.mag == nearest) {
            glTexParameteri(p.dimension, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        } else if (p.filter.mag == linear && p.mipmap.filter.mag == nearest) {
            glTexParameteri(p.dimension, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        } else if (p.filter.mag == nearest && p.mipmap.filter.mag == linear) {
            glTexParameteri(p.dimension, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        } else {
            fprintf(stderr, "error: texture: invalid texture filtering parameters\n");
            exit(EXIT_FAILURE);
        }
    }

    texture::texture(const texture_create_info &p, const char *path) : handle(0), target(p.dimension) {
        rsc_image img = rsc_read_image(path);
        glGenTextures(1, &handle);
        glBindTexture(p.dimension, handle);

        int ch_count = img.channel_count == 4 ? GL_RGBA : GL_RGB;
        printf("info: image \"%s\" has %d channels\n", path, img.channel_count);

        switch (p.dimension) {
            case dim_2d:
                glTexImage2D(dim_2d, 0, ch_count, img.width, img.height, 0, ch_count, gl::ubyte, img.bytes);
                glGenerateMipmap(dim_2d);
                break;

            default:
                fprintf(stderr, "error: texture: unhandled texture dimension\n");
                exit(EXIT_FAILURE);
        }

        glTexParameteri(p.dimension, GL_TEXTURE_WRAP_S, p.wrap.s);
        glTexParameteri(p.dimension, GL_TEXTURE_WRAP_T, p.wrap.t);
        glTexParameteri(p.dimension, GL_TEXTURE_WRAP_R, p.wrap.r);

        bind_min_filter(p);
        bind_mag_filter(p);
        img.release();
    }

    void texture::use(uint unit) const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(target, handle);
    }

}