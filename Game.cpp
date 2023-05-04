#include "Game.h"
#include "Organisms/Organism.h"
#include "Organisms/Animals/Human.h"
#include "Configurations/config.h"
#include "const.h"

Game::Game() {}

void Game::loadSave() {
    organisms.clear();
    auto config = new Config("../../../Configurations/save.txt", &organisms, this);
    config->loadSave();
    delete(config);
}

void Game::saveGame() {
    auto config = new Config("../../../Configurations/save.txt", &organisms, this);
    config->save();
    delete(config);
}

void Game::loadConfig() {
    organisms.clear();
    auto config = new Config("../../../Configurations/config.txt", &organisms, this);
    config->loadConfig();
    delete(config);
}

void Game::nextTurn() {
    sort(organisms.begin(), organisms.end(), [] (Organism* a, Organism* b) {
        if (a->getInitiative() > b->getInitiative()) return true;
        if (a->getInitiative() < b->getInitiative()) return false;
        if (a->getAge() > b->getAge()) return true;
        if (a->getAge() < b->getAge()) return false;
        return false;
    });

    for (auto i = 0; i < organisms.size(); ++i) {
        if(organisms[i]->getIsAlive()) {
            organisms[i]->action();
            organisms[i]->collision();
        }
    }
    for (auto i = 0; i < organisms.size(); ++i) {
        if (!organisms[i]->getIsAlive()) {
            organisms.erase(organisms.begin() + i);
            if(i == organisms.size()) break;
            if (organisms[i] != *organisms.begin()) i--;
        } else {
            organisms[i]->increaseAge();
        }
    }

//    for (auto iter = organisms.begin(); iter != organisms.end(); iter++) {
//        auto organism = *iter;
//        if(organism->getIsAlive()) {
//            organism->action();
//            organism->collision();
//        }
//    }
//    for (auto iter = organisms.begin(); iter != organisms.end(); iter++) {
//        auto organism = *iter;
//        if (organism->getIsAlive()) organism->increaseAge();
//    }
//    for (auto iter = organisms.begin(); iter != organisms.end(); iter++) {
//        auto organism = *iter;
//        if (!organism->getIsAlive()) {
//            iter = organisms.erase(iter);
//            if(iter == organisms.end()) break;
//        }
//    }
    if(this->alzurShield == 1) alzurShield = -ALZUR_SHIELD_LOCK;
    else if(this->alzurShield < 0) alzurShield++;
    else if(this->alzurShield > 0) alzurShield--;
    this->turnsNumber++;
}

bool Game::getGameRunning() {
    return this->gameRunning;
}
void Game::endGame() {
    gameRunning = false;
}
int Game::getWidth() {
    return this->width;
}
int Game::getHeight() {
    return this->height;
}
InputState Game::getInputState() {
    return this->inputState;
}
bool Game::isAlzurShieldActive() {
    if(alzurShield > 0) return true;
    return false;
}
int Game::getTurnsNumber() {
    return this->turnsNumber;
}
void Game::setTurnsNumber(int _turnsNumber) {
    this->turnsNumber = _turnsNumber;
}

void Game::setBgDimensions(int _width, int _height) {
    this->width = _width;
    this->height = _height;
}

void Game::setAzurShield(int turns) {
    this->alzurShield = turns;
}

int Game::getAzurShield() {
    return this->alzurShield;
}

void Game::updateInput() {
    int event = getch();
    event = getch();
    if(!loadGame) {
        if(event != 'l' && event != 'c') {
            addWarning("You should load game first!\n");
            return;
        }
    }
    switch (event) {
        case 'a':
            if(alzurShield == 0)
                this->alzurShield = ALZUR_SHIELD_DURATION_SET;
            else
                addWarning("You cannot activate alzurShield!\n");
            updateInput();
            break;
        case 'l':
            this->loadSave();
            break;
        case 'c':
            this->loadConfig();
            break;
        case 's':
            this->saveGame();
            break;
        case ARROW_UP:
            this->inputState = {true, false, false, false};
            break;
        case ARROW_DOWN:
            this->inputState = {false, true, false, false};
            break;
        case ARROW_LEFT:
            this->inputState = {false, false, false, true};
            break;
        case ARROW_RIGHT:
            this->inputState = {false, false, true, false};
            break;
        default:
            break;
    };
}

void Game::menu() {
    std::cout << "Animal World - Anna Krasodomska - 188863" << std::endl << std::endl << "l - load saved game" << std::endl << "c - load config" << std::endl << "s - save game" << std::endl << "a - activate Alzur Shield" << std::endl << std::endl << std::to_string(turnsNumber) << " TURN" << std::endl << std::endl;
}

void Game::addMessage(std::string _message) {
    messages += _message;
}

void Game::addWarning(std::string _warning) {
    warnings += _warning;
}

void Game::cleanSetups() {
    loadGame = false;
    alzurShield = 0;
    turnsNumber = 0;
}

void Game::graphics() {
    system( "cls" );
    menu();
    if(loadGame) {
        if(alzurShield > 0) std::cout << "Alzur Shield activated for " << alzurShield << " turns" << std::endl;
        else if(alzurShield == 0) std::cout << "Alzur Shield can be activated" << std::endl;
        else std::cout << "Alzur Shield can't be activated for " << -alzurShield << " turns" << std::endl;
        std::cout << "WARNINGS" << std::endl;
        if(warnings != "") std::cout << warnings << std::endl;
        else std::cout << "    ...none" << std::endl;
        warnings = "";
        std::cout << getBoardState() << std::endl;
    }
    std::cout << messages << std::endl;
    messages = "";
    if(!gameRunning)
        std::cout << std::endl << "YOU FAILED!" << std::endl;
}

std::string Game::getBoardState() {
    std::string state = "";
    for(int y = -1; y <= height; y++) {
        state += "|";
        for(int x = 0; x < width; x++) {
            if(y == -1) {
                state += ">";
                continue;
            } else if(y == height) {
                state += "<";
                continue;
            }
            bool isThereOrganism = false;
            for(auto & organism : organisms) {
                if(organism->getPosition() == math_vector(x,y)) {
                    if(organism->getIsAlive()) { // prewencyjnie, zabezpieczenie
                        state += organism->graphics();
                        isThereOrganism = true;
                    }
                }
            }
            if(!isThereOrganism)
                state += " ";
        }
        state += "|\n";
    }
    return state;
}