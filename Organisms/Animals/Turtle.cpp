#include "Turtle.h"
#include "../../Game.h"
#include "../../random.h"

Turtle::Turtle(math_vector position, Game *game) : Animal(position, TURTLE_STRENGTH, TURTLE_INITIATIVE, game) {}

Turtle::Turtle(Game *game, int strength, int initiative, int age, math_vector position) : Animal(game, strength, initiative, age, position) {}

void Turtle::action() {
    if(!randomChoiceProbability(PROBABILITY_TURTLE_MOVE)) return;
    move();
}

void Turtle::collisionAnswer(Organism *beingInConflict) {
    if(beingInConflict == nullptr) return;
    if(beingInConflict->getStrength() < STRENGTH_REPEL_ATTACK_TURTLE) {
        auto* conflictAnimal = dynamic_cast<Animal*>(beingInConflict);
        if(dynamic_cast<Animal*>(beingInConflict) != nullptr) {
            conflictAnimal->comeBack();
            game->addMessage(conflictAnimal->getOrganismType() + " attack is repel by " + this->getOrganismType() + " and must back off to the previous position" + "\n");
        }
    }
    else {
        kill();
        game->addMessage(this->getOrganismType() + " is kill by " + beingInConflict->getOrganismType() + "\n");
    }
}

std::string Turtle::getSign() {
    return "T";
}

Organism* Turtle::createNewOne(math_vector positionForNew) {
    return new Turtle(positionForNew, this->game);
}

bool Turtle::isTheSameSpecie(Organism *beingInConflict) {
    if(dynamic_cast<Turtle*>(beingInConflict) != nullptr)
        return true;
    return false;
}

std::string Turtle::getOrganismType() const {
    return "TURTLE";
}

int Turtle::getStep() const {
    return TURTLE_STEP;
}