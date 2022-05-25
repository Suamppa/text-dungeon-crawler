#include "Item.h"

#ifndef WEAPON_H
#define WEAPON_H

class Weapon: public Item
{
public:
    int minAttack, maxAttack, defence;
    Weapon(string, int, int, int);
};

#endif
