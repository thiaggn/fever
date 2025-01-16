//
// Created by thiag on 15/01/2025.
//

#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

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