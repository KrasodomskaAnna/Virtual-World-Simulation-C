#ifndef C_WOLF_H
#define C_WOLF_H

#include <iostream>
#include "Animal.h"

class Wolf : public Animal {
public:
    Wolf(math_vector position, Game *game);
    Wolf(Game *game, int strength, int initiative, int age, math_vector position);
    Organism* createNewOne(math_vector positionForNew) override;
    bool isTheSameSpecie(Organism* beingInConflict) override;
    std::string getOrganismType() const override;
protected:
    int getStep() const override;
    std::string getSign() override;
};


#endif //C_WOLF_H
