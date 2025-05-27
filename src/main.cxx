#include <raylib.h>

#include "animation.hxx"
#include "main.hxx"
#include "player.hxx"

static void DrawGameScreen(Player &player, Animation &anim, Animator &animator,
                           PlayerManager &pmng, Texture2D &texture)
{
  float delta = GetFrameTime();

  Vector2 pos = {player.position.x - (anim.resolution.x * 3),
                 player.position.y - (anim.resolution.y * 3)};

  ClearBackground(FLOOR);
  DrawRectangle((SWIDTH - 100) / 2, (SHEIGHT - 100) % 2, 100, 100, RED);

  pmng.Refresh(&player, &anim, &animator, delta);
  animator.Draw(&anim, texture, pos, 5, 4);
}

static void DrawMenuScreen(int screenWidth, int screenHeight)
{
  ClearBackground(BG);
  DrawText("Elarion", (screenWidth / 2), (screenHeight / 2), 20, BLACK);
}

int main(void)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(SWIDTH, SHEIGHT, "Elarion");
  SetExitKey(KEY_NULL);

  Animation anim;
  Animator animator;
  Texture2D texture = LoadTexture("./assets/player.png");
  animator.Init(&anim, anim.frame, 0.1f, {16, 16}, false);

  PlayerManager pmng;
  Player player = pmng.Init({0, 0}, 300.0f, {16.0f, 16.0f});

  ScreenState current_screen = SCREEN_GAME;

  while (!WindowShouldClose())
  {
    int sW = GetScreenWidth();
    int sH = GetScreenHeight();

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
      BeginMode2D(player.camera);
      DrawGameScreen(player, anim, animator, pmng, texture);
      EndMode2D();
      break;

    case SCREEN_MENU:
      DrawMenuScreen(sW, sH);
      break;
    }

    EndDrawing();
  }

  UnloadTexture(texture);
  CloseWindow();
  return 0;
}
