//
// Created by kosero on 15.07.2025.
//

#include <raylib.h>
#include "game_loop.hxx"
#include "animation.hxx"
#include "player.hxx"


void game_loop(player_c *   player,
               animation_c *anim) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  anim->update();
  anim->draw(player_c::texture, *player, 6.0f);
  EndDrawing();

  player_c::Refresh(player);
}
