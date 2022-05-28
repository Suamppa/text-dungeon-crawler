#include "Armour.h"
#include "Weapon.h"
#include <deque>
#include <iostream>
#include <random>

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

using namespace std;

class GameCharacter
{
public:
    string name;
    int maxHealth, currentHealth, minAttack, maxAttack, defence, xpYield;
    deque<Item *> inventory;
    Armour * equipHead, * equipUpperBody, * equipHands, * equipLowerBody, * equipFeet;
    Weapon * equipRItem, * equipLItem;
    GameCharacter(string, int, int, int, int, int, deque<Item *> = deque<Item *>());
    int takeDamage(int);
    bool checkIsDead();
    void equipArmour(Armour *, char);
    Armour * unequipArmour(Armour *);
    void equipWeapon(Weapon *, bool=true);
    Weapon * unequipWeapon(Weapon *);
    void updateStats(int, int, int, int);
};

#endif
