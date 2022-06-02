#include "Armour.cpp"
#include "Dungeon.cpp"
#include "GameCharacter.cpp"
#include "Item.cpp"
#include "Player.cpp"
#include "RNG.cpp"
#include "Room.cpp"
#include "Weapon.cpp"
#include <deque>
#include <iostream>

/*
 TODO:
 x ShuffleBag-luonti lukuvälille
 x Enemy- ja Item-poolit käyttämään intPickeriä rangella, jos haluat
 x Luonnissa varattujen ja kokeiltujen indeksien poissulkeminen uuden valinnasta jumin estämiseksi
 x Navigointi kuntoon
 x Kartan printtaus (ainakin testiksi)
 x "You enter the room..." viestit toistuvat turhan usein (vihollisen voittamisen jälkeen jne.)
 x Karttaominaisuus pelaajalle
 - Dungeon-vektoreiden vaihto deque-tyyppiin?
 - Iteraattorit käyttöön
 - HP:n palautuminen
 - Estä vaikean vihollisen lisääminen ensimmäisiin huoneisiin
 - Kunnon inventory
 */

int main()
{
    // Main loop
    while (true) {
        // Set up the player
        cout << "The dungeon is dark and full of horrors. What is your name?\n";
        string playerName;
        cin >> playerName;
        Weapon crackedDagger = Weapon("Cracked dagger", 1, 5, 0);
        Weapon plank = Weapon("Wooden plank", 0, 0, 1);
        Armour shirt = Armour("Shirt", 0, 1, 'u');
        // Tämä toteutus tarkoittaa, että jokainen esine on uniikki,
        // eikä samaa esinettä voi käsitellä kahtena erillisenä kopiona.
        deque<Item *> playerItems = deque<Item *>({&crackedDagger, &plank, &shirt});
        Player player = Player(playerName, 1, 0, 50, 100, 15, 20, 10, playerItems);

        /* The original setup
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

        Dungeon dungeon = Dungeon(&player);

        int result = dungeon.runDungeon();
        if (result == 0) {
            cout << "Thank you for playing!\n";
            break;
        }
    }
}
