#include "engine/engine.h"
#include "engine/drawing.h"
#include "engine/font.h"
#include "engine/sprite.h"
#include <stdio.h>

Engine *engine;
Texture *sample;
Font *testfont;
Sprite *testsprite;


void draw_test () {
  draw_clear(engine, 0);
  draw_text_raw(engine,testfont,3,3,"Lorem ipsum dolor sit amet, consectetur", 0b11100000); 
  draw_text_raw(engine,testfont,3,3+8,"adipiscing elit, sed do eiusmod tempor", 0b00011100); 
  draw_text_raw(engine,testfont,3,3+8*2,"42=101010 --- y=mx+c",0b00000011); 
  draw_sprite(engine, testsprite, 50, 50);
}

void update_test (double dt) {
  update_sprite(testsprite, dt);
}

int main(int argc, const char *argv[]) {

  sample = loadTexture("assets/graphics/anim_test.hg");
  testfont = loadFont("assets/fonts/default.hf");
  testsprite = newSprite(sample, 2, 2, 32, 32, 1, 1.0f, 0, 0);
  engine = newEngine(256, 200, 3, "mkpixel");
  engine->on_draw = draw_test;
  engine->on_update = update_test;
  engine_init(engine);
  engine_run(engine);

  return 0;
}

int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
