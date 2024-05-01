#include "player.h"

#define GRAVITY 9.81f

void
init_player(Player *player, int screen_width, int screen_height)
{
    Vector2 position = {(float)(screen_width >> 2), (float)(screen_height >> 1)};
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 acceleration = {0.0f, 100.0f * GRAVITY};

    player->position = position;
    player->velocity = velocity;
    player->acceleration = acceleration;
}

void
update_player(Player *player, float delta_time)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        player->velocity.y -= 300.0f;
    }

    player->velocity.y += delta_time * player->acceleration.y;
    player->position.y += delta_time * player->velocity.y;
}

void
draw_player(Player *player)
{
    DrawCircleV(player->position, 16.0f, BLACK);
}

bool
check_out_of_bounds(Player *player, int screen_width, int screen_height)
{
    return player->position.y < 0.0f || screen_height < player->position.y;
}
