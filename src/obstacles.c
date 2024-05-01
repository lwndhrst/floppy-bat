#include "obstacles.h"

#include <stdlib.h>

#define OBSTACLE_DISTANCE_PIXELS 250
#define OBSTACLE_WIDTH_PIXELS 50
#define OBSTACLE_TOTAL_PIXELS (OBSTACLE_DISTANCE_PIXELS + OBSTACLE_WIDTH_PIXELS)
#define OBSTACLE_OPENING_PIXELS 128

#define SCROLL_SPEED 100.0f
#define SCROLL_ACCEL 10.0f

void
randomize_opening_position(Obstacle *obstacle, int screen_height)
{
    int margin = OBSTACLE_OPENING_PIXELS;
    float y = GetRandomValue(0 + margin, screen_height - margin);

    obstacle->top_y = 0.0f;
    obstacle->top_height = y - (float)(OBSTACLE_OPENING_PIXELS >> 1);
    obstacle->bot_y = y + (float)(OBSTACLE_OPENING_PIXELS >> 1);
    obstacle->bot_height = (float)screen_height - obstacle->bot_y;
}

void
init_obstacle_system(ObstacleSystem *obstacle_system, int screen_width, int screen_height)
{
    int num_obstacles = 1 + (screen_width / OBSTACLE_TOTAL_PIXELS);

    Obstacle *obstacles = malloc(num_obstacles * sizeof(Obstacle));

    for (int i = 0; i < num_obstacles; ++i)
    {
        Obstacle obstacle;
        obstacle.x = screen_width + i * OBSTACLE_TOTAL_PIXELS;

        randomize_opening_position(&obstacle, screen_height);
        obstacles[i] = obstacle;
    }

    obstacle_system->screen_width = screen_width;
    obstacle_system->screen_height = screen_height;
    obstacle_system->scroll_speed = SCROLL_SPEED;
    obstacle_system->scroll_accel = SCROLL_ACCEL;
    obstacle_system->num_obstacles = num_obstacles;
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
    obstacle_system->scroll_speed += obstacle_system->scroll_accel * delta_time;

    for (int i = 0; i < obstacle_system->num_obstacles; ++i)
    {
        Obstacle *obstacle = &obstacle_system->obstacles[i];

        obstacle->x -= obstacle_system->scroll_speed * delta_time;
        if (obstacle->x < -OBSTACLE_WIDTH_PIXELS)
        {
            int rightmost_idx = (i + obstacle_system->num_obstacles - 1) % obstacle_system->num_obstacles;
            obstacle->x = obstacle_system->obstacles[rightmost_idx].x + OBSTACLE_TOTAL_PIXELS;
            randomize_opening_position(obstacle, obstacle_system->screen_height);
        }
    }
}

void
draw_obstacles(ObstacleSystem *obstacle_system)
{
    for (int i = 0; i < obstacle_system->num_obstacles; ++i)
    {
        Obstacle *obstacle = &obstacle_system->obstacles[i];

        DrawRectangle(obstacle->x,
                      obstacle->top_y,
                      OBSTACLE_WIDTH_PIXELS,
                      obstacle->top_height,
                      PURPLE);

        DrawRectangle(obstacle->x,
                      obstacle->bot_y,
                      OBSTACLE_WIDTH_PIXELS,
                      obstacle->bot_height,
                      PURPLE);
    }
}

bool
check_collisions(ObstacleSystem *obstacle_system, Player *player)
{
    for (int i = 0; i < obstacle_system->num_obstacles; ++i)
    {
        Obstacle *obstacle = &obstacle_system->obstacles[i];

        float dx = player->position.x - obstacle->x;
        if (0.0f < dx && dx < OBSTACLE_WIDTH_PIXELS)
        {
            float dy = player->position.y - obstacle->top_height;
            if (dy < 0.0f || OBSTACLE_OPENING_PIXELS < dy)
            {
                return true;
            }
        }
    }

    return false;
}
