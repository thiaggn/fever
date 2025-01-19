#pragma once
#include "glad/glad.h"
#include "ogl/shared/aliases.h"
#include <vector>

namespace gl {
    enum buffer_usage {
        static_draw = GL_STATIC_DRAW,
        dynamic_draw = GL_DYNAMIC_DRAW,
        stream_draw = GL_STREAM_DRAW
    };

    struct attribute {
        int location;
        int size;
        data_type type;
        boolean normalized;
        void* offset;

        attribute(int l, int s, data_type t, boolean n, void* o)
            : location(l), size(s), type(t), normalized(n), offset(o) {}
    };

    struct vertex_buffer {
        uint handle;
        int acc_offset;
        std::vector<attribute> attributes;

        vertex_buffer();
        vertex_buffer(const void *data, llint size_bytes);
        void location(int location, int size, data_type d_type, boolean normalized = gl::no);
        void save_locations() const;
        void load_static(const void *data, llint size) const;
    };

    struct index_buffer {
        uint handle;

        index_buffer(const void *data, llint size_bytes);
    };
}