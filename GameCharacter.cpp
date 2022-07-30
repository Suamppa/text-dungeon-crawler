#include "GameCharacter.h"
#include "Room.h"

// (name, health, min attack, max attack, defence, XP yield, inventory)
GameCharacter::GameCharacter(string n, int h, int mina, int maxa, int d, int xpy, deque<shared_ptr<Item>> & inv)
{
    name = n;
    baseMaxHealth = h;
    baseMinAttack = mina;
    baseMaxAttack = maxa;
    baseDefence = d;
    xpYield = xpy;

    // equippedArmour = vector<Armour *>({equippedHead, equippedUpperBody, equippedHands, equippedLowerBody, equippedFeet});
    // equippedWeapons = vector<Weapon *>({equippedRItem, equippedLItem});
    // These need to be nullptr to start
    // unique_ptr<Item> & equippedHead = noItem;
    // unique_ptr<Item> & equippedUpperBody = noItem;
    // unique_ptr<Item> & equippedHands = noItem;
    // unique_ptr<Item> & equippedLowerBody = noItem;
    // unique_ptr<Item> & equippedFeet = noItem;
    // unique_ptr<Item> & equippedRItem = noItem;
    // unique_ptr<Item> & equippedLItem = noItem;

    int invToAdd = inv.size();
    // Item * pItem;
    for (int i = 0; i < invToAdd; i++) {
        // pItem = static_cast<Item *>(inv[i]);
        // auto pItem = move(inv[i]);
        inventory.push_back(move(inv[i]));
    }
    inventorySize = inventory.size();
    // char equipType;
    for (int i = 0; i < inventorySize; i++) {
        equipItem(inventory[i]);

        // equipType = inventory[i]->getEquipType();
        // if (equipType == ' ') continue;
        // else if (equipType == 'w') {
        //     // Weapon * pWeapon = static_cast<Weapon *>(inventory[i]);
        //     unique_ptr<Item> pWeapon = move(inventory[i]);
        //     // Stat comparison to be implemented as additional logic for auto-equipping
        //     if (equippedRItem == nullptr) equipWeapon(pWeapon);
        //     else if (equippedLItem == nullptr) equipWeapon(pWeapon, false);
        // } else {
        //     Armour * pArmour = static_cast<Armour *>(inventory[i]);
        //     // Stat comparison to be implemented as logic for auto-equipping
        //     equipArmour(pArmour, equipType);
        // }
    }
    currentHealth = getMaxHealth();
    cout << name << " constructed. Inventory:\n";
    for (int i = 0; i < inventorySize; i++) {
        if (inventory.at(i)->getEquipState()) cout << '[' << inventory.at(i)->getInfoStr() << "]\n";
        else cout << inventory.at(i)->getInfoStr() << '\n';
    }
    cout << "End of inventory\n";
}

int GameCharacter::takeDamage(int amount)
{
    int damage = amount - getDefence();
    if (damage < 0) {
        damage = 0;
    }
    currentHealth -= damage;
    return damage;
}

bool GameCharacter::checkIsDead()
{
    if (currentHealth <= 0) {
        dropItem();
        return true;
    }
    return false;
}

// GameCharacter class' equipItem function is automated with no user input;
// the stronger item is equipped based on stat score
void GameCharacter::equipItem(shared_ptr<Item> & pToEquip) {
    char equipType = pToEquip->getEquipType();
    if (equipType == ' ') return;
    if (equipType == 'w') {
        if (equippedRItem.pItem == nullptr) {
            equippedRItem.equipItem(pToEquip);
            return;
        } else if (equippedLItem.pItem == nullptr) {
            equippedLItem.equipItem(pToEquip);
            return;
        } else {
            int rightScore = equippedRItem.pItem->getStatScore();
            int leftScore = equippedLItem.pItem->getStatScore();
            int itemScore = pToEquip->getStatScore();
            if (leftScore < rightScore && itemScore > leftScore) {
                equippedLItem.equipItem(pToEquip);
                return;
            } else if (rightScore < leftScore && itemScore > rightScore) {
                equippedRItem.equipItem(pToEquip);
                return;
            }
        }
        return;
    } else if (equipType == 'u') {
        equippedUpperBody.equipItem(pToEquip);
        return;
    } else if (equipType == 'l') {
        equippedLowerBody.equipItem(pToEquip);
        return;
    } else if (equipType == 't') {
        equippedHead.equipItem(pToEquip);
        return;
    } else if (equipType == 'f') {
        equippedFeet.equipItem(pToEquip);
        return;
    } else if (equipType == 'h') {
        equippedHands.equipItem(pToEquip);
        return;
    }
}

