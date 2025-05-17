#include <raylib.h>

#include "animation.h"
#include "game.h"
#include "player.h"

int main(void)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(SWIDTH, SHEIGHT, "lumtopia");

  Player player = player_init((Vector2){0, 0}, (Vector2){16, 16});

  Texture2D player_idle_down_texture =
      LoadTexture("./assets/player/idle/Sword_Idle_Down.png");
  Texture2D player_idle_up_texture =
      LoadTexture("./assets/player/idle/Sword_Idle_Up.png");
  Texture2D player_idle_right_texture =
      LoadTexture("./assets/player/idle/Sword_Idle_Right.png");
  Texture2D player_idle_left_texture =
      LoadTexture("./assets/player/idle/Sword_Idle_Left.png");

  Texture2D player_walk_down_texture =
      LoadTexture("./assets/player/walk/Sword_Walk_Down.png");
  Texture2D player_walk_up_texture =
      LoadTexture("./assets/player/walk/Sword_Walk_Up.png");
  Texture2D player_walk_right_texture =
      LoadTexture("./assets/player/walk/Sword_Walk_Right.png");
  Texture2D player_walk_left_texture =
      LoadTexture("./assets/player/walk/Sword_Walk_Left.png");

  Animation anim_idle_down, anim_idle_up, anim_idle_right, anim_idle_left;
  Animation anim_walk_down, anim_walk_up, anim_walk_right, anim_walk_left;

  animation_init(&anim_idle_down, 0, 6, 0.1f, 128, 128, false);
  animation_init(&anim_idle_up, 0, 6, 0.1f, 128, 128, false);
  animation_init(&anim_idle_right, 0, 6, 0.1f, 128, 128, false);
  animation_init(&anim_idle_left, 0, 6, 0.1f, 128, 128, false);

  animation_init(&anim_walk_down, 0, 6, 0.1f, 128, 128, false);
  animation_init(&anim_walk_up, 0, 6, 0.1f, 128, 128, false);
  animation_init(&anim_walk_right, 0, 6, 0.1f, 128, 128, false);
  animation_init(&anim_walk_left, 0, 6, 0.1f, 128, 128, false);

  Camera2D camera = {0};
  camera.target = player.position;
  camera.offset = (Vector2){SWIDTH / 2.0f, SHEIGHT / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  while (!WindowShouldClose())
  {
    float deltaTime = GetFrameTime();

    if (camera.zoom > 3.0f)
      camera.zoom = 3.0f;
    else if (camera.zoom < 0.25f)
      camera.zoom = 0.25f;

    camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

    BeginDrawing();
    ClearBackground(DARKGREEN);
    BeginMode2D(camera);

    update_player(&player, &camera, &anim_idle_up, deltaTime);

    Texture2D current_texture;
    Animation* current_anim;

    switch (player.state)
    {
    case UP_WALK:
      current_texture = player_walk_up_texture;
      current_anim = &anim_walk_up;
      break;
    case DOWN_WALK:
      current_texture = player_walk_down_texture;
      current_anim = &anim_walk_down;
      break;
    case RIGHT_WALK:
      current_texture = player_walk_right_texture;
      current_anim = &anim_walk_right;
      break;
    case LEFT_WALK:
      current_texture = player_walk_left_texture;
      current_anim = &anim_walk_left;
      break;
    case UP_IDLE:
      current_texture = player_idle_up_texture;
      current_anim = &anim_idle_up;
      break;
    case DOWN_IDLE:
      current_texture = player_idle_down_texture;
      current_anim = &anim_idle_down;
      break;
    case RIGHT_IDLE:
      current_texture = player_idle_right_texture;
      current_anim = &anim_idle_right;
      break;
    case LEFT_IDLE:
      current_texture = player_idle_left_texture;
      current_anim = &anim_idle_left;
      break;
    default:
      current_texture = player_idle_down_texture;
      current_anim = &anim_idle_down;
      break;
    }

    animation_update(current_anim);

    Vector2 pos = {player.position.x - (current_anim->frame_width * 3),
                   player.position.y - (current_anim->frame_height * 3)};

    draw_animation(current_anim, current_texture, pos, 6, 6);

    float cubeSize = 32;
    DrawRectangle(0, 0, cubeSize, cubeSize, MAROON);

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
