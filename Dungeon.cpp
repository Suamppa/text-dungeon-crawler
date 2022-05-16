#include "Dungeon.h"

Dungeon::Dungeon(Player p)
{
    player = p;
}

/* void Dungeon::printActions(int numActions, string actions[], bool allowStats, bool allowInventory) {
    cout << "Choose an action:\n";
    for (int i = 0; i < numActions; i++) {
        cout << actions[i] << "\n";
    }
    if (allowStats) {
        cout << "[S]tats" << "\n";
    }
    if (allowInventory) {
        cout << "[I]nventory" << "\n";
    }
} */

template <typename T>
bool Dungeon::check2DBounds(vector<vector<T>> & vec, int y, int x) {
    try
    {
        if (vec.at(y).at(x)) return true;
    }
    catch(const out_of_range &oor)
    {
        return false;
    }
    return true;
}

void Dungeon::findAdjacentRooms(bool isRoom, int iy, int ix, vector<vector<int>> & saveToVec, bool useDiagonals) {
    int y, x;
    int adjInds[2] = {-1, 1};
    if (useDiagonals) {
        for (int i = 0; i < 2; i++) {
            y = iy - 1;
            x = ix + adjInds[i];
            if (check2DBounds(hasRoom, y, x) && (hasRoom[y][x] == isRoom)) {
                saveToVec.push_back({y, x});
            }
            y = iy + 1;
            if (check2DBounds(hasRoom, y, x) && (hasRoom[y][x] == isRoom)) {
                saveToVec.push_back({y, x});
            }
        }
        return;
    }
    // Default behaviour
    for (int i = 0; i < 2; i++) {
        y = iy + adjInds[i];
        x = ix + adjInds[i];
        if (check2DBounds(hasRoom, y, ix) && (hasRoom[y][ix] == isRoom)) {
            saveToVec.push_back({y, ix});
        }
        if (check2DBounds(hasRoom, iy, x) && (hasRoom[iy][x] == isRoom)) {
            saveToVec.push_back({iy, x});
        }
    }
}

void Dungeon::findAdjacentRooms(bool isRoom, int iy, int ix, vector<bool> & saveToVec) {
    int y, x;
    int adjInds[2] = {-1, 1};
    for (int i = 0; i < 2; i++) {
        y = iy + adjInds[i];
        x = ix + adjInds[i];
        if (check2DBounds(hasRoom, y, ix) && (hasRoom[y][ix] == isRoom)) {
            saveToVec.push_back(true);
        } else saveToVec.push_back(false);
        if (check2DBounds(hasRoom, iy, x) && (hasRoom[iy][x] == isRoom)) {
            saveToVec.push_back(true);
        } else saveToVec.push_back(false);
    }
}

void Dungeon::addRoom(int y, int x, bool isExit, vector<Item> items, vector<GameCharacter> enemies) {
    rooms[y][x] = Room(y, x, isExit, items, enemies);
    hasRoom[y][x] = true;
    ++numRooms;
}

