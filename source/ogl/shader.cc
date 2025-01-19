#include "shader.h"
#include <rsc/resource.h>
#include <string>

namespace gl {
    shader::shader(shader_type type, const char *path) {
        handle = glCreateShader(type);

        std::string prefixed_path = "shaders/";
        prefixed_path.append(path);

        struct rsc_text r = rsc_read_text(prefixed_path.c_str());
        glShaderSource(handle, 1, &r.bytes, nullptr);
        glCompileShader(handle);

        if (!compilation_succeded(handle)) {
            exit(EXIT_FAILURE);
        }
    }

    int shader::compilation_succeded(uint shader) {
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetShaderInfoLog(shader, 512, nullptr, info_log);

            fprintf(stderr, "error: gl_program::add_shader: failed to compile shader.\n");
            fprintf(stderr, "%s", info_log);
        }

        return success;
    }
}