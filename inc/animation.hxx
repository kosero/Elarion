//
// Created by kosero on 15.07.2025.
//

#ifndef ANIMATION_HXX
#define ANIMATION_HXX

#include <raylib.h>
#include "player.hxx"

class animation_c {
  int   frame_count;
  int   current_frame;
  float frame_time;
  float elapsed_time;
  int   frame_width;
  int   frame_height;

public:
  explicit animation_c(int count = 5, float time = 0.1f, int fw = 16,
                       int fh    = 16);

  void update();
  void draw(const Texture2D &texture, const player_c &player,
            float            scale) const;
};

#endif // ANIMATION_HXX