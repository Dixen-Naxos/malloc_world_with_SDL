//
// Created by arman on 26/11/2021.
//

#include "sdl_functions.h"

#include "cli.h"

void renderElement(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect *rectangle, int x, int y, SDL_Window *window) {
    (*rectangle).x = y * 32;
    (*rectangle).y = x * 32;
    if (SDL_QueryTexture(texture, NULL, NULL, &(*rectangle).w, &(*rectangle).h))
        SDL_ExitAndDestroy("Can't display texture", renderer, window);
    SDL_RenderCopy(renderer, texture, NULL, rectangle);

}

void renderMap(Game* game, SDL_Rect* rectangle){
    for (int posX = 0; posX < (game->maps[9][game->player->mapId / 3][0]); posX += 1) {
        for (int posY = 0; posY < (game->maps[9][game->player->mapId / 3][1]); posY += 1) {
            renderElement(game->mapTextures[game->maps[game->player->mapId][posX][posY] + 3], game->renderer,
                          rectangle, posX, posY, game->window);
        }
    }
}

void SDL_ExitAndDestroy(const char *exitMessage, SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_ExitWithError(exitMessage);
}

void SDL_ExitWithError(const char *message) {
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

// create window
int createWindow(SDL_Window **window, int x, int y) {

    *window = SDL_CreateWindow("lifegame-editor4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x,
                               y, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        SDL_ExitWithError("Error create window");
        return 1;
    }

    return 0;
}

// create texture
SDL_Texture** createTexture(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Surface **surface) {

    *texture = SDL_CreateTextureFromSurface(*renderer, *surface);
    if (*texture == NULL) {
        SDL_ExitWithError("Error create texture");
    }

    return texture;
}

// load texture
int loadTexture(SDL_Texture **texture, SDL_Rect *rectangle) {

    // load texture
    if (SDL_QueryTexture(*texture, NULL, NULL, &(*rectangle).w, &(*rectangle).h) != 0) {
        SDL_ExitWithError("Error loading texture");
    }

    return 0;
}

// create renderer
int createRenderer(SDL_Renderer **renderer, SDL_Window **window) {

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
    if (*renderer == NULL) {
        SDL_ExitWithError("Error create renderer");
    }
    return 0;
}

//Create image
int createImg(SDL_Renderer **renderer, SDL_Window **window, SDL_Surface **image, SDL_Texture **texture, SDL_Rect *rect,
              char *path, int x, int y) {
    *image = IMG_Load(path);
    if (*image == NULL)
        SDL_ExitAndDestroy("Can't load image", *renderer, *window);

    *texture = SDL_CreateTextureFromSurface(*renderer, *image);
    if (*texture == NULL)
        SDL_ExitAndDestroy("Can't create texture", *renderer, *window);
    SDL_FreeSurface(*image);

    if (SDL_QueryTexture(*texture, NULL, NULL, &(*rect).w, &(*rect).h) != 0)
        SDL_ExitAndDestroy("Can't display texture", *renderer, *window);
    (*rect).x = x;
    (*rect).y = y;
}

// reload renderer
int updateRenderer(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Rect *rectangle) {

    // copy texture
    if (SDL_RenderCopy(*renderer, *texture, NULL, rectangle)) {
        SDL_ExitWithError("Error display texture");
    }

    // update renderer
    //SDL_RenderPresent(*renderer);

    return 0;
}

int loadFont(TTF_Font **font) {
    *font = TTF_OpenFont("../resources/font/OpenSans-Regular.ttf", 28);
    if (*font == NULL) {
        SDL_ExitWithError("Error load TTF font");
    }
    return 0;
}

// start SDL
int initSDL(void) {

    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        SDL_ExitWithError("Error init SDL");
    }

    if (TTF_Init() == -1) {
        SDL_ExitWithError("Error init TTF");
    }
    return 0;
}

void displayTTF(SDL_Renderer *renderer, TTF_Font *font, char *texte, int x, int y) {
    SDL_Color color = {0, 0, 0};
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, texte, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);
    SDL_Rect textRect = {x, y, texW, texH};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

SDL_bool SDLMoveChoice(Game* game, SDL_Scancode scancodeMove){
    switch (scancodeMove) {
        case SDL_SCANCODE_DOWN:
            checkCanMove(game, 3);
            decrementTimers(game);
            break;
        case SDL_SCANCODE_UP:
            checkCanMove(game, 1);
            decrementTimers(game);
            break;
        case SDL_SCANCODE_RIGHT:
            checkCanMove(game, 2);
            decrementTimers(game);
            break;
        case SDL_SCANCODE_LEFT:
            checkCanMove(game, 4);
            decrementTimers(game);
            break;
        case SDL_SCANCODE_ESCAPE:
            return SDL_FALSE;
        default:
            break;
    }
    return SDL_TRUE;
}

void SDLMove(Game* game){
    SDL_Surface *menuImg = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Rect menuRectangle;
    createImg(&game->renderer, &game->window, &menuImg, &menuTexture, &menuRectangle,
              "../resources/textures/fonds/battle.jpg", 0, 0);
    SDL_Rect *rectangle = malloc(sizeof(SDL_Rect));
    SDL_bool moveOn = SDL_TRUE;
    while (moveOn) {
        SDL_Event eventMove;
        while (SDL_PollEvent(&eventMove)) {
            switch (eventMove.type) {
                case SDL_KEYDOWN:
                    moveOn = SDLMoveChoice(game, eventMove.key.keysym.scancode);
                    SDL_Delay(500);
                default:
                    break;
            }
        }
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, menuTexture, NULL, &menuRectangle);
        renderMap(game, rectangle);
        displayTTF(game->renderer, game->font, "test", 600, 600);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(1000 / 60);
    }
}

SDL_bool SDLTurnChoice(Game* game, SDL_Scancode scancodeTurn){
    switch (scancodeTurn) {
        case SDL_SCANCODE_0:
            return SDL_FALSE;
        case SDL_SCANCODE_1:
            newGame(game);
            break;
        case SDL_SCANCODE_2:
            saveGame(game);
            break;

        default:
            break;
    }
    return SDL_TRUE;
}

void SDLTurn(Game* game){
    SDL_Surface *menuImg = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Rect menuRectangle;
    createImg(&game->renderer, &game->window, &menuImg, &menuTexture, &menuRectangle,
              "../resources/textures/fonds/TurnMenu.png", 0, 0);
    SDL_bool gameOn = SDL_TRUE;
    while (gameOn) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    gameOn = SDLTurnChoice(game, event.key.keysym.scancode);
                default:
                    break;
            }
        }
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, menuTexture, NULL, &menuRectangle);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(1000 / 60);
    }
}

SDL_bool SDLMainChoice(Game* game, SDL_Scancode scancode){
    switch (scancode) {
        case SDL_SCANCODE_0:
            return SDL_FALSE;
        case SDL_SCANCODE_1:
            SDLTurn(game);
            break;
        case SDL_SCANCODE_2:
            loadGame(game);
            SDLTurn(game);
            break;
        default:
            break;
    }
    return SDL_TRUE;
}

void SDLMainMenu(Game* game){
    SDL_Surface *menuImg = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Rect menuRectangle;
    createImg(&game->renderer, &game->window, &menuImg, &menuTexture, &menuRectangle,
              "../resources/textures/fonds/MainMenu.png", 0, 0);
    SDL_bool program_launched = SDL_TRUE;
    while (program_launched) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    program_launched = SDLMainChoice(game, event.key.keysym.scancode);
                default:
                    break;
            }
        }
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, menuTexture, NULL, &menuRectangle);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(1000 / 60);
    }
}