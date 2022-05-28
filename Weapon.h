#include "Item.h"

#ifndef WEAPON_H
#define WEAPON_H

class Weapon: public Item
{
private:
    char equipType;
    bool equipped;
public:
    int minAttack, maxAttack, defence;
    Weapon(string, int, int, int);
    void setEquipType();
    char getEquipType();
    void setEquipState(bool);
    bool getEquipState();
    string getInfoStr();
};

#endif
