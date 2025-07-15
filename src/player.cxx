//
// Created by kosero on 15.07.2025.
//

#include <raylib.h>
#include "player.hxx"
#include "input_map.hxx"

#include <iostream>

Texture2D player_c::texture = {};

void player_c::loadTexture() {
  texture = LoadTexture("assets/player.png");
  if (texture.id == 0) {
    std::cerr << "[err]: Failed to load texture 'assets/player.png'\n";
    std::exit(EXIT_FAILURE);
  }
}

void player_c::unloadTexture() {
  if (texture.id != 0) {
    UnloadTexture(texture);
    texture.id = 0;
  }
}

player_c::player_c(const Vector2 p, const Vector2 v, const float s)
  : pos(p), vel(v), speed(s) {}

void player_c::Refresh(player_c *p) {
  if (UI_UP()) { p->pos.y -= 5; } else if (UI_DOWN()) { p->pos.y += 5; } else if
  (UI_RIGHT()) { p->pos.x += 5; } else if (UI_LEFT()) { p->pos.x -= 5; }
}
