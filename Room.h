#include "Item.h"
#include "GameCharacter.h"
// #include <random>
#include <vector>

#ifndef ROOM_H
#define ROOM_H

class Room
{
public:
    int pos;
    bool isExit;
    vector<Item> items;
    vector<GameCharacter> enemies;
    Room(int = 0, bool = false, vector<Item> = vector<Item>(), vector<GameCharacter> = vector<GameCharacter>());
    void clearLoot();
    void clearEnemies();
};

#endif
