#pragma once

#include <raylib.h>

typedef struct {
    Vector2 position;
} Obstacle;

typedef struct {
    int screen_width;
    int screen_height;
    float scroll_speed;
    float scroll_accel;
    int num_obstacles;
    Obstacle *obstacles;
} ObstacleSystem;

void init_obstacle_system(ObstacleSystem *obstacle_system, int screen_width, int screen_height);
void destroy_obstacle_system(ObstacleSystem *obstacle_system);
void update_obstacles(ObstacleSystem *obstacle_system, float delta_time);
void draw_obstacles(ObstacleSystem *obstacle_system);
