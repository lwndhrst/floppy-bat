#include "obstacles.h"

#include <stdlib.h>

#define OBSTACLE_DISTANCE_PIXELS 50
#define OBSTACLE_WIDTH_PIXELS 30
#define OBSTACLE_TOTAL_PIXELS (OBSTACLE_DISTANCE_PIXELS + OBSTACLE_WIDTH_PIXELS)
#define SCROLL_SPEED 200.0f

int num_obstacles = 0;

void
init_obstacle_system(ObstacleSystem *obstacle_system)
{
    int screen_width = GetScreenWidth();

    num_obstacles = 1 + (screen_width / OBSTACLE_TOTAL_PIXELS);

    Obstacle *obstacles = malloc(num_obstacles * sizeof(Obstacle));

    for (int i = 0; i < num_obstacles; ++i) {
        Vector2 position = {screen_width + i * OBSTACLE_TOTAL_PIXELS, 0.0f};
        Obstacle obstacle = {position};
        obstacles[i] = obstacle;
    }

    obstacle_system->obstacles = obstacles;
}

void
destroy_obstacle_system(ObstacleSystem *obstacle_system)
{
    free(obstacle_system->obstacles);
}

void
update_obstacles(ObstacleSystem *obstacle_system, float delta_time)
{
    if (!num_obstacles) {
        return;
    }

    for (int i = 0; i < num_obstacles; ++i) {
        float new_x = obstacle_system->obstacles[i].position.x - (SCROLL_SPEED * delta_time);
        if (new_x < -OBSTACLE_WIDTH_PIXELS) {
            int idx = (i + (num_obstacles - 1)) % num_obstacles;
            new_x = obstacle_system->obstacles[idx].position.x + OBSTACLE_TOTAL_PIXELS;
        }
        obstacle_system->obstacles[i].position.x = new_x;
    }
}

void
draw_obstacles(ObstacleSystem *obstacle_system)
{
    if (!num_obstacles) {
        return;
    }

    for (int i = 0; i < num_obstacles; ++i) {
        Vector2 start_pos = {obstacle_system->obstacles[i].position.x, 0.0f};
        Vector2 end_pos = {obstacle_system->obstacles[i].position.x, (float)GetScreenHeight()};

        DrawLineEx(start_pos, end_pos, OBSTACLE_WIDTH_PIXELS, PURPLE);
    }
}
