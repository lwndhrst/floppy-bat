#pragma once

#include <raylib.h>

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Texture2D spritesheet;
    size_t sprite_width;
    size_t sprite_height;

    size_t hitbox_offset_top;
    size_t hitbox_offset_bot;
} Player;

void init_player(Player *player, int screen_width, int screen_height);
void update_player(Player *player, float delta_time);
void draw_player(Player *player);

bool check_out_of_bounds(Player *player, int screen_width, int screen_height);
