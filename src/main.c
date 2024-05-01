#include <raylib.h>

#include "obstacles.h"
#include "player.h"

typedef enum {
    Menu,
    Game,
    GameOver,
} Scene;

int
main(void)
{
    // ***********************************************
    // Init
    // ***********************************************

    const int screen_width = 600;
    const int screen_height = 400;

    InitWindow(screen_width, screen_height, "Floppy Bat");

    // TODO: Start into menu scene
    Scene scene = Game;

    Player player;
    init_player(&player, screen_width, screen_height);

    ObstacleSystem obstacles_system;
    init_obstacle_system(&obstacles_system, screen_width, screen_height);

    while (!WindowShouldClose())
    {

        // ***********************************************
        // Update
        // ***********************************************

        float delta_time = GetFrameTime();

        update_player(&player, delta_time);
        update_obstacles(&obstacles_system, delta_time);

        if (check_collisions(&obstacles_system, &player) ||
            check_out_of_bounds(&player, screen_width, screen_height))
        {
            scene = GameOver;
        }

        // ***********************************************
        // Draw
        // ***********************************************

        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_obstacles(&obstacles_system);
        draw_player(&player);

        if (scene == GameOver)
        {
            const char *text = "BONK!";
            const int font_size = 128;
            int text_width = MeasureText(text, font_size);

            DrawText(text,
                     (screen_width - text_width) >> 1,
                     (screen_height - font_size) >> 1,
                     font_size,
                     BLACK);
        }

        EndDrawing();
    }

    // ***********************************************
    // Cleanup
    // ***********************************************

    destroy_obstacle_system(&obstacles_system);

    CloseWindow();
    return 0;
}
