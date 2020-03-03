#ifndef ENGINE_DRAWING_H
#define ENGINE_DRAWING_H

#include "engine.h"
#include "texture.h"

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
            unsigned int global_x = in_texture_x + x;
            unsigned int global_y = in_texture_y + y;
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

#endif
