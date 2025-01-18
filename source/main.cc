#include <ctx/context.h>
#include <ogl/opengl.h>

float vert1[] = {
        // posicoes          // cores           // coordenada da textura
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
};

unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
};

gl_state create_triangle(const float vert[], llint size) {
    gl_vertex_buffer vbuf(vert, size);
    vbuf.location(0, 3, gl_float);
    vbuf.location(1, 3, gl_float);
    vbuf.location(2, 2, gl_float);

    gl_index_buffer ibuf(indices, sizeof(indices));

    gl_state s = gl.create_state();
    s.add(vbuf);
    s.add(ibuf);
    return s;
}

gl_texture create_texture(const char *path) {
    gl_texture_params p(gl_2D);
    p.wrap.s = gl_repeat;
    p.wrap.t = gl_repeat;
    p.filter.min = gl_nearest;
    p.filter.mag = gl_linear;
    p.mipmap.filter.min = gl_nearest;
    p.mipmap.filter.mag = gl_linear;
    gl_texture tex(p, path);
    return tex;
}

int main() {
    ctx_context c = ctx_create(450, 450, "Fever Renderer");

    gl_program prog;
    prog.add(gl_vertex_shader, "vertex.glsl");
    prog.add(gl_fragment_shader, "fragment.glsl");
    prog.link();

    gl_state state = create_triangle(vert1, sizeof(vert1));
    gl_texture tex = create_texture("smile.jpg");

    while (c.available()) {
        gl.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        gl.clear(gl_color_buffer);

        tex.use();
        prog.use();
        state.recover();
        gl.draw_elements(gl_triangles, 6, gl_uint, nullptr);

        c.swap_buffers();
    }

    c.terminate();
    return 0;
}