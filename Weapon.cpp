#include "Weapon.h"

Weapon::Weapon(string n, int mina, int maxa, int d): Item(n)
{
    minAttack = mina;
    maxAttack = maxa;
    defence = d;
    setEquipType();
    equipped = false;
    statScore = (minAttack + maxAttack) / 2 + defence;
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

int Weapon::getMinAttack() {
    return minAttack;
}

int Weapon::getMaxAttack() {
    return maxAttack;
}

int Weapon::getDefence() {
    return defence;
}

int Weapon::getStatScore() {
    return statScore;
}