void GameCharacter::unequipItem(Equipment unequipFrom) {
    unequipFrom.unequipItem();
} // Individual unequip functions for each equipment slot may be more useful for outside calls?

void GameCharacter::unequipAll() {
    equippedRItem.unequipItem();
    equippedLItem.unequipItem();
    equippedHead.unequipItem();
    equippedUpperBody.unequipItem();
    equippedHands.unequipItem();
    equippedLowerBody.unequipItem();
    equippedFeet.unequipItem();
}

// Drops all items in inventory
void GameCharacter::dropItem() {
    unequipAll();
    for (int i = 0; i < inventorySize; i++) currentRoom->items.push_back(move(inventory.at(i)));
    inventory.clear();
}

// Drops the item stored at index in inventory into the GameCharacter's current room
// void GameCharacter::dropItem(int index) {
//     if (inventory.at(index)->getEquipState()) inventory.at(index)->getEquipSlot()->unequipItem();
//     currentRoom->items.push_back(move(inventory.at(index)));
//     deque<shared_ptr<Item>>::iterator it = inventory.begin() + index;
//     inventory.erase(it);
// }

// Drops the item pointed to by iterator into the GameCharacter's current room
// void GameCharacter::dropItem(deque<shared_ptr<Item>>::iterator it) {
//     shared_ptr<Item> & pItem = *it;
//     if (pItem->getEquipState()) pItem->getEquipSlot()->unequipItem();
//     currentRoom->items.push_back(move(pItem));
//     inventory.erase(it);
// }

// void GameCharacter::equipItem(unique_ptr<Item> & pItem, int index) {
//     char equipType = pItem->getEquipType();
//     if (equipType == ' ') return;
//     if (equipType == 'w') {
//         if (equippedRItem.first == nullptr) {
//             equippedRItem.first = move(pItem);
//             return;
//         } else if (equippedLItem.first == nullptr) {
//             equippedLItem.first = move(pItem);
//             equippedLItem.second = index;
//             return;
//         } else {
//             int rightScore = equippedRItem.first->getStatScore();
//             int leftScore = equippedLItem.first->getStatScore();
//             // A pair where first holds the stat score of the weaker item and
//             // second is a boolean marking if the weaker weapon is on the left hand
//             pair<int, bool> leftWeaker = (rightScore > leftScore) ?
//                 make_pair(leftScore, true) : make_pair(rightScore, false);
//             if (pItem->getStatScore() > leftWeaker.first) {
//                 if (leftWeaker.second) {
//                     unequipItem(equippedLItem);
//                     equippedLItem.first = move(pItem);
//                     equippedLItem.second = index;
//                     return;
//                 } else {
//                     unequipItem(equippedRItem);
//                     equippedRItem.first = move(pItem);
//                     equippedRItem.second = index;
//                     return;
//                 }
//             }
//         }
//         // if (equippedRItem.first == nullptr) {
//         //     equippedRItem.first = move(pItem);
//         //     equippedRItem.second = index;
//         //     return;
//         // } else if (equippedLItem.first == nullptr) {
//         //     equippedLItem.first = move(pItem);
//         //     equippedLItem.second = index;
//         //     return;
//         // } else {
//         //     int rightScore = equippedRItem.first->getStatScore();
//         //     int leftScore = equippedLItem.first->getStatScore();
//         //     // A pair where first holds the stat score of the weaker item and
//         //     // second is a boolean marking if the weaker weapon is on the left hand
//         //     pair<int, bool> leftWeaker = (rightScore > leftScore) ?
//         //         make_pair(leftScore, true) : make_pair(rightScore, false);
//         //     if (pItem->getStatScore() > leftWeaker.first) {
//         //         if (leftWeaker.second) {
//         //             unequipItem(equippedLItem);
//         //             equippedLItem.first = move(pItem);
//         //             equippedLItem.second = index;
//         //             return;
//         //         } else {
//         //             unequipItem(equippedRItem);
//         //             equippedRItem.first = move(pItem);
//         //             equippedRItem.second = index;
//         //             return;
//         //         }
//         //     }
//         // }
//         return;
//         // string input;
//         // char selection;
//         // vector<char> legalInputs = {'1', '2', 'c'};
//         // cout << "1. Equip on right hand\n2. Equip on left hand\n[C]ancel\n";
//         // while (true) {
//         //     cin >> input;
//         //     selection = tolower(input.front());
//         //     for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
//         //         if (*it == selection) {
//         //             if (selection == 'c') return;
//         //             else if (selection == '1') {
//         //                 cout << pItem->name << " equipped on the right hand.\n";
//         //                 swapEquipment(equippedRItem, pItem, index);
//         //                 return;
//         //             } else if (selection == '2') {
//         //                 cout << pItem->name << " equipped on the left hand.\n";
//         //                 swapEquipment(equippedLItem, pItem, index);
//         //                 return;
//         //             }
//         //         }
//         //     }
//         //     cout << "Invalid choice.\n";
//         // }
//     } else if (equipType == 'u') {
//         swapEquipment(equippedUpperBody, pItem, index);
//         // if (equippedUpperBody.first != nullptr) unequipItem(equippedUpperBody);
//         // equippedUpperBody.first = move(pItem);
//         // equippedUpperBody.first->setEquipState(true);
//         // equippedUpperBody.second = index;
//         return;
//     } else if (equipType == 'l') {
//         swapEquipment(equippedLowerBody, pItem, index);
//         return;
//     } else if (equipType == 't') {
//         swapEquipment(equippedHead, pItem, index);
//         return;
//     } else if (equipType == 'f') {
//         swapEquipment(equippedFeet, pItem, index);
//         return;
//     } else if (equipType == 'h') {
//         swapEquipment(equippedHands, pItem, index);
//         return;
//     }
// }

