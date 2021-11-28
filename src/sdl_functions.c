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

    *window = SDL_CreateWindow("Malloc World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x,
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

SDL_bool SDLPnjChoice(Game* game, SDL_Scancode scancodePnj){
    switch (scancodePnj) {
        case SDL_SCANCODE_0:
            return SDL_FALSE;
        case SDL_SCANCODE_1:
            repairStuff(game);
            break;
        case SDL_SCANCODE_2:
            break;
        case SDL_SCANCODE_3:
            break;
        default:
            break;
    }
    return SDL_TRUE;
}

void SDLPnjMenu(Game* game){
    SDL_Surface *menuImg = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Rect menuRectangle;
    createImg(&game->renderer, &game->window, &menuImg, &menuTexture, &menuRectangle,
              "../resources/textures/fonds/PNJMenu.png", 0, 0);

    SDL_Surface *PNJImg = NULL;
    SDL_Texture *PNJTexture = NULL;
    SDL_Rect PNJRectangle;
    createImg(&game->renderer, &game->window, &PNJImg, &PNJTexture, &PNJRectangle,
              "../resources/textures/fonds/briatte.png", 640, 50);
    SDL_bool gameOn = SDL_TRUE;
    while (gameOn) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    gameOn = SDLPnjChoice(game, event.key.keysym.scancode);
                default:
                    break;
            }
        }
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, menuTexture, NULL, &menuRectangle);
        SDL_RenderCopy(game->renderer, PNJTexture, NULL, &PNJRectangle);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(1000 / 60);
    }
}

SDL_bool SDLPotionChoice(Game* game, SDL_Scancode scancodePotion, int* posPotion){
    switch (scancodePotion) {
        case SDL_SCANCODE_1:
            if(posPotion[0] != -1 && game->player->inventory->inventoryContent[posPotion[0]]->quantity > 0 && strcmp(game->player->inventory->inventoryContent[posPotion[0]]->type, "Soin") == 0) {
                game->player->currentHp += 30;
                game->player->inventory->inventoryContent[posPotion[0]]->quantity -= 1;
            }
            break;
        case SDL_SCANCODE_2:
            if(posPotion[1] != -1 && game->player->inventory->inventoryContent[posPotion[1]]->quantity > 0 && strcmp(game->player->inventory->inventoryContent[posPotion[1]]->type, "Soin") == 0) {
                game->player->currentHp += 80;
                game->player->inventory->inventoryContent[posPotion[1]]->quantity -= 1;
            }
            break;
        case SDL_SCANCODE_3:
            if(posPotion[2] != -1 && game->player->inventory->inventoryContent[posPotion[2]]->quantity > 0 && strcmp(game->player->inventory->inventoryContent[posPotion[2]]->type, "Soin") == 0) {
                game->player->currentHp += 200;
                game->player->inventory->inventoryContent[posPotion[2]]->quantity -= 1;
            }
            break;
        default:
            break;
    }
    if(game->player->currentHp > game->player->hpEvolution[game->player->level]) {
        game->player->currentHp = game->player->hpEvolution[game->player->level];
    }
    return SDL_FALSE;
}

void displayPotionMenu(Game* game, int* posPotion){
    if(game->player->currentHp < game->player->hpEvolution[game->player->level]) {
        for(int i = 0; i < INVENTORY_SIZE; i++) {
            if(game->player->inventory->inventoryContent[i]->value == 15) {
                posPotion[0] = i;
            } else if(game->player->inventory->inventoryContent[i]->value == 26) {
                posPotion[1] = i;
            } else if(game->player->inventory->inventoryContent[i]->value == 34) {
                posPotion[2] = i;
            }
        }
        SDL_Surface *menuImg = NULL;
        SDL_Texture *menuTexture = NULL;
        SDL_Rect menuRectangle;
        createImg(&game->renderer, &game->window, &menuImg, &menuTexture, &menuRectangle,
                  "../resources/textures/fonds/battle.jpg", 0, 0);
        char text[256];
        if(posPotion[0] != -1 || posPotion[1] != -1 || posPotion[2] != -1) {

            if (posPotion[0] != -1) {
                sprintf(text, "Vous avez %d potions de niveau I. Appuyez sur 1 pour les utiliser.\n",
                        game->player->inventory->inventoryContent[posPotion[0]]->quantity);
                displayTTF(game->renderer, game->font, text, 50, 50);
            }

            if (posPotion[1] != -1) {
                sprintf(text, "Vous avez %d potions de niveau II. Appuyez sur 2 pour les utiliser.\n",
                        game->player->inventory->inventoryContent[posPotion[1]]->quantity);
                displayTTF(game->renderer, game->font, text, 50, 100);
            }

            if (posPotion[2] != -1) {
                sprintf(text, "Vous avez %d potions de niveau III. Appuyez sur 3 pour les utiliser.\n",
                        game->player->inventory->inventoryContent[posPotion[2]]->quantity);
                displayTTF(game->renderer, game->font, text, 50, 150);
            }
        }
        }
}

