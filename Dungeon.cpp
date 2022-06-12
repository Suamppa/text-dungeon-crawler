#include "Dungeon.h"

Dungeon::Dungeon(Player * p)
{
    player = p;
    depth = 0;
    revealMap = false;
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

void Dungeon::addRoom(int y, int x, vector<Item *> & items, vector<GameCharacter> enemies, bool isExit) {
    if (items.size()) cout << "In addRoom: " << items[0]->getInfoStr() << '\n';
    rooms[y][x] = new Room(y, x, isExit, items, enemies);
    if (items.size()) cout << "After construction: " << rooms[y][x]->items.at(0)->getInfoStr() << '\n';
    map[y][x] = '0';
}

void Dungeon::generateDungeon(int gridX, int gridY, int minRooms, int maxRooms) {
    // 1. Create starting room
    // 2. Pick an adjacent space to handle next
    // 3. Check if the space has a room
    // 4. Generate a room in that space if empty
    // 5. Repeat steps 2-4 up to until max number of rooms is reached

    cout << "Starting dungeon creation..." << endl;
    if (numRooms) {
        // Make sure the allocated memory is freed
        for (int i = 0; i < dungeonHeight; i++) {
            for (int j = 0; j < dungeonWidth; j++) {
                rooms[i][j]->~Room();
                delete rooms[i][j];
            }
        }
        rooms.clear();
    }

    ++depth;
    int gridSize = gridX * gridY;
    numRooms = 0;
    // minRooms and maxRooms are the minimum and maximum number of rooms *allowed*,
    // but they are not necessarily the final amounts
    maxRooms = ((maxRooms < gridSize) && (maxRooms > 0)) ? maxRooms : gridSize;

    // Create a 2D vector of the dungeon level
    //// hasRoom-vektorin vaihto deque-tyyppiin?
    hasRoom = vector<vector<bool>>(gridY, vector<bool>(gridX, false));
    // Choose the index of the starting room
    int indexY = rng(0, gridY-1);
    int indexX = rng(0, gridX-1);
    startY = indexY;
    startX = indexX;
    hasRoom[startY][startX] = true;
    ++numRooms;
    cout << "Starting room selected" << endl;
    
    // Enemy creation and selection can be made fancier, this is just a mockup
    deque<Item *> noItems = deque<Item *>();
    GameCharacter littleMonster = GameCharacter("Little Monster", 50, 15, 20, 5, 25, noItems);
    GameCharacter bigMonster = GameCharacter("Big Monster", 100, 25, 30, 10, 50, noItems);
    Weapon sword = Weapon("Sword", 20, 25, 1);
    Weapon shield = Weapon("Shield", 0, 0, 5);
    Armour ironHelmet = Armour("Iron helmet", 2, 2, 't');
    cout << "Enemy and item pools created" << endl;

    ShuffleBag<int> intPicker;
    vector<GameCharacter> enemyPool = {littleMonster, littleMonster, littleMonster, bigMonster};
    int enemyPoolEnd = enemyPool.size() - 1;
    vector<Item *> itemPool = {&sword, &shield, &ironHelmet};
    // vector<Item *> itemPool = {static_cast<Weapon *>(&sword), static_cast<Weapon *>(&shield), static_cast<Armour *>(&ironHelmet)};
    cout << itemPool[0]->getInfoStr() << '\n';
    int itemPoolEnd = itemPool.size() - 1;
    int y, x, roomType, poolInd, nonExitOdds;
    bool allowExit = false;
    bool isExit = false;
    vector<GameCharacter> roomEnemies;
    vector<Item *> roomItems;
    // A vector for holding the indices of available adjacent free spaces
    vector<vector<int>> freeInds;

    // Main generation loop
    cout << "Starting layout generation" << endl;
    while (numRooms < maxRooms) {
        cout << "Picking a new index" << endl;
        // Check adjacent indices for free space
        findAdjacentRooms(false, indexY, indexX, freeInds);

        // If no adjacent spaces are free, check diagonals
        if (freeInds.size() < 1) {
            findAdjacentRooms(false, indexY, indexX, freeInds, true);
        }

        // If a free space is still not found, create an exit if allowed or find a free adjacent space elsewhere
        if (freeInds.size() < 1) {
            if (allowExit) {
                if (!hasRoom[indexY][indexX]) hasRoom[indexY][indexX] = true;
                exitY = indexY;
                exitX = indexX;
                cout << "Exit selected\nDungeon layout finished" << endl;
                break;
            } else {
                cout << "No free space, finding a free index" << endl;
                bool indFound = false;
                for (int i = 0; i < gridY-1; i++) {
                    for (int j = 0; j < gridX-1; j++) {
                        if (hasRoom[i][j] && (!hasRoom[i][j+1] || !hasRoom[i+1][j])) {
                            indexY = i;
                            indexX = j;
                            indFound = true;
                            break;
                        }
                    }
                    if (indFound) break;
                }
                if (indFound) continue;
                for (int i = gridY-1; i > 0; i--) {
                    for (int j = gridX-1; j > 0; j--) {
                        if (hasRoom[i][j] && (!hasRoom[i][j-1] || !hasRoom[i-1][j])) {
                            indexY = i;
                            indexX = j;
                            indFound = true;
                            break;
                        }
                    }
                    if (indFound) break;
                }
                if (indFound) continue;
                else {
                    cout << "Dungeon generation failed" << endl;
                    return;
                }   // This statement should not be reachable
            }
        }

        // Pick a random free index and flag it for room creation (add to hasRoom)
        intPicker.addRange(0, freeInds.size(), true);
        y = intPicker.draw();
        indexY = freeInds[y][0];
        indexX = freeInds[y][1];
        hasRoom[indexY][indexX] = true;
        ++numRooms;
        cout << "Room #" << numRooms << " placed" << endl;

        if (allowExit) {
            // Roll for exit
            // Chance is based on the number of rooms created
            cout << "Rolling for exit creation" << endl;
            nonExitOdds = maxRooms - numRooms;
            intPicker.empty();
            intPicker.add(0, nonExitOdds);
            intPicker.add(1);
            isExit = intPicker.draw(true);
        }
        // Stop layout creation when an exit is set
        if (isExit) {
            exitY = indexY;
            exitX = indexX;
            cout << "Exit selected\nDungeon layout finished" << endl;
            break;
        }
        
        if ((!allowExit) && (numRooms >= minRooms)) {
            cout << "Allowing exit creation" << endl;
            allowExit = true;
        }
        intPicker.empty();
        freeInds.clear();
    }

    // Print the room map for testing
    for (int i = 0; i < gridY; i++) {
        for (int j = 0; j < gridX; j++) {
            if (i == startY && j == startX) {
                cout << "[" << hasRoom[i][j] << "]";
                continue;
            }
            if (startX == 0 && j == 0) cout << " ";
            cout << hasRoom[i][j];
            if (!(i == startY && j == startX - 1)) cout << " ";
        }
        cout << endl;
    }

    // Trim the grid to fit just the actual rooms
    bool saveRow;
    int minX = gridX - 1;
    int maxX = 0;
    cout << "Original dungeon size: " << gridY << 'x' << gridX << '\n';
    cout << "Starting dungeon trimming" << endl;
    for (int i = gridY-1; i >= 0; i--) {
        saveRow = false;
        for (int j = gridX-1; j >= 0; j--) {
            if (!saveRow && hasRoom[i][j]) {
                cout << "Room found, saving row" << endl;
                saveRow = true;
                maxX = max(j + 1, maxX);
                cout << "maxX changed to " << maxX << endl;
            } else if (saveRow && hasRoom[i][j]) {
                minX = min(j, minX);
                cout << "minX changed to " << minX << endl;
            }
        }
        if (!saveRow) {
            cout << "Deleting empty row" << endl;
            hasRoom.erase(hasRoom.begin() + i);
            // rooms.erase(rooms.begin() + i);
            // map.erase(map.begin() + i);
            // Correct start and exit locations if necessary
            if (i < startY) --startY;
            if (i < exitY) --exitY;
        }
    }
    dungeonHeight = hasRoom.size();
    if ((minX != 0) || (maxX < gridX)) {
        cout << "Trimming width" << '\n';
        cout << "minX = " << minX << "\nmaxX = " << maxX << endl;
        for (int i = 0; i < dungeonHeight; i++) {
            if (maxX < gridX - 1) {
                hasRoom[i].erase(hasRoom[i].begin()+maxX, hasRoom[i].end());
                // rooms[i].erase(rooms[i].begin()+maxX, rooms[i].end());
                // map[i].erase(map[i].begin()+maxX, map[i].end());
            } else if (maxX == gridX - 1) {
                hasRoom[i].erase(hasRoom[i].begin()+maxX);
                // rooms[i].erase(rooms[i].begin()+maxX);
                // map[i].erase(map[i].begin()+maxX);
            }
            if (minX > 0) {
                hasRoom[i].erase(hasRoom[i].begin(), hasRoom[i].begin()+minX);
                // rooms[i].erase(rooms[i].begin(), rooms[i].begin()+minX);
                // map[i].erase(map[i].begin(), map[i].begin()+minX);
            }
        }
        // Correct start and exit locations
        startX -= minX;
        exitX -= minX;
    }
    dungeonWidth = hasRoom[0].size();
    cout << "Trim finished" << endl;

    // Print the room map for testing
    for (int i = 0; i < dungeonHeight; i++) {
        for (int j = 0; j < dungeonWidth; j++) {
            if (i == startY && j == startX) {
                cout << "[" << hasRoom[i][j] << "]";
                continue;
            }
            if (startX == 0 && j == 0) cout << " ";
            cout << hasRoom[i][j];
            if (!(i == startY && j == startX - 1)) cout << " ";
        }
        cout << endl;
    }

    // Create the actual rooms
    cout << "Starting room generation" << endl;
    Room emptyRoom = Room();
    rooms = vector<vector<Room *>>(dungeonHeight, vector<Room *>(dungeonWidth, &emptyRoom));
    map = vector<vector<char>>(dungeonHeight, vector<char>(dungeonWidth, ' '));
    for (int i = 0; i < dungeonHeight; i++) {
        for (int j = 0; j < dungeonWidth; j++) {
            if (hasRoom[i][j]) {
                // Randomise enemies and loot, then create room
                // This implementation is temporary as rooms with both enemies and loot are planned
                // Starting room is always empty
                if ((i == startY) && (j == startX)) roomType = 0;
                else {
                    // intPicker.add({0, 1, 1, 1, 2}); // 0 = empty, 1 = enemy, 2 = loot
                    intPicker.add(2);
                    roomType = intPicker.draw();
                    intPicker.empty();
                }
                cout << "Room [" << i << ',' << j << "] type picked" << endl;
                if (roomType == 1) {
                    // Randomise enemy
                    intPicker.addRange(0, enemyPoolEnd);
                    poolInd = intPicker.draw();
                    roomEnemies.push_back(enemyPool[poolInd]);
                }
                if (roomType == 2) {
                    // Randomise item
                    intPicker.addRange(0, itemPoolEnd);
                    poolInd = intPicker.draw();
                    char equipType = itemPool[poolInd]->getEquipType();
                    cout << equipType << '\n';
                    if (equipType == ' ') roomItems.push_back(new Item(*itemPool[poolInd]));
                    else if (equipType == 'w') {
                        Weapon * pWeapon = static_cast<Weapon *>(itemPool[poolInd]);
                        roomItems.push_back(new Weapon(*pWeapon));
                        cout << roomItems[0]->getInfoStr() << '\n';
                    } else {
                        Armour * pArmour = static_cast<Armour *>(itemPool[poolInd]);
                        roomItems.push_back(new Armour(*pArmour));
                        cout << roomItems[0]->getInfoStr() << '\n';
                    }
                }
                addRoom(i, j, roomItems, roomEnemies);
                cout << "Room added to [" << i << ',' << j << ']' << endl;

                if ((i == exitY) && (j == exitX)) {
                    rooms[i][j]->isExit = true;
                    map[i][j] = 'C';
                }

                roomEnemies.clear();
                // int numRoomItems = roomItems.size();
                // for (int i = 0; i < numRoomItems; i++) delete roomItems[i];
                roomItems.clear();
                intPicker.empty();
            }
        }
    }

    cout << "Setting player position" << endl;
    player->currentRoom = rooms[startY][startX];
    player->previousRoom = rooms[startY][startX];
    player->currentRoom->visited = true;
    map[startY][startX] = 'O';
    cout << "Dungeon generation finished" << endl;
}

char Dungeon::handleInput(
    int numActions, string actions[], vector<char> legalInputs,
    bool allowStats, bool allowInventory, string header
) {
    string input;
    char selection;
    cout << header << "\n";
    for (int i = 0; i < numActions; i++) {
        cout << actions[i] << "\n";
    }
    if (allowStats) {
        cout << "[S]tats\n";
        legalInputs.push_back('s');
        ++numActions;
    }
    if (allowInventory) {
        cout << "[I]nventory\n";
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

char Dungeon::handleInput(
    vector<string> actions, vector<char> & legalInputs, bool allowStats,
    bool allowInventory, bool allowCancel, string header
) {
    string input;
    char selection;
    int numActions = legalInputs.size();
    cout << header << "\n";
    for (int i = 0; i < numActions; i++) {
        cout << legalInputs[i] << ". " << actions[i] << "\n";
    }
    if (allowStats) {
        cout << "[S]tats\n";
        legalInputs.push_back('s');
        ++numActions;
    }
    if (allowInventory) {
        cout << "[I]nventory\n";
        legalInputs.push_back('i');
        ++numActions;
    }
    if (allowCancel) {
        cout << "[C]ancel\n";
        legalInputs.push_back('c');
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
            player->printStats();
            continue;
        } else if (selection == 'i') {
            player->printInventory();
            continue;
        } else if (selection == '1') {
            int rawDamage = rng(player->getMinAttack(), player->getMaxAttack());
            int finalDamage = enemy->takeDamage(rawDamage);
            cout << "Your attack does " << finalDamage << " damage.\n";
        } else if (selection == '2') {
            player->changeRooms(player->previousRoom);
            enterRoom(player->currentRoom);
            return;
        } else {
            cout << "Invalid choice.\n";
            continue;
        }
        // check if enemy is dead
        if (enemy->checkIsDead()) {
            cout << "You win! You have defeated the " << enemy->name << ".\n";
            cout << "You gained " << enemy->xpYield << " XP.\n";
            player->gainXp(enemy->xpYield);
            player->currentRoom->clearEnemies();
            return;
        }
        // handle enemy actions
        int rawDamage = rng(enemy->getMinAttack(), enemy->getMaxAttack());
        int finalDamage = player->takeDamage(rawDamage);
        cout << enemy->name << "'s attack does " << finalDamage << " damage.\n";
        if (player->checkIsDead()) {
            return;
        }
        cout << "You now have " << player->currentHealth << " health.\n";
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
            player->printStats();
            continue;
        } else if (selection == 'i') {
            player->accessInventory();
            continue;
        } else if (selection == '1') {
            handleFightActions(&enemy);
            return;
        } else if (selection == '2') {
            cout << "You make a hasty retreat.\n";
            player->changeRooms(player->previousRoom);
            enterRoom(player->currentRoom);
            return;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void Dungeon::handleLootActions(Room * room) {
    player->lootRoom(room);
    for (int i = 0; i < room->items.size(); i++) {
        cout << "You open the chest and find a " << room->items[i]->getInfoStr() << "!\n";
    }
    room->clearLoot();
}

void Dungeon::handleRoomWithChest(Room * room) {
    int numItems = room->items.size();
    cout << "In Dungeon::handleRoomWithChest: \n";
    for (int i = 0; i < numItems; i++) cout << room->items[i]->getInfoStr() << '\n';

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
            player->printStats();
            continue;
        } else if (selection == 'i') {
            player->accessInventory();
            continue;
        } else if (selection == '1') {
            handleLootActions(room);
            return;
        } else if (selection == '2') {
            handleMovementActions(player->currentRoom);
            return;    
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void Dungeon::handleExitRoom(Room * room) {
    cout << "There's a set of stairs leading deeper downwards.\n";
    string actions[] = {
        "1. Descend",
        "2. Move to another room"
    };
    vector<char> options;
    options.insert(options.end(), {'1', '2'});
    int numActions = options.size();
    while(true) {
        char selection;
        selection = handleInput(numActions, actions, options);
        if (selection == 's') {
            player->printStats();
            continue;
        } else if (selection == 'i') {
            player->accessInventory();
            continue;
        } else if (selection == '1') {
            int width, height, minRooms, maxRooms;
            int modifier = depth + player->level;
            width = rng(modifier + 2, modifier + 6);
            height = rng(modifier + 2, modifier + 6);
            minRooms = width * height / (modifier * 2);
            maxRooms = width * height / modifier;

            generateDungeon(width, height, minRooms, maxRooms);

            // Print the dungeon map for testing
            for (int i = 0; i < dungeonHeight; i++) {
                for (int j = 0; j < dungeonWidth; j++) {
                    cout << map[i][j] << ' ';
                }
                cout << endl;
            }
            
            player->currentHealth = player->getMaxHealth();
            cout << "You descend deeper into the dungeon.\n";
            return;
        } else if (selection == '2') {
            handleMovementActions(player->currentRoom);
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
            player->printStats();
            continue;
        } else if (selection == 'i') {
            player->accessInventory();
            continue;
        } else if (selection == '1') {
            handleMovementActions(player->currentRoom);
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
    } else if (room->isExit) {
        handleExitRoom(room);
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
    vector<vector<int>> adjacentRooms;
    vector<char> options;
    char selection;
    int optionASCII = 48;   // 48 is the ASCII code for 0

    findAdjacentRooms(true, room->y, room->x, availableRooms);
    for (int i = 0; i < 4; i++) {
        if (availableRooms[i]) {
            actions.push_back(allActions[i]);
            adjacentRooms.push_back({room->y + allMovements[i][0], room->x + allMovements[i][1]});
            ++optionASCII;
            options.push_back(optionASCII);
        }
    }
    int numOptions = options.size();
    printMap(room, adjacentRooms);
    selection = handleInput(actions, options, false, false, true);
    if (selection == 'c') return;
    for (int i = 0; i < numOptions; i++) {
        if (selection == options[i]) {
            player->changeRooms(rooms[adjacentRooms[i][0]][adjacentRooms[i][1]]);
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

void Dungeon::printMap(Room * room, vector<vector<int>> & adjacentRooms) {
    string mapToPrint;
    bool drawn;
    for (int i = 0; i < dungeonHeight; i++) {
        for (int j = 0; j < dungeonWidth; j++) {
            drawn = false;
            if (hasRoom[i][j]) {
                if (rooms[i][j] == room) {
                    mapToPrint.push_back('X');  // Player's current position
                    drawn = true;
                }
                else if (revealMap || rooms[i][j]->visited) {
                    mapToPrint.push_back(map[i][j]);  // A visited room
                    drawn = true;
                }
                else {
                    for (vector<vector<int>>::iterator it = adjacentRooms.begin(); it != adjacentRooms.end(); it++) {
                        if ((it->at(0) == i) && (it->at(1) == j)) {
                            mapToPrint.push_back('o');  // An adjacent, not yet visited room
                            drawn = true;
                            break;
                        }
                    }
                }
            }
            if (!drawn) mapToPrint.push_back(' ');
            // A space between all characters looks cleaner
            mapToPrint.push_back(' ');
        }
        mapToPrint.push_back('\n');
    }
    cout << mapToPrint;
}

bool Dungeon::performEndGameLogic() {
    string actions[] = {"1. Yes", "2. No"};
    while(true) {
        vector<char> options;
        options.insert(options.end(), {'1', '2'});
        int numActions = options.size();
        char selection;
        selection = handleInput(numActions, actions, options, false, false);
        if (selection == '1') {
            return true;
        } else if (selection == '2') {
            return false;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

int Dungeon::runDungeon() {
    int width, height, minRooms, maxRooms;
    width = rng(5, 9);
    height = rng(5, 9);
    minRooms = width * height / 6;
    maxRooms = width * height / 4;

    generateDungeon(width, height, minRooms, maxRooms);

    int ey, ex;

    // Print the dungeon map for testing
    for (int i = 0; i < dungeonHeight; i++) {
        for (int j = 0; j < dungeonWidth; j++) {
            cout << map[i][j] << ' ';

            if (hasRoom[i][j] && i != startY && j != startX) {
                ey = i;
                ex = j;
            }

        }
        cout << endl;
    }

    cout << "Outside of the scope of generateDungeon\nExample item at " << ey << ", " << ex << ":\n";
    cout << rooms[ey][ex]->items.at(0)->getInfoStr() << '\n';

    cout << "You find yourself in an empty room. You have no idea how you got here.\n";
    while(true) {
        // enter room
        enterRoom(player->currentRoom);
        // check if dead
        if (player->checkIsDead()) {
            cout << "You have died! Try again?\n";
            return performEndGameLogic();
        }
    }
}
