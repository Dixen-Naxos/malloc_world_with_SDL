#include "player.h"

Player * initPlayer(Item** itemList){
    int temp[11] = {0, 100, 110, 130, 160, 200, 250, 300, 350, 425, 500};
    int temp2[11] = {0, 10, 15, 25, 30, 40, 50, 52, 58, 64, 70};
    Player * mainPlayer = malloc(sizeof(Player));
    mainPlayer->currentHp = 100;
    mainPlayer->level = 1;
    mainPlayer->currentXp=0;
    mainPlayer->posX = 4;
    mainPlayer->posY = 4;
    mainPlayer->inventory = initPlayerInventory(itemList);
    mainPlayer->mapId = 0;
    mainPlayer->hpEvolution = malloc(sizeof(int) * 11);
    mainPlayer->xpEvolution = malloc(sizeof(int) * 11);
    for(int i = 0; i < 11; i += 1){
        mainPlayer->hpEvolution[i] = temp[i];
        mainPlayer->xpEvolution[i] = temp2[i];
    }
    return mainPlayer;
}

Inventory* getInventory(Player* player){
    return player->inventory;
}