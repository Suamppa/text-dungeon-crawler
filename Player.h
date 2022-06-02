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
    Player(string, int, int, int, int, int, int, int, deque<Item *> &);
    void addItem(Item *);
    // void addItem(Weapon);
    // void addItem(Armour);
    // void increaseStats(int, int, int, int);
    void gainXp(int);
    void levelUp(int);
    void lootRoom(Room *);
    void changeRooms(Room *);
    void printStats();
    void printInventory();
    void accessInventory();
    void handleUseItem(Item *);
    void handleUseItem(Weapon *);
    void handleUseItem(Armour *);
};

#endif
