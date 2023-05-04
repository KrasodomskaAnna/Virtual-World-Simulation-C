#ifndef C_DANDELION_H
#define C_DANDELION_H

#include <iostream>
#include "Plant.h"

class Dandelion : public Plant {
public:
    Dandelion(math_vector position, Game *game);
    Dandelion(Game *game, int strength, int initiative, int age, math_vector position);
    void action() override;
    Organism* createNewOne(math_vector positionForNew) override;
    std::string getOrganismType() const override;
protected:
    std::string getSign() override;
};


#endif //C_DANDELION_H
