#pragma once

#include <raylib.h>

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
} Player;

void init_player(Player *player, int screen_width, int screen_height);
void update_player(Player *player, float delta_time);
void draw_player(Player *player);
