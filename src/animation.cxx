#include <cstdint>
#include <raylib.h>

#include "animation.hxx"

void Animator::Init(Animation *anim, Frame frame, float speed,
                    Vector2 resolution, bool is_flipped)
{
  anim->frame = frame;
  anim->speed = speed;
  anim->duration_left = speed;
  anim->resolution = resolution;
  anim->is_flipped = is_flipped;
}

void Animator::Refresh(Animation *anim, float delta)
{
  anim->duration_left -= delta;

  if (anim->duration_left <= 0.0f)
  {
    anim->duration_left = anim->speed;
    anim->frame.current++;

    if (anim->frame.current > anim->frame.last)
    {
      anim->frame.current = anim->frame.first;
    }
  }
}

static Rectangle get_frame_rect(Animation *anim, int16_t frames_per_row)
{
  int16_t frame_index_x = anim->frame.current % frames_per_row;
  int16_t frame_index_y = anim->frame.current / frames_per_row;

  float x = static_cast<float>(frame_index_x) * anim->resolution.x;
  float y = static_cast<float>(frame_index_y) * anim->resolution.y;

  return Rectangle{x, y, anim->resolution.x, anim->resolution.y};
}

void Animator::Draw(Animation *anim, Texture2D texture, Vector2 position,
                    int16_t scale, int16_t frames_per_row)
{
  Rectangle src = get_frame_rect(anim, frames_per_row);

  if (anim->is_flipped)
  {
    src.x += anim->resolution.x;
    src.width *= -1;
  }

  float scaled_width = anim->resolution.x * static_cast<float>(scale);
  float scaled_height = anim->resolution.y * static_cast<float>(scale);
  Rectangle dest{position.x, position.y, scaled_width, scaled_height};

  Vector2 origin = {0, 0};

  DrawTexturePro(texture, src, dest, origin, 0.0f, WHITE);
}
