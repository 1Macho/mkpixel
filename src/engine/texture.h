#ifndef ENGINE_SPRITE_H
#define ENGINE_SPRITE_H

#include "colour.h"
#include <stdlib.h>

typedef struct {
  int width;
  int height;
  // unsigned char(*data);
  Colour(*data);
} Texture;

Texture *newTexture(int width, int height) {
  Texture *self = (Texture *)calloc(1, sizeof(*self));
  self->width = width;
  self->height = height;
  self->data = (Colour *)calloc(self->width * self->height * 1, sizeof(Colour));
  return self;
}


void texture_set_pixel(Texture *self, int x, int y, Colour colour) {
  if (x < self->width && y < self->height) {
    self->data[self->width * y + x] = colour;
  }
}

Colour texture_get_pixel(Texture *self, int x, int y) {
  if (x < self->width && y < self->height) {
    return self->data[self->width * y + x];
  }
  return makeColour(0,0,0);
}


#endif
