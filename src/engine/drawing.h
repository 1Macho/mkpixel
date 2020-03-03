#ifndef ENGINE_DRAWING_H
#define ENGINE_DRAWING_H

#include "engine.h"

void draw_set_pixel(Engine *engine, int x, int y, 
  unsigned char color_id) {
  if (x < engine->fb->width && y < engine->fb->height) {
    engine->fb->data[engine->fb->width * y + x] = 
      engine->palette->data[color_id];
  }
}

#endif