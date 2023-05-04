#include "Dandelion.h"

Dandelion::Dandelion(math_vector position, Game *game) : Plant(position, PLANT_STRENGTH, game) {}

Dandelion::Dandelion(Game *game, int strength, int initiative, int age, math_vector position) : Plant(game, strength, initiative, age, position) {}

void Dandelion::action() {
    for(int i = 0; i < TRY_DANDELION_TO_SOW_NUMBER; i++)
        this->sow();
}

std::string Dandelion::getSign() {
    return "D";
}

Organism *Dandelion::createNewOne(math_vector positionForNew) {
    return new Dandelion(positionForNew, this->game);
}

std::string Dandelion::getOrganismType() const {
    return "DANDELION";
}