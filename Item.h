#include <iostream>
#include <string>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item
{
// private:
//     char equipType;
public:
    string name;
    Item(string="");
    virtual string getInfoStr();
    // int health, minAttack, maxAttack, defence;
    // Item(string, int, int, int, int, char);
    // void setEquipType(char) noexcept(false);
};

#endif
