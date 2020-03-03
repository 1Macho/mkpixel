#include "engine/engine.h"
#include "engine/drawing.h"
#include <stdio.h>

Engine *engine;
Texture *sample;

void draw_test () {
  draw_clear(engine, 0x11);
  draw_texture_options(engine, sample,
      10, 15, 16,
      16, 32, 32,
      0, 0);
  //for (unsigned int x = 0; x < 256; x++) {
  //  for (unsigned int y = 0; y < 144; y++) {
  //    draw_set_pixel(engine, x, y, x+y);
  //  }
  //}
}

int main(int argc, const char *argv[]) {

  sample = loadTexture("assets/graphics/sample.hg");
  printf("%u\n", sample->side);
  engine = newEngine(256, 200, 3, "mkpixel");
  engine->on_draw = draw_test;
  engine_init(engine);
  engine_run(engine);

  return 0;
}

int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
