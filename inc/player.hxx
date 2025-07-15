//
// Created by kosero on 15.07.2025.
//

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <raylib.h>

class player_c {
public:
  Vector2     pos; // position
  Vector2     vel; // velocity
  const float speed;

  static Texture2D texture;

  static void loadTexture();
  static void unloadTexture();

  explicit player_c(Vector2 p = {0.0f, 0.0f}, Vector2 v = {0, 0},
                    float   s = 300.0f);

  static void Refresh(player_c *p);
};

#endif // PLAYER_HXX
