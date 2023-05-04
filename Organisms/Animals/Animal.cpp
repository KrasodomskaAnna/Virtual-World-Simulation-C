#include "Animal.h"
#include "../../Game.h"

Animal::Animal(math_vector position, int strength, int initiative, Game *game) : Organism(position, strength, initiative, game) {
    this->previousPosition = position;
}

Animal::Animal(Game *game, int strength, int initiative, int age, math_vector position) : Organism(game, strength, initiative, age, position) {}

void Animal::action() {
    move();
}

void Animal::swapPosition(math_vector newPosition) {
    this->previousPosition = this->position;
    this->position = newPosition;
}

void Animal::move() {
    math_vector newPosition = positionMove();
    if(newPosition == math_vector(-1, -1)) return;
    swapPosition(newPosition);
    game->addMessage(this->getOrganismType() + " move on a new position " + this->getPositionNotation() + "\n");
}

math_vector Animal::positionMove() {
    return randomNeighbor(false, this->getStep());
}

bool Animal::handleDeath(Organism* beingInConflict) {
    this->kill();
    return true;
}

void Animal::collision() {
    Organism* beingInConflict = collisionWith();
    if(beingInConflict == nullptr) return;
    if(isTheSameSpecie(beingInConflict)) {
        this->position = this->previousPosition;
        reproduce(dynamic_cast<Animal*>(beingInConflict));
        return;
    }
    if(beingInConflict->getStrength() <= this->strength)
        beingInConflict->collisionAnswer(this);
    else {
        if(handleDeath(beingInConflict))
            game->addMessage(this->getOrganismType() + " went to position " + this->getPositionNotation() + " so is kill by " + beingInConflict->getOrganismType() + "\n");

    }
}

void Animal::reproduce(Animal* animalReproducingWith) {
    math_vector positionForNew = randomNeighbor(true, NEIGHBOUR_SHIFT);
    if(positionForNew == math_vector(-1, -1)) {
        positionForNew = animalReproducingWith->randomNeighbor(true, NEIGHBOUR_SHIFT);
        if(positionForNew == math_vector(-1, -1)) {
            game->addWarning("Can't reproduce " + this->getOrganismType() + " on position " + this->getPositionNotation() + "\n");
            return;
        }
    }
    game->addMessage(this->getOrganismType() + " from position " + this->getPositionNotation() + " change position and met " + animalReproducingWith->getOrganismType() + " on position" + animalReproducingWith->getPositionNotation() + " so they reproduce" + "\n");
    game->organisms.push_back(this->createNewOne(positionForNew));
}

std::string Animal::getSign() {
    return "a";
}

void Animal::collisionAnswer(Organism *beingInConflict) {
    if(beingInConflict == nullptr) return;
    if(handleDeath(beingInConflict));
        game->addMessage(this->getOrganismType() + " from position " + this->getPositionNotation() + " is kill by " + beingInConflict->getOrganismType() + " which change his position with the aim of kill" + "\n");
}

void Animal::comeBack() {
    this->position =  this->previousPosition;
}

void Animal::runAway() {
    action();
    collision();
}

std::string Animal::getOrganismType() const {
    return "";
}