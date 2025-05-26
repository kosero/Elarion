#include <raylib.h>

#include "animation.hxx"
#include "main.hxx"
#include "player.hxx"

int main(void)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(SWIDTH, SHEIGHT, "test");

  Animation anim;
  Animator animator;
  Texture2D texture = LoadTexture("./assets/character.png");
  animator.Init(&anim, anim.frame, 0.1f, {16, 16}, false);

  Camera2D cam;
  PlayerManager pmng;
  Player player = pmng.Init(cam, {0, 0}, 300.0f, {16, 16});

  while (!WindowShouldClose())
  {
    float delta = GetFrameTime();

    Vector2 pos = {player.position.x - (anim.resolution.x * 3),
                   player.position.y - (anim.resolution.y * 3)};

    BeginDrawing();
    ClearBackground(FLOOR);
    BeginMode2D(player.camera);

    pmng.Refresh(&player, &anim, &animator, delta);
    animator.Draw(&anim, texture, pos, 5, 4);

    DrawRectangle((SWIDTH - 100) / 2, (SHEIGHT - 100) % 2, 100, 100, RED);

    EndMode2D();
    EndDrawing();
  }

  UnloadTexture(texture);
  CloseWindow();
  return 0;
}
