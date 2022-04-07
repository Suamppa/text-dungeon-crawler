#include "RNG.h"

random_device randDev;
mt19937 generator(randDev());

int rng(int rangeFrom, int rangeTo) {
    // rangeFrom and rangeTo are included in the possible result
    uniform_int_distribution<int> distr(rangeFrom, rangeTo);
    return distr(generator);
}

template <typename T>
void shuffleVector(vector<T> * contents) {
    shuffle(contents->begin(), contents->end(), generator);
}

template <typename T>
ShuffleBag<T>::ShuffleBag(initializer_list<T> base)
{
    // data.resize(initCapacity);
    // capacity = data.capacity();
    
    data = base;
    size = data.size();
    currentPosition = size - 1;
}

template <typename T>
void ShuffleBag<T>::add(T item, int amount) {
    if (amount > 1) {
        for (int i = 0; i < amount; i++) {
            data.push_front(item);
            currentPosition++;
        }
    } else {
        data.push_front(item);
        currentPosition++;
    }
    size = data.size();
}

template <typename T>
void ShuffleBag<T>::add(initializer_list<T> items, int amount) {
    // for (int i = 0; i < items.size(); i++) {
    for (T item: items) {
        if (amount > 1) {
            for (int j = 0; j < amount; j++) {
                data.push_front(item);
                currentPosition++;
            }
        } else {
            data.push_front(item);
            currentPosition++;
        }
    }
    size = data.size();
}

template <typename T>
T ShuffleBag<T>::draw(bool debug) {
    // Logic to start over.
    // This allows for adding new items without having to shuffle previously drawn ones back in.
    if (currentPosition < 0) {
        if (size < 1) {
            currentItem = data[0];
            return currentItem; 
        }
        currentPosition = size - 1;
    }

    // Print for testing
    if (debug) {
        cout << "\nPossible values:";
        if (currentPosition == 0) {
            cout << " " << data[0];
        } else {
            for (int i = 0; i < currentPosition+1; i++) {
            cout << " " << data[i];
            }
        }
        cout << endl << "Result: ";
    }

    int pos = rng(0, currentPosition);
    currentItem = data[pos];
    data[pos] = data[currentPosition];
    data[currentPosition] = currentItem;
    currentPosition--;
    return currentItem;
}

template <typename T>
void ShuffleBag<T>::empty() {
    data.clear();
    size = data.size();
}
