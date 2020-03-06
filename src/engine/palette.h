#ifndef ENGINE_PALETTE_H
#define ENGINE_PALETTE_H

#include "colour.h"

typedef struct {
  Colour data[256];
} Palette;

Palette *newPalette() {
  Palette *self = (Palette *)calloc(1, sizeof(*self));
  return self;
}

Palette *defaultPalette() {
  static Palette *default_palette;
  if (default_palette == NULL) {
    default_palette = newPalette();
    for (unsigned int i = 0; i < 256; i++) {
      unsigned char r = (i >> 5) * 255 / 7;
      unsigned char g = ((i >> 2) & 0x07) * 255 / 7;
      unsigned char b = (i & 0x03) * 255 / 3;
      default_palette->data[i] = makeColour(r,g,b);
    }
  }
  return default_palette;
}

Palette *loadPalette(char *path) {
  // Get file descriptor.
  FILE *fd = fopen(path, "r");
  if (fd == NULL) {
    return NULL;
  }

  Palette *self = newPalette();
  for (unsigned int i = 0; i < 256; i++) {
    self->data[i].r = fgetc(fd);
    self->data[i].g = fgetc(fd);
    self->data[i].b = fgetc(fd);
  }

  fclose(fd);
  return self;
}

void debug_palette(Palette *self) {
  for (unsigned int i = 0; i < 256; i++) {
    printf("%02hhx%02hhx%02hhx\n", self->data[i].r, 
      self->data[i].g, 
      self->data[i].b);
  }
}

#endif
