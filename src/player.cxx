//
// Created by kosero on 15.07.2025.
//

#include <raylib.h>
#include "player.hxx"
#include "input_map.hxx"

void player_c::Refresh(player_s *p) {
  if (UI_UP()) { p->pos.y -= 5; } else if (UI_DOWN()) { p->pos.y += 5; }
  if (UI_RIGHT()) { p->pos.x += 5; } else if (UI_LEFT()) { p->pos.x -= 5; }
}