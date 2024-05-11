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

    player->spritesheet = LoadTexture(TextFormat("%s/spritesheets/bat.png", ASSETS_PATH));
    player->sprite_width = 64;
    player->sprite_height = 64;

    player->hitbox_offset_top = player->sprite_height >> 2;
    player->hitbox_offset_bot = player->sprite_height >> 2;
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
    Rectangle player_rect = {player->position.x, player->position.y, player->sprite_width, player->sprite_height};

    const size_t frame_width = 16;
    const size_t frame_height = 16;
    const size_t num_frames = 4;

    Rectangle frames[num_frames];
    for (size_t i = 0; i < num_frames; ++i)
    {
        frames[i] = (Rectangle){i * frame_width, 0, frame_width, frame_height};
    }

    float rotation = player->velocity.y * 0.025f;

    if (player->velocity.y > 10.0f)
    {
        DrawTexturePro(player->spritesheet, frames[0], player_rect, (Vector2){0, 0}, rotation, WHITE);
    }
    else if (player->velocity.y > 0.0f)
    {
        DrawTexturePro(player->spritesheet, frames[1], player_rect, (Vector2){0, 0}, rotation, WHITE);
    }
    else if (player->velocity.y < -10.0f)
    {
        DrawTexturePro(player->spritesheet, frames[2], player_rect, (Vector2){0, 0}, rotation, WHITE);
    }
    else
    {
        DrawTexturePro(player->spritesheet, frames[3], player_rect, (Vector2){0, 0}, rotation, WHITE);
    }
}

bool
check_out_of_bounds(Player *player, int screen_width, int screen_height)
{
    return player->position.y + player->hitbox_offset_top < 0.0f ||
           screen_height + player->hitbox_offset_bot < player->position.y + player->sprite_height;
}
