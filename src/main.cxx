#include "game_loop.hxx"
#include "window.hxx"

int main() {
  window_c window;
  window.init();
  player_s player;

  while (!window_c::shouldClose()) { game_loop(&player); }

  window_c::close();
}