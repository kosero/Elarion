#ifndef PLAYER_H
#define PLAYER_H

#include "animation.hxx"
#include <raylib.h>

struct State
{
  bool IDLE;
  bool WALKING;
};

struct Player
{
  Vector2 position;
  Vector2 velocity;
  float speed;
  Vector2 hitbox;
  Camera2D camera;
  State state;
};

class PlayerManager
{
public:
  Player Init(Camera2D camera, Vector2 position, float speed, Vector2 hitbox);
  void Refresh(Player *player, Animation *anim, Animator *animator,
               float delta);
};

#endif // !PLAYER_H
