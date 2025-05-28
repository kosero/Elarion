#include <cstdint>
#include <raylib.h>

#include "animation.hxx"

void c_animation::Init(t_animation &animation, t_frame &frame, float speed,
                       Vector2 &resolution, bool is_flipped)
{
  animation.frame = frame;
  animation.speed = speed;
  animation.duration_left = speed;
  animation.resolution = resolution;
  animation.is_flipped = is_flipped;
}

void c_animation::Refresh(t_animation &animation, float delta)
{
  animation.duration_left -= delta;

  if (animation.duration_left <= 0.0f)
  {
    animation.duration_left = animation.speed;
    animation.frame.current++;

    if (animation.frame.current > animation.frame.last)
    {
      animation.frame.current = animation.frame.first;
    }
  }
}

static Rectangle get_frame_rect(t_animation &animation, int16_t frames_per_row)
{
  int16_t frame_index_x = animation.frame.current % frames_per_row;
  int16_t frame_index_y = animation.frame.current / frames_per_row;

  float x = static_cast<float>(frame_index_x) * animation.resolution.x;
  float y = static_cast<float>(frame_index_y) * animation.resolution.y;

  return Rectangle{x, y, animation.resolution.x, animation.resolution.y};
}

void c_animation::Draw(t_animation &animation, Texture2D &texture,
                       Vector2 &position, int16_t scale, int16_t frames_per_row)
{
  Rectangle src = get_frame_rect(animation, frames_per_row);

  if (animation.is_flipped)
  {
    src.x += animation.resolution.x;
    src.width *= -1;
  }

  float scaled_width = animation.resolution.x * static_cast<float>(scale);
  float scaled_height = animation.resolution.y * static_cast<float>(scale);
  Rectangle dest{position.x, position.y, scaled_width, scaled_height};

  DrawTexturePro(texture, src, dest, {0, 0}, 0.0f, WHITE);
}
