#include "engine/engine.h"
#include "engine/drawing.h"
#include "engine/font.h"
#include <stdio.h>

Engine *engine;
Texture *sample;
Font *testfont;


void draw_test () {
  draw_clear(engine, 0b10000000);
  draw_texture_options(engine, sample,
      10, 15, 0,
      0, 64, 64,
      0, 0);

}

int main(int argc, const char *argv[]) {

  sample = loadTexture("assets/graphics/sample.hg");
  testfont = loadFont("assets/fonts/default.hf");
  printf("%u\n", testfont->characters[0].data[1]);
  printf("%u\n", sample->side);
  engine = newEngine(256, 200, 3, "mkpixel");
  engine->on_draw = draw_test;
  engine_init(engine);
  engine_run(engine);

  return 0;
}

int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
