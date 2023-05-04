#ifndef C_GAME_H
#define C_GAME_H
#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include "const.h"
#include "math_vector.h"

struct InputState {
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
};

class Organism;

class Game {
public:
    Game();
    void loadSave();
    void saveGame();
    void loadConfig();
    void graphics();
    void nextTurn();
    bool getGameRunning();
    void endGame();
    int getWidth();
    int getHeight();
    InputState getInputState();
    void updateInput();
    std::vector<Organism*> organisms;
    bool isAlzurShieldActive();
    void setBgDimensions(int _width, int _height);
    void setAzurShield(int turns);
    int getAzurShield();
    int getTurnsNumber();
    void setTurnsNumber(int _turnsNumber);
    void cleanSetups();
    void addMessage(std::string _message);
    void addWarning(std::string _warning);
    bool loadGame = false;
    void menu();
private:
    bool gameRunning = true;
    int width = 0, height = 0;
    InputState inputState;
    // Alzur Shield -> if is 0 it can be use, if is + for this number of turns will be active, if is - for this number of turns can't be use
    int alzurShield = 0;
    int turnsNumber = 0;
    std::string messages;
    std::string warnings;
    std::string getBoardState();
};


#endif //C_GAME_H
