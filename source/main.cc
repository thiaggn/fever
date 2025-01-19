#include <ctx/context.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ogl/opengl.h>

float vert1[] = {
        // positions          // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // top left
};

unsigned int indices[] = {
        0,
        1,
        3,
        1,
        2,
        3,
};

gl::state create_triangle(const float vert[], llint size) {
    gl::vertex_buffer vbuf(vert, size);
    vbuf.location(0, 3, gl::float32);
    vbuf.location(2, 2, gl::float32);

    gl::index_buffer ibuf(indices, sizeof(indices));

    gl::state s = GL.create_state();
    s.add(vbuf);
    s.add(ibuf);
    return s;
}

gl::texture create_texture(const char *path) {
    gl::texture_create_info p(gl::dim_2d);
    p.wrap.s = gl::repeat;
    p.wrap.t = gl::repeat;
    p.filter.min = gl::nearest;
    p.filter.mag = gl::nearest;
    p.mipmap.filter.min = gl::nearest;
    p.mipmap.filter.mag = gl::nearest;
    gl::texture tex(p, path);
    return tex;
}

int main() {
    ctx_context c = ctx_create(450, 450, "Fever Renderer");
    gl::texture tex1 = create_texture("awesomeface.png");

    gl::program prog;
    prog.add_shader(gl::vertex_shader, "vertex.glsl");
    prog.add_shader(gl::fragment_shader, "fragment.glsl");
    prog.add_texture(0, "TexSampler0", tex1);
    prog.save();

    glm::mat<4, 4, float> t(1.0);
    t = glm::translate(t, glm::vec3(0.5f, -0.5f, 0.0f));

    gl::uniform t_uniform = prog.set_uniform("Transform", t);

    gl::state state = create_triangle(vert1, sizeof(vert1));

    while (c.available()) {
        GL.clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        GL.clear(gl::color_buffer_bit);

        glm::mat4 t1 = glm::rotate(t, (float) c.get_time(), glm::vec3(0.0f, 0.0f, 1.0f));
        t_uniform.update(t1);

        prog.use();
        state.recover();
        GL.draw_elements(gl::triangles, 6, gl::uint32, nullptr);

        c.swap_buffers();
    }

    c.terminate();
    return 0;
}