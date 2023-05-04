#ifndef C_RANDOM_H
#define C_RANDOM_H
#pragma once
#include <cstdlib>
#include <ctime>
#include "math_vector.h"

enum class Directions {
    N,
    S,
    E,
    W
};

Directions intToDirection(int direction);

bool randomChoiceProbability(float probability);

math_vector randomPlace(math_vector position);

math_vector randomPosition(int width, int height);

#endif //C_RANDOM_H
