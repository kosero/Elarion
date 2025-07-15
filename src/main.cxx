#include "game_loop.hxx"
#include "window.hxx"

int main() {
  window_c window;
  window.init();

  while (!window_c::shouldClose()) { game_loop(); }

  window_c::close();
}