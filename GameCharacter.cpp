#include "GameCharacter.h"

GameCharacter::GameCharacter(string n, int h, int mina, int maxa, int d, int xpy, deque<Item *> inv)
{
    name = n;
    maxHealth = h;
    currentHealth = h;
    minAttack = mina;
    maxAttack = maxa;
    defence = d;
    xpYield = xpy;
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
            if (equipRItem == NULL) equipWeapon(pWeapon);
            else if (equipLItem == NULL) equipWeapon(pWeapon, false);
        } else {
            Armour * pArmour = static_cast<Armour *>(inventory[i]);
            // Stat comparison to be implemented as logic for auto-equipping
            equipArmour(pArmour, equipType);
        }
    }
}

int GameCharacter::takeDamage(int amount)
{
    int damage = amount - defence;
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
    if (equipType == 't') {
        if (equipHead != NULL) equipHead = unequipArmour(equipHead);
        equipHead = piece;
    }
    else if (equipType == 'u') {
        if (equipUpperBody != NULL) equipUpperBody = unequipArmour(equipUpperBody);
        equipUpperBody = piece;
    }
    else if (equipType == 'h') {
        if (equipHands != NULL) equipHands = unequipArmour(equipHands);
        equipHands = piece;
    }
    else if (equipType == 'l') {
        if (equipLowerBody != NULL) equipLowerBody = unequipArmour(equipLowerBody);
        equipLowerBody = piece;
    }
    else if (equipType == 'f') {
        if (equipFeet != NULL) equipFeet = unequipArmour(equipFeet);
        equipFeet = piece;
    }
    piece->setEquipState(true);
    updateStats(piece->health, 0, 0, piece->defence);
}

Armour * GameCharacter::unequipArmour(Armour * piece) {
    updateStats(-piece->health, 0, 0, -piece->defence);
    piece->setEquipState(false);
    return NULL;
}

// Set bool equipRight = false to use equipLItem instead of equipRItem
void GameCharacter::equipWeapon(Weapon * weapon, bool equipRight) {
    if (equipRight) {
        if (equipRItem != NULL) equipRItem = unequipWeapon(equipRItem);
        equipRItem = weapon;
    }
    else {
        if (equipLItem != NULL) equipLItem = unequipWeapon(equipLItem);
        equipLItem = weapon;
    }
    weapon->setEquipState(true);
    updateStats(0, weapon->minAttack, weapon->maxAttack, weapon->defence);
}

Weapon * GameCharacter::unequipWeapon(Weapon * weapon) {
    updateStats(0, -weapon->minAttack, -weapon->maxAttack, -weapon->defence);
    weapon->setEquipState(false);
    return NULL;
}

// Pass negative values to decrease stats
void GameCharacter::updateStats(int maxHP, int mina, int maxa, int def) {
    maxHealth += maxHP;
    currentHealth += maxHP;
    minAttack += mina;
    maxAttack += maxa;
    defence += def;
}
