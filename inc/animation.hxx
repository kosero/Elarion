#ifndef ANIMATION_HXX
#define ANIMATION_HXX

#include <cstdint>
#include <raylib.h>

struct Frame
{
  int16_t first;
  int16_t last;
  int16_t current;
};

struct Animation
{
  Frame frame;
  float speed;
  float duration_left;
  Vector2 resolution;
  bool is_flipped;
};

class Animator
{
public:
  void Init(Animation *anim, Frame frame, float speed, Vector2 resolution,
            bool is_flipped);
  void Refresh(Animation *anim, float delta);
  void Draw(Animation *anim, Texture2D texture, Vector2 position, int16_t scale,
            int16_t frames_per_row);
};

#endif
