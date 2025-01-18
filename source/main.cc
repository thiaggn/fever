#include <ctx/context.h>
#include <ogl/opengl.h>
#include <math.h>

float vert1[] = {
        -0.8, 0.6, 0.0, 1.0, 0.0, 0.0,
        -0.4, 0.2, 0.0, 0.0, 0.0, 1.0,
         0.0, 0.8, 0.0, 0.0, 1.0, 0.0,
};

struct gl_state create_triangle(const float vert[], llint size) {
    gl_vertex_buffer vbuf(vert, size);
    vbuf.set(0, 3, gl_float);
    vbuf.set(1, 3, gl_float);

    gl_state s = gl.create_state();
    s.add(vbuf);
    return s;
}

int main() {
    ctx_context c = ctx_create(450, 450, "Fever Renderer");

    gl_program p;
    p.add(gl_vert_shader, "vertex.glsl");
    p.add(gl_frag_shader, "fragment.glsl");
    p.link();

    gl_state s = create_triangle(vert1, sizeof(vert1));

    while (c.available()) {
        gl.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        gl.clear(gl_color_buffer);

        p.use();
        s.recover();
        gl.draw_buffer(gl_triangles, 0, 3);

        c.swap_buffers();
    }

    c.terminate();
    return 0;
}