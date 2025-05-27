#include <cstdint>
#include <raylib.h>

#include "animation.hxx"
#include "player.hxx"

Player PlayerManager::Init(Vector2 position, float speed, Vector2 hitbox)
{
  Player p;
  Camera2D c;

  p.position = position;
  p.speed = speed;
  p.hitbox = hitbox;

  p.camera = c;
  p.camera.zoom = 1.0f;
  p.camera.rotation = 0;

  return p;
}

static void set_anim_if_needed(Animation *anim, int16_t start, int16_t end)
{
  if (anim->frame.first != start || anim->frame.last != end)
  {
    anim->frame.first = start;
    anim->frame.last = end;
    anim->frame.current = start;
  }
}

static void apply_anim(Animation *anim, Animator *animator, float delta,
                       int16_t start, int16_t end)
{
  set_anim_if_needed(anim, start, end);
  animator->Refresh(anim, delta);
}

void PlayerManager::Refresh(Player *player, Animation *anim, Animator *animator,
                            float delta)
{
  struct Direction
  {
    bool active;
    Vector2 velocity;
    int16_t anim_start;
    int16_t anim_end;
  } directions[] = {
      {IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT), {-player->speed, 0.0f}, 4, 7},
      {IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT), {player->speed, 0.0f}, 12, 15},
      {IsKeyDown(KEY_W) || IsKeyDown(KEY_UP), {0.0f, -player->speed}, 8, 11},
      {IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN), {0.0f, player->speed}, 0, 3}};

  player->velocity = {0.0f, 0.0f};
  player->state.WALKING = false;

  int16_t last_anim_start = anim->frame.first;

  for (const auto &dir : directions)
  {
    if (dir.active)
    {
      player->velocity = dir.velocity;
      apply_anim(anim, animator, delta, dir.anim_start, dir.anim_end);
      player->state.WALKING = true;
      break;
    }
  }

  if (!player->state.WALKING)
  {
    anim->frame.current = last_anim_start;
  }

  player->position.x += player->velocity.x * delta;
  player->position.y += player->velocity.y * delta;

  player->state.IDLE = !player->state.WALKING;

  int width = GetScreenWidth();
  int height = GetScreenHeight();
  player->camera.offset = {static_cast<float>(width) / 2.0f,
                           static_cast<float>(height) / 2.0f};
  player->camera.target = player->position;
}
