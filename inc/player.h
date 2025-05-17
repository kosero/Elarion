#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#include "animation.h"

typedef enum
{
  UP_WALK,
  DOWN_WALK,
  RIGHT_WALK,
  LEFT_WALK,
  UP_IDLE,
  DOWN_IDLE,
  RIGHT_IDLE,
  LEFT_IDLE
} PlayerState;

typedef struct Player
{
  Vector2 position;
  Vector2 velocity;
  float speed;
  Vector2 hitbox;
  PlayerState state;
} Player;

Player player_init(Vector2 position, Vector2 hitbox);
void update_player(Player* player, Camera2D* camera, Animation* anim,
                   float delta);

#endif // !PLAYER_H
