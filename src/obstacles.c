#include "obstacles.h"

#include <stdlib.h>

#define OBSTACLE_DISTANCE_PIXELS 250
#define OBSTACLE_WIDTH_PIXELS 50
#define OBSTACLE_TOTAL_PIXELS (OBSTACLE_DISTANCE_PIXELS + OBSTACLE_WIDTH_PIXELS)
#define OBSTACLE_OPENING_PIXELS 128

#define SCROLL_SPEED 100.0f
#define SCROLL_ACCEL 10.0f

int
get_random_bounded_y_coord(int screen_height)
{
    int margin = OBSTACLE_OPENING_PIXELS;
    return GetRandomValue(0 + margin, screen_height - margin);
}

void
init_obstacle_system(ObstacleSystem *obstacle_system, int screen_width, int screen_height)
{
    int num_obstacles = 1 + (screen_width / OBSTACLE_TOTAL_PIXELS);

    Obstacle *obstacles = malloc(num_obstacles * sizeof(Obstacle));

    for (int i = 0; i < num_obstacles; ++i) {
        Vector2 position = {
            (float)(screen_width + i * OBSTACLE_TOTAL_PIXELS),
            get_random_bounded_y_coord(screen_height)};

        Obstacle obstacle = {position};
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

    for (int i = 0; i < obstacle_system->num_obstacles; ++i) {
        Obstacle *obstacle = &obstacle_system->obstacles[i];

        float x = obstacle->position.x - (obstacle_system->scroll_speed * delta_time);
        if (x < -OBSTACLE_WIDTH_PIXELS) {
            int idx = (i + (obstacle_system->num_obstacles - 1)) % obstacle_system->num_obstacles;
            x = obstacle_system->obstacles[idx].position.x + OBSTACLE_TOTAL_PIXELS;
            obstacle->position.y = get_random_bounded_y_coord(obstacle_system->screen_height);
        }

        obstacle->position.x = x;
    }
}

void
draw_obstacles(ObstacleSystem *obstacle_system)
{
    for (int i = 0; i < obstacle_system->num_obstacles; ++i) {
        Obstacle *obstacle = &obstacle_system->obstacles[i];

        Vector2 start_pos_top = {obstacle->position.x, 0.0f};
        Vector2 end_pos_top = {obstacle->position.x, obstacle->position.y - (OBSTACLE_OPENING_PIXELS >> 1)};

        Vector2 start_pos_bot = {obstacle->position.x, obstacle->position.y + (OBSTACLE_OPENING_PIXELS >> 1)};
        Vector2 end_pos_bot = {obstacle->position.x, obstacle_system->screen_height};

        DrawLineEx(start_pos_top, end_pos_top, OBSTACLE_WIDTH_PIXELS, PURPLE);
        DrawLineEx(start_pos_bot, end_pos_bot, OBSTACLE_WIDTH_PIXELS, PURPLE);
    }
}
