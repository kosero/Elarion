#include <raylib.h>

#include "animation.hxx"
#include "main.hxx"
#include "player.hxx"
#include "ui/button.hxx"

static void DrawGameScreen(t_game_context *ctx)
{
  Vector2 pos = {ctx->splayer->position.x - (ctx->sanimation->resolution.x * 3),
                 ctx->splayer->position.y -
                     (ctx->sanimation->resolution.y * 3)};

  ClearBackground(FLOOR);
  DrawRectangle((SWIDTH - 100) / 2, (SHEIGHT - 100) % 2, 100, 100, RED);

  ctx->cplayer->Refresh(ctx->splayer, ctx->sanimation, ctx->canimation,
                        ctx->delta);
  ctx->canimation->Draw(*ctx->sanimation, *ctx->texture, pos, 5, 4);
}

static void DrawMenuScreen(t_menu_context *ctx)
{
  Vector2 pos{(ctx->screen.x - ctx->button->size.x) / 2,
              (ctx->screen.y - ctx->button->size.y) / 2};

  ClearBackground(BG);
  ctx->cbutton->draw(*ctx->button, pos, ctx->mouse_position);

  if (ctx->cbutton->is_click(*ctx->button, pos, ctx->mouse_position))
  {
    *ctx->current_screen = SCREEN_GAME;
  }
}

int main(void)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(SWIDTH, SHEIGHT, "Elarion");
  SetExitKey(KEY_NULL);

  t_animation sanimation;
  c_animation canimation;
  Texture2D texture = LoadTexture("./assets/player.png");
  Vector2 res = {16, 16};
  canimation.Init(sanimation, sanimation.frame, 0.1f, res, false);

  t_player splayer;
  c_player cplayer;
  splayer.hitbox = {16, 16};
  splayer.camera.zoom = 1.0f;
  splayer.camera.rotation = 0;

  t_button button;
  c_button cbutton;
  button.font_family = LoadFont("assets/font.ttf");
  button.text = "Resume";

  t_screen_state current_screen = SCREEN_MENU;

  while (!WindowShouldClose())
  {
    Vector2 screen = {(float)GetScreenWidth(), (float)GetScreenHeight()};
    Vector2 mouse = GetMousePosition();
    float delta = GetFrameTime();

    if (IsKeyPressed(KEY_ESCAPE))
      current_screen =
          (current_screen == SCREEN_GAME) ? SCREEN_MENU : SCREEN_GAME;

    BeginDrawing();

    if (current_screen == SCREEN_GAME)
    {
      BeginMode2D(splayer.camera);
      t_game_context game_ctx{&splayer,    &cplayer, &sanimation,
                              &canimation, &texture, delta};
      DrawGameScreen(&game_ctx);
      EndMode2D();
    }
    else
    {
      t_menu_context menu_ctx{&button, &cbutton, screen, mouse,
                              &current_screen};
      DrawMenuScreen(&menu_ctx);
    }

    EndDrawing();
  }

  UnloadTexture(texture);
  CloseWindow();
  return 0;
}
