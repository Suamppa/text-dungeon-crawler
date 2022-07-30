#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "Armour.h"
#include "Item.h"
#include "Weapon.h"
#include <deque>
#include <iostream>
#include <memory>
#include <random>

using namespace std;

class Room;

class GameCharacter
{
public:
    struct Equipment {
        shared_ptr<Item> pItem;
        
        void equipItem(shared_ptr<Item> &);
        void unequipItem();
    } equippedRItem, equippedLItem, equippedHead, equippedUpperBody, equippedHands, equippedLowerBody, equippedFeet;
    
    Room * currentRoom;
    string name;
    int baseMaxHealth, currentHealth, baseMinAttack, baseMaxAttack, baseDefence, xpYield, inventorySize;
    deque<shared_ptr<Item>> inventory;
    // shared_ptr<Item> equippedRItem, equippedLItem, equippedHead,
    // equippedUpperBody, equippedHands, equippedLowerBody, equippedFeet;
    // Equipment equippedRItem, equippedLItem, equippedHead,
    // equippedUpperBody, equippedHands, equippedLowerBody, equippedFeet;
    // First holds the pointer to the equipped item itself, second stores the inventory index of that item
    // pair<unique_ptr<Item>, int> equippedRItem, equippedLItem, equippedHead,
    // equippedUpperBody, equippedHands, equippedLowerBody, equippedFeet;
    // unique_ptr<Item> & equippedRItem, & equippedLItem, & equippedHead,
    // & equippedUpperBody, & equippedHands, & equippedLowerBody, & equippedFeet;
    // vector<Armour *> equippedArmour;
    // vector<Weapon *> equippedWeapons;
    
    GameCharacter(string, int, int, int, int, int, deque<shared_ptr<Item>> &);
    int takeDamage(int);
    bool checkIsDead();
    void equipItem(shared_ptr<Item> &);
    // void swapEquipment(shared_ptr<Item> &, shared_ptr<Item> &);

    void unequipItem(Equipment);
    void unequipAll();
    void dropItem();
    // void dropItem(int);
    // void dropItem(deque<shared_ptr<Item>>::iterator);
    // void equipArmour(unique_ptr<Armour>, char);
    // void unequipArmour(Armour *);

    // void equipWeapon(unique_ptr<Weapon>, bool=true);
    // void unequipWeapon(Weapon *);

    // void unequipItem(char);

    void updateBaseStats(int, int, int, int);
    int getMaxHealth();
    int getDefence();
    int getMinAttack();
    int getMaxAttack();
    // ~GameCharacter();
};

#endif
