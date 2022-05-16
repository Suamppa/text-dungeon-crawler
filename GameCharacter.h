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
    GameCharacter(string, int, int, int, int, int);
    int takeDamage(int);
    bool checkIsDead();
};

#endif
