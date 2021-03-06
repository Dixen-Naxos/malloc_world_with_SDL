//
// Created by Audrey Divito on 15/11/2021.
//

#ifndef MALLOC_WORLD_BATTLES_H
#define MALLOC_WORLD_BATTLES_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "player.h"
#include "monsters.h"
#include "move.h"

void updateXP(Player* player, Monster* monster);
void battle(Player* player, Monster* monster, int idWeapon, int armor);
int menu(Player* player, Monster* monster, Game* game, int posX, int posY);
void usingPotion(Player* player);
int roundChoices(Player* player, Monster* monster, int choice, int idWeapon, int maxArmor);
int weaponChoice(Player* player);
int armorChoice(Player* player);
int attackInBattle(Player* player, Monster* monster, int idWeapon, int maxArmor);
int escapeFromBattle(void);
void defeat(Game* game);
#endif //MALLOC_WORLD_BATTLES_H
