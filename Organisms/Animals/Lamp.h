#ifndef C_LAMP_H
#define C_LAMP_H

#include <iostream>
#include "Animal.h"

class Lamp : public Animal {
public:
    Lamp(math_vector position, Game *game);
    Lamp(Game *game, int strength, int initiative, int age, math_vector position);
    Organism* createNewOne(math_vector positionForNew) override;
    bool isTheSameSpecie(Organism* beingInConflict) override;
    std::string getOrganismType() const override;
protected:
    int getStep() const override;
    std::string getSign() override;
};


#endif //C_LAMP_H
