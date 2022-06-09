#include "GameCharacter.h"

GameCharacter::GameCharacter(string n, int h, int mina, int maxa, int d, int xpy, deque<Item *> & inv)
{
    name = n;
    baseMaxHealth = h;
    baseMinAttack = mina;
    baseMaxAttack = maxa;
    baseDefence = d;
    xpYield = xpy;
    // equippedArmour = vector<Armour *>({equippedHead, equippedUpperBody, equippedHands, equippedLowerBody, equippedFeet});
    // equippedWeapons = vector<Weapon *>({equippedRItem, equippedLItem});
    // These need to be NULL to start
    equippedHead = NULL;
    equippedUpperBody = NULL;
    equippedHands = NULL;
    equippedLowerBody = NULL;
    equippedFeet = NULL;
    equippedRItem = NULL;
    equippedLItem = NULL;
    int invToAdd = inv.size();
    Item * pItem;
    for (int i = 0; i < invToAdd; i++) {
        pItem = static_cast<Item *>(inv[i]);
        inventory.push_back(pItem);
    }
    int inventorySize = inventory.size();
    char equipType;
    for (int i = 0; i < inventorySize; i++) {
        equipType = inventory[i]->getEquipType();
        if (equipType == ' ') continue;
        else if (equipType == 'w') {
            Weapon * pWeapon = static_cast<Weapon *>(inventory[i]);
            // Stat comparison to be implemented as additional logic for auto-equipping
            if (equippedRItem == NULL) equipWeapon(pWeapon);
            else if (equippedLItem == NULL) equipWeapon(pWeapon, false);
        } else {
            Armour * pArmour = static_cast<Armour *>(inventory[i]);
            // Stat comparison to be implemented as logic for auto-equipping
            equipArmour(pArmour, equipType);
        }
    }
    currentHealth = getMaxHealth();
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
    return currentHealth <= 0;
}

void GameCharacter::equipArmour(Armour * piece, char equipType) {
    if (equipType == 'u') {
        if (equippedUpperBody != NULL) unequipItem(equipType);
        equippedUpperBody = piece;
    } else if (equipType == 'l') {
        if (equippedLowerBody != NULL) unequipItem(equipType);
        equippedLowerBody = piece;
    } else if (equipType == 't') {
        if (equippedHead != NULL) unequipItem(equipType);
        equippedHead = piece;
    } else if (equipType == 'f') {
        if (equippedFeet != NULL) unequipItem(equipType);
        equippedFeet = piece;
    } else if (equipType == 'h') {
        if (equippedHands != NULL) unequipItem(equipType);
        equippedHands = piece;
    }
    piece->setEquipState(true);
}

// void GameCharacter::unequipArmour(Armour * piece) {
//     piece->setEquipState(false);
//     piece = NULL;
// }

// Set bool equipRight = false to use equippedLItem instead of equippedRItem
void GameCharacter::equipWeapon(Weapon * weapon, bool equipRight) {
    if (equipRight) {
        if (equippedRItem != NULL) unequipItem('R');
        equippedRItem = weapon;
    }
    else {
        if (equippedLItem != NULL) unequipItem('L');
        equippedLItem = weapon;
    }
    weapon->setEquipState(true);
}

// void GameCharacter::unequipWeapon(Weapon * weapon) {
//     weapon->setEquipState(false);
//     weapon = NULL;
// }

// Item types: 'R' = right weapon, 'L' = left weapon,
// 't' = top/head, 'u' = upper body, 'h' = hands/arms, 'l' = lower body, 'f' = feet
void GameCharacter::unequipItem(char itemType) {
    if (itemType == 'R') {
        equippedRItem->setEquipState(false);
        equippedRItem = NULL;
    } else if (itemType == 'L') {
        equippedLItem->setEquipState(false);
        equippedLItem = NULL;
    } else if (itemType == 'u') {
        equippedUpperBody->setEquipState(false);
        equippedUpperBody = NULL;
    } else if (itemType == 'l') {
        equippedLowerBody->setEquipState(false);
        equippedLowerBody = NULL;
    } else if (itemType == 't') {
        equippedHead->setEquipState(false);
        equippedHead = NULL;
    } else if (itemType == 'f') {
        equippedFeet->setEquipState(false);
        equippedFeet = NULL;
    } else if (itemType == 'h') {
        equippedHands->setEquipState(false);
        equippedHands = NULL;
    } else cout << "Invalid item type '" << itemType << '\'';
}

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
    int toAdd;
    // This implementation requires getting into smart pointers
    // int numArmourSlots = equippedArmour.size();
    // for (int i = 0; i < numArmourSlots; i++) {
    //     if (equippedArmour[i] != NULL) {
    //         cout << "Value: " << equippedArmour[i]->health << endl;
    //         total += equippedArmour.at(i)->health;
    //     }
    // }

    if (equippedHead != NULL) {
        toAdd = equippedHead->getHealth();
        total += toAdd;
    }
    if (equippedUpperBody != NULL) {
        toAdd = equippedUpperBody->getHealth();
        total += toAdd;
    }
    if (equippedHands != NULL) {
        toAdd = equippedHands->getHealth();
        total += toAdd;
    }
    if (equippedLowerBody != NULL) {
        toAdd = equippedLowerBody->getHealth();
        total += toAdd;
    }
    if (equippedFeet != NULL) {
        toAdd = equippedFeet->getHealth();
        total += toAdd;
    }
    return total;
}

int GameCharacter::getDefence() {
    int total = baseDefence;
    // int numArmourSlots = equippedArmour.size();
    // for (int i = 0; i < numArmourSlots; i++) {
    //     if (equippedArmour[i] != NULL) total += equippedArmour[i]->defence;
    // }

    if (equippedHead != NULL) total += equippedHead->getDefence();
    if (equippedUpperBody != NULL) total += equippedUpperBody->getDefence();
    if (equippedHands != NULL) total += equippedHands->getDefence();
    if (equippedLowerBody != NULL) total += equippedLowerBody->getDefence();
    if (equippedFeet != NULL) total += equippedFeet->getDefence();
    return total;
}

int GameCharacter::getMinAttack() {
    int total = baseMinAttack;
    // int numWeaponSlots = equippedWeapons.size();
    // for (int i = 0; i < numWeaponSlots; i++) {
    //     if (equippedWeapons[i] != NULL) total += equippedWeapons[i]->minAttack;
    // }

    if (equippedRItem != NULL) total += equippedRItem->getMinAttack();
    if (equippedLItem != NULL) total += equippedLItem->getMinAttack();
    return total;
}

int GameCharacter::getMaxAttack() {
    int total = baseMaxAttack;
    // int numWeaponSlots = equippedWeapons.size();
    // for (int i = 0; i < numWeaponSlots; i++) {
    //     if (equippedWeapons[i] != NULL) total += equippedWeapons[i]->maxAttack;
    // }

    if (equippedRItem != NULL) total += equippedRItem->getMaxAttack();
    if (equippedLItem != NULL) total += equippedLItem->getMaxAttack();
    return total;
}

GameCharacter::~GameCharacter() {
    int inventorySize = inventory.size();
    for (int i = 0; i < inventorySize; i++) {
        delete inventory[i];
    }
    // int numArmourSlots = equippedArmour.size();
    // for (int i = 0; i < numArmourSlots; i++) {
    //     delete equippedArmour[i];
    // }
    // int numWeaponSlots = equippedWeapons.size();
    // for (int i = 0; i < numWeaponSlots; i++) {
    //     delete equippedWeapons[i];
    // }
}
