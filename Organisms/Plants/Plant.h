#ifndef C_PLANT_H
#define C_PLANT_H
#pragma once

#include <iostream>
#include "../Organism.h"

class Grass;

class Plant : public Organism {
public:
    Plant(math_vector position, int strength, Game* game);
    Plant(Game *game, int strength, int initiative, int age, math_vector position);
    void action() override;
    void collision() override;
    void collisionAnswer(Organism* beingInConflict) override;
    void sow();
    virtual Organism* createNewOne(math_vector positionForNew) = 0;
    std::string getOrganismType() const override;
protected:
    std::string getSign() override;
};


#endif //C_PLANT_H
