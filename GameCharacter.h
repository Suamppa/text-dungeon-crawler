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
    int baseMaxHealth, currentHealth, baseMinAttack, baseMaxAttack, baseDefence, xpYield;
    deque<Item *> inventory;
    Armour * equippedHead, * equippedUpperBody, * equippedHands, * equippedLowerBody, * equippedFeet;
    Weapon * equippedRItem, * equippedLItem;
    // vector<Armour *> equippedArmour;
    // vector<Weapon *> equippedWeapons;
    
    GameCharacter(string, int, int, int, int, int, deque<Item *> &);
    int takeDamage(int);
    bool checkIsDead();
    void equipArmour(Armour *, char);
    // void unequipArmour(Armour *);

    void equipWeapon(Weapon *, bool=true);
    // void unequipWeapon(Weapon *);

    void unequipItem(char);
    void updateBaseStats(int, int, int, int);
    int getMaxHealth();
    int getDefence();
    int getMinAttack();
    int getMaxAttack();
    ~GameCharacter();
};

#endif
