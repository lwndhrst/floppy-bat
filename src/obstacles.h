#pragma once

#include <raylib.h>

typedef struct {
    Vector2 position;
} Obstacle;

typedef struct {
    Obstacle *obstacles;
} ObstacleSystem;

void init_obstacle_system(ObstacleSystem *obstacle_system);
void destroy_obstacle_system(ObstacleSystem *obstacle_system);
void update_obstacles(ObstacleSystem *obstacle_system, float delta_time);
void draw_obstacles(ObstacleSystem *obstacle_system);
