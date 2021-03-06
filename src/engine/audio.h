#ifndef ENGINE_AUDIO_H
#define ENGINE_AUDIO_H

void audio_check_errors (char *source);

#include "engine.h"
#include "audioclip.h"
#include <AL/al.h>
#include <AL/alc.h>

void audio_check_errors (char *source) {
  ALCenum error;
  error = alGetError();
  if (error != AL_NO_ERROR) {
    printf("Audio error in %s! %u\n", source, error);
  }
}

void audio_pause_source (Engine *engine, int source_id) {
  alSourcePause(engine->audio_sources[source_id]);
}

void audio_stop_source (Engine *engine, int source_id) {
  alSourceStop(engine->audio_sources[source_id]);
}

unsigned char audio_is_playing (Engine *engine, int source_id) {
  int source_status = -1;
  alGetSourcei(engine->audio_sources[source_id], AL_SOURCE_STATE,
     &source_status);
  return source_status == AL_PLAYING;
}

unsigned char audio_is_stopped (Engine *engine, int source_id) {
  int source_status = -1;
  alGetSourcei(engine->audio_sources[source_id], AL_SOURCE_STATE,
     &source_status);
  return source_status == AL_STOPPED;
}

unsigned char audio_is_paused (Engine *engine, int source_id) {
  int source_status = -1;
  alGetSourcei(engine->audio_sources[source_id], AL_SOURCE_STATE,
     &source_status);
  return source_status == AL_PAUSED;
}

int audio_play_clip (Engine *engine, AudioClip *clip,
  float gain, float pitch, unsigned char loop) {
  int selected_source_id = -1;
  for (unsigned short i = 0; i < 256; i++) {
    int source_status = -1;
    alGetSourcei(engine->audio_sources[i], AL_SOURCE_STATE,
      &source_status);
    audio_check_errors("Get source state");
    if (!(source_status == AL_PLAYING) & 
        !(source_status == AL_PAUSED)) {
      selected_source_id = i;
      break;
    }
  }
  if (selected_source_id == -1) {
    return -1;
  }
  alSourcef(engine->audio_sources[selected_source_id], 
    AL_GAIN, gain);
  audio_check_errors("Gain");
  alSourcef(engine->audio_sources[selected_source_id],
    AL_PITCH, pitch);
  audio_check_errors("Pitch");
  if (loop) {
    alSourcei(engine->audio_sources[selected_source_id],
      AL_LOOPING, AL_TRUE);
  } else {
    alSourcei(engine->audio_sources[selected_source_id],
      AL_LOOPING, AL_FALSE);
  }
  audio_check_errors("Loop");
  alSourcei(engine->audio_sources[selected_source_id],
    AL_BUFFER, clip->al_buffer_id);
  audio_check_errors("Bind buffer");
  alSourcePlay(engine->audio_sources[selected_source_id]);
  audio_check_errors("Play source");
  return selected_source_id;
}

#endif