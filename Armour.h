#include "Item.h"

#ifndef ARMOUR_H
#define ARMOUR_H

class Armour: public Item
{
private:
    char equipType;
public:
    int health, defence;
    Armour(string, int, int, char);
    void setEquipType(char) noexcept(false);
    string getInfoStr();
};

#endif
