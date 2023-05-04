#include "Antelope.h"
#include "../../Game.h"
#include "../../random.h"

Antelope::Antelope(math_vector position, Game *game) : Animal(position, ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, game) {}

Antelope::Antelope(Game *game, int strength, int initiative, int age, math_vector position) : Animal(game, strength, initiative, age, position) {}

bool Antelope::handleDeath(Organism* beingInConflict) {
    if(dynamic_cast<Animal*>(beingInConflict) == nullptr) {
        if(escape()) return false;
    }
    this->kill();
    return true;
}

std::string Antelope::getSign() {
    return "A";
}

Organism* Antelope::createNewOne(math_vector positionForNew) {
    return new Antelope(positionForNew, this->game);
}

bool Antelope::isTheSameSpecie(Organism *beingInConflict) {
    if(dynamic_cast<Antelope*>(beingInConflict) != nullptr)
        return true;
    return false;
}

bool Antelope::escape() {
    if(!randomChoiceProbability(PROBABILITY_ANTELOPE_ESCAPE)) return false;
    math_vector newPosition = randomNeighbor(true, NEIGHBOUR_SHIFT);
    if(newPosition == math_vector(-1, -1)) return false;
    this->previousPosition = this->position;
    this->position = newPosition;
    game->addMessage(this->getOrganismType() + " runAway from attack" + "\n");
    return true;
}

std::string Antelope::getOrganismType() const {
    return "ANTELOPE";
}

int Antelope::getStep() const {
    return ANTELOPE_STEP;
}