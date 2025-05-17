#include "animation.h"

void animation_init(Animation* self, int first, int last, float speed,
                    int frame_width, int frame_height, bool flipped)
{
  self->first = first;
  self->last = last;
  self->cur = first;
  self->speed = speed;
  self->duration_left = speed;
  self->frame_width = frame_width;
  self->frame_height = frame_height;
  self->flipped = flipped;
}

void animation_update(Animation* self)
{
  float dt = GetFrameTime();
  self->duration_left -= dt;

  if (self->duration_left <= 0.0f)
  {
    self->duration_left = self->speed;
    self->cur++;
  }

  if (self->cur > self->last)
  {
    self->cur = self->first;
  }
}

Rectangle animation_frame(Animation* self, int num_frames_per_row)
{
  int x = (self->cur % num_frames_per_row) * self->frame_width;
  int y = (self->cur / num_frames_per_row) * self->frame_height;

  return (Rectangle){.x = (float)x,
                     .y = (float)y,
                     .width = (float)self->frame_width,
                     .height = (float)self->frame_height};
}

void draw_animation(Animation* anim, Texture2D texture, Vector2 position,
                    int scale, int frames_per_row)
{
  Rectangle src = animation_frame(anim, frames_per_row);

  if (anim->flipped)
  {
    src.width *= -1;
    src.x += anim->frame_width;
  }

  Rectangle dst = {.x = position.x,
                   .y = position.y,
                   .width = anim->frame_width * scale,
                   .height = anim->frame_height * scale};

  Vector2 origin = {0};
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}
