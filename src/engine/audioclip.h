#ifndef ENGINE_AUDIOCLIP_H
#define ENGINE_AUDIOCLIP_H

#include <stdlib.h>
#include "trd/stb_vorbis.h"
#include <AL/al.h>

typedef struct {
  int channels;
  int sample_rate;
  int sample_count;
  short *data;

  ALuint al_buffer_id;
} AudioClip;

AudioClip *loadAudioClip (char *path) {
  AudioClip *self = calloc(1, sizeof(AudioClip));
  self->sample_count = stb_vorbis_decode_filename(path, 
    &self->channels, &self->sample_rate, &self->data);

  alGenBuffers(1, &self->al_buffer_id);
  ALenum format = AL_FORMAT_MONO16;
  if (self->channels > 1)
  {
    format = AL_FORMAT_STEREO16;
  }
  alBufferData(self->al_buffer_id, format, self->data, 
    self->sample_count, self->sample_rate);
  return self;
}

#endif