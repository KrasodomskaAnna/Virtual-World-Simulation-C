#include "Guarana.h"
#include "../../Game.h"
#include "../Animals/Animal.h"

Guarana::Guarana(math_vector position, Game *game) : Plant(position, PLANT_STRENGTH, game) {}

Guarana::Guarana(Game *game, int strength, int initiative, int age, math_vector position) : Plant(game, strength, initiative, age, position) {}

std::string Guarana::getSign() {
    return "U";
}

void Guarana::collisionAnswer(Organism* beingInConflict) {
    if(beingInConflict == nullptr) return;
    if(dynamic_cast<Animal*>(beingInConflict) == nullptr) return;
    beingInConflict->setStrength(beingInConflict->getStrength() + GUARANA_INCREASE_STRENGTH_WHO_EAT);
    game->addMessage(this->getOrganismType() + " increased strength of " + beingInConflict->getOrganismType() + " so it's now " +
                             std::to_string(beingInConflict->getStrength()) + "\n");
    kill();
}

Organism *Guarana::createNewOne(math_vector positionForNew) {
    return new Guarana(positionForNew, this->game);
}

std::string Guarana::getOrganismType() const {
    return "GUARANA";
}