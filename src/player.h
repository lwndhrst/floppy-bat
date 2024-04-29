#pragma once

#include <raylib.h>

#define GRAVITY 9.81f

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
} Player;

void update_player(Player *player);
void draw_player(Player *player);
