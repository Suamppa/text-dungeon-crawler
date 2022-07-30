#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon: public Item
{
private:
    char equipType;
    bool equipped;
    int minAttack, maxAttack, defence, statScore;
public:
    Weapon(string, int, int, int);
    void setEquipType();
    char getEquipType();
    void setEquipState(bool);
    bool getEquipState();
    string getInfoStr();
    int getMinAttack();
    int getMaxAttack();
    int getDefence();
    int getStatScore();
};

#endif