// void GameCharacter::swapEquipment(shared_ptr<Item> & slot, shared_ptr<Item> & pItem) {
//     if (slot != nullptr) unequipItem(slot);
//     pItem->setEquipState(true);
//     slot.first = move(pItem);
//     slot.second = index;
// }

// void GameCharacter::swapEquipment(pair<unique_ptr<Item>, int> & slot, unique_ptr<Item> & pItem, int index) {
//     if (slot.first != nullptr) unequipItem(slot);
//     pItem->setEquipState(true);
//     slot.first = move(pItem);
//     slot.second = index;
// }

// void GameCharacter::unequipItem(pair<unique_ptr<Item>, int> & unequipFrom) {
//     unequipFrom.first->setEquipState(false);
//     inventory.at(unequipFrom.second) = move(unequipFrom.first);
//     unequipFrom.second = -1;
// }

// void GameCharacter::equipArmour(unique_ptr<Armour> piece, char equipType) {
//     if (equipType == 'u') {
//         if (equippedUpperBody != nullptr) unequipItem(equipType);
//         equippedUpperBody = piece;
//     } else if (equipType == 'l') {
//         if (equippedLowerBody != nullptr) unequipItem(equipType);
//         equippedLowerBody = piece;
//     } else if (equipType == 't') {
//         if (equippedHead != nullptr) unequipItem(equipType);
//         equippedHead = piece;
//     } else if (equipType == 'f') {
//         if (equippedFeet != nullptr) unequipItem(equipType);
//         equippedFeet = piece;
//     } else if (equipType == 'h') {
//         if (equippedHands != nullptr) unequipItem(equipType);
//         equippedHands = piece;
//     }
//     piece->setEquipState(true);
// }

// void GameCharacter::unequipArmour(Armour * piece) {
//     piece->setEquipState(false);
//     piece = nullptr;
// }

// Set bool equipRight = false to use equippedLItem instead of equippedRItem
// void GameCharacter::equipWeapon(unique_ptr<Weapon> weapon, bool equipRight) {
//     if (equipRight) {
//         if (equippedRItem != nullptr) unequipItem('R');
//         equippedRItem = weapon;
//     }
//     else {
//         if (equippedLItem != nullptr) unequipItem('L');
//         equippedLItem = weapon;
//     }
//     weapon->setEquipState(true);
// }

// void GameCharacter::unequipWeapon(Weapon * weapon) {
//     weapon->setEquipState(false);
//     weapon = nullptr;
// }

