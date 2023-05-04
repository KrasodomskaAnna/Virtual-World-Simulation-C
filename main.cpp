#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"

int main() {
    srand(time(NULL));
    Game *game = new Game();
    game->menu();
    while (game->getGameRunning()) {
        game->updateInput();
        if(game->loadGame)
            game->nextTurn();
        game->graphics();
    }
    delete (game);
    return 0;
}
