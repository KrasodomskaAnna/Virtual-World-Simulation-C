#include "Lamp.h"

Lamp::Lamp(math_vector position, Game *game) : Animal(position, LAMP_STRENGTH, LAMP_INITIATIVE, game) {}

Lamp::Lamp(Game *game, int strength, int initiative, int age, math_vector position) : Animal(game, strength, initiative, age, position) {}

std::string Lamp::getSign() {
    return "L";
}

Organism* Lamp::createNewOne(math_vector positionForNew) {
    return new Lamp(positionForNew, this->game);
}

bool Lamp::isTheSameSpecie(Organism *beingInConflict) {
    if(dynamic_cast<Lamp*>(beingInConflict) != nullptr)
        return true;
    return false;
}

std::string Lamp::getOrganismType() const {
    return "LAMP";
}

int Lamp::getStep() const {
    return LAMP_STEP;
}