//
// Created by kosero on 15.07.2025.
//

#include "window.hxx"
#include <raylib.h>

window_c::window_c(int w, int h, const char *t)
  : title(t), width(w), height(h) {}

void window_c::init() const {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(width, height, title);
}

bool window_c::shouldClose() { return WindowShouldClose(); }

void window_c::close() { CloseWindow(); }