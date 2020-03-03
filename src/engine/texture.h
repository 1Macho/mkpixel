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

Texture *loadTexture (char *path) {
    // Get file descriptor.
    FILE *fd = fopen(path, "r");
    if (fd == NULL) {
      return NULL;
    }


    // Get file stat
    struct stat sbuf;
    if (stat(path, &sbuf) == -1) {
        return NULL;
    }
    unsigned int file_length = sbuf.st_size;

    // Load data from stream.
    unsigned char *file_data = calloc(file_length,
      sizeof(unsigned char));
    for (unsigned int i = 0; i < file_length; i++) {
      file_data[i] = fgetc(fd);
    }

    fclose(fd);

    // Construct the texture
    Texture *self = (Texture *)calloc(1, sizeof(*self));
    self->data = file_data;
    self->side = sqrt(file_length);

    return self;
}

unsigned char texture_get_pixel(Texture *self, int x, int y) {
  if (x < self->side && y < self->side) {
    return self->data[self->side * y + x];
  }
  return 0;
}

#endif
