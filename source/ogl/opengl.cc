#include "opengl.h"
#include <stdio.h>


namespace gl {
    state::state() : handle(0) {
        glGenVertexArrays(1, &handle);
        glBindVertexArray(handle);
    }

    void state::recover() const {
        glBindVertexArray(handle);
    }

    void state::add(const vertex_buffer & b) const {
        glBindVertexArray(handle);
        glBindBuffer(GL_ARRAY_BUFFER, b.handle);
        b.save_locations();
    }

    void state::add(const index_buffer &b) const {
        glBindVertexArray(handle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.handle);
    }

    void instance::clear_color(float r, float g, float b, float a) const {
        glClearColor(r, g, b, a);
    }

    void instance::clear(buffer_bit b) const {
        glClear(b);
    }

    void instance::draw_buffer(primitive p, int first, int many_vertices) const {
        glDrawArrays(p, first, many_vertices);
    }

    void instance::draw_elements(primitive p, int count, data_type index_dtype, void *offset) const {
        glDrawElements(p, count, index_dtype, offset);
    }

    state instance::create_state() const {
        struct state s;
        return s;
    }

    void check_error() {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            printf("Erro OpenGL: %d\n", error);
        }
    }
}

const gl::instance GL;


