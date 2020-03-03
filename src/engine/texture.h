#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    unsigned int side;
    unsigned char *data;
} Texture;

Texture *mapTexture (char *path) {
    // Get file descriptor.
    int fd;
    if ((fd = open(path, O_RDONLY)) == -1) {
        return NULL;
    }

    // Get file stat
    struct stat sbuf;
    if (stat(path, &sbuf) == -1) {
        return NULL;
    }
    unsigned int file_length = sbuf.st_size;

    // Map file to memory.
    unsigned char *file_data;
    if ((file_data = mmap((caddr_t)0, sbuf.st_size, 
        PROT_READ, MAP_PRIVATE, fd, 0)) == (caddr_t)(-1)) {
        return NULL;
    }

    // Construct the texture
    Texture *self = (Texture *)calloc(1, sizeof(*self));
    self->data = file_data;
    self->side = sqrt(file_length);

    return self;
}

#endif