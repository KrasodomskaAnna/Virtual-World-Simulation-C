#ifndef C_NIGHTSHADE_H
#define C_NIGHTSHADE_H

#include <iostream>
#include "Plant.h"

class Nightshade : public Plant {
public:
    Nightshade(math_vector position, Game *game);
    Nightshade(Game *game, int strength, int initiative, int age, math_vector position);
    void collisionAnswer(Organism* beingInConflict) override;
    Organism* createNewOne(math_vector positionForNew) override;
    std::string getOrganismType() const override;
protected:
    std::string getSign() override;
};


#endif //C_NIGHTSHADE_H
