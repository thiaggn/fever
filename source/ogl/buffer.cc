#include "buffer.h"
#include "glad/glad.h"
#include "ogl/shared/aliases.h"
#include "ogl/shared/enums.h"


gl_vertex_buffer::gl_vertex_buffer() : handle(0), stride(0), acc_offset(0) {
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ARRAY_BUFFER, handle);
}

gl_vertex_buffer::gl_vertex_buffer(const void *data, llint size_bytes): handle(0), stride(0), acc_offset(0) {
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    load_static(data, size_bytes);
}

void gl_vertex_buffer::load_static(const void *data, llint size) const {
    glBufferData(GL_ARRAY_BUFFER, size, data, gl_buffer_usage::static_draw);
}

void gl_vertex_buffer::set(int location, int size, gl_data_type d_type, gl_bool_value normalized) {
    int type_size = gl_type_to_size_map.at(d_type);
    attributes.emplace_back(location, size, d_type, normalized, (void *)((llint)acc_offset));
    acc_offset += type_size * size;
}

void gl_vertex_buffer::save_locations() const {
    for (const gl_attribute &attr: attributes) {
        glVertexAttribPointer(attr.location, attr.size, attr.type, attr.normalized, acc_offset, attr.offset);
        glEnableVertexAttribArray(attr.location);
    }
}