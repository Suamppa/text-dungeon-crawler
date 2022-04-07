#include "Player.h"
#include "RNG.h"
#include <iostream>
#include <vector>

#ifndef DUNGEON_H
#define DUNGEON_H

using namespace std;

class Dungeon
{
public:
    Player player;
    Room rooms[4];
    vector<vector<bool>> dungeon;
    Dungeon(Player);
    void generateDungeon(int, int); // to be implemented as procedural generator
    int runDungeon();
    void enterRoom(Room *);
    char handleInput(int, string[], vector<char>, bool=true, bool=true);
    void handleEmptyRoom(Room *);
    void handleRoomWithChest(Room *);
    void handleRoomWithEnemy(Room *);
    void handleLootActions(Room *);
    void handleFightActions(GameCharacter *);
    void handleMovementActions(Room *);
    // void printActions(int, string[], bool=true, bool=true);
    int performEndGameLogic();
};

#endif
