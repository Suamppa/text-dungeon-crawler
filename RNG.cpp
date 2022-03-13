#include "RNG.h"

random_device randDev;
mt19937 generator(randDev());

int rng(int rangeFrom, int rangeTo) {
    uniform_int_distribution<int> distr(rangeFrom, rangeTo);
    return distr(generator);
}
