#ifndef C_HUMAN_H
#define C_HUMAN_H

#include "Animal.h"

class Human : public Animal {
public:
    Human(math_vector position, Game *game);
    Human(Game *game, int strength, int initiative, int age, math_vector position);
    void action() override;
    void collision() override;
    void collisionAnswer(Organism* beingInConflict) override;
    Organism* createNewOne(math_vector positionForNew) override;
    bool isTheSameSpecie(Organism* beingInConflict) override;
    std::string getOrganismType() const override;
    void kill() override;
protected:
    int getStep() const override;
    std::string getSign() override;
};


#endif //C_HUMAN_H
