#ifndef C_GRASS_H
#define C_GRASS_H

#include <iostream>
#include "Plant.h"

class Grass : public Plant {
public:
    Grass(math_vector position, Game *game);
    Grass(Game *game, int strength, int initiative, int age, math_vector position);
    Organism* createNewOne(math_vector positionForNew) override;
    std::string getOrganismType() const override;
protected:
    std::string getSign() override;
};


#endif //C_GRASS_H
