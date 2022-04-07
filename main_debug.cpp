/**********************************************
 A TESTING ENVIRONMENT FOR PROTOTYPING FEATURES
 **********************************************/

// #include "Dungeon.cpp"
// #include "Player.cpp"
// #include "GameCharacter.cpp"
// #include "Item.cpp"
// #include "Room.cpp"
#include "RNG.cpp"
#include <iostream>

int main() {
    ShuffleBag<int> box({1, 2, 3, 4, 5});
    // box.add({1, 2, 3, 4, 5});
    cout << "First five:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << box.draw(true) << endl;
    }
    box.add({6, 7, 8, 9, 10});
    // for (int i = 6; i < 11; i++) {
    //     box.add(i);
    // }
    cout << "Draw twenty more:" << endl;
    for (int i = 0; i < 20; i++) {
        cout << box.draw(true) << endl;
    }

    return 0;
}
