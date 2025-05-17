#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>

typedef struct Animation
{
  int first;
  int last;
  int cur;
  float speed;
  float duration_left;
  int frame_width;
  int frame_height;
  bool flipped;
} Animation;

void animation_init(Animation* self, int first, int last, float speed,
                    int frame_width, int frame_height, bool flipped);
void animation_update(Animation* self);
Rectangle animation_frame(Animation* self, int num_frames_per_row);
void draw_animation(Animation* anim, Texture2D texture, Vector2 position,
                    int scale, int frames_per_row);

#endif
