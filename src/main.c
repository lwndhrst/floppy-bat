#include "raylib.h"

int
main(void)
{
    const int screenWidth = 600;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Hello World!");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 230, 190, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
