#ifndef C_SOSNOWSKY_HOGWEED_H
#define C_SOSNOWSKY_HOGWEED_H

#include <iostream>
#include "Plant.h"

class Sosnowsky_hogweed : public Plant {
public:
    Sosnowsky_hogweed(math_vector position, Game *game);
    Sosnowsky_hogweed(Game *game, int strength, int initiative, int age, math_vector position);
    void action() override;
    void collisionAnswer(Organism* beingInConflict) override;
    Organism* createNewOne(math_vector positionForNew) override;
    std::string getOrganismType() const override;
protected:
    std::string getSign() override;
private:
    void canKillAndExecute(Organism* beingInConflict);
};


#endif //C_SOSNOWSKY_HOGWEED_H
