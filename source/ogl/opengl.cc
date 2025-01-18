#include "opengl.h"
#include <stdio.h>

void checkOpenGLError() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Erro OpenGL: %d\n", error);
    }
}

gl_state::gl_state() : handle(0) {
    glGenVertexArrays(1, &handle);
    glBindVertexArray(handle);
}

void gl_state::recover() const {
    glBindVertexArray(handle);
}

void gl_state::add(const gl_vertex_buffer & b) const {
    glBindVertexArray(handle);
    glBindBuffer(GL_ARRAY_BUFFER, b.handle);
    b.save_locations();
}

void gl_state::add(const gl_index_buffer &b) const {
    glBindVertexArray(handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.handle);
}

void gl_instance::clear_color(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}

void gl_instance::clear(gl_bit b) const {
    glClear(b);
}

void gl_instance::draw_buffer(gl_primitive p, int first, int many_vertices) const {
    glDrawArrays(p, first, many_vertices);
}

void gl_instance::draw_elements(gl_primitive p, int count, gl_data_type index_dtype, void *offset) const {
    glDrawElements(p, count, index_dtype, offset);
}

gl_state gl_instance::create_state() const {
    struct gl_state s;
    return s;
}

const gl_instance gl;
