#include "Human.h"
#include "../../Game.h"

Human::Human(math_vector position, Game *game) : Animal(position, HUMAN_STRENGTH, HUMAN_INITIATIVE, game) {}

Human::Human(Game *game, int strength, int initiative, int age, math_vector position) : Animal(game, strength, initiative, age, position) {}

void Human::kill() {
    this->isAlive = false;
    game->endGame();
}

void Human::action() {
    InputState _inputState = game->getInputState();
    math_vector newPos{-1, -1};
    if(_inputState.up)
        newPos = this->position + math_vector(0, -1*HUMAN_STEP);
    else if(_inputState.down)
        newPos = this->position + math_vector(0, 1*HUMAN_STEP);
    else if(_inputState.right)
        newPos = this->position + math_vector(1*HUMAN_STEP, 0);
    else if(_inputState.left)
        newPos = this->position + math_vector(-1*HUMAN_STEP, 0);
    if(isOnBoard(newPos))
        swapPosition(newPos);
}

void Human::collision() {
    Organism* beingInConflict = collisionWith();
    if(beingInConflict == nullptr) return;
    Animal* collisionAnimal = dynamic_cast<Animal*>(beingInConflict);
    if(!game->isAlzurShieldActive() || collisionAnimal == nullptr) {
        if(beingInConflict->getStrength() <= this->strength)
            beingInConflict->collisionAnswer(this);
        else this->kill();
    }
    else {
        collisionAnimal->runAway();
        game->addMessage(this->getOrganismType() + " from position " + this->getPositionNotation() + " deter " + collisionAnimal->getOrganismType() + " which go away to " + collisionAnimal->getPositionNotation() + "\n");
    }
}

void Human::collisionAnswer(Organism *beingInConflict) {
    if(beingInConflict == nullptr) return;
    if(!game->isAlzurShieldActive()) {
        kill();
        return;
    }
    auto* collisionAnimal = dynamic_cast<Animal*>(beingInConflict);
    if(collisionAnimal != nullptr)
        collisionAnimal->runAway();
}

Organism* Human::createNewOne(math_vector positionForNew) {
    // human can not reproduce
    throw;
}

bool Human::isTheSameSpecie(Organism *beingInConflict) {
    // there is only one human in the world
    throw;
}

std::string Human::getSign() {
    return "H";
}

std::string Human::getOrganismType() const {
    return "HUMAN";
}

int Human::getStep() const {
    return HUMAN_STEP;
}