void Dungeon::generateDungeon(int gridX, int gridY, int minRooms, int maxRooms) {
    // 1. Create starting room
    // 2. Pick an adjacent space to handle next
    // 3. Check if the space has a room
    // 4. Generate a room in that space if empty
    // 5. Repeat steps 2-4 up to until max number of rooms is reached

    cout << "Starting dungeon creation..." << endl;
    int gridSize = gridX * gridY;
    numRooms = 0;
    // minRooms and maxRooms are the minimum and maximum number of rooms *allowed*,
    // but they are not necessarily the final amounts
    maxRooms = ((maxRooms < gridSize) && (maxRooms > 0)) ? maxRooms : gridSize;

    // Create a 2D vector of the dungeon level
    // vector<vector<bool>> dungeon(gridY, vector<bool>(gridX, 0));
    hasRoom = vector<vector<bool>>(gridY, vector<bool>(gridX, false));
    rooms = vector<vector<Room>>(gridY, vector<Room>(gridX, Room()));
    // Choose the index of the starting room
    int indexY = rng(0, gridY-1);
    int indexX = rng(0, gridX-1);
    // Construct the first room
    startY = indexY;
    startX = indexX;
    addRoom(startY, startX, false);
    cout << "First room created" << endl;
    
    // Enemy creation and selection can be made fancier, this is just a mockup
    GameCharacter littleMonster = GameCharacter("Little Monster", 50, 15, 20, 5, 25);
    GameCharacter bigMonster = GameCharacter("Big Monster", 100, 25, 30, 10, 50);
    // vector<GameCharacter> enemyPool{littleMonster, littleMonster, littleMonster, bigMonster};
    Item sword = Item("Sword", 0, 20, 25, 1);
    Item shield = Item("Shield", 0, 0, 0, 5);
    cout << "Enemy and item pools created" << endl;

    ShuffleBag<int> intPicker;
    vector<GameCharacter> enemyPool = {littleMonster, littleMonster, littleMonster, bigMonster};
    int enemyPoolEnd = enemyPool.size() - 1;
    vector<Item> itemPool = {sword, shield};
    int itemPoolEnd = itemPool.size() - 1;
    int y, x, roomType, poolInd, nonExitOdds;
    bool allowExit = false;
    bool isExit = false;
    vector<GameCharacter> roomEnemies;
    vector<Item> roomItems;
    // A vector for holding the indices of available adjacent free spaces
    vector<vector<int>> freeInds;
    // int adjInds[2] = {-1, 1};

    // Main generation loop
    while (numRooms <= maxRooms) {
        cout << "Picking a new index" << endl;
        // Check adjacent indices for free space
        findAdjacentRooms(false, indexY, indexX, freeInds);
        // for (int i = 0; i < 2; i++) {
        //     y = indexY + adjInds[i];
        //     x = indexX + adjInds[i];
        //     if (check2DBounds(hasRoom, y, indexX)) {
        //         if (!hasRoom[y][indexX]) freeInds.push_back({y, indexX});
        //     }
        //     if (check2DBounds(hasRoom, indexY, x)) {
        //         if (!hasRoom[indexY][x]) freeInds.push_back({indexY, x});
        //     }
        // }

        // If no adjacent spaces are free, check diagonals
        if (freeInds.size() < 1) {
            findAdjacentRooms(false, indexY, indexX, freeInds, true);
        }
        //     for (int i = 0; i < 2; i++) {
        //         y = indexY - 1;
        //         x = indexX + adjInds[i];
        //         if (check2DBounds(hasRoom, y, x)) {
        //             if (!hasRoom[y][x]) freeInds.push_back({y, x});
        //         }
        //         y = indexY + 1;
        //         if (check2DBounds(hasRoom, y, x)) {
        //             if (!hasRoom[y][x]) freeInds.push_back({y, x});
        //         }
        //     }
        // }

        // If a free space is still not found, create an exit if allowed or find a free adjacent space elsewhere
        if (freeInds.size() < 1) {
            if (allowExit) {
                if (!hasRoom[indexY][indexX]) {
                    addRoom(indexY, indexX, true, roomItems, roomEnemies);
                } else rooms[indexY][indexX].isExit = true;
                cout << "Exit created\nDungeon generation finished" << endl;
                break;
            } else {
                cout << "No free space, finding a new reference" << endl;
                if (indexY >= gridY / 2) {
                    for (int i = 0; i < gridY-1; i++) {
                        for (int j = 0; j < gridX-1; j++) {
                            if (hasRoom[i][j] && (!hasRoom[i][j+1] || !hasRoom[i+1][j])) {
                                indexY = i;
                                indexX = j;
                                continue;
                            }
                        }
                    }
                } else {
                    for (int i = gridY-1; i > 0; i--) {
                        for (int j = gridX-1; j > 0; j--) {
                            if (hasRoom[i][j] && (!hasRoom[i][j-1] || !hasRoom[i-1][j])) {
                                indexY = i;
                                indexX = j;
                                continue;
                            }
                        }
                    }
                }
            }
        }

        // Pick a random free index
        intPicker.addRange(0, freeInds.size(), true);
        y = intPicker.draw();
        indexY = freeInds[y][0];
        indexX = freeInds[y][1];
        intPicker.empty();

        /*
        // Randomly pick an adjacent space
        intPicker.add({0, 1});
        y = intPicker.draw();
        x = intPicker.draw();
        // Randomise the 1's sign
        intPicker.empty();
        intPicker.add({-1, 1});
        y *= intPicker.draw();
        x *= intPicker.draw();
        // Check for border values and flip y/x if needed
        if ((y == -1) && (indexY < 1)) {
            y = 1;
        } else if ((y == 1) && (indexY >= gridY-1)) {
            y = -1;
        }
        if ((x == -1) && (indexX < 1)) {
            x = 1;
        } else if ((x == 1) && (indexX >= gridX-1)) {
            x = -1;
        }
        // Update index
        indexY += y;
        indexX += x;
        intPicker.empty();
        cout << "New index selected" << endl;
         */

        if (!hasRoom[indexY][indexX]) {
            // Randomise enemies and loot, then create room
            // This implementation is temporary as rooms with both enemies and loot are planned
            intPicker.add({0, 1, 1, 1, 2}); // 0 = empty, 1 = enemy, 2 = loot
            roomType = intPicker.draw();
            cout << "Room type picked" << endl;
            if (roomType == 1) {
                // Randomise enemy
                intPicker.empty();
                intPicker.addRange(0, enemyPoolEnd);
                poolInd = intPicker.draw();
                roomEnemies.push_back(enemyPool[poolInd]);
            }
            if (roomType == 2) {
                // Randomise item
                intPicker.empty();
                intPicker.addRange(0, itemPoolEnd);
                poolInd = intPicker.draw();
                roomItems.push_back(itemPool[poolInd]);
            }
            if (allowExit) {
                // Roll for exit
                // Chance is based on the number of rooms created
                cout << "Rolling for exit creation" << endl;
                nonExitOdds = maxRooms - (numRooms + 1);
                intPicker.empty();
                intPicker.add(0, nonExitOdds);
                intPicker.add(1);
                isExit = intPicker.draw(true);
            }
            addRoom(indexY, indexX, isExit, roomItems, roomEnemies);
            cout << "Room #" << numRooms << " created" << endl;

            // Stop dungeon creation when an exit is created
            if (isExit) {
                cout << "Exit created\nDungeon generation finished" << endl;
                break;
            }
            
            if ((!allowExit) && (numRooms >= minRooms)) {
                cout << "Allowing exit creation" << endl;
                allowExit = true;
            }
            roomEnemies.clear();
            roomItems.clear();
            intPicker.empty();
        } else {
            cout << "Room already created here" << endl;
        }
        freeInds.clear();
    }
}

