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
    int capacity;
public:
    int size;
    ShuffleBag(int);
    void add(T, int);
    T next();
};

#include "RNG.cpp"

#endif
