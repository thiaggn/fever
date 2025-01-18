#pragma once
#include "shared/enums.h"
#include "shared/aliases.h"

struct gl_shader {
    uint handle;

    gl_shader(gl_shader_type type, const char *path);
    int compilation_succeded(uint shader);
};