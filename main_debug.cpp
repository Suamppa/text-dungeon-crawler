/*********************************************
A TESTING ENVIRONMENT FOR PROTOTYPING FEATURES
 *********************************************/

// #include "Dungeon.cpp"
// #include "Player.cpp"
// #include "GameCharacter.cpp"
// #include "Item.cpp"
// #include "Room.cpp"
// #include "RNG.cpp"
#include <iostream>
#include <vector>

using namespace std;

char handleInput(vector<string> actions, vector<char> legalInputs, bool allowStats, bool allowInventory) {
    while (true) {
        string input;
        char selection;
        int numActions = actions.size();
        cout << "numActions: " << numActions << "\n";
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

int main() {
    vector<string> actions = {"First option", "Second option"};
    vector<char> inputs = {'1', '2'};
    char selection;
    selection = handleInput(actions, inputs, false, false);
    cout << "Input: " << selection << endl;

    /*
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
     */

    /*
    vector<vector<bool>> test_vector;
    test_vector = vector<vector<bool>>(5, vector<bool>(6, false));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            cout << test_vector[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Size: " << test_vector.size() << endl;
    cout << "In range: " << check2DBounds(test_vector, 4, 5) << endl;
     */

    /*
    vector<vector<int>> values;
    values.push_back({2, 3});
    cout << values[0][0] << ", " << values[0][1] << endl;
     */

    /*
    int maxRooms = 10;
    maxRooms = ((maxRooms < 30) && (maxRooms > 0)) ? maxRooms : 30;
    cout << maxRooms << endl;
     */

    // cout << 5 / 2 << endl;

    // vector<char> options;
    // int number = 2;
    // options.push_back(static_cast<char>(number));
    // options.push_back('3');
    /*
    vector<char> numbers;
    for (int i = 0; i < 6; i++) {
        numbers.push_back(49 + i);
    }
    for (int i = 0; i < 6; i++) {
        cout << numbers[i] << "\n";
    }
     */

    return 0;
}
