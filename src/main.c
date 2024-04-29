#include <raylib.h>

#include "player.h"

int
main(void)
{
    const int screen_width = 600;
    const int screen_height = 400;

    InitWindow(screen_width, screen_height, "Floppy Bat");
    SetTargetFPS(60);

    Player player;
    init_player(&player, screen_width, screen_height);

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
