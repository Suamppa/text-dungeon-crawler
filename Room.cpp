#include "Room.h"

// Most of this is prototyping for procedural dungeon generation

// Room::Room()
// {
//     // Constructor for the first room of a level
//     pos = 0;    // will be deprecated

//     isExit = false;
//     // Wall walls[4] = {north, east, south, west};
//     int doors[4] = {0};
//     items = vector<Item>();
//     enemies = vector<GameCharacter>();

//     // Generate an array of ints for marking doors
//     ShuffleBag<int> drawBox;
//     int value;
//     drawBox.add(1); // first room has a guaranteed door
//     for (int i = 0; i < 3; i++) {
//         value = rng(0, 1);
//         drawBox.add(value);
//     }
//     for (int i = 0; i < 4; i++) {
//         doors[i] = drawBox.draw();
//     }
//     // north = Wall(drawBox.draw());
//     // east = Wall(drawBox.draw());
//     // south = Wall(drawBox.draw());
//     // west = Wall(drawBox.draw());
// } // Empty room constructor base

Room::Room(int iy, int ix, bool ie, vector<Item> is, vector<GameCharacter> gcs)
{
    y = iy;
    x = ix;
    isExit = ie;
    items = is;
    enemies = gcs;
    visited = false;
}

// Old Room constructor
// Room::Room(int p, bool ie, vector<Item> is, vector<GameCharacter> gcs)
// {
//     pos = p;
//     isExit = ie;
//     items = is;
//     enemies = gcs;
// }

// Room::Room(int p, int entry, int neighbourStates[4], bool fd, bool ie, vector<Item> is, vector<GameCharacter> gcs)
// {
//     // neighbourStates is an array consisting of 4 integers, each signifying a neighbouring room's state in the
//     // order N, E, S, W. 0 = empty space, 1 = room with no linking door, 2 = room with a linking door.

//     pos = p;    // will be deprecated

//     forceDoor = fd;
//     isExit = ie;
//     int doors[4] = {0};
//     doors[entry] = 1;   // linking door from previous room (will be overruled by neighbourStates)
//     items = is;
//     enemies = gcs;
//     // neighbours = ns;
//     // int numNeighbours = neighbours.size();
//     // Wall walls[4] = {north, east, south, west};
//     int doorsToGenerate = 4;
//     for (int i = 0; i < 4; i++) {
//         if (neighbourStates[i] == 2) {
//             doors[i] = 1;
//             doorsToGenerate--;
//         } else if (neighbourStates[i] == 1) {
//             doors[i] = -1;
//             doorsToGenerate--;
//         }
//     }
//     if (doorsToGenerate > 1) {
//         // Generate an array of ints for marking doors
//         ShuffleBag<int> drawBox;
//         int value;
//         if (forceDoor) {
//             drawBox.add(1);
//             doorsToGenerate--;
//         }
//         for (int i = 0; i < doorsToGenerate; i++) {
//             value = rng(0, 1);
//             drawBox.add(value);
//         }
//         for (int i = 0; i < 4; i++) {
//             if (doors[i] == 0) {
//                 doors[i] = drawBox.draw();
//             } else if (doors[i] == -1) {
//                 doors[i] = 0;
//             }
//         }
//     }
// } // Base for a room constructor including doors

void Room::clearLoot() {
    items.clear();
}

void Room::clearEnemies() {
    enemies.clear();
}
