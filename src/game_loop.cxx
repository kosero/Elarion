//
// Created by kosero on 15.07.2025.
//

#include <raylib.h>
#include "game_loop.hxx"
#include "player.hxx"

void game_loop(player_s *player) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawCircle(static_cast<int>(player->pos.x),
             static_cast<int>(player->pos.y),
             50.0f, RED);

  EndDrawing();

  player_c::Refresh(player);
}
