#include "Player.h"
#include "RNG.h"
#include <stdexcept>

#ifndef DUNGEON_H
#define DUNGEON_H

using namespace std;

class Dungeon
{
public:
    Player player;
    // Room rooms[4];
    // Holds the actual room data
    vector<vector<Room>> rooms;
    // Grid representing accessible rooms
    vector<vector<bool>> hasRoom;
    int numRooms, startY, startX;
    Dungeon(Player);
    // Checks if the argument 2D vector's index at (y, x) is reachable and returns a corresponding boolean value
    template <typename T>
    bool check2DBounds(vector<vector<T>> &, int, int);
    // Checks the adjacent indices of hasRoom counter-clockwise starting from iy-1 (and ix-1 for diagonals)
    // for booleans equal to isRoom and adds them to the end of the 2D vector saveToVec
    void findAdjacentRooms(bool, int, int, vector<vector<int>> &, bool=false);
    // Checks the adjacent indices of hasRoom counter-clockwise starting from iy-1 for booleans equal to isRoom
    // and adds 4 boolean values to saveToVec corresponding to the match
    void findAdjacentRooms(bool, int, int, vector<bool> &);
    void addRoom(int, int, bool, vector<Item> = vector<Item>(), vector<GameCharacter> = vector<GameCharacter>());
    // gridX and gridY must be greater than 1
    void generateDungeon(int, int, int, int);
    int runDungeon();
    void enterRoom(Room *);
    char handleInput(int, string[], vector<char>, bool=true, bool=true);
    char handleInput(vector<string>, vector<char> &, bool=true, bool=true);
    void handleEmptyRoom(Room *);
    void handleRoomWithChest(Room *);
    void handleRoomWithEnemy(Room *);
    void handleLootActions(Room *);
    void handleFightActions(GameCharacter *);
    void handleMovementActions(Room *);
    // void printActions(int, string[], bool=true, bool=true);
    int performEndGameLogic();
};

#endif
