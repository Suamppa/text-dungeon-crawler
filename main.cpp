#include "Dungeon.cpp"
#include "Player.cpp"
#include "GameCharacter.cpp"
#include "Item.cpp"
#include "Room.cpp"
#include "RNG.cpp"
#include <iostream>

/*
 TODO:
 x ShuffleBag-luonti lukuvälille
 x Enemy- ja Item-poolit käyttämään intPickeriä rangella, jos haluat
 x Luonnissa varattujen ja kokeiltujen indeksien poissulkeminen uuden valinnasta jumin estämiseksi
 x Navigointi kuntoon
 x Kartan printtaus (ainakin testiksi)
 - "You enter the room..." viestit toistuvat turhan usein (vihollisen voittamisen jälkeen jne.)
 - HP:n palautuminen
 - Estä vaikean vihollisen lisääminen ensimmäisiin huoneisiin
 - Kunnon inventory
 */

int main()
{
    // Main loop
    while (true) {
        // Set up the player
        cout << "Welcome to our dungeon crawler! What is your name?\n";
        string playerName;
        cin >> playerName;
        Player player = Player(playerName, 1, 0, 50, 100, 15, 20, 10);

        /*
        // Set up the first room
        Room firstRoom = Room(0, false, vector<Item>(), vector<GameCharacter>());

        // Set up the second room
        Item sword = Item("Sword", 0, 20, 25, 5);
        vector<Item> secondRoomItems;
        secondRoomItems.push_back(sword);
        Room secondRoom = Room(1, false, secondRoomItems, vector<GameCharacter>());

        // Set up the third room
        GameCharacter firstEnemy = GameCharacter("Little Monster", 50, 15, 20, 5, 25);
        vector<GameCharacter> thirdRoomEnemies;
        thirdRoomEnemies.push_back(firstEnemy);
        Room thirdRoom = Room(2, false, vector<Item>(), thirdRoomEnemies);

        // Set up the fourth room
        GameCharacter secondEnemy = GameCharacter("Big Monster", 100, 25, 30, 10, 50);
        vector<GameCharacter> fourthRoomEnemies;
        fourthRoomEnemies.push_back(secondEnemy);
        Room fourthRoom = Room(3, true, vector<Item>(), fourthRoomEnemies);

        Dungeon dungeon = Dungeon(player);
        dungeon.rooms[0] = firstRoom;
        dungeon.rooms[1] = secondRoom;
        dungeon.rooms[2] = thirdRoom;
        dungeon.rooms[3] = fourthRoom;
         */

        Dungeon dungeon = Dungeon(player);
        dungeon.generateDungeon(10, 10, 4, 20);

        // Print the room map for testing
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == dungeon.startY && j == dungeon.startX) {
                    cout << "[" << dungeon.hasRoom[i][j] << "]";
                    continue;
                }
                cout << dungeon.hasRoom[i][j];
                if (!(i == dungeon.startY && j == dungeon.startX - 1)) cout << " ";
            }
            cout << endl;
        }

        int result = dungeon.runDungeon();
        if (result == 0) {
            cout << "Goodbye!\n";
            break;
        }
    }
}
