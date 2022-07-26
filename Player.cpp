#include "Player.h"

Player::Player(string n, int lvl, int cxp, int mxp, int h, int mina, int maxa, int d, deque<shared_ptr<Item>> & inv):
GameCharacter(n, h, mina, maxa, d, cxp, inv)
{
    level = lvl;
    currentXp = cxp;
    maxXp = mxp;
    // Weapon fists = Weapon("Fists", 1, 5, 0);
    // addItem(fists);
}

// void Player::increaseStats(int h, int mina, int maxa, int d) {
//     currentHealth += h;
//     baseMaxHealth += h;
//     baseMinAttack += mina;
//     baseMaxAttack += maxa;
//     baseDefence += d;
// }

void Player::addItem(shared_ptr<Item> & item) {
    inventory.push_back(move(item));
    inventorySize = inventory.size();
    // increaseStats(item.health, item.minAttack, item.maxAttack, item.defence);
}

// void Player::addItem(Weapon weapon) {
//     inventory.push_back(weapon);
// }

// void Player::addItem(Armour armour) {
//     inventory.push_back(armour);
// }

void Player::gainXp(int amount) {
    currentXp += amount;
    // int overflowXp = maxXp - currentXp;
    if (currentXp >= maxXp) {
        int overflowXp = currentXp - maxXp;
        levelUp(overflowXp);
    }
}

void Player::levelUp(int oxp) {
    ++level;
    currentXp = oxp;
    if (level > 8) {
        maxXp = (400 / 5 * pow(level, 3)) / 100;
    } else maxXp += 50;
    updateBaseStats(5, 1, 1, 1);
    cout << "Level up! You are now level " << level << ".\n";
}

void Player::lootRoom(Room * room) {
    int numItems = room->items.size();

    // vector<Item *> items = room->items;
    cout << "In Player::lootRoom: ";
    for (int i = 0; i < numItems; i++) {
        cout << room->items[i]->getInfoStr() << '\n';
        addItem(room->items[i]);
    }
}

void Player::changeRooms(Room * newRoom) {
    previousRoom = currentRoom;
    currentRoom = newRoom;
    currentRoom->visited = true;
}

void Player::printStats() {
    cout << name << '\n';
    cout << "Level: " << level << '\n';
    cout << "XP: " << currentXp << " / " << maxXp << '\n';
    cout << "HP: " << currentHealth << " / " << getMaxHealth() << '\n';
    cout << "Attack: " << getMinAttack() << "-" << getMaxAttack() << '\n';
    cout << "Defence: " << getDefence() << '\n';
    cout << "\nEquipment:\n";
    cout << "Right weapon: ";
    equippedRItem.pItem == nullptr ? cout << "None\n" : cout << equippedRItem.pItem->name << '\n';
    cout << "Left weapon: ";
    equippedLItem.pItem == nullptr ? cout << "None\n" : cout << equippedLItem.pItem->name << '\n';
    cout << "Head: ";
    equippedHead.pItem == nullptr ? cout << "None\n" : cout << equippedHead.pItem->name << '\n';
    cout << "Upper body: ";
    equippedUpperBody.pItem == nullptr ? cout << "None\n" : cout << equippedUpperBody.pItem->name << '\n';
    cout << "Lower body: ";
    equippedLowerBody.pItem == nullptr ? cout << "None\n" : cout << equippedLowerBody.pItem->name << '\n';
    cout << "Hands: ";
    equippedHands.pItem == nullptr ? cout << "None\n" : cout << equippedHands.pItem->name << '\n';
    cout << "Feet: ";
    equippedFeet.pItem == nullptr ? cout << "None\n" : cout << equippedFeet.pItem->name << '\n';
    cout << '\n';
}

// void Player::findAndPrintEquipped(const int index) {
//     if (index == equippedRItem.second) cout << '[' << equippedRItem.pItem->getInfoStr() << ']';
//     else if (index == equippedLItem.second) cout << '[' << equippedLItem.pItem->getInfoStr() << ']';
//     else if (index == equippedUpperBody.second) cout << '[' << equippedUpperBody.pItem->getInfoStr() << ']';
//     else if (index == equippedLowerBody.second) cout << '[' << equippedLowerBody.pItem->getInfoStr() << ']';
//     else if (index == equippedHead.second) cout << '[' << equippedHead.pItem->getInfoStr() << ']';
//     else if (index == equippedFeet.second) cout << '[' << equippedFeet.pItem->getInfoStr() << ']';
//     else if (index == equippedHands.second) cout << '[' << equippedHands.pItem->getInfoStr() << ']';
// }

