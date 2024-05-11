#include "obstacles.h"

#include <stdint.h>
#include <stdlib.h>

#define OBSTACLE_DISTANCE_PIXELS 250
#define OBSTACLE_OPENING_PIXELS 128

#define SCROLL_SPEED 100.0f
#define SCROLL_ACCEL 10.0f

void
randomize_opening_position(ObstacleSystem *obstacle_system, Obstacle *obstacle, int screen_height)
{
    int margin = OBSTACLE_OPENING_PIXELS;
    float y = GetRandomValue(0 + margin, screen_height - margin);

    obstacle->top_y = y - (float)(OBSTACLE_OPENING_PIXELS >> 1) - obstacle_system->sprite_height;
    obstacle->top_height = y - (float)(OBSTACLE_OPENING_PIXELS >> 1);
    obstacle->bot_y = y + (float)(OBSTACLE_OPENING_PIXELS >> 1);
    obstacle->bot_height = (float)screen_height - obstacle->bot_y;
}

void
init_obstacle_system(ObstacleSystem *obstacle_system, int screen_width, int screen_height)
{
    obstacle_system->spritesheet = LoadTexture(TextFormat("%s/spritesheets/obstacle.png", ASSETS_PATH));
    obstacle_system->sprite_width = 16 << 2;
    obstacle_system->sprite_height = 64 << 2;

    int num_obstacles = 2 + (screen_width / (OBSTACLE_DISTANCE_PIXELS + obstacle_system->sprite_width));

    Obstacle *obstacles = malloc(num_obstacles * sizeof(Obstacle));

    for (int i = 0; i < num_obstacles; ++i)
    {
        Obstacle obstacle;
        obstacle.x = screen_width + OBSTACLE_DISTANCE_PIXELS + i * (OBSTACLE_DISTANCE_PIXELS + obstacle_system->sprite_width);
        obstacle.prev_x = obstacle.x;

        randomize_opening_position(obstacle_system, &obstacle, screen_height);
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

        obstacle->prev_x = obstacle->x;
        obstacle->x -= obstacle_system->scroll_speed * delta_time;
        if (obstacle->x < -obstacle_system->sprite_width)
        {
            int rightmost_idx = (i + obstacle_system->num_obstacles - 1) % obstacle_system->num_obstacles;
            obstacle->x = obstacle_system->obstacles[rightmost_idx].x + OBSTACLE_DISTANCE_PIXELS + obstacle_system->sprite_width;
            randomize_opening_position(obstacle_system, obstacle, obstacle_system->screen_height);
        }
    }
}

void
draw_obstacles(ObstacleSystem *obstacle_system)
{
    const size_t frame_width = 16;
    const size_t frame_height = 64;

    Rectangle sprite_bot = {0, 0, frame_width, frame_height};
    Rectangle sprite_top = {frame_width, 0, frame_width, frame_height};

    for (int i = 0; i < obstacle_system->num_obstacles; ++i)
    {
        Obstacle *obstacle = &obstacle_system->obstacles[i];

        Rectangle target_top = {obstacle->x, obstacle->top_y, obstacle_system->sprite_width, obstacle_system->sprite_height};
        Rectangle target_bot = {obstacle->x, obstacle->bot_y, obstacle_system->sprite_width, obstacle_system->sprite_height};

        DrawTexturePro(obstacle_system->spritesheet,
                       sprite_top,
                       target_top,
                       (Vector2){0, 0},
                       0.0f,
                       WHITE);

        DrawTexturePro(obstacle_system->spritesheet,
                       sprite_bot,
                       target_bot,
                       (Vector2){0, 0},
                       0.0f,
                       WHITE);

        // DrawRectangle(obstacle->x,
        //               obstacle->top_y,
        //               OBSTACLE_WIDTH_PIXELS,
        //               obstacle->top_height,
        //               PURPLE);

        // DrawRectangle(obstacle->x,
        //               obstacle->bot_y,
        //               OBSTACLE_WIDTH_PIXELS,
        //               obstacle->bot_height,
        //               PURPLE);
    }
}

bool
check_collisions(ObstacleSystem *obstacle_system, Player *player)
{
    for (int i = 0; i < obstacle_system->num_obstacles; ++i)
    {
        Obstacle *obstacle = &obstacle_system->obstacles[i];

        float dx = player->position.x - obstacle->x;
        if (dx + player->sprite_width > 0.0f &&
            dx < obstacle_system->sprite_width)
        {
            float dy = player->position.y - obstacle->top_height;
            if (dy + player->hitbox_offset_top < 0.0f ||
                dy + player->sprite_height > OBSTACLE_OPENING_PIXELS + player->hitbox_offset_bot)
            {
                return true;
            }
        }
    }

    return false;
}

int
calc_score(ObstacleSystem *obstacle_system, Player *player)
{
    for (int i = 0; i < obstacle_system->num_obstacles; ++i)
    {
        Obstacle *obstacle = &obstacle_system->obstacles[i];

        if (player->position.x <= obstacle->prev_x + (float)(obstacle_system->sprite_width >> 1) &&
            player->position.x >= obstacle->x + (float)(obstacle_system->sprite_width >> 1))
        {
            return 1;
        }
    }

    return 0;
}
