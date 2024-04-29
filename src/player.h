#pragma once

#include <raylib.h>

#define GRAVITY 9.81f

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
} Player;

void init_player(Player *player, const int screen_width, const int screen_height);
void update_player(Player *player);
void draw_player(Player *player);