// Simply prints the player inventory
void Player::printInventory() {
    cout << "Inventory:\n";
    for (int i = 0; i < inventorySize; i++) {
        cout << i+1 << ". ";
        if (inventory.at(i)->getEquipState()) cout << '[' << inventory.at(i)->getInfoStr() << ']';
        else cout << inventory.at(i)->getInfoStr();
        cout << '\n';
    }
    cout << '\n';
}

// Prints the player inventory and enables item interaction
void Player::accessInventory() {
    // Contains a specialised mini-version of Dungeon::handleInput
    vector<char> legalInputs;
    string input;
    char selection;
    bool validInput = false;
    int optionASCII = 48;
    cout << "Inventory:\n";
    for (int i = 0; i < inventorySize; i++) {
        cout << i+1 << ". ";
        // if (inventory.at(i)->getEquipState()) cout << '[' << inventory.at(i)->getInfoStr() << ']';
        // if (inventory.at(i) == nullptr) findAndPrintEquipped(i);
        if (inventory.at(i)->getEquipState()) cout << '[' << inventory.at(i)->getInfoStr() << ']';
        else cout << inventory.at(i)->getInfoStr();
        cout << '\n';
        ++optionASCII;
        legalInputs.push_back(optionASCII);
    }
    cout << "[C]ancel\n";
    legalInputs.push_back('c');
    while (!validInput) {
        cout << "Select option: ";
        cin >> input;
        selection = tolower(input.front());
        for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
            if (*it == selection) {
                if (selection == 'c') {
                    cout << '\n';
                    return;
                }
                int itemNum = (int) selection - 49;
                handleUseItem(inventory.at(itemNum));
                validInput = true;
                break;
                // } else {
                    // int itemNum = (int) selection - 49;
                    // char equipType = inventory[itemNum]->getEquipType();
                    // if (equipType == ' ') {
                    //     handleUseItem(inventory[itemNum]);
                    //     validInput = true;
                    //     break;
                    // } else if (equipType == 'w') {
                    //     // Weapon * pWeapon = static_cast<Weapon *>(inventory[itemNum]);
                    //     handleUseItem(inventory[itemNum]);
                    //     validInput = true;
                    //     break;
                    // } else {
                    //     // Armour * pArmour = static_cast<Armour *>(inventory[itemNum]);
                    //     handleUseItem(inventory[itemNum]);
                    //     validInput = true;
                    //     break;
                    // }
                // }
            }
        }
        if (!validInput) cout << "Invalid choice.\n";
    }
    cout << '\n';
    accessInventory();
}

