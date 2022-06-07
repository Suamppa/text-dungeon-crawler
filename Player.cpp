#include "Player.h"

Player::Player(string n, int lvl, int cxp, int mxp, int h, int mina, int maxa, int d, deque<Item *> & inv):
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

void Player::addItem(Item * item) {
    inventory.push_back(item);
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
    vector<Item> items = room->items;
    for (int i = 0; i < items.size(); i++) {
        addItem(&items[i]);
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
    equippedRItem == NULL ? cout << "None\n" : cout << equippedRItem->name << '\n';
    cout << "Left weapon: ";
    equippedLItem == NULL ? cout << "None\n" : cout << equippedLItem->name << '\n';
    cout << "Head: ";
    equippedHead == NULL ? cout << "None\n" : cout << equippedHead->name << '\n';
    cout << "Upper body: ";
    equippedUpperBody == NULL ? cout << "None\n" : cout << equippedUpperBody->name << '\n';
    cout << "Lower body: ";
    equippedLowerBody == NULL ? cout << "None\n" : cout << equippedLowerBody->name << '\n';
    cout << "Hands: ";
    equippedHands == NULL ? cout << "None\n" : cout << equippedHands->name << '\n';
    cout << "Feet: ";
    equippedFeet == NULL ? cout << "None\n" : cout << equippedFeet->name << '\n';
    cout << '\n';
}

// Simply prints the player inventory
void Player::printInventory() {
    int inventorySize = inventory.size();
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
    while (true) {
        vector<char> legalInputs;
        string input;
        char selection;
        bool backToTop;
        int optionASCII = 48;
        int inventorySize = inventory.size();
        cout << "Inventory:\n";
        for (int i = 0; i < inventorySize; i++) {
            cout << i+1 << ". ";
            if (inventory.at(i)->getEquipState()) cout << '[' << inventory.at(i)->getInfoStr() << ']';
            else cout << inventory.at(i)->getInfoStr();
            cout << '\n';
            ++optionASCII;
            legalInputs.push_back(optionASCII);
        }
        cout << "[C]ancel\n";
        legalInputs.push_back('c');
        while (true) {
            backToTop = false;
            cin >> input;
            selection = tolower(input.front());
            for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
                if (*it == selection) {
                    if (selection == 'c') return;
                    else {
                        int itemNum = (int) selection - 49;
                        char equipType = inventory[itemNum]->getEquipType();
                        if (equipType == ' ') {
                            handleUseItem(inventory[itemNum]);
                            backToTop = true;
                            break;
                        } else if (equipType == 'w') {
                            Weapon * pWeapon = static_cast<Weapon *>(inventory[itemNum]);
                            handleUseItem(pWeapon);
                            backToTop = true;
                            break;
                        } else {
                            Armour * pArmour = static_cast<Armour *>(inventory[itemNum]);
                            handleUseItem(pArmour);
                            backToTop = true;
                            break;
                        }
                    }
                }
            }
            if (backToTop) break;
            cout << "Invalid choice.\n";
        }
    cout << '\n';
    }
}

void Player::handleUseItem(Item * item) {
    string input;
    cout << item->getInfoStr() << "\n[C]ancel\n";
    cin >> input;
    return;
}

void Player::handleUseItem(Weapon * weapon) {
    string input;
    char selection;
    vector<char> legalInputs;
    cout << weapon->getInfoStr() << '\n';
    if (weapon->getEquipState()) {
        cout << "Equipped on the ";
        weapon == equippedRItem ? cout << "right " : cout << "left ";
        cout << "hand\n";
        // It's most likely more user-friendly to have a different key for unequipping to avoid accidents
        cout << "[U]nequip\n";
        legalInputs.push_back('u');
    } else {
        cout << "1. Equip on right hand\n2. Equip on left hand\n";
        legalInputs.push_back('1');
        legalInputs.push_back('2');
    }
    cout << "[C]ancel\n";
    legalInputs.push_back('c');
    while (true) {
        cin >> input;
        selection = tolower(input.front());
        for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
            if (*it == selection) {
                if (selection == 'c') return;
                else if (selection == '1') {
                    equipWeapon(weapon);
                    cout << weapon->name << " equipped on the right hand.\n";
                    return;
                } else if (selection == '2') {
                    equipWeapon(weapon, false);
                    cout << weapon->name << " equipped on the left hand.\n";
                    return;
                } else if (selection == 'u') {
                    cout << weapon->name << " unequipped.\n";
                    // Tämä ei välttämättä toimi kuten pitäisi
                    weapon = unequipWeapon(weapon);
                    return;
                }
            }
        }
        cout << "Invalid choice.\n";
    }
}

void Player::handleUseItem(Armour * piece) {
    string input;
    char selection, equipType;
    vector<char> legalInputs;
    cout << piece->getInfoStr() << '\n';
    if (piece->getEquipState()) {
        // It's most likely more user-friendly to have a different key for unequipping to avoid accidents
        cout << "[U]nequip\n";
        legalInputs.push_back('u');
    } else {
        cout << "1. Equip\n";
        legalInputs.push_back('1');
        equipType = piece->getEquipType();
    }
    cout << "[C]ancel\n";
    legalInputs.push_back('c');
    while (true) {
        cin >> input;
        selection = tolower(input.front());
        for (vector<char>::iterator it = legalInputs.begin(); it != legalInputs.end(); it++) {
            if (*it == selection) {
                if (selection == 'c') return;
                else if (selection == '1') {
                    equipArmour(piece, equipType);
                    cout << piece->name << " equipped.\n";
                    return;
                } else if (selection == 'u') {
                    cout << piece->name << " unequipped.\n";
                    piece = unequipArmour(piece);
                    return;
                }
            }
        }
        cout << "Invalid choice.\n";
    }
}
