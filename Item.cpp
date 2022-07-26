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

// 'w' = weapon, 't' = top/head, 'u' = upper body, 'h' = hands/arms, 'l' = lower body, 'f' = feet, ' ' = generic item
char Item::getEquipType() {
    return ' ';
}

// void Item::setEquipState() {
//     equipped = false;
// }

bool Item::getEquipState() {
    return false;
}

void Item::setEquipState(bool b) {
    return;
}

string Item::getInfoStr() {
    return name;
}

int Item::getHealth() {
    return 0;
}

int Item::getMinAttack() {
    return 0;
}

int Item::getMaxAttack() {
    return 0;
}

int Item::getDefence() {
    return 0;
}

int Item::getStatScore() {
    return 0;
}
