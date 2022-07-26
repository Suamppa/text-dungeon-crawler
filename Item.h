#include <iostream>
#include <string>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item
{
// private:
    // char equipType;
    // bool equipped;
    // int health, minAttack, maxAttack, defence;
public:
    string name;
    Item(string="");
    // virtual void setEquipType();

    virtual char getEquipType();
    // virtual void setEquipState();

    virtual bool getEquipState();
    virtual void setEquipState(bool);
    virtual string getInfoStr();
    virtual int getHealth();
    virtual int getMinAttack();
    virtual int getMaxAttack();
    virtual int getDefence();
    virtual int getStatScore();
    // int health, minAttack, maxAttack, defence;
    // Item(string, int, int, int, int, char);
    // void setEquipType(char) noexcept(false);
};

#endif
