#include <raylib.h>

#include "animation.hxx"
#include "main.hxx"

int main(void)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(SWIDTH, SHEIGHT, "test");

  Animation anim;
  Animator animator;
  Texture2D texture = LoadTexture("./assets/character.png");
  animator.Init(&anim, {0, 3, 0}, 0.1f, {16, 16}, false);

  while (!WindowShouldClose())
  {
    animator.Refresh(&anim);
    BeginDrawing();
    ClearBackground(FLOOR);

    animator.Draw(&anim, texture, {0, 0}, 5, 4);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
