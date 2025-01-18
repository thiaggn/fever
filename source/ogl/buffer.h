#pragma once
#include "ogl/shared/aliases.h"
#include <vector>

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
    int stride;
    int acc_offset;
    std::vector<gl_attribute> attributes;

    gl_vertex_buffer();
    gl_vertex_buffer(const void *data, llint size_bytes);
    void set(int location, int size, gl_data_type d_type, gl_bool_value normalized = gl_false);
    void save_locations() const;
    void load_static(const void *data, llint size) const;
};