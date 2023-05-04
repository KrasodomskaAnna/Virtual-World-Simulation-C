#ifndef C_FOX_H
#define C_FOX_H

#include <iostream>
#include "Animal.h"

class Fox : public Animal {
public:
    Fox(math_vector position, Game *game);
    Fox(Game *game, int strength, int initiative, int age, math_vector position);
    Organism* createNewOne(math_vector positionForNew) override;
    bool isTheSameSpecie(Organism* beingInConflict) override;
    std::string getOrganismType() const override;
protected:
    int getStep() const override;
    std::string getSign() override;
    bool isFree(math_vector _position) override;
    math_vector positionMove() override;
};


#endif //C_FOX_H
