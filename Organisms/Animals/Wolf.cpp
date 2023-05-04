#include "Wolf.h"

Wolf::Wolf(math_vector position, Game *game) : Animal(position, WOLF_STRENGTH, WOLF_INITIATIVE, game) {}

Wolf::Wolf(Game *game, int strength, int initiative, int age, math_vector position) : Animal(game, strength, initiative, age, position) {}

std::string Wolf::getSign() {
    return "W";
}

Organism* Wolf::createNewOne(math_vector positionForNew) {
    return new Wolf(positionForNew, this->game);
}

bool Wolf::isTheSameSpecie(Organism *beingInConflict) {
    if(dynamic_cast<Wolf*>(beingInConflict) != nullptr)
        return true;
    return false;
}

std::string Wolf::getOrganismType() const {
    return "WOLF";
}

int Wolf::getStep() const {
    return WOLF_STEP;
}