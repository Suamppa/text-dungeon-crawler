#include "Weapon.h"

Weapon::Weapon(string n, int mina, int maxa, int d): Item(n)
{
    name = n;
    minAttack = mina;
    maxAttack = maxa;
    defence = d;
}
