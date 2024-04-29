#include "player.h"

void
init_player(Player *player, const int screen_width, const int screen_height)
{
    Vector2 position = {(float)screen_width / PI, (float)screen_height / 2};
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 acceleration = {0.0f, 50.0f * GRAVITY};

    player->position = position;
    player->velocity = velocity;
    player->acceleration = acceleration;
}

void
update_player(Player *player)
{
    if (IsKeyPressed(KEY_SPACE)) {
        player->velocity.y -= 200.0f;
    }

    float delta_time = GetFrameTime();
    player->velocity.y += delta_time * player->acceleration.y;
    player->position.y += delta_time * player->velocity.y;
}

void
draw_player(Player *player)
{
    DrawCircleV(player->position, 10.0f, BLACK);
}
