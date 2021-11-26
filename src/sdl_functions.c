//
// Created by arman on 26/11/2021.
//

#include "sdl_functions.h"


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
int createTexture(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Surface **surface) {

    *texture = SDL_CreateTextureFromSurface(*renderer, *surface);
    if (*texture == NULL) {
        SDL_ExitWithError("Error create texture");
    }

    return 0;
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
    *font = TTF_OpenFont("src/font/OpenSans-Regular.ttf", 28);
    if (*font == NULL) {
        SDL_ExitWithError("Error load TTF font");
    }
    return 0;
}

// start SDL
int initSDL() {

    // init SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        SDL_ExitWithError("Error init SDL");
    }

    if (TTF_Init() == -1) {
        SDL_ExitWithError("Error init TTF");
    }
    return 0;
}