//
// Created by kosero on 15.07.2025.
//

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <raylib.h>

struct player_s {
  Vector2     pos; // position
  Vector2     vel; // velocity
  const float speed;

  // Camera2D cam; // camera

  // bool isWalking;
};


class player_c {
public:
  static void Refresh(player_s *p);
};

#endif //PLAYER_HXX
