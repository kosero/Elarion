#ifndef ANIMATION_HXX
#define ANIMATION_HXX

#include <cstdint>
#include <raylib.h>

typedef struct s_frame
{
  int16_t first;
  int16_t last;
  int16_t current;
} t_frame;

typedef struct s_animation
{
  t_frame frame;
  float speed;
  float duration_left;
  Vector2 resolution;
  bool is_flipped;
} t_animation;

class c_animation
{
public:
  void Init(t_animation &animation, t_frame &frame, float speed,
            Vector2 &resolution, bool is_flipped);
  void Refresh(t_animation &animation, float delta);
  void Draw(t_animation &animation, Texture2D &texture, Vector2 &position,
            int16_t scale, int16_t frames_per_row);
};

#endif
