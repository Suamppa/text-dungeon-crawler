#include "Armour.h"
#include "GameCharacter.h"
#include "RNG.h"
#include "Weapon.h"

#ifndef ROOM_H
#define ROOM_H

class Room
{
public:
    int y, x;
    bool isExit, visited;
    // Items and enemies are vectors for future implementations
    vector<Item *> items;
    vector<GameCharacter> enemies;
    Room();
    Room(int, int, bool, vector<Item *> &, vector<GameCharacter> = vector<GameCharacter>());
    // Room(int, bool=false, vector<Item> = vector<Item>(), vector<GameCharacter> = vector<GameCharacter>());
    void clearLoot();
    void clearEnemies();
    ~Room();
};

#endif