// Item types: 'R' = right weapon, 'L' = left weapon,
// 't' = top/head, 'u' = upper body, 'h' = hands/arms, 'l' = lower body, 'f' = feet
// void GameCharacter::unequipItem(char itemType) {
//     if (itemType == 'R') {
//         equippedRItem->setEquipState(false);
//         equippedRItem = nullptr;
//     } else if (itemType == 'L') {
//         equippedLItem->setEquipState(false);
//         equippedLItem = nullptr;
//     } else if (itemType == 'u') {
//         equippedUpperBody->setEquipState(false);
//         equippedUpperBody = nullptr;
//     } else if (itemType == 'l') {
//         equippedLowerBody->setEquipState(false);
//         equippedLowerBody = nullptr;
//     } else if (itemType == 't') {
//         equippedHead->setEquipState(false);
//         equippedHead = nullptr;
//     } else if (itemType == 'f') {
//         equippedFeet->setEquipState(false);
//         equippedFeet = nullptr;
//     } else if (itemType == 'h') {
//         equippedHands->setEquipState(false);
//         equippedHands = nullptr;
//     } else cout << "Invalid item type '" << itemType << '\'';
// }

// Pass negative values to decrease stats
void GameCharacter::updateBaseStats(int maxHP, int mina, int maxa, int def) {
    baseMaxHealth += maxHP;
    currentHealth += maxHP;
    baseMinAttack += mina;
    baseMaxAttack += maxa;
    baseDefence += def;
}

int GameCharacter::getMaxHealth() {
    int total = baseMaxHealth;
    if (equippedHead.pItem != nullptr) total += equippedHead.pItem->getHealth();
    if (equippedUpperBody.pItem != nullptr) total += equippedUpperBody.pItem->getHealth();
    if (equippedHands.pItem != nullptr) total += equippedHands.pItem->getHealth();
    if (equippedLowerBody.pItem != nullptr) total += equippedLowerBody.pItem->getHealth();
    if (equippedFeet.pItem != nullptr) total += equippedFeet.pItem->getHealth();
    return total;
}

int GameCharacter::getDefence() {
    int total = baseDefence;
    if (equippedHead.pItem != nullptr) total += equippedHead.pItem->getDefence();
    if (equippedUpperBody.pItem != nullptr) total += equippedUpperBody.pItem->getDefence();
    if (equippedHands.pItem != nullptr) total += equippedHands.pItem->getDefence();
    if (equippedLowerBody.pItem != nullptr) total += equippedLowerBody.pItem->getDefence();
    if (equippedFeet.pItem != nullptr) total += equippedFeet.pItem->getDefence();
    if (equippedRItem.pItem != nullptr) total += equippedRItem.pItem->getDefence();
    if (equippedLItem.pItem != nullptr) total += equippedLItem.pItem->getDefence();
    return total;
}

int GameCharacter::getMinAttack() {
    int total = baseMinAttack;
    // int numWeaponSlots = equippedWeapons.size();
    // for (int i = 0; i < numWeaponSlots; i++) {
    //     if (equippedWeapons[i] != nullptr) total += equippedWeapons[i]->minAttack;
    // }

    if (equippedRItem.pItem != nullptr) total += equippedRItem.pItem->getMinAttack();
    if (equippedLItem.pItem != nullptr) total += equippedLItem.pItem->getMinAttack();
    return total;
}

int GameCharacter::getMaxAttack() {
    int total = baseMaxAttack;
    // int numWeaponSlots = equippedWeapons.size();
    // for (int i = 0; i < numWeaponSlots; i++) {
    //     if (equippedWeapons[i] != nullptr) total += equippedWeapons[i]->maxAttack;
    // }

    if (equippedRItem.pItem != nullptr) total += equippedRItem.pItem->getMaxAttack();
    if (equippedLItem.pItem != nullptr) total += equippedLItem.pItem->getMaxAttack();
    return total;
}

void GameCharacter::Equipment::equipItem(shared_ptr<Item> & pToEquip) {
    if (pItem != nullptr) unequipItem();
    pItem = pToEquip;
    pItem->setEquipState(true);
    // pItem->setEquipped(this);
}

void GameCharacter::Equipment::unequipItem() {
    pItem->setEquipState(false);
    // pItem->setEquipped();
    pItem.reset();
}

// void GameCharacter::Equipment::equipItem(unique_ptr<Item> & pItem) {
//     if (name.length()) unequipItem();
//     pItem->setEquipState(true);
//     name = pItem->name;
//     health = pItem->getHealth();
//     minAttack = pItem->getMinAttack();
//     maxAttack = pItem->getMaxAttack();
//     defence = pItem->getDefence();
//     statScore = pItem->getStatScore();
// }
