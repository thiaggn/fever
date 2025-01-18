#pragma once
#include "glad/glad.h"
#include "ogl/shared/aliases.h"
#include <vector>

enum gl_buffer_usage {
    static_draw = GL_STATIC_DRAW,
    dynamic_draw = GL_DYNAMIC_DRAW,
    stream_draw = GL_STREAM_DRAW
};

struct gl_attribute {
    int location;
    int size;
    gl_data_type type;
    gl_bool_value normalized;
    void* offset;

    gl_attribute(int l, int s, gl_data_type t, gl_bool_value n, void* o)
        : location(l), size(s), type(t), normalized(n), offset(o) {}
};

struct gl_vertex_buffer {
    uint handle;
    int acc_offset;
    std::vector<gl_attribute> attributes;

    gl_vertex_buffer();
    gl_vertex_buffer(const void *data, llint size_bytes);
    void location(int location, int size, gl_data_type d_type, gl_bool_value normalized = gl_false);
    void save_locations() const;
    void load_static(const void *data, llint size) const;
};

struct gl_index_buffer {
    uint handle;

    gl_index_buffer(const void *data, llint size_bytes);
};