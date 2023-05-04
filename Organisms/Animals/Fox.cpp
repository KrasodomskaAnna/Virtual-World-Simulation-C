#include "Fox.h"
#include "../../Game.h"
#include "../../random.h"

Fox::Fox(math_vector position, Game *game) : Animal(position, FOX_STRENGTH, FOX_INITIATIVE, game) {}

Fox::Fox(Game *game, int strength, int initiative, int age, math_vector position) : Animal(game, strength, initiative, age, position) {}

std::string Fox::getSign() {
    return "F";
}

Organism* Fox::createNewOne(math_vector positionForNew) {
    return new Fox(positionForNew, this->game);
}

bool Fox::isTheSameSpecie(Organism *beingInConflict) {
    if(dynamic_cast<Fox*>(beingInConflict) != nullptr)
        return true;
    return false;
}

math_vector Fox::positionMove() {
    return randomNeighbor(true, this->getStep());
}

bool Fox::isFree(math_vector _position) {
    bool canBeAddedToVector = true;
    for(auto & organism : game->organisms) {
        if(_position == organism->getPosition()) {
            if(organism->getStrength() > this->strength) {
                canBeAddedToVector = false;
                break;
            }
        }
    }
    return canBeAddedToVector;
}

std::string Fox::getOrganismType() const {
    return "FOX";
}

int Fox::getStep() const {
    return FOX_STEP;
}