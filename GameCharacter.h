#include "Item.h"
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
    vector<Item> inventory;
    Item * equipHead, * equipUpperBody, * equipHands, * equipRItem, * equipLItem, * equipLowerBody, * equipFeet;
    GameCharacter(string, int, int, int, int, int, vector<Item> = vector<Item>());
    int takeDamage(int);
    bool checkIsDead();
};

#endif
