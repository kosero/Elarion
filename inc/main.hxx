#pragma once

#ifndef MAIN_HXX
#define MAIN_HXX

#include "player.hxx"
#include "ui/button.hxx"
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

typedef struct s_menu_context
{
  t_button *button;
  c_button *cbutton;
  Vector2 screen;
  Vector2 mouse_position;
  t_screen_state *current_screen;
} t_menu_context;

typedef struct s_game_context
{
  t_player *splayer;
  c_player *cplayer;
  t_animation *sanimation;
  c_animation *canimation;
  Texture2D *texture;
  float delta;
} t_game_context;

#endif
