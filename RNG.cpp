#include "RNG.h"

random_device randDev;
mt19937 generator(randDev());

int rng(int rangeFrom, int rangeTo) {
    uniform_int_distribution<int> distr(rangeFrom, rangeTo);
    return distr(generator);
}

template <typename T>
void shuffleVector(vector<T> * contents) {
    shuffle(contents->begin(), contents->end(), generator);
}

template <typename T>
ShuffleBag<T>::ShuffleBag(int initCapacity)
{
    data.resize(initCapacity);
    currentPosition = -1;
    capacity = data.capacity();
    size = data.size();
}

template <typename T>
void ShuffleBag<T>::add(T item, int amount) {
    for (int i = 0; i < amount; i++) {
        data.push_back(item);
    }
    currentPosition = size - 1;
}

template <typename T>
T ShuffleBag<T>::next() {
    if (currentPosition < 1) {
        currentPosition = size - 1;
        currentItem = data[0];
        return currentItem;
    }
    int pos = rng(0, currentPosition);
    currentItem = data[pos];
    data[pos] = data[currentPosition];
    data[currentPosition] = currentItem;
    currentPosition--;
    return currentItem;
}
