#include "aliases.h"
#include "enums.h"

const std::map<gl::data_type, int> gl_type_to_size_map = {
        {gl::float32, sizeof(float)},
        {gl::int32, sizeof(int)},
        {gl::uint32, sizeof(unsigned int)},
};