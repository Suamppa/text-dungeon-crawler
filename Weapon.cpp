#include "Weapon.h"

Weapon::Weapon(string n, int mina, int maxa, int d): Item(n)
{
    name = n;
    minAttack = mina;
    maxAttack = maxa;
    defence = d;
}

string Weapon::getInfoStr() {
    return name + ", ATK: " + to_string(minAttack) + '-' + to_string(maxAttack) + ", DEF: " + to_string(defence);
}
