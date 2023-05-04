#include "Nightshade.h"
#include "../../Game.h"

Nightshade::Nightshade(math_vector position, Game *game) : Plant(position, NIGHTSHADE_STRENGTH, game) {}

Nightshade::Nightshade(Game *game, int strength, int initiative, int age, math_vector position) : Plant(game, strength, initiative, age, position) {}

std::string Nightshade::getSign() {
    return "N";
}

void Nightshade::collisionAnswer(Organism* beingInConflict) {
    if(beingInConflict == nullptr) return;
    beingInConflict->kill();
    game->addMessage(beingInConflict->getOrganismType() + " is kill by " + this->getOrganismType() + "\n");
}

Organism *Nightshade::createNewOne(math_vector positionForNew) {
    return new Nightshade(positionForNew, this->game);
}

std::string Nightshade::getOrganismType() const {
    return "NIGHTSHADE";
}