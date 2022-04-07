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

void Dungeon::generateDungeon(int gridX, int gridY) {
    // 1. Create starting room
    // 2. Pick an adjacent space to handle next
    // 3. Check if the space has a room
    // 4. Roll for room generation in that space if empty
    // 5. Repeat steps 2-4 until max number of rooms is reached

    // Create a 2D vector of the dungeon level
    vector<vector<bool>> dungeon(gridY, vector<bool>(gridX, 0));
    // Choose the index of the starting room
    int startY = rng(0, gridY-1);
    int startX = rng(0, gridX-1);
    // call first room constructor

    // Randomly pick an adjacent space
    ShuffleBag<int> shuffleBag({0, 1});
    int y, x;
    y = shuffleBag.draw();
    x = shuffleBag.draw();
    // Randomise the 1's sign
    shuffleBag.empty();
    shuffleBag.add({-1, 1});
    y *= shuffleBag.draw();
    x *= shuffleBag.draw();

    for (int i = 0; i < gridY; i++) {
        for (int j = 0; j < gridX; j++) {
            // create rooms
        }
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
            numActions++;
        }
        if (allowInventory) {
            cout << "[I]nventory" << "\n";
            legalInputs.push_back('i');
            numActions++;
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
    cout << "You enter the room and see a " << enemy.name << ".\n";
    string actions[] = {
        "1. Fight the " + enemy.name,
        "2. Go back to the previous room"
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
    cout << "You enter the room and see a large chest in the middle.\n";
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
            return;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void Dungeon::handleEmptyRoom(Room * room) {
    cout << "You enter the room but it is empty.\n";
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

// ugly, can it be improved?
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
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
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
        // movement options
        handleMovementActions(player.currentRoom);
    }
}
