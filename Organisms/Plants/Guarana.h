#ifndef C_GUARANA_H
#define C_GUARANA_H

#include <iostream>
#include "Plant.h"

class Guarana : public Plant {
public:
    Guarana(math_vector position, Game *game);
    Guarana(Game *game, int strength, int initiative, int age, math_vector position);
    void collisionAnswer(Organism* beingInConflict) override;
    Organism* createNewOne(math_vector positionForNew) override;
    std::string getOrganismType() const override;
protected:
    std::string getSign() override;
};


#endif //C_GUARANA_H
