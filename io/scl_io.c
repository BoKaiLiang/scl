#include "scl_io.h"

void scl_load_file(const char* filename, char** txt_src, size_t* txt_len) {
    FILE* file = NULL;
    if (NULL == (file = fopen(filename, "rb"))) {
        fclose(file);
        fprintf(stderr, "OPEN FILE ERROR: %s", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);

    size_t len = (size_t)ftell(file);
    if (len == 0) { return; }
    if (txt_len) { *txt_len = len; }
    *txt_src = calloc(len + 1, sizeof(char));

    fseek(file, 0, SEEK_SET);

    fread(*txt_src, 1, len, file); 
    fclose(file);
}