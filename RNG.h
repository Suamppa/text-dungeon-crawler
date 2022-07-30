#ifndef RNG_H
#define RNG_H

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <deque>
#include <initializer_list>

using namespace std;

// Generate a random integer from rangeFrom to (and including) rangeTo
int rng(int, int);
template <typename T>
void shuffleVector(vector<T> *);

// ShuffleBag based on the article "Shuffle Bags: Making Random() Feel More Random"
// by Jon Davis, October 24, 2012:
// https://gamedevelopment.tutsplus.com/tutorials/shuffle-bags-making-random-feel-more-random--gamedev-1249
template <typename T>
class ShuffleBag
{
private:
    deque<T> data;
    T currentItem;
    int currentPosition;
    // int capacity;
public:
    int size;
    ShuffleBag(initializer_list<T> = initializer_list<T>());
    void add(T, int=1);
    void add(initializer_list<T>, int=1);
    // ShuffleBag must be of type int.
    // End of range is included by default.
    // Args: range start, range end, exclude end (default false).
    void addRange(int, int, bool=false);
    T draw(bool=false);
    void empty();
};

// #include "RNG.cpp"

#endif
