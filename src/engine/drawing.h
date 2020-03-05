#ifndef ENGINE_DRAWING_H
#define ENGINE_DRAWING_H

#include "sprite.h"
#include "engine.h"
#include "texture.h"
#include "font.h"
#include "util.h"
#include <string.h>

Colour draw_resolve_colour(Engine *engine, unsigned char id) {
  return engine->palette->data[id];
}

void draw_set_pixel(Engine *engine, int x, int y, 
  unsigned char color_id) {
  framebuffer_set_pixel(engine->fb, x, y, 
    draw_resolve_colour(engine, color_id));
}

void draw_clear(Engine *engine, unsigned char id) {
  framebuffer_clear(engine->fb, draw_resolve_colour(engine,
    id));
}

// Hyper-function that has all options for drawing.
void draw_texture_options(Engine *engine, Texture *texture,
  unsigned int x, unsigned int y, unsigned int o_x,
  unsigned int o_y, unsigned int s_x, unsigned int s_y,
  unsigned char mask_alpha, unsigned char alpha_color) {
    
  for (unsigned int relative_x = 0; relative_x < s_x; 
    relative_x++) {
    for (unsigned int relative_y = 0; relative_y < s_y;
      relative_y++) {
      unsigned int in_texture_x = relative_x + o_x;
      unsigned int in_texture_y = relative_y + o_y;
      unsigned int global_x = in_texture_x + x - o_x;
      unsigned int global_y = in_texture_y + y - o_y;
      unsigned char id_at_pixel 
        = texture_get_pixel(texture, 
        in_texture_x, in_texture_y);
      if (mask_alpha) {
        if (alpha_color == id_at_pixel) {
          continue;
        }
      }
      draw_set_pixel(engine, global_x, global_y,
        id_at_pixel);
    }
  }
}

void draw_text_raw(Engine *engine, 
  Font *font, unsigned int x, unsigned int y,
  char *text, unsigned int color_id) {
  unsigned int text_length = strlen(text);
  for (unsigned int i = 0; i < text_length; i++) {
    CharFont characterFont 
      = charfont_from_ascii(font, text[i]);
    unsigned char offset = i * 6;
    for (unsigned int int_y = 0; int_y < 8; int_y++) {
      unsigned char row_data = characterFont.data[int_y];
      for (unsigned int int_x = 0; int_x < 8; int_x++) {
        unsigned char should_set 
          = util_bit_value(row_data, 8 - int_x);
        //printf("%u\n", row_data);
        if (should_set) {
          unsigned char g_x = x + int_x + offset;
          unsigned char g_y = y + int_y;
          draw_set_pixel(engine, g_x, g_y, 
            color_id);
        }
      }
    }
  }
}

void draw_sprite (Engine *engine, Sprite *self, unsigned int x, 
  unsigned int y) {
  unsigned int state_x = self->state % self->hor_states;
  unsigned int state_y = self->state / self->hor_states;
  unsigned int tex_x = state_x * self->hor_state_size;
  unsigned int tex_y = state_y * self->ver_state_size;
  draw_texture_options(engine, self->sheet, x, y, tex_x, tex_y,
    self->hor_state_size, self->ver_state_size, 
    1, self->alpha_mask);
}

#endif
