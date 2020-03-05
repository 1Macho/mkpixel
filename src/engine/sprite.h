#ifndef ENGINE_SPRITE_H
#define ENGINE_SPRITE_H

#include "texture.h"

typedef struct {
  Texture *sheet;
  unsigned int hor_states;
  unsigned int ver_states;
  unsigned int hor_state_size;
  unsigned int ver_state_size;
  unsigned char animated;
  float period;
  float clock;
  unsigned int state;
  unsigned char alpha_mask;
} Sprite;

Sprite *newSprite (Texture *sheet, unsigned int hor_states, 
  unsigned int ver_states, unsigned int hor_state_size,
  unsigned int ver_state_size, unsigned char animated,
  float period, unsigned int state, unsigned char alpha_mask) {
  
  Sprite *self = calloc(1, sizeof(Sprite));
  self->sheet = sheet;
  self->hor_states = hor_states;
  self->ver_states = ver_states;
  self->hor_state_size = hor_state_size;
  self->ver_state_size = ver_state_size;
  self->animated = animated;
  self->period = period;
  self->clock = period;
  self->state = state;
  self->alpha_mask = alpha_mask;
  return self;
}

void sprite_resolve_clock (Sprite *self);

void update_sprite (Sprite *self, double dt) {
  if (self->animated) {
    self->clock -= dt;
    sprite_resolve_clock(self);
  }
}

void sprite_resolve_clock (Sprite *self) {
  if(self->clock < 0) {
    self->state++;
    if (self->state >= self->hor_states * self->ver_states) {
      self->state = 0;
    }
    float remainder = self->clock;
    self->clock = self->period;
    self->clock += remainder;
    sprite_resolve_clock(self);
  }
}

#endif