void SDLPotionMenu(Game* game){
    int* posPotion = malloc(sizeof(int) * 3);
    posPotion[0] = -1;
    posPotion[1] = -1;
    posPotion[2] = -1;

    SDL_Surface *menuImg = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Rect menuRectangle;
    createImg(&game->renderer, &game->window, &menuImg, &menuTexture, &menuRectangle,
              "../resources/textures/fonds/battle.jpg", 0, 0);
    SDL_bool potionOn = SDL_TRUE;

    while (potionOn) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    potionOn = SDLPotionChoice(game, event.key.keysym.scancode, posPotion);
                default:
                    break;
            }
        }
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, menuTexture, NULL, &menuRectangle);
        displayPotionMenu(game, posPotion);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(1000 / 60);
    }
}

void displayCarac(Game* game, Monster* monster, int weaponIndex){
    char text[256];
    if(weaponIndex != -1){
        sprintf(text, "Nom : %s     HP : %d", monster->name, monster->hp);
        displayTTF(game->renderer, game->font, text, 450, 30);
        sprintf(text, "Player :  HP : %d   durability : %d", game->player->currentHp, game->player->inventory->inventoryContent[weaponIndex]->durability);
        displayTTF(game->renderer, game->font, text, 100, 600);
    }
}

SDL_bool SDLBattleChoice(Game* game, SDL_Scancode scancodeBattle, Monster* monster, int* weaponIndex, int armor, int posX, int posY){
    int res;
    switch (scancodeBattle) {
        case SDL_SCANCODE_0:
            return SDL_FALSE;
        case SDL_SCANCODE_1:
            res = attackInBattle(game->player, monster, *weaponIndex, armor);
            if(game->player->inventory->inventoryContent[*weaponIndex]->durability == 0){
                printf("index 1 : %d", * weaponIndex);
                *weaponIndex = SDLWeaponMenu(game);
                printf("index 2 : %d", * weaponIndex);
                if(*weaponIndex == -1){
                    return SDL_FALSE;
                }
            }
            if(res == 1){
                updateXP(game->player, monster);
                movePlayerAddTimer(game, posX, posY, 15);
                return SDL_FALSE;
            }else if(res == 2) {
                defeat(game);
            }
            break;
        case SDL_SCANCODE_2:
            SDLPotionMenu(game);
            break;
        case SDL_SCANCODE_3:
            res = escapeFromBattle();
            if(res == 1){
                return SDL_FALSE;
            }
        default:
            break;
    }
    return SDL_TRUE;
}

void SDLBattleMenu(Game* game, int monsterId, int posX, int posY){
    int armor = armorChoice(game->player);
    int* weaponIndex = malloc(sizeof(int));
    *weaponIndex = SDLWeaponMenu(game);
    SDL_Surface *menuImg = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Rect menuRectangle;
    createImg(&game->renderer, &game->window, &menuImg, &menuTexture, &menuRectangle,
              "../resources/textures/fonds/battleMenu.png", 0, 0);
    Monster* copyMonster = malloc(sizeof(Monster));
    *copyMonster = (Monster) {game->monsterList[monsterId]->id, game->monsterList[monsterId]->name, game->monsterList[monsterId]->hp, game->monsterList[monsterId]->att, game->monsterList[monsterId]->def, game->monsterList[monsterId]->xp, game->monsterList[monsterId]->imagePath};

    SDL_Surface *monsterImg = NULL;
    SDL_Texture *monsterTexture = NULL;
    SDL_Rect monsterRectangle;
    createImg(&game->renderer, &game->window, &monsterImg, &monsterTexture, &monsterRectangle,
              copyMonster->imagePath, 300, 100);

    SDL_bool monsterOn = SDL_TRUE;
    while (monsterOn) {
        SDL_Event eventWeapon;
        while (SDL_PollEvent(&eventWeapon)) {
            switch (eventWeapon.type) {
                case SDL_KEYDOWN:
                    if(*weaponIndex != -1){
                        monsterOn = SDLBattleChoice(game, eventWeapon.key.keysym.scancode, copyMonster, weaponIndex, armor, posX, posY);
                    }else{
                        monsterOn = SDL_FALSE;
                    }
                default:
                    break;
            }
        }
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, menuTexture, NULL, &menuRectangle);
        SDL_RenderCopy(game->renderer, monsterTexture, NULL, &monsterRectangle);
        displayCarac(game, copyMonster, *weaponIndex);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(1000 / 60);
    }
    free(copyMonster);
}

void displayAvailableWeapons(Game* game, int* posWeapon){
    int cpt = 0;
    char* weaponText = malloc(sizeof(char) * 256);
    for(int i = 0; i < INVENTORY_SIZE; i++) {
        if(strcmp(game->player->inventory->inventoryContent[i]->type, "Arme") == 0 && game->player->inventory->inventoryContent[i]->durability > 0) {
            posWeapon[cpt] = i;
            sprintf(weaponText, "Tapez %d pour prendre cette arme : %s %d %d", cpt, game->player->inventory->inventoryContent[i]->name, game->player->inventory->inventoryContent[i]->durability, game->player->inventory->inventoryContent[i]->damage);
            displayTTF(game->renderer, game->font, weaponText, 480, 30  + 32 * cpt);
            cpt += 1;
        }
    }
    free(weaponText);
}

int verifyWeapon(Game* game, int* choice, int* posWeapon){
    if(*posWeapon != -1){
        if(game->player->inventory->inventoryContent[posWeapon[*choice]]->damage > 0 && game->player->inventory->inventoryContent[posWeapon[*choice]]->durability > 0){
            return 1;
        }
    }
    return 0;
}

SDL_bool SDLWeaponChoice(Game* game, SDL_Scancode scancodeWeapon, int* choice, int* posWeapon){
    if (scancodeWeapon >= 48 && scancodeWeapon <= 57){
        *choice = scancodeWeapon - 48;
        if(verifyWeapon(game, choice, posWeapon) == 1)
            return SDL_FALSE;
    }
    return SDL_TRUE;
}

int SDLWeaponMenu(Game* game) {
    int* choice = malloc(sizeof(int));
    *choice = -1;
    int* posWeapon = malloc(sizeof(unsigned int*) * 10);
    for(int i = 0; i<10; i += 1){
        posWeapon[i] = -1;
    }
    SDL_Surface *menuImg = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Rect menuRectangle;
    createImg(&game->renderer, &game->window, &menuImg, &menuTexture, &menuRectangle,
              "../resources/textures/fonds/battle.jpg", 0, 0);
    SDL_bool weaponOn = SDL_TRUE;
    while (weaponOn) {
        if(checkInInventoryWeapon(game) == 0){
            weaponOn = SDL_FALSE;
            break;
        }
        SDL_Event eventWeapon;
        while (SDL_PollEvent(&eventWeapon)) {
            switch (eventWeapon.type) {
                case SDL_KEYDOWN:
                    weaponOn = SDLWeaponChoice(game, eventWeapon.key.keysym.sym, choice, posWeapon);
                default:
                    break;
            }
        }
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, menuTexture, NULL, &menuRectangle);
        displayAvailableWeapons(game, posWeapon);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(1000 / 30);
    }
    return *choice;
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
                default:
                    break;
            }
        }
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, menuTexture, NULL, &menuRectangle);
        renderMap(game, rectangle);
        displayTTF(game->renderer, game->font, game->text, 600, 600);
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