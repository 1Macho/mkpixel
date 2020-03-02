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
    for (unsigned int i = 0; i < 255; i++) {
      unsigned char r   = (i >> 5) * 255 / 7;
      unsigned char g = ((i >> 2) & 0x07) * 255 / 7;
      unsigned char b  = (i & 0x03) * 255 / 3;
      default_palette->data[i] = makeColour(r,g,b);
    }
  }
  return default_palette;
}

#endif
