#ifndef C_TURTLE_H
#define C_TURTLE_H

#include <iostream>
#include "Animal.h"

class Turtle : public Animal {
public:
    Turtle(math_vector position, Game *game);
    Turtle(Game *game, int strength, int initiative, int age, math_vector position);
    void action() override;
    void collisionAnswer(Organism *beingInConflict) override;
    Organism* createNewOne(math_vector positionForNew) override;
    bool isTheSameSpecie(Organism* beingInConflict) override;
    std::string getOrganismType() const override;
protected:
    int getStep() const override;
    std::string getSign() override;
};


#endif //C_TURTLE_H
