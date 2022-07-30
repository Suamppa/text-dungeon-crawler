#ifndef PLAYER_H
#define PLAYER_H

#include "Room.h"
#include <cmath>

class Player: public GameCharacter
{
// private:
    // A helper function for printInventory and accessInventory
    // void findAndPrintEquipped(const int);
public:
    Room * previousRoom;
    int level, currentXp, maxXp;
    Player(string, int, int, int, int, int, int, int, deque<shared_ptr<Item>> &);
    void addItem(shared_ptr<Item> &);
    // void addItem(Weapon);
    // void addItem(Armour);
    // void increaseStats(int, int, int, int);

    bool checkIsDead();
    void gainXp(int);
    void levelUp(int);
    void lootRoom(Room *);
    void changeRooms(Room *);
    void printStats();
    void printInventory();
    void accessInventory();
    void handleUseItem(shared_ptr<Item> &);
    // void handleUseItem(Item *)
    // void handleUseItem(Weapon *);
    // void handleUseItem(Armour *);
    // void equipItem(shared_ptr<Item> &);
};

#endif
