#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

#ifndef RNG_H
#define RNG_H

using namespace std;

int rng(int, int);
template <typename T>
void shuffleVector(vector<T> *);

template <typename T>
class ShuffleBag
{
private:
    vector<T> data;
    T currentItem;
    int currentPosition;
    // int capacity;
public:
    int size;
    ShuffleBag(vector<T> = vector<T>());
    void add(T, int=1);
    T next();
    void empty();
};

#include "RNG.cpp"

#endif
