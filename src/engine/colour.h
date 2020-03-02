#ifndef ENGINE_COLOUR_H
#define ENGINE_COLOUR_H

#include <stdint.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Colour;

Colour makeColour(unsigned char r, unsigned char g, 
  unsigned char b) {
  Colour self;

  self.r = r;
  self.g = g;
  self.b = b;

  return self;
}
#endif
