#pragma once

#include <raylib.h>

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
} Player;

void init_player(Player *player);
void update_player(Player *player, float delta_time);
void draw_player(Player *player);
