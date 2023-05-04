#include "Plant.h"
#include "../../Game.h"
#include "../../random.h"
#include "../Animals/Animal.h"

Plant::Plant(math_vector position, int strength, Game* game) : Organism(position, strength, PLANT_INITIATIVE, game) {}

Plant::Plant(Game *game, int strength, int initiative, int age, math_vector position) : Organism(game, strength, initiative, age, position) {}

void Plant::action() {
    this->sow();
}

void Plant::collision() {
    collisionAnswer(collisionWith());
}

std::string Plant::getSign() {
    return "p";
}

void Plant::collisionAnswer(Organism *beingInConflict) {
    if(beingInConflict == nullptr) return;
    kill();
    if(dynamic_cast<Animal*>(beingInConflict) != nullptr)
        game->addMessage(beingInConflict->getOrganismType() + " change position to " + this->getPositionNotation() + " so eat " + this->getOrganismType() + "\n");
}

void Plant::sow() {
    if(!randomChoiceProbability(PROBABILITY_SOW)) return;
    math_vector positionForNew = randomNeighbor(true, NEIGHBOUR_SHIFT);
    if(positionForNew == math_vector(-1, -1)) return;
    game->addMessage(this->getOrganismType() + " sow a new plant!" + "\n");
    game->organisms.push_back(this->createNewOne(positionForNew));
}

std::string Plant::getOrganismType() const {
    return "";
}