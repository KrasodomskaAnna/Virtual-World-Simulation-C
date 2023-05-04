#include "Sosnowsky_hogweed.h"
#include "../../Game.h"
#include "../Animals/Animal.h"

Sosnowsky_hogweed::Sosnowsky_hogweed(math_vector position, Game *game) : Plant(position, SOSNOWSKY_STRENGTH, game) {}

Sosnowsky_hogweed::Sosnowsky_hogweed(Game *game, int strength, int initiative, int age, math_vector position) : Plant(game, strength, initiative, age, position) {}

void Sosnowsky_hogweed::action() {
    for(auto & organism : game->organisms) {
        for(int x = -1; x <= 1; x++) {
            for(int y = -1; y <= 1; y++) {
                if(x == 0 && y == 0) continue;
                if(organism->getPosition() == (position + math_vector(x,y)))
                    canKillAndExecute(organism);
            }
        }
    }
    this->sow();
}

std::string Sosnowsky_hogweed::getSign() {
    return "S";
}

void Sosnowsky_hogweed::collisionAnswer(Organism* beingInConflict) {
    if(beingInConflict == nullptr) return;
    beingInConflict->kill();
    game->addMessage(beingInConflict->getOrganismType() + " is kill by " + this->getOrganismType() + "\n");
}

Organism *Sosnowsky_hogweed::createNewOne(math_vector positionForNew) {
    return new Sosnowsky_hogweed(positionForNew, this->game);
}

std::string Sosnowsky_hogweed::getOrganismType() const {
    return "SOSNOWSKY";
}

void Sosnowsky_hogweed::canKillAndExecute(Organism* beingInConflict) {
    if(dynamic_cast<Animal*>(beingInConflict) != nullptr) {
        beingInConflict->kill();
        game->addMessage(beingInConflict->getOrganismType() + " is kill by " + this->getOrganismType() + "\n");
    }
}