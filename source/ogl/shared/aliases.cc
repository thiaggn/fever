#include "aliases.h"

const std::map<gl_data_type, int> gl_type_to_size_map = {
        {gl_float, sizeof(float)},
        {gl_int, sizeof(int)},
        {gl_uint, sizeof(unsigned int)},
};