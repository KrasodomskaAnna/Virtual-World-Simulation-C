#ifndef C_ORGANISM_H
#define C_ORGANISM_H
#pragma once

#include <vector>
#include <string>
#include <functional>
#include "../math_vector.h"
#include "../const.h"

class Game;

class Organism {
public:
    Organism(math_vector position, int strength, int initiative, Game* game);
    Organism(Game *game, int strength, int initiative, int age, math_vector position);
    virtual void action() = 0;
    virtual void collision() = 0;
    std::string graphics();
    virtual void collisionAnswer(Organism* beingInConflict) = 0;
    bool getIsAlive();
    virtual void kill();
    void setStrength(int _strength);
    int getStrength();
    int getInitiative();
    int getAge();
    void increaseAge();
    math_vector getPosition();
    virtual std::string getOrganismType() const = 0;
    std::string getPositionNotation();
protected:
    bool isOnBoard(math_vector _position);
    math_vector randomNeighbor(bool moveOnEmptyField, int shift);
    Organism* collisionWith();
    Game* game;
    int strength;
    int initiative;
    int age = 0;
    bool isAlive = true;
    math_vector position{0, 0};
    virtual std::string getSign() = 0;
    virtual bool isFree(math_vector _position);
};


#endif //C_ORGANISM_H
