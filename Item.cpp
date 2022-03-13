#include "Item.h"

Item::Item(string n, int h, int mina, int maxa, int d) {
    name = n;
    health = h;
    minAttack = mina;
    maxAttack = maxa;
    defence = d;
}
