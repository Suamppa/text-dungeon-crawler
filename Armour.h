#ifndef ARMOUR_H
#define ARMOUR_H

#include "Item.h"

class Armour: public Item
{
private:
    char equipType;
    bool equipped;
    int health, defence, statScore;
public:
    // Allowed types: 't' = top/head, 'u' = upper body, 'h' = hands/arms, 'l' = lower body, 'f' = feet
    Armour(string, int, int, char);
    void setEquipType(char) noexcept(false);
    char getEquipType();
    void setEquipState(bool);
    bool getEquipState();
    string getInfoStr();
    int getHealth();
    int getDefence();
    int getStatScore();
};

#endif
