//
// Created by kosero on 15.07.2025.
//

#include <raylib.h>
#include "game_loop.hxx"
#include "player.hxx"

void game_loop(player_s *player) {
  DrawCircle(static_cast<int>(player->pos.x), static_cast<int>(player->pos.x),
             50.0f, RED);
  player_c::Refresh(player);
}