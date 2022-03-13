#include "Room.h"

Room::Room(int p, bool ie, vector<Item> is, vector<GameCharacter> gcs)
{
    // walls = {N, E, S, W}: 0 = wall, 1 = door, 2 = entry, 3 = exit
    // int walls[4];
    
    pos = p;
    isExit = ie;
    items = is;
    enemies = gcs;
}

void Room::clearLoot() {
    items.clear();
}

void Room::clearEnemies() {
    enemies.clear();
}
