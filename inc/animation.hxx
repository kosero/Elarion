#ifndef ANIMATION_H
#define ANIMATION_H

#include <cstdint>
#include <raylib.h>
#include <stdint.h>

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
  Rectangle get_frame_rect(Animation *anim, int16_t frames_per_row);
  void Refresh(Animation *anim);
  void Draw(Animation *anim, Texture2D texture, Vector2 position, int16_t scale,
            int16_t frames_per_row);
};

#endif
