//
// Created by kosero on 15.07.2025.
//

#include "animation.hxx"
#include <raylib.h>

animation_c::animation_c(const int count, const float time, const int fw,
                         const int fh)
  : frame_count(count), current_frame(0), frame_time(time),
    elapsed_time(0.0f), frame_width(fw), frame_height(fh) {}

void animation_c::update() {
  elapsed_time += GetFrameTime();
  while (elapsed_time >= frame_time) {
    elapsed_time -= frame_time;
    current_frame = (current_frame + 1) % frame_count;
  }
}

void animation_c::draw(const Texture2D &texture, const player_c &player,
                       const float      scale) const {
  const Rectangle src = {
      static_cast<float>(current_frame * frame_width),
      0.0f,
      static_cast<float>(frame_width),
      static_cast<float>(frame_height)
  };

  const Rectangle dest = {
      player.pos.x,
      player.pos.y,
      src.width * scale,
      src.height * scale
  };

  DrawTexturePro(texture, src, dest, {0, 0}, 0.0f, WHITE);
}
