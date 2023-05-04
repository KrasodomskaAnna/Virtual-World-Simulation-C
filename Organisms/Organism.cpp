#include "Organism.h"
#include "../Game.h"


Organism::Organism(math_vector position, int strength, int initiative, Game* game) : game(game), position(position), strength(strength), initiative(initiative) {}

Organism::Organism(Game *game, int strength, int initiative, int age, math_vector position) : game(game), strength(strength), initiative(initiative), age(age), position(position) {}

std::string Organism::graphics() {
    return this->getSign();
}

int Organism::getInitiative() {
    return this->initiative;
}

int Organism::getAge() {
    return this->age;
}

void Organism::increaseAge() {
    this->age++;
}

math_vector Organism::getPosition() {
    return this->position;
}

bool Organism::getIsAlive() {
    return this->isAlive;
}

void Organism::setStrength(int _strength) {
    this->strength = _strength;
}

int Organism::getStrength() {
    return this->strength;
}

bool Organism::isOnBoard(math_vector _position) {
    return _position.x < game->getWidth() && _position.x >= 0 && _position.y < game->getHeight() && _position.y >= 0;
}

Organism* Organism::collisionWith() {
    for(auto & organism : game->organisms) {
        if(organism == this) continue;
        if(organism->getPosition() == this->position) {
            if(organism->getIsAlive())
                return organism;
        }
    }
    return nullptr;
}

void Organism::kill() {
    this->isAlive = false;
}

math_vector Organism::randomNeighbor(bool moveOnEmptyField, int shift) {
    std::vector<math_vector> freePositions;
    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            if(x == 0 && y == 0) continue;
            if(isOnBoard(position+math_vector(x,y))) {
                if(moveOnEmptyField) {
                    if(isFree(position+math_vector(x,y)))
                        freePositions.emplace_back(position+math_vector(x,y));
                }
                else freePositions.emplace_back(position+math_vector(x,y));
            }
        }
    }
    if(freePositions.empty()) return math_vector{-1,-1};
    int randomChoice = rand()%freePositions.size();
    for(auto & freePosition : freePositions) {
        if(randomChoice == 0) return freePosition;
        else randomChoice--;
    }
    return math_vector(-1,-1);
}

bool Organism::isFree(math_vector _position) {
    bool canBeAddedToVector = true;
    for(auto & organism : game->organisms) {
        if(_position == organism->getPosition()) {
            canBeAddedToVector = false;
            break;
        }
    }
    return canBeAddedToVector;
}


std::string Organism::getPositionNotation() {
    return  "(" + std::to_string(this->getPosition().x) + ", " + std::to_string(this->getPosition().y) + ")";
}