#ifndef PLAYER_HXX
#define PLAYER_HXX

#include "animation.hxx"
#include <raylib.h>

typedef struct s_player_state
{
  bool IDLE;
  bool WALKING;
} t_player_state;

typedef struct s_player
{
  Vector2 position = {0, 0};
  Vector2 velocity;
  float speed = 300.0f;
  Vector2 hitbox;
  Camera2D camera;
  t_player_state state;
} t_player;

class c_player
{
public:
  void Refresh(t_player *player, t_animation *sanimation,
               c_animation *canimation, float delta);
};

#endif // !PLAYER_H
