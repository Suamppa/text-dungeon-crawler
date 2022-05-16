#include "Item.h"
#include "GameCharacter.h"
#include "RNG.h"

#ifndef ROOM_H
#define ROOM_H

class Room
{
// private:
    // bool forceDoor; // forceDoor forces the generated room to have a new door
public:
    int pos;    // will be deprecated

    int y, x;
    bool isExit;
    // vector<int> walls;  // walls = {N, E, S, W}: 0 = wall, 1 = door, 2 = entry
    // Wall north, east, south, west;
    // Wall walls[4];
    // int north, east, south, west;
    // Items and enemies are vectors for future implementations
    vector<Item> items;
    vector<GameCharacter> enemies;
    // int doors[4];
    Room(int=-1, int=-1, bool=false, vector<Item> = vector<Item>(), vector<GameCharacter> = vector<GameCharacter>());
    Room(int, bool=false, vector<Item> = vector<Item>(), vector<GameCharacter> = vector<GameCharacter>());
    // Room(int, int, int[], bool, bool, vector<Item> = vector<Item>(), vector<GameCharacter> = vector<GameCharacter>());
    void clearLoot();
    void clearEnemies();
};

struct Door
{
    Room * leadsTo;
    Door(Room *);
};

#endif
