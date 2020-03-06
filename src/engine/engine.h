#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "palette.h"
#include "colour.h"
#include "framebuffer.h"

typedef struct {
  GLFWwindow *window;
  int screenWidth;
  int screenHeight;
  char *title;
  unsigned int fbID;
  unsigned int fbWidth;
  unsigned int fbHeight;
  unsigned int upscale;
  double nowTime;
  double lastTime;
  double dt;
  Framebuffer *fb;
  Palette *palette;

  void (*on_update)(double dt);
  void (*on_draw)();
  void (*callback_window_size)(GLFWwindow *window, int width, int height);
  void (*callback_key)(GLFWwindow *window, int key,
    int scancode, int action, int mods);
  void (*callback_fbt_input)(GLFWwindow *window,
    unsigned int codepoint);
  void (*callback_cursor_position)(GLFWwindow *window,
    double xpos, double ypos);
} Engine;

Engine *newEngine(unsigned int tW, unsigned int tH,
  unsigned int upscale, char *title) {
  // Engine *self = malloc(sizeof(*self));
  Engine *self = (Engine *)calloc(1, sizeof(*self));
  self->upscale = upscale;
  self->screenWidth = tW * upscale;
  self->screenHeight = tH * upscale;
  self->fbWidth = tW;
  self->fbHeight = tH;
  self->palette = defaultPalette();
  self->fb = newFramebuffer(self->fbWidth, self->fbHeight);

  self->title = title;
  // engine_init(self);
  return self;
}


int engine_init(Engine *self) {

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


  self->window = glfwCreateWindow(self->screenWidth,
    self->screenHeight, self->title, NULL, NULL);
  if (!self->window) {
    glfwTerminate();
    return -1;
  }

  glfwSetWindowSizeCallback(self->window,
    self->callback_window_size);
  glfwSetKeyCallback(self->window,
    self->callback_key);
  glfwSetCharCallback(self->window,
    self->callback_fbt_input);
  glfwSetCursorPosCallback(self->window,
    self->callback_cursor_position);

  glfwMakeContextCurrent(self->window);

  glEnable(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
    GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_NEAREST);

  glGenTextures(1, &self->fbID);

  return 0;
}

void engine_draw(Engine *self) {
  glClear(GL_COLOR_BUFFER_BIT);

  if(self->on_draw != NULL) {
    self->on_draw(self->fb);
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, self->fbWidth,
    self->fbHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
    self->fb->data);

  glBegin(GL_TRIANGLES);
  glTexCoord2f(0.0, 1.0); // 01
  glVertex2f(-1.0f, -1.0f);
  glTexCoord2f(0.0, 0.0); // 00
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0); // 11
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(1.0, 1.0); // 11
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(0.0, 0.0); // 00
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0, 0.0); // 10
  glVertex2f(1.0f, 1.0f);
  glEnd();

  glfwSwapBuffers(self->window);
}

void engine_tick(Engine *self) {

  self->nowTime = glfwGetTime();
  self->dt = (self->nowTime - self->lastTime);
  self->lastTime = self->nowTime;

  //printf("%f\n", 1/self->dt);

  if (self->on_update != NULL) {
    self->on_update(self->dt);
  }
  engine_draw(self);

  glfwPollEvents();
}

void engine_run(Engine *self) {
  while (!glfwWindowShouldClose(self->window)) {
    engine_tick(self);
  }

  glfwTerminate();
}

#endif
