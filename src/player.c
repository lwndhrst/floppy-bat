#include "player.h"

#define GRAVITY 9.81f

void
init_player(Player *player)
{
    Vector2 position = {(float)GetScreenWidth() / PI, (float)GetScreenHeight() / 2.0f};
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 acceleration = {0.0f, 50.0f * GRAVITY};

    player->position = position;
    player->velocity = velocity;
    player->acceleration = acceleration;
}

void
update_player(Player *player, float delta_time)
{
    if (IsKeyPressed(KEY_SPACE)) {
        player->velocity.y -= 200.0f;
    }

    player->velocity.y += delta_time * player->acceleration.y;
    player->position.y += delta_time * player->velocity.y;
}

void
draw_player(Player *player)
{
    DrawCircleV(player->position, 16.0f, BLACK);
}
