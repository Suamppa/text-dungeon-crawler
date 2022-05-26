#include "Armour.h"

Armour::Armour(string n, int h, int d, char et): Item(n)
{
    try {
        setEquipType(et);
    }
    catch(char except) {
        cout << "Armour equip type '" << except << "' is not valid.\n";
    }
    name = n;
    health = h;
    defence = d;
}

// Allowed types: 't' = top/head, 'u' = upper body, 'h' = hands/arms, 'l' = lower body, 'f' = feet
void Armour::setEquipType(char type) {
    char legalTypes[6] = {'t', 'u', 'h', 'l', 'f'};
    for (const char &i : legalTypes) {
        if (type == i) {
            equipType = type;
            return;
        }
    }
    throw type;
}

string Armour::getInfoStr() {
    return name + ", HP: " + to_string(health) + ", DEF: " + to_string(defence);
}
