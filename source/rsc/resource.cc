//
// Created by thiag on 15/01/2025.
//

#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct rsc_text rsc_read_text(const char *path) {
    std::string prefixed_path = "../assets/";
    prefixed_path.append(path);

    rsc_text resource{};
    FILE *file = fopen(prefixed_path.c_str(), "r");
    if (!file) {
        perror("error: rsc_read_text: failed to load file");
        return resource;
    }

    // Move o ponteiro do arquivo para o final para determinar o tamanho
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Aloca memória para os bytes do arquivo
    char *buff = (char *) calloc(1, file_size+1);
    if (buff == nullptr) {
        perror("error: rsc_read_text: failed to allocate memory");
        fclose(file);
    }

    // Lê os bytes do arquivo
    fread(buff, 1, file_size, file);
    fclose(file);

    resource.size = file_size+1;
    resource.bytes = buff;
    return resource;
}

rsc_image rsc_read_image(const char* path) {
    std::string prefixed_path = "../assets/images/";
    prefixed_path.append(path);

    rsc_image r{};
    stbi_set_flip_vertically_on_load(true);
    r.bytes = stbi_load(prefixed_path.c_str(), &r.width, &r.height, &r.channels_count, 0);


    if (r.bytes == nullptr) {
        const char *reason = stbi_failure_reason();
        fprintf(stderr, "error: rsc_read_image: stbi_load: failed to load image \"%s\": %s\n", prefixed_path.c_str(), reason);
        exit(EXIT_FAILURE);
    }

    return r;
}


void rsc_image::release() {
    stbi_image_free(bytes);
    bytes = nullptr;
}
