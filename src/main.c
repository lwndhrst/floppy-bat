#include <raylib.h>

#include "obstacles.h"
#include "player.h"

int
main(void)
{
    // ***********************************************
    // init
    // ***********************************************

    const int screen_width = 600;
    const int screen_height = 400;

    InitWindow(screen_width, screen_height, "Floppy Bat");

    Player player;
    init_player(&player, screen_width, screen_height);

    ObstacleSystem obstacles_system;
    init_obstacle_system(&obstacles_system, screen_width, screen_height);

    while (!WindowShouldClose()) {

        // ***********************************************
        // update
        // ***********************************************

        float delta_time = GetFrameTime();
        update_player(&player, delta_time);
        update_obstacles(&obstacles_system, delta_time);

        // ***********************************************
        // draw
        // ***********************************************

        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_obstacles(&obstacles_system);
        draw_player(&player);

        EndDrawing();
    }

    // ***********************************************
    // cleanup
    // ***********************************************

    destroy_obstacle_system(&obstacles_system);

    CloseWindow();
    return 0;
}
