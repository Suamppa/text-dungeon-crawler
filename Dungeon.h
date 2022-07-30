#ifndef DUNGEON_H
#define DUNGEON_H

#include "Player.h"
#include "RNG.h"
#include <stdexcept>

using namespace std;

class Dungeon
{
public:
    Player * player;
    // Holds the actual room data
    vector<vector<unique_ptr<Room>>> rooms;
    // Grid representing accessible rooms
    vector<vector<bool>> hasRoom;
    // Map of the dungeon, rooms represented by characters
    vector<vector<char>> map;
    int numRooms, startY, startX, exitY, exitX, depth, dungeonHeight, dungeonWidth;
    bool revealMap;
    Dungeon(Player &);
    // Checks if the argument 2D vector's index at (y, x) is reachable and returns a corresponding boolean value
    template <typename T>
    bool check2DBounds(vector<vector<T>> &, int, int);
    // Checks the adjacent indices of hasRoom counter-clockwise starting from iy-1 (and ix-1 for diagonals)
    // for booleans equal to isRoom and adds them to the end of the 2D vector saveToVec
    void findAdjacentRooms(bool, int, int, vector<vector<int>> &, bool=false);
    // Checks the adjacent indices of hasRoom counter-clockwise starting from iy-1 for booleans equal to isRoom
    // and adds 4 boolean values to saveToVec corresponding to the match
    void findAdjacentRooms(bool, int, int, vector<bool> &);
    // Adds a new Room object at position y,x on rooms and the character '0' to map
    void addRoom(int, int, vector<shared_ptr<Item>> &, vector<GameCharacter> = vector<GameCharacter>(), bool=false);
    // gridX and gridY must be greater than 1
    void generateDungeon(int, int, int, int);
    // Main gameplay loop
    int runDungeon();
    // Checks the argument room's type and calls the relevant function
    void enterRoom(Room *);
    // Handles user input. Takes an array of strings for printing.
    char handleInput(int, string[], vector<char>, bool=true, bool=true, string="Choose an action:");
    // Handles user input. Takes a vector of strings for printing and
    // automatically labels the argument actions during printing with legalInputs.
    char handleInput(vector<string>, vector<char> &, bool=true, bool=true, bool=false, string="Choose an action:");
    // Logic for an empty room
    void handleEmptyRoom(Room *);
    // Logic for a room with a chest
    void handleRoomWithChest(Room *);
    // Logic for a room with an enemy
    void handleRoomWithEnemy(Room *);
    // Logic for a room with an exit. If the player chooses to descend, a new dungeon (level) is generated.
    void handleExitRoom(Room *);
    // Logic for looting (like opening a chest)
    void handleLootActions(Room *);
    // Fight handler
    void handleFightActions(GameCharacter *);
    // Movement handler. Uses findAdjacentRooms to dynamically find possible rooms to move to and
    // prints the options and handles user input with handleInput. Updates player position based on input.
    void handleMovementActions(Room *);
    // Prints the player map. Only visited and adjacent rooms are revealed.
    // adjacentRooms expects a 2D vector of adjacent room indices.
    void printMap(Room *, vector<vector<int>> &);
    // Upon player death, handles whether a new game is started or not based on user input
    bool performEndGameLogic();
    // ~Dungeon();
};

#endif
