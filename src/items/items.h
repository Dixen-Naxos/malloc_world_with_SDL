/**
 * FILENAME: items.h
 * Made by: GROUPE 5 - AL2
 * Projet: Malloc-World
 * Date de création: 15/10/2021
 * Dernière modification : 15/10/2021
 * Par: DAILLY Armand
 */

#ifndef MALLOC_WORLD_ITEMS_H
#define MALLOC_WORLD_ITEMS_H

#include "../include/structures.h"

Item** createItemList();
Item* getOneItem(Item**, int);
Item* setNewItemFromList(Item** itemList, int id);

#endif //MALLOC_WORLD_ITEMS_H