char Dungeon::handleInput(int numActions, string actions[], vector<char> legalInputs, bool allowStats, bool allowInventory) {
    while (true) {
        string input;
        char selection;
        cout << "Choose an action:\n";
        for (int i = 0; i < numActions; i++) {
            cout << actions[i] << "\n";
        }
        if (allowStats) {
            cout << "[S]tats" << "\n";
            legalInputs.push_back('s');
            ++numActions;
        }
        if (allowInventory) {
            cout << "[I]nventory" << "\n";
            legalInputs.push_back('i');
            ++numActions;
        }
        cin >> input;
        selection = tolower(input.front());
        for (int i = 0; i < numActions; i++) {
            if (selection == legalInputs[i]) {
                return legalInputs[i];
            }
        }
        cout << "Invalid choice.\n";
    }
}

char Dungeon::handleInput(vector<string> actions, vector<char> & legalInputs, bool allowStats, bool allowInventory) {
    string input;
    char selection;
    int numActions = legalInputs.size();
    cout << "Choose an action:\n";
    for (int i = 0; i < numActions; i++) {
        cout << legalInputs[i] << ". " << actions[i] << "\n";
    }
    if (allowStats) {
        cout << "[S]tats" << "\n";
        legalInputs.push_back('s');
        ++numActions;
    }
    if (allowInventory) {
        cout << "[I]nventory" << "\n";
        legalInputs.push_back('i');
        ++numActions;
    }
    while (true) {
        cin >> input;
        selection = tolower(input.front());
        for (int i = 0; i < numActions; i++) {
            if (selection == legalInputs[i]) {
                return legalInputs[i];
            }
        }
        cout << "Invalid choice.\n";
    }
}

