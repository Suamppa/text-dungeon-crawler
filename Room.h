#include "Item.h"
#include "GameCharacter.h"
#include "RNG.h"

#ifndef ROOM_H
#define ROOM_H

class Room
{
public:
    int y, x;
    bool isExit, visited;
    // Items and enemies are vectors for future implementations
    vector<Item> items;
    vector<GameCharacter> enemies;
    Room(int=-1, int=-1, bool=false, vector<Item> = vector<Item>(), vector<GameCharacter> = vector<GameCharacter>());
    Room(int, bool=false, vector<Item> = vector<Item>(), vector<GameCharacter> = vector<GameCharacter>());
    void clearLoot();
    void clearEnemies();
};

#endif
