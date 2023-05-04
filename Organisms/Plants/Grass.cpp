#include "Grass.h"

Grass::Grass(math_vector position, Game *game) : Plant(position, PLANT_STRENGTH, game) {}

Grass::Grass(Game *game, int strength, int initiative, int age, math_vector position) : Plant(game, strength, initiative, age, position) {}

std::string Grass::getSign() {
    return "G";
}

Organism *Grass::createNewOne(math_vector positionForNew) {
    return new Grass(positionForNew, this->game);
}

std::string Grass::getOrganismType() const {
    return "GRASS";
}