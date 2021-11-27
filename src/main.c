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

void createMapTextures(Game *game) {
    char *paths[103] = {"../resources/textures/-3.png", "../resources/textures/-2.png", "../resources/textures/-1.png",
                       "../resources/textures/0.png", "../resources/textures/1.png", "../resources/textures/2.png",
                       "../resources/textures/3.png", "../resources/textures/4.png", "../resources/textures/5.png",
                       "../resources/textures/6.png", "../resources/textures/7.png", "../resources/textures/8.png",
                       "../resources/textures/9.png", "../resources/textures/10.png", "../resources/textures/11.png",
                       "../resources/textures/12.png", "../resources/textures/13.png", "../resources/textures/14.png",
                       "../resources/textures/15.png", "../resources/textures/16.png", "../resources/textures/17.png",
                       "../resources/textures/18.png", "../resources/textures/19.png", "../resources/textures/20.png",
                       "../resources/textures/21.png"};
    paths[102] = "../resources/textures/99.png";
    SDL_Surface *surfaces[103];
    for(int i = 0; i < 25; i += 1){
        surfaces[i] = IMG_Load(paths[i]);
        if (surfaces[i] == NULL)
            SDL_ExitAndDestroy("Can't load image", game->renderer, game->window);
    }
    surfaces[102] = IMG_Load(paths[102]);
    if (surfaces[102] == NULL)
        SDL_ExitAndDestroy("Can't load image", game->renderer, game->window);
    for (int i = 0; i < 25; i += 1) {
        game->mapTextures[i] = SDL_CreateTextureFromSurface(game->renderer, surfaces[i]);
        if (game->mapTextures[i] == NULL)
            SDL_ExitAndDestroy("Can't create texture", game->renderer, game->window);
    }
    game->mapTextures[102] = SDL_CreateTextureFromSurface(game->renderer, surfaces[102]);
    if (game->mapTextures[102] == NULL)
        SDL_ExitAndDestroy("Can't create texture", game->renderer, game->window);
    for(int i = 0; i < 24; i += 1){
        free(surfaces[i]);
    }
    free(surfaces[102]);
}


int main(int argc, char **argv) {
    initSDL();
    srand(time(NULL));

    int x = 10;
    int y = 10;
    int zone = 1;
    Game *game = initGame(x, y, zone); // Initialisation de départ du jeu
    displayMap(game->maps[0], game->maps[9][0][0], game->maps[9][0][1]);

    game->player->level = 10;
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
    return game;
}