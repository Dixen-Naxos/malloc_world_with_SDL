//
// Created by arman on 26/11/2021.
//

#ifndef MALLOC_WORLD_WITH_SDL_SDL_FUNCTIONS_H
#define MALLOC_WORLD_WITH_SDL_SDL_FUNCTIONS_H

#include "../../ext/SDL2/include/SDL.h"
#include "../../ext/SDL2/include/SDL_ttf.h"
#include "../../ext/SDL2/include/SDL_image.h"
#include "cli.h"
#include "battles.h"

void renderElement(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect *rectangle, int x, int y, SDL_Window *window);

void renderMap(Game* game, SDL_Rect* rectangle);

int initSDL();

SDL_Surface** loadAllSurfaces(Game* game);

SDL_Rect** createAllRect(int nbRect);

SDL_Texture** loadAllTextures(Game* game, SDL_Renderer** renderer);

void SDL_ExitAndDestroy(const char *exitMessage, SDL_Renderer *renderer, SDL_Window *window);

void SDL_ExitWithError(const char *message);

int createWindow(SDL_Window **window, int x, int y);

int createRenderer(SDL_Renderer **renderer, SDL_Window **window);

int createImg(SDL_Renderer **renderer, SDL_Window **window, SDL_Surface **image, SDL_Texture **texture, SDL_Rect *rect,
              char *path, int x, int y);

int loadFont(TTF_Font **font);

SDL_Texture** createTexture(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Surface **surface);

int loadTexture(SDL_Texture **texture, SDL_Rect *rectangle);

int updateRenderer(SDL_Texture **texture, SDL_Renderer **renderer, SDL_Rect *rectangle);

void displayTTF(SDL_Renderer *renderer, TTF_Font *font, char *texte, int x, int y);

void createMapTextures(Game *game);

SDL_bool SDLPotionChoice(Game* game, SDL_Scancode scancodePotion, int* posPotion);

void SDLPotionMenu(Game* game);

void displayCarac(Game* game, Monster* monster, int weaponIndex);

SDL_bool SDLBattleChoice(Game* game, SDL_Scancode scancodeBattle, Monster* monster, int* weaponIndex, int armor, int posX, int posY);

void SDLBattleMenu(Game* game, int monsterId, int posX, int posY);

void displayAvailableWeapons(Game* game, int* posWeapon);

int verifyWeapon(Game* game, int* weaponChoice, int* posWeapon);

SDL_bool SDLWeaponChoice(Game* game, SDL_Scancode scancodeWeapon, int* weaponChoice, int* posWeapon);

int SDLWeaponMenu(Game* game);





void SDLMove(Game* game);

SDL_bool SDLMoveChoice(Game* game, SDL_Scancode scancode);





SDL_bool SDLMainChoice(Game* game, SDL_Scancode scancode);

void SDLMainMenu(Game* game);

#endif //MALLOC_WORLD_WITH_SDL_SDL_FUNCTIONS_H
