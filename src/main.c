/**
 * FILENAME: main.c
 * Made by: GROUPE 5 - AL2
 * Projet: Malloc-World
 * Date de création: 09/10/2021
 * Dernière modification : 22/10/2021
 * Par: DAILLY Armand
 */

#include <time.h>
#include "cli.h"
#include <sdl_functions.h>

//gcc src/*.c -o cmake-build-debug/malloc_world_with_SDL -I src/include -L ext/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
//.\cmake-build-debug\malloc_world_with_SDL.exe
Game *initGame(int, int, int);

int main(int argc, char **argv) {
    initSDL();
    srand(time(NULL));

    int x = 10;
    int y = 10;
    int zone = 1;
    Game *game = initGame(x, y, zone); // Initialisation de départ du jeu
    displayMap(game->maps[0], game->maps[9][0][0], game->maps[9][0][1]);
    addToInventory(game, 15, 60);
    SDLMainMenu(game);

    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);

    SDL_Quit();

    //start(game);
    freeGame(game);
    return 0;
}

Game *initGame(int x, int y, int zone) {
    Game *game = malloc(sizeof(Game));
    game->maps = initAllMaps(x, y);
    game->maps[0][4][4] = 1;
    fillAllMaps(game->maps, zone);
    game->itemList = createItemList();
    game->monsterList = createMonsterList();
    game->player = initPlayer(game->itemList);
    game->craft = initCraft();
    game->storage = initStorage();
    game->window = NULL;
    game->renderer = NULL;
    createWindow(&game->window, 1280, 720);
    createRenderer(&game->renderer, &game->window);
    createMapTextures(game);
    game->font = NULL;
    loadFont(&game->font);
    game->text = malloc(sizeof(char) * 256);
    return game;
}