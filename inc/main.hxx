#ifndef MAIN_HXX
#define MAIN_HXX

#include <raylib.h>

#define SWIDTH 800
#define SHEIGHT 600

constexpr Color FLOOR{76, 129, 73, 1};
constexpr Color BG{30, 33, 36, 0};

typedef enum
{
  SCREEN_MENU,
  SCREEN_GAME,
} t_screen_state;

#endif