void Dungeon::handleFightActions(GameCharacter * enemy) {
    string actions[] = {
        "1. Attack",
        "2. Retreat"
    };
    vector<char> options;
    options.insert(options.end(), {'1', '2'});
    int numActions = options.size();
    while(true) {
        // handle player actions
        char selection;
        selection = handleInput(numActions, actions, options);
        if (selection == 's') {
            player.printStats();
            continue;
        } else if (selection == 'i') {
            player.printInventory();
            continue;
        } else if (selection == '1') {
            int rawDamage = rng(player.minAttack, player.maxAttack);
            int finalDamage = enemy->takeDamage(rawDamage);
            cout << "Your attack does " << finalDamage << " damage.\n";
        } else if (selection == '2') {
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        } else {
            cout << "Invalid choice.\n";
            continue;
        }
        // check if enemy is dead
        if (enemy->checkIsDead()) {
            cout << "You win! You have defeated the " << enemy->name << ".\n";
            cout << "You gained " << enemy->xpYield << " XP.\n";
            player.gainXp(enemy->xpYield);
            player.currentRoom->clearEnemies();
            return;
        }
        // handle enemy actions
        int rawDamage = rng(enemy->minAttack, enemy->maxAttack);
        int finalDamage = player.takeDamage(rawDamage);
        cout << enemy->name << "'s attack does " << finalDamage << " damage.\n";
        if (player.checkIsDead()) {
            return;
        }
        cout << "You now have " << player.currentHealth << " health.\n";
    }
}

