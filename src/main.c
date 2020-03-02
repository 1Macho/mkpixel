#include "engine/engine.h"
#include <stdio.h>

Engine *engine;

void draw_test () {
  for (unsigned int x = 0; x < 256; x++) {
    for (unsigned int y = 0; y < 144; y++) {
      engine_set_pixel(engine, x, y, x+y);
    }
  }
}

int main(int argc, const char *argv[]) {

  engine = newEngine(256, 144, 6, "mkpixel");
  engine->on_draw = draw_test;
  engine_init(engine);
  engine_run(engine);

  return 0;
}

int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
