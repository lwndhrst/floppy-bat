#include <raylib.h>

#include "game.h"
#include "menu.h"

int
main(void)
{
    const int screen_width = 1600;
    const int screen_height = 900;

    InitWindow(screen_width, screen_height, "Floppy Bat");

    Scene scene = SCENE_MAIN_MENU;
    Game game;

    while (!WindowShouldClose())
    {
        switch (scene)
        {
        case SCENE_MAIN_MENU:
            scene = main_menu(screen_width, screen_height);
            break;
        case SCENE_GAME:
            init_game(&game, screen_width, screen_height);
            run_game(&game);
            destroy_game(&game);
            scene = game_over_menu(screen_width, screen_height, game.score);
            break;
        case SCENE_QUIT:
            goto cleanup;
        default:
            break;
        }
    }

cleanup:
    CloseWindow();

    return 0;
}
