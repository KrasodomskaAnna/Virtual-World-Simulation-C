#include "random.h"

Directions intToDirection(int direction) {
    switch (direction) {
        case 1:
            return Directions::N;
        case 2:
            return Directions::S;
        case 3:
            return Directions::E;
        case 4:
            return Directions::W;
        default:
            throw;
    }
}

bool randomChoiceProbability(float probability) {
    if(rand()%100 <= probability*100)
        return true;
    return false;
}

math_vector randomPlace(math_vector position) {
    Directions direction = intToDirection(rand()%4);
    switch (direction) {
        case Directions::N:
            return position + math_vector(0, -1);
        case Directions::S:
            return position + math_vector(0, 1);
        case Directions::E:
            return position + math_vector(1, 0);
        case Directions::W:
            return position + math_vector(-1, 0);
        default:
            throw;
    }
}

math_vector randomPosition(int width, int height) {
    int x = rand()%width;
    int y = rand()%height;
    return {x, y};
}