void Player::handleUseItem(shared_ptr<Item> & pItem) {
    string input;
    char selection;
    vector<char> legalInputs;
    char equipType;
    bool equipState = pItem->getEquipState();
    // // LESSON: Smart pointers aren't always the answer.
    // // In this case, lifetime management is not needed and smart pointers only cause issues (copying).
    // unique_ptr<Equipment> unequipFrom;
    Equipment * unequipFrom;
    cout << pItem->getInfoStr() << '\n';
    if (dynamic_pointer_cast<Weapon>(pItem) != nullptr) {
        if (pItem->getEquipState()) {
            cout << "Equipped on the ";
            if (pItem == equippedRItem.pItem) {
                // unequipFrom = make_unique<Equipment>(equippedRItem);
                unequipFrom = &equippedRItem;
                cout << "right ";
            } else if (pItem == equippedLItem.pItem) {
                // unequipFrom = make_unique<Equipment>(equippedLItem);
                unequipFrom = &equippedLItem;
                cout << "left ";
            } else {
                cout << "\nERROR: Equip state and equipment mismatch.\n";
            }
            cout << "hand\n";
            // It's most likely more user-friendly to have a different key for unequipping to avoid accidents
            cout << "[U]nequip\n";
            legalInputs.push_back('u');
        } else {
            cout << "1. Equip on right hand\n2. Equip on left hand\n";
            equipType = pItem->getEquipType();
            legalInputs.push_back('1');
            legalInputs.push_back('2');
        }
    } else if (dynamic_pointer_cast<Armour>(pItem) != nullptr) {
        if (pItem->getEquipState()) {
            cout << "Equipped on ";
            if (pItem == equippedUpperBody.pItem) {
                // unequipFrom = make_unique<Equipment>(equippedUpperBody);
                unequipFrom = &equippedUpperBody;
                cout << "upper body.\n";
            } else if (pItem == equippedLowerBody.pItem) {
                // unequipFrom = make_unique<Equipment>(equippedLowerBody);
                unequipFrom = &equippedLowerBody;
                cout << "lower body.\n";
            } else if (pItem == equippedHead.pItem) {
                // unequipFrom = make_unique<Equipment>(equippedHead);
                unequipFrom = &equippedHead;
                cout << "head.\n";
            } else if (pItem == equippedFeet.pItem) {
                // unequipFrom = make_unique<Equipment>(equippedFeet);
                unequipFrom = &equippedFeet;
                cout << "feet.\n";
            } else if (pItem == equippedHands.pItem) {
                // unequipFrom = make_unique<Equipment>(equippedHands);
                unequipFrom = &equippedHands;
                cout << "hands.\n";
            }
            cout << "[U]nequip\n";
            legalInputs.push_back('u');
        } else {
            cout << "1. Equip\n";
            equipType = pItem->getEquipType();
            legalInputs.push_back('1');
        }
    }
    cout << "[C]ancel\n";
    legalInputs.push_back('c');
    while (true) {
        cout << "Select option: ";
        cin >> input;
        selection = tolower(input.front());
        for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
            if (*it == selection) {
                if (selection == 'c') return;
                else if (selection == '1') {
                    // OLISIKO TYYPIN MÄÄRITTÄVÄ ALALUOKKA ARMOURILLE PAREMPI RATKAISU?
                    if (equipType == 'w') {
                        equippedRItem.equipItem(pItem);
                        cout << pItem->name << " equipped on the right hand.\n";
                        return;
                    } else if (equipType == 'u') {
                        equippedUpperBody.equipItem(pItem);
                        cout << pItem->name << " equipped on upper body.\n";
                        return;
                    } else if (equipType == 'l') {
                        equippedLowerBody.equipItem(pItem);
                        cout << pItem->name << " equipped on lower body.\n";
                        return;
                    } else if (equipType == 't') {
                        equippedHead.equipItem(pItem);
                        cout << pItem->name << " equipped on head.\n";
                        return;
                    } else if (equipType == 'f') {
                        equippedFeet.equipItem(pItem);
                        cout << pItem->name << " equipped on feet.\n";
                        return;
                    } else if (equipType == 'h') {
                        equippedHands.equipItem(pItem);
                        cout << pItem->name << " equipped on hands.\n";
                        return;
                    }
                } else if (selection == '2' && equipType == 'w') {
                    equippedLItem.equipItem(pItem);
                    cout << pItem->name << " equipped on the left hand.\n";
                    return;
                } else if (selection == 'u') {
                    cout << pItem->name << " unequipped.\n";
                    unequipFrom->unequipItem();
                    return;
                }
            }
        }
        cout << "Invalid choice.\n";
    }
}

// void Player::handleUseItem(Item * item) {
//     string input;
//     cout << item->getInfoStr() << "\n[C]ancel\n";
//     cin >> input;
//     return;
// }

// void Player::handleUseItem(Weapon * weapon) {
//     string input;
//     char selection;
//     vector<char> legalInputs;
//     char unequipFrom;
//     cout << weapon->getInfoStr() << '\n';
//     if (weapon->getEquipState()) {
//         cout << "Equipped on the ";
//         if (weapon == equippedRItem) {
//             unequipFrom = 'R';
//             cout << "right ";
//         } else if (weapon == equippedLItem) {
//             unequipFrom = 'L';
//             cout << "left ";
//         } else {
//             unequipFrom = ' ';
//             cout << "\nERROR: Equip state and equipment mismatch.\n";
//         }
//         cout << "hand\n";
//         // It's most likely more user-friendly to have a different key for unequipping to avoid accidents
//         cout << "[U]nequip\n";
//         legalInputs.push_back('u');
//     } else {
//         cout << "1. Equip on right hand\n2. Equip on left hand\n";
//         legalInputs.push_back('1');
//         legalInputs.push_back('2');
//     }
//     cout << "[C]ancel\n";
//     legalInputs.push_back('c');
//     while (true) {
//         cin >> input;
//         selection = tolower(input.front());
//         for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
//             if (*it == selection) {
//                 if (selection == 'c') return;
//                 else if (selection == '1') {
//                     equipWeapon(weapon);
//                     cout << weapon->name << " equipped on the right hand.\n";
//                     return;
//                 } else if (selection == '2') {
//                     equipWeapon(weapon, false);
//                     cout << weapon->name << " equipped on the left hand.\n";
//                     return;
//                 } else if (selection == 'u') {
//                     cout << weapon->name << " unequipped.\n";
//                     unequipItem(unequipFrom);
//                     return;
//                 }
//             }
//         }
//         cout << "Invalid choice.\n";
//     }
// }

