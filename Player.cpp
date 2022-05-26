#include "Player.h"

Player::Player(string n, int lvl, int cxp, int mxp, int h, int mina, int maxa, int d, vector<Item *> inv):
GameCharacter(n, h, mina, maxa, d, cxp, inv)
{
    level = lvl;
    currentXp = cxp;
    maxXp = mxp;
    // Weapon fists = Weapon("Fists", 1, 5, 0);
    // addItem(fists);
}

void Player::increaseStats(int h, int mina, int maxa, int d) {
    currentHealth += h;
    maxHealth += h;
    minAttack += mina;
    maxAttack += maxa;
    defence += d;
}

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
    increaseStats(5, 1, 1, 1);
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
    cout << name << "\n";
    cout << "Level: " << level << "\n";
    cout << "XP: " << currentXp << " / " << maxXp << "\n";
    cout << "HP: " << currentHealth << " / " << maxHealth << "\n";
    cout << "Attack: " << minAttack << "-" << maxAttack << "\n";
    cout << "Defence: " << defence << "\n";
    cout << "\n";
}

void Player::printInventory() {
    int count = 1;
    int inventorySize = inventory.size();
    cout << "Inventory:\n";
    for (int i = 0; i < inventorySize; i++) {
        cout << i+1 << ". " << inventory.at(i)->getInfoStr() << "\n";
    }
    // for (vector<Item *>::iterator it = inventory.begin(); it != inventory.end(); it++) {
    //     cout << count << ". " << it.getInfoStr() << '\n';
    //     ++count;
    // }
    cout << "\n";
}
