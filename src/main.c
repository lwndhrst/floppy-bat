#include <raylib.h>

#include "player.h"

int
main(void)
{
    const int screen_width = 600;
    const int screen_height = 400;

    InitWindow(screen_width, screen_height, "Floppy Bat");
    SetTargetFPS(60);

    Vector2 position = {(float)screen_width / PI, (float)screen_height / 2};
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 acceleration = {0.0f, 50.0f * GRAVITY};

    Player player = {position, velocity, acceleration};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        update_player(&player);
        draw_player(&player);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
