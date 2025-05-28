#include <raylib.h>

#include "animation.hxx"
#include "main.hxx"
#include "player.hxx"
#include "ui/button.hxx"

static void DrawGameScreen(t_player &splayer, t_animation &sanimation,
                           c_animation &canimation, c_player &cplayer,
                           Texture2D &texture, float delta)
{

  Vector2 pos = {splayer.position.x - (sanimation.resolution.x * 3),
                 splayer.position.y - (sanimation.resolution.y * 3)};

  ClearBackground(FLOOR);
  DrawRectangle((SWIDTH - 100) / 2, (SHEIGHT - 100) % 2, 100, 100, RED);

  cplayer.Refresh(&splayer, &sanimation, &canimation, delta);
  canimation.Draw(sanimation, texture, pos, 5, 4);
}

static void DrawMenuScreen(t_button &button, c_button &cbutton, Vector2 &screen,
                           Vector2 &mouse_position,
                           t_screen_state *current_screen)
{
  Vector2 pos{(screen.x - button.size.x) / 2, (screen.y - button.size.y) / 2};
  ClearBackground(BG);
  cbutton.draw(button, pos, mouse_position);

  if (cbutton.is_click(button, pos, mouse_position))
  {
    *current_screen = SCREEN_GAME;
  }
}

int main(void)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(SWIDTH, SHEIGHT, "Elarion");
  SetExitKey(KEY_NULL);

  t_animation sanimation;
  c_animation canimation;
  Texture2D texture = LoadTexture("./assets/player.png");
  Vector2 hitbox = {16, 16};
  canimation.Init(sanimation, sanimation.frame, 0.1f, hitbox, false);

  t_player splayer;
  c_player cplayer;
  Camera2D c;

  splayer.hitbox = {16, 16};

  splayer.camera = c;
  splayer.camera.zoom = 1.0f;
  splayer.camera.rotation = 0;

  Vector2 mouse;
  Vector2 screen;

  t_button button;
  c_button cbutton;
  Font font = LoadFont("assets/font.ttf");
  button.font_family = font;
  button.text = "Resume";

  t_screen_state current_screen = SCREEN_GAME;

  while (!WindowShouldClose())
  {
    screen = {static_cast<float>(GetScreenWidth()),
              static_cast<float>(GetScreenHeight())};

    mouse = GetMousePosition();
    float delta = GetFrameTime();

    switch (current_screen)
    {
    case SCREEN_GAME:
      if (IsKeyPressed(KEY_ESCAPE))
        current_screen = SCREEN_MENU;
      break;

    case SCREEN_MENU:
      if (IsKeyPressed(KEY_ESCAPE))
        current_screen = SCREEN_GAME;
      break;
    }

    BeginDrawing();

    switch (current_screen)
    {
    case SCREEN_GAME:
      BeginMode2D(splayer.camera);
      DrawGameScreen(splayer, sanimation, canimation, cplayer, texture, delta);
      EndMode2D();
      break;

    case SCREEN_MENU:
      DrawMenuScreen(button, cbutton, screen, mouse, &current_screen);
      break;
    }

    EndDrawing();
  }

  UnloadTexture(texture);
  CloseWindow();
  return 0;
}
