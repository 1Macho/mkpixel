#ifndef ENGINE_FRAMEBUFFER_H
#define ENGINE_FRAMEBUFFER_H

#include "colour.h"
#include <stdlib.h>

typedef struct {
  unsigned int width;
  unsigned int height;
  // unsigned char(*data);
  Colour(*data);
} Framebuffer;

Framebuffer *newFramebuffer(int width, int height) {
  Framebuffer *self = (Framebuffer *)calloc(1, 
    sizeof(*self));
  self->width = width;
  self->height = height;
  self->data = (Colour *)calloc(self->width * self->height 
    * 1, sizeof(Colour));
  return self;
}

void framebuffer_set_pixel(Framebuffer *self, int x, int y, 
  Colour colour) {
  if (x < self->width && y < self->height) {
    self->data[self->width * y + x] = colour;
  }
}

void framebuffer_clear(Framebuffer *self, Colour colour) {
  for (unsigned int x = 0; x < self->width; x++) {
    for (unsigned int y = 0; y < self->height; y++) {
      framebuffer_set_pixel(self, x, y, colour);
    }
  }
}

Colour framebuffer_get_pixel(Framebuffer *self, int x, int y) {
  if (x < self->width && y < self->height) {
    return self->data[self->width * y + x];
  }
  return makeColour(0,0,0);
}


#endif
