#ifndef C_ANTELOPE_H
#define C_ANTELOPE_H

#include <iostream>
#include "Animal.h"

class Antelope : public Animal {
public:
    Antelope(math_vector position, Game *game);
    Antelope(Game *game, int strength, int initiative, int age, math_vector position);
    Organism* createNewOne(math_vector positionForNew) override;
    bool isTheSameSpecie(Organism* beingInConflict) override;
    std::string getOrganismType() const override;
protected:
    int getStep() const override;
    std::string getSign() override;
    bool handleDeath(Organism* beingInConflict) override;
private:
    bool escape();
};


#endif //C_ANTELOPE_H
