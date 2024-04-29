#include <raylib.h>

#include "player.h"

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