// void Player::handleUseItem(Armour * piece) {
//     string input;
//     char selection, equipType;
//     vector<char> legalInputs;
//     Armour * unequipFrom;
//     cout << piece->getInfoStr() << '\n';
//     equipType = piece->getEquipType();
//     if (piece->getEquipState()) {
//         if (equipType == 't') unequipFrom = equippedHead;
//         else if (equipType == 'u') unequipFrom = equippedUpperBody;
//         else if (equipType == 'h') unequipFrom = equippedHands;
//         else if (equipType == 'l') unequipFrom = equippedLowerBody;
//         else if (equipType == 'f') unequipFrom = equippedFeet;
//         else {
//             unequipFrom = nullptr;
//             cout << "ERROR: Equip state and equipment mismatch.\n";
//         }
//         // It's most likely more user-friendly to have a different key for unequipping to avoid accidents
//         cout << "[U]nequip\n";
//         legalInputs.push_back('u');
//     } else {
//         cout << "1. Equip\n";
//         legalInputs.push_back('1');
//     }
//     cout << "[C]ancel\n";
//     legalInputs.push_back('c');
//     while (true) {
//         cin >> input;
//         selection = tolower(input.front());
//         for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
//             if (*it == selection) {
//                 if (selection == 'c') return;
//                 else if (selection == '1') {
//                     equipArmour(piece, equipType);
//                     cout << piece->name << " equipped.\n";
//                     return;
//                 } else if (selection == 'u') {
//                     cout << unequipFrom->name << " unequipped.\n";
//                     unequipItem(equipType);
//                     return;
//                 }
//             }
//         }
//         cout << "Invalid choice.\n";
//     }
// }

// void Player::equipItem(shared_ptr<Item> & pItem) {
//     char equipType = pItem->getEquipType();
//     if (equipType == ' ') return;
//     if (equipType == 'w') {
//         // if (!useUserInput) {
//         //     if (equippedRItem.first == nullptr) {
//         //         equippedRItem.first = move(pItem);
//         //         equippedRItem.second = index;
//         //         return;
//         //     } else if (equippedLItem.first == nullptr) {
//         //         equippedLItem.first = move(pItem);
//         //         equippedLItem.second = index;
//         //         return;
//         //     } else {
//         //         int rightScore = equippedRItem.first->getStatScore();
//         //         int leftScore = equippedLItem.first->getStatScore();
//         //         // A pair where first holds the stat score of the weaker item and
//         //         // second is a boolean marking if the weaker weapon is on the left hand
//         //         pair<int, bool> leftWeaker = (rightScore > leftScore) ?
//         //             make_pair(leftScore, true) : make_pair(rightScore, false);
//         //         if (pItem->getStatScore() > leftWeaker.first) {
//         //             if (leftWeaker.second) {
//         //                 unequipItem(equippedLItem);
//         //                 equippedLItem.first = move(pItem);
//         //                 equippedLItem.second = index;
//         //                 return;
//         //             } else {
//         //                 unequipItem(equippedRItem);
//         //                 equippedRItem.first = move(pItem);
//         //                 equippedRItem.second = index;
//         //                 return;
//         //             }
//         //         }
//         //     }
//         //     return;
//         // }
//         string input;
//         char selection;
//         vector<char> legalInputs = {'1', '2', 'c'};
//         cout << "1. Equip on right hand\n2. Equip on left hand\n[C]ancel\n";
//         while (true) {
//             cin >> input;
//             selection = tolower(input.front());
//             for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
//                 if (*it == selection) {
//                     if (selection == 'c') return;
//                     else if (selection == '1') {
//                         cout << pItem->name << " equipped on the right hand.\n";
//                         swapEquipment(equippedRItem, pItem, index);
//                         return;
//                     } else if (selection == '2') {
//                         cout << pItem->name << " equipped on the left hand.\n";
//                         swapEquipment(equippedLItem, pItem, index);
//                         return;
//                     }
//                 }
//             }
//             cout << "Invalid choice.\n";
//         }
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
