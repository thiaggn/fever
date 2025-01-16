#include <ctx/context.h>
#include <ogl/opengl.h>


float vertices[] = {
        0.5f, 0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,// bottom left
        -0.5f, 0.5f, 0.0f  // top left
};

uint indices[] = {
        0, 1, 3,
        1, 2, 3,
};

void setup_triangle() {
    gl_buffer vbo(gl_vertex_buffer);
    vbo.load_static(vertices, sizeof(vertices));
    vbo.push_attrib(gl_float, 3);

    gl_buffer ebo(gl_element_buffer);
    ebo.load_static(indices, sizeof(indices));
}

int main() {
    ctx_context c = ctx_create(800, 600, "LearnOpenGL");

    gl_program p;
    p.load_shader("shaders/vertex.glsl", gl_vertex_shader);
    p.load_shader("shaders/fragment.glsl", gl_fragment_shader);
    p.link();

    gl_bindings vao = gl_capture_bindings(setup_triangle);

    while (c.available()) {
        gl_clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        gl_clear(gl_color_buffer);

        p.use();
        vao.bind();
        gl_draw_elements(gl_triangles, 6, gl_uint, nullptr);

        c.swap_buffers();
    }

    c.terminate();
    return 0;
}