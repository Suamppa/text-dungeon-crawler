#include "GameCharacter.h"

GameCharacter::GameCharacter(string n, int h, int mina, int maxa, int d, int xpy, vector<Item> inv)
{
    name = n;
    maxHealth = h;
    currentHealth = h;
    minAttack = mina;
    maxAttack = maxa;
    defence = d;
    xpYield = xpy;
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
