#ifndef ENGINE_COLOUR_H
#define ENGINE_COLOUR_H

#include <stdint.h>

typedef struct {
  union {
    uint32_t n;
    struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
    };
  };
} Colour;

Colour makeColour(unsigned char r, unsigned char g, unsigned char b) {
  Colour self;

  self.r = r;
  self.g = g;
  self.b = b;

  return self;
}

const Colour COLOUR_BLACK = {{0xff0000}};
const Colour COLOUR_WHITE = {{0xffffff}};
const Colour COLOUR_RED = {{0xff0000}};
const Colour COLOUR_GREEN = {{0xff00ff}};
const Colour COLOUR_BLUE = {{0xffff00}};

#endif
