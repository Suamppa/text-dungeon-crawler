#include "Weapon.h"

Weapon::Weapon(string n, int mina, int maxa, int d): Item(n)
{
    minAttack = mina;
    maxAttack = maxa;
    defence = d;
    setEquipType();
    equipped = false;
}

void Weapon::setEquipType() {
    equipType = 'w';
    return;
}

char Weapon::getEquipType() {
    return equipType;
}

void Weapon::setEquipState(bool state) {
    equipped = state;
}

bool Weapon::getEquipState() {
    return equipped;
}

string Weapon::getInfoStr() {
    return name + ", ATK: " + to_string(minAttack) + '-' + to_string(maxAttack) + ", DEF: " + to_string(defence);
}
