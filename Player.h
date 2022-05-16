#include "Room.h"
#include <cmath>

#ifndef PLAYER_H
#define PLAYER_H

class Player: public GameCharacter
{
public:
    Room * currentRoom;
    Room * previousRoom;
    int level, currentXp, maxXp;
    vector<Item> inventory;
    Player(string="", int=0, int=0, int=0, int=0, int=0, int=0, int=0);
    void addItem(Item);
    void increaseStats(int, int, int, int);
    void gainXp(int);
    void levelUp(int);
    void lootRoom(Room *);
    void changeRooms(Room *);
    void printStats();
    void printInventory();
};

#endif
