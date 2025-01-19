#include "buffer.h"
#include "glad/glad.h"
#include "ogl/shared/aliases.h"
#include "ogl/shared/enums.h"

namespace gl {
    vertex_buffer::vertex_buffer() : handle(0), acc_offset(0) {
        glGenBuffers(1, &handle);
        glBindBuffer(GL_ARRAY_BUFFER, handle);
    }

    vertex_buffer::vertex_buffer(const void *data, llint size_bytes): handle(0), acc_offset(0) {
        glGenBuffers(1, &handle);
        glBindBuffer(GL_ARRAY_BUFFER, handle);
        load_static(data, size_bytes);
    }

    void vertex_buffer::load_static(const void *data, llint size) const {
        glBufferData(GL_ARRAY_BUFFER, size, data, buffer_usage::static_draw);
    }

    void vertex_buffer::location(int location, int size, data_type d_type, boolean normalized) {
        int type_size = gl_type_to_size_map.at(d_type);
        attributes.emplace_back(location, size, d_type, normalized, (void *)((llint)acc_offset));
        acc_offset += type_size * size;
    }

    void vertex_buffer::save_locations() const {
        for (const attribute &attr: attributes) {
            glVertexAttribPointer(attr.location, attr.size, attr.type, attr.normalized, acc_offset, attr.offset);
            glEnableVertexAttribArray(attr.location);
        }
    }

    index_buffer::index_buffer(const void *data, llint size_bytes): handle(0) {
        glGenBuffers(1, &handle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_bytes, data, buffer_usage::static_draw);
    }
}