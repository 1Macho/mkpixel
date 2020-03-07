#include "engine/audio.h"
#include "engine/engine.h"
#include "engine/drawing.h"
#include "engine/font.h"
#include "engine/audioclip.h"
#include "engine/sprite.h"
#include <stdio.h>

Engine *engine;
Texture *sample;
Font *testfont;
Sprite *testsprite;
AudioClip *testclip;


void draw_test () {
  draw_clear(engine, 0);
  draw_text_raw(engine,testfont,3,3,"the quick brown fox jumped over the", 0b11100000); 
  draw_text_raw(engine,testfont,3,3+8,"some kind of dog or something", 0b00011100); 
  draw_text_raw(engine,testfont,3,3+8*2,"THE LAZY, YELLOW DOG JUMPED OVER THE", 0b11100000); 
  draw_text_raw(engine,testfont,3,3+8*3,"SLOW FOX! HAH yeah idk -+-.../\\", 0b00011100); 
  draw_sprite(engine, testsprite, 50, 50);
}

int played = 0;

void update_test (double dt) {
  update_sprite(testsprite, dt);
  if (!played) {
    audio_play_clip(engine, testclip, 800, 1, 0);
    printf("played\n");
    played = 1;
  }
}

int main(int argc, const char *argv[]) {
  engine = newEngine(256, 200, 3, "mkpixel");
  engine_init(engine);
  engine->on_draw = draw_test;
  engine->on_update = update_test;
  testclip = loadAudioClip("assets/audioclips/sample.ogg");
  sample = loadTexture("assets/graphics/anim_test.hg");
  testfont = loadFont("assets/fonts/default.hf");
  testsprite = newSprite(sample, 2, 2, 32, 32, 1, 1.0f, 0, 4, 0);
  printf("%u, %u, %u, %u\n", testclip->channels, testclip->sample_rate, testclip->sample_count, testclip->al_buffer_id);
  engine_run(engine);

  return 0;
}

int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
