#include <stdio.h>
#include "../MyLibraries/headers/systemdata.h"
#include "../MyLibraries/headers/file_func.h"
#include <assert.h>

#define FILE_TO_HACK "/Users/ivanvodolazenko/DOSBox/code/CRACK/PASSW_2.COM"

const size_t FILE_HASH = 1093625989429848259;

int Djb2HashCount(const char *filename, size_t *hash);
int FileHack(const char *filename);

int main() {

    size_t hash = 0;
    if (Djb2HashCount(FILE_TO_HACK, &hash) != SUCCESS)
        return ERROR;

    if (hash != FILE_HASH) {
        printf(RED "This is the wrong file. I refuse to hack it." END_OF_COLOR "\n");
        return ERROR;
    }
    else {
        printf(BRIGHT_GREEN "Perfect file!" END_OF_COLOR "\n");
    }

    if (FileHack(FILE_TO_HACK) != SUCCESS)
        return ERROR;

    printf(YELLOW "The hack is successful" END_OF_COLOR "\n");

    return SUCCESS;
}

int Djb2HashCount(const char *filename, size_t *hash) {

    assert(filename);
    assert(hash);

    char *buf = readbuf(filename);
    if (!buf)   return ERROR;

    size_t len_of_file = filelen(filename);

    *hash = 5381;
    for (size_t i = 0; i < len_of_file; i++)
        *hash = (*hash << 5) + *hash + (size_t) buf[i];

    return SUCCESS;
}

int FileHack(const char *filename) {

    assert(filename);

    FILE *fn = fileopen(filename, READ_WRITE);
    if (!fn)    return ERROR;

    fseek(fn, 0x57, SEEK_SET);
    char buffer = 1;
    fwrite(&buffer, sizeof(char), 1, fn);

    fclose(fn);

    return SUCCESS;
}