#ifndef C_ANIMAL_H
#define C_ANIMAL_H

#include <iostream>
#include "../Organism.h"

class Animal : public Organism {
public:
    Animal(math_vector position, int strength, int initiative, Game* game);
    Animal(Game *game, int strength, int initiative, int age, math_vector position);
    void action() override;
    void collision() override;
    void collisionAnswer(Organism* beingInConflict) override;
    virtual Organism* createNewOne(math_vector positionForNew) = 0;
    virtual bool isTheSameSpecie(Organism* beingInConflict) = 0;
    void comeBack();
    void runAway();
    std::string getOrganismType() const override;
protected:
    math_vector previousPosition{0,0};
    void reproduce(Animal* animalReproducingWith);
    void move();
    virtual int getStep() const = 0;
    std::string getSign() override;
    virtual bool handleDeath(Organism* beingInConflict);
    virtual math_vector positionMove();
    void swapPosition(math_vector newPosition);
};


#endif //C_ANIMAL_H