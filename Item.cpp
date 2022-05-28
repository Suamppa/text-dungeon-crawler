#include "Item.h"

// Item::Item(string n, int h, int mina, int maxa, int d, char et)
// {
//     try {
//         setEquipType(et);
//     }
//     catch(char except) {
//         cout << "Item equip type '" << except << "' not valid.\n";
//     }
//     name = n;
//     health = h;
//     minAttack = mina;
//     maxAttack = maxa;
//     defence = d;
// }

// void Item::setEquipType(char type) {
//     char legalTypes[6] = {'t', 'u', 'h', 'w', 'l', 'f'};
//     for (const char &i : legalTypes) {
//         if (type == i) {
//             equipType = type;
//             return;
//         }
//     }
//     throw type;
// }

Item::Item(string n)
{
    name = n;
    // setEquipType();
    // equipped = false;
}

// void Item::setEquipType() {
//     equipType = ' ';
// }

char Item::getEquipType() {
    return ' ';
}

// void Item::setEquipState() {
//     equipped = false;
// }

bool Item::getEquipState() {
    return false;
}

string Item::getInfoStr() {
    return name;
}
