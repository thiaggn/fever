#include <glad/glad.h>
#include <rsc/resource.h>
#include <map>
#include <vector>

void checkOpenGLError() {
    GLenum error = glGetError();  // Obtém o código de erro
    if (error != GL_NO_ERROR) {   // Se houver erro
        printf("Erro OpenGL: %d\n", error);  // Exibe o erro
    }
}

typedef unsigned int uint;
typedef long long llint;

enum gl_buffer_type {
    gl_vertex_buffer = GL_ARRAY_BUFFER,
    gl_element_buffer = GL_ELEMENT_ARRAY_BUFFER
};

enum gl_bool_value {
    gl_false = GL_FALSE,
    gl_true  = GL_TRUE
};

enum gl_primitive {
    gl_triangles = GL_TRIANGLES,
};

enum gl_data_type {
    gl_float = GL_FLOAT,
    gl_uint = GL_UNSIGNED_INT,
    gl_int = GL_INT,
};

enum gl_shader_type {
    gl_vertex_shader      = GL_VERTEX_SHADER,
    gl_fragment_shader    = GL_FRAGMENT_SHADER,
    gl_compute_shader     = GL_COMPUTE_SHADER,
    gl_tesscontrol_shader = GL_TESS_CONTROL_SHADER,
    gl_tesseval_shader    = GL_TESS_EVALUATION_SHADER,
    gl_geometry_shader    = GL_GEOMETRY_SHADER,
};

enum gl_buffer_usage {
    static_draw  = GL_STATIC_DRAW,
    dynamic_draw = GL_DYNAMIC_DRAW,
    stream_draw  = GL_STREAM_DRAW
};

enum gl_bit {
    gl_color_buffer = GL_COLOR_BUFFER_BIT,
    stencil_buffer = GL_STENCIL_BUFFER_BIT
};

static std::map<gl_data_type, int> gl_type_to_size_map = {
        {gl_float, sizeof(float)},
        {gl_int, sizeof(int)},
        {gl_uint, sizeof(unsigned int)},
};

struct gl_buffer {
    uint handle;
    gl_buffer_type type;
    int att_i;
    llint acc_off;

    explicit gl_buffer(gl_buffer_type t): handle(0) {
        type = t;
        att_i = 0;
        acc_off = 0;
        glGenBuffers(1, &handle);
        glBindBuffer(t, handle);
    }

    void load_static(void *data, llint size) const {
        glBufferData(type, size, data, gl_buffer_usage::static_draw);
    }

    void push_attrib(gl_data_type d_type, int size, gl_bool_value normalized = gl_false) {
        int d_type_size = gl_type_to_size_map[d_type];

        int stride = d_type_size * size;
        llint offset = acc_off;

        glVertexAttribPointer(att_i, size, d_type, normalized, stride, (void*)(offset));
        checkOpenGLError();
        glEnableVertexAttribArray(att_i);

        acc_off += stride;
        att_i++;
    }
};


struct gl_program {
    uint handle;


    gl_program() {
        handle = glCreateProgram();
    }

    void load_shader(const char *path, gl_shader_type type) const {
        struct rsc_text r = rsc_read_text(path);
        uint shader = glCreateShader(type);
        glShaderSource(shader, 1, &r.bytes, nullptr);
        glCompileShader(shader);

        if (!check_shader_compilation(shader)) {
            exit(EXIT_FAILURE);
        }

        glAttachShader(handle, shader);
        glDeleteShader(shader);
    }

    inline void link() const {
        glLinkProgram(handle);
        if(!check_program_linking()) exit(EXIT_FAILURE);
    }

    inline void use() const {
        glUseProgram(handle);
    }


    static int check_shader_compilation(uint shader) {
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetShaderInfoLog(shader, 512, nullptr, info_log);

            fprintf(stderr, "error: gl_program::load_shader: failed to compile shader.\n");
            fprintf(stderr, "%s", info_log);
        }

        return success;
    }

    int check_program_linking() const {
        int success;
        glGetProgramiv(handle, GL_LINK_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetProgramInfoLog(handle, 512, nullptr, info_log);
            fprintf(stderr, "error: gl_program::link: failed to link shader.\n");
            fprintf(stderr, "%s", info_log);
        }

        return success;
    }
};

typedef void (*procedure_func) ();

struct gl_bindings {
    uint handle;

    gl_bindings(): handle(0) {
        glGenVertexArrays(1, &handle);
        glBindVertexArray(handle);
    }

    void bind() const {
        glBindVertexArray(handle);
    }
};

struct gl_bindings gl_capture_bindings(procedure_func f) {
    gl_bindings b;
    f();
    glBindVertexArray(0);
    return b;
}

void gl_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void gl_clear(gl_bit b) {
    glClear(b);
}

void gl_draw_from_buffer(gl_primitive p, int first, int count) {
    glDrawArrays(p, first, count);
}

void gl_draw_elements(gl_primitive p, int count, gl_data_type type, void *indices) {
    glDrawElements(p, count, type, indices);
}