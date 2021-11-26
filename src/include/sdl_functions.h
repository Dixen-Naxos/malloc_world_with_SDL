//
// Created by arman on 26/11/2021.
//

#ifndef MALLOC_WORLD_WITH_SDL_SDL_FUNCTIONS_H
#define MALLOC_WORLD_WITH_SDL_SDL_FUNCTIONS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

int initSDL();

void SDL_ExitAndDestroy(const char *exitMessage, SDL_Renderer *renderer, SDL_Window *window);

void SDL_ExitWithError(const char *message);

int createWindow(SDL_Window **window, int x, int y);

int createRenderer(SDL_Renderer **renderer, SDL_Window **window);

int createImg(SDL_Renderer **renderer, SDL_Window **window, SDL_Surface **image, SDL_Texture **texture, SDL_Rect *rect,
              char *path, int x, int y);

int loadFont(TTF_Font **font);

int createTexture(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Surface **surface);

int loadTexture(SDL_Texture **texture, SDL_Rect *rectangle);

int updateRenderer(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Rect *rectangle);

#endif //MALLOC_WORLD_WITH_SDL_SDL_FUNCTIONS_H