void Dungeon::handleRoomWithEnemy(Room * room) {
    GameCharacter enemy = room->enemies.front();
    cout << "You see a " << enemy.name << ".\n";
    string actions[] = {
        "1. Fight the " + enemy.name,
        "2. Retreat to the previous room"
    };
    vector<char> options;
    options.insert(options.end(), {'1', '2'});
    int numActions = options.size();
    while(true) {
        char selection;
        selection = handleInput(numActions, actions, options);
        if (selection == 's') {
            player.printStats();
            continue;
        } else if (selection == 'i') {
            player.printInventory();
            continue;
        } else if (selection == '1') {
            handleFightActions(&enemy);
            return;
        } else if (selection == '2') {
            cout << "You make a hasty retreat.\n";
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void Dungeon::handleLootActions(Room * room) {
    player.lootRoom(room);
    for (int i = 0; i < room->items.size(); i++) {
        cout << "You open the chest and find a " << room->items[i].name
        << " (HP: +" << room->items[i].health
        << ", ATK: +" << room->items[i].minAttack << "-" << room->items[i].maxAttack
        << ", DEF: +" << room->items[i].defence << ")!\n";
    }
    room->clearLoot();
}

void Dungeon::handleRoomWithChest(Room * room) {
    cout << "You see a large chest in the middle of the room.\n";
    string actions[] = {
        "1. Loot the chest",
        "2. Move to another room"
    };
    vector<char> options;
    options.insert(options.end(), {'1', '2'});
    int numActions = options.size();
    while(true) {
        char selection;
        selection = handleInput(numActions, actions, options);
        if (selection == 's') {
            player.printStats();
            continue;
        } else if (selection == 'i') {
            player.printInventory();
            continue;
        } else if (selection == '1') {
            handleLootActions(room);
            return;
        } else if (selection == '2') {
            handleMovementActions(player.currentRoom);
            return;    
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void Dungeon::handleEmptyRoom(Room * room) {
    cout << "This room seems to be empty.\n";
    string actions[] = {
        "1. Move to another room"
    };
    vector<char> options;
    options.push_back('1');
    int numActions = options.size();
    while(true) {
        char selection;
        selection = handleInput(numActions, actions, options);
        if (selection == 's') {
            player.printStats();
            continue;
        } else if (selection == 'i') {
            player.printInventory();
            continue;
        } else if (selection == '1') {
            handleMovementActions(player.currentRoom);
            return;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void Dungeon::enterRoom(Room * room) {
    if (room->enemies.size() != 0) {
        // handle room with enemy
        handleRoomWithEnemy(room);
    } else if (room->items.size() != 0) {
        // handle room with chest
        handleRoomWithChest(room);
    } else {
        // handle empty room
        handleEmptyRoom(room);
    }
}

void Dungeon::handleMovementActions(Room * room) {
    string allActions[4] = {"Move north", "Move west", "Move south", "Move east"};
    int allMovements[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    vector<bool> availableRooms;
    vector<string> actions;
    vector<vector<int>> movements;
    vector<char> options;
    char selection;
    int optionASCII = 48;   // 49 is the ASCII code for 1

    findAdjacentRooms(true, room->y, room->x, availableRooms);
    for (int i = 0; i < 4; i++) {
        if (availableRooms[i]) {
            actions.push_back(allActions[i]);
            movements.push_back({allMovements[i][0], allMovements[i][1]});
            ++optionASCII;
            options.push_back(optionASCII);
        }
    }
    int numOptions = options.size();
    selection = handleInput(actions, options, false, false);
    for (int i = 0; i < numOptions; i++) {
        if (selection == options[i]) {
            int y = room->y + movements[i][0];
            int x = room->x + movements[i][1];
            player.changeRooms(&rooms[y][x]);
            cout << "You head " << actions[i].substr(5) << ".\n";
            return;
        }
    }
}

// Old movement handling from the course, kept for the sheer contrast
/*
void Dungeon::handleMovementActions(Room * room) {
    while(true) {
        if (room->pos == 0) {
            string actions[] = {"1. Move right", "2. Move down"};
            vector<char> options;
            options.insert(options.end(), {'1', '2'});
            int numActions = options.size();
            char selection;
            selection = handleInput(numActions, actions, options, false, false);
            if (selection == '1') {
                player.changeRooms(&rooms[1]);
                return;
            } else if (selection == '2') {
                player.changeRooms(&rooms[2]);
                return;
            } else {
                cout << "Invalid choice.\n";
            }
        } else if (room->pos == 1) {
            string actions[] = {"1. Move left"};
            vector<char> options;
            options.push_back('1');
            int numActions = options.size();
            char selection;
            selection = handleInput(numActions, actions, options, false, false);
            if (selection == '1') {
                player.changeRooms(&rooms[0]);
                return;
            } else {
                cout << "Invalid choice.\n";
            }
        } else if (room->pos == 2) {
            string actions[] = {"1. Move up", "2. Move right"};
            vector<char> options;
            options.insert(options.end(), {'1', '2'});
            int numActions = options.size();
            char selection;
            selection = handleInput(numActions, actions, options, false, false);
            if (selection == '1') {
                player.changeRooms(&rooms[0]);
                return;
            } else if (selection == '2') {
                player.changeRooms(&rooms[3]);
                return;
            } else {
                cout << "Invalid choice.\n";
            }
        } else {
            string actions[] = {"1. Move left"};
            vector<char> options;
            options.push_back('1');
            int numActions = options.size();
            char selection;
            selection = handleInput(numActions, actions, options, false, false);
            if (selection == '1') {
                player.changeRooms(&rooms[2]);
                return;
            } else {
                cout << "Invalid choice.\n";
            }
        }
    }
}
 */

int Dungeon::performEndGameLogic() {
    string actions[] = {"1. Yes", "2. No"};
    while(true) {
        vector<char> options;
        options.insert(options.end(), {'1', '2'});
        int numActions = options.size();
        char selection;
        selection = handleInput(numActions, actions, options, false, false);
        if (selection == '1') {
            return 1;
        } else if (selection == '2') {
            return 0;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

int Dungeon::runDungeon() {
    cout << "Welcome to the dungeon! Inside you will find treasure but also enemies. Enter at your peril!\n";
    player.currentRoom = &rooms[startY][startX];
    player.previousRoom = &rooms[startY][startX];
    while(true) {
        // enter room
        enterRoom(player.currentRoom);
        // check if dead
        if (player.checkIsDead()) {
            cout << "Game over! Try again?\n";
            return performEndGameLogic();
        } else {
            if (player.currentRoom->isExit) {
                if (player.currentRoom->enemies.size() == 0) {
                    cout << "You win! Play again?\n";
                    return performEndGameLogic();
                }
            }
        }
    }
}
