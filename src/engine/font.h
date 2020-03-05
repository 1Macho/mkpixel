#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
  unsigned char data[8];
} CharFont;

typedef struct {
  CharFont characters[128];
} Font;

CharFont charfont_from_ascii (Font *font, unsigned char ascii) {
  //printf("%u\n",ascii);
  if (ascii == 32) {
    return font->characters[255];
  }
  return font->characters[ascii-33];
}

Font *loadFont (char *path) {

  // Get file descriptor.
  FILE *fd = fopen(path, "r");
  if (fd == NULL) {
    return NULL;
  }

  // Load font data from file.
  Font *self = calloc(1, sizeof(Font));
  for (unsigned int charid = 0; charid < 128; charid++) {
    for (unsigned int row = 0; row < 8; row++) {
      self->characters[charid].data[row] = fgetc(fd);
    }
  }

  fclose(fd);
  return self;
}

#endif
