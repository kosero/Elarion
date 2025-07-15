//
// Created by kosero on 15.07.2025.
//

#include "animation.hxx"
#include "game_loop.hxx"
#include "window.hxx"

int main() {
  const window_c window;
  window.init();

  player_c           player;
  static animation_c anim;

  while (!window_c::shouldClose()) { game_loop(&player, &anim); }

  window_c::close();
  return 0;
}
