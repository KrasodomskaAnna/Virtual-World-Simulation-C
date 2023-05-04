#ifndef C_CONFIG_H
#define C_CONFIG_H

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../Game.h"
#include "../random.h"

#include "../Organisms/Animals/Antelope.h"
#include "../Organisms/Animals/Fox.h"
#include "../Organisms/Animals/Lamp.h"
#include "../Organisms/Animals/Turtle.h"
#include "../Organisms/Animals/Wolf.h"

#include "../Organisms/Plants/Dandelion.h"
#include "../Organisms/Plants/Grass.h"
#include "../Organisms/Plants/Guarana.h"
#include "../Organisms/Plants/Nightshade.h"
#include "../Organisms/Plants/Sosnowsky_hogweed.h"

#define CONFIG_MAX_LINE_LENGTH 100

#define firstIndent 0
#define secondIndent 4
#define thirdIndent 8
#define secondIndentOptionNumber 3

#define NEVER_BEFORE 0

#define HUNDRED_PERCENT 100.0
#define FIELDS_OCCUPIED_BY_ORGANISM_PERCENT 20.0/HUNDRED_PERCENT
#define DEFAULT_ORGANISM_TRAIT -1


class Config {
public:
    Config(const char *path, std::vector<Organism *> *organisms, Game *game) : organisms(organisms), game(game) {
        this->file = fopen(path, "r+"); // otwieranie pliku
    }

    void save() {
        for (int i = 0; i < firstIndent; i++)
            fputs(" ", this->file);
        fputs("save", this->file);

        for (int w = 0; w < secondIndentOptionNumber; w++) {
            fputs("\n", file);
            for (int i = 0; i < secondIndent; i++)
                fputs(" ", file);
            if (w == 0) fprintf(file, "Turns %d", game->getTurnsNumber());
            else if (w == 1) fprintf(file, "BSize %d %d", game->getWidth(), game->getHeight());
            else if (w == 2) fprintf(file, "AzurS %d", game->getAzurShield());
        }

        for (auto &organism: game->organisms) {
            fputs("\n", file);
            for (int i = 0; i < thirdIndent; i++)
                fputs(" ", file);
            std::string type = organism->getOrganismType();
            fprintf(file, "Organ %s %d %d %d %d %d", &type, organism->getStrength(), organism->getInitiative(),
                    organism->getAge(), organism->getPosition().x, organism->getPosition().y);
        }
        game->cleanSetups();
    }

    void loadSave() {
        char optionType[7];

        while (!feof(this->file)) { // repeat until it's not the end of file EOF
            char line[CONFIG_MAX_LINE_LENGTH]; // Buffer to store the line

            fgets(line, CONFIG_MAX_LINE_LENGTH, this->file);
            auto len = strlen(line); // keep line length

            auto indent = 0;
            while (indent < len && line[indent] == ' ') { // cont indent -> number of spaces
                indent++;
            }

            switch (indent) {
                case firstIndent:
                    sscanf(line, "%6s", optionType);
                    optionType[6] = 0; // "null termination"
                    if (strncmp(optionType, "save", 5) != 0)
                        Config::displayError("Unsupported save title");
                    break;
                case secondIndent:
                    sscanf(line, "%5s", optionType);
                    optionType[5] = 0; // "null termination"
                    if (strncmp(optionType, "AzurS", 6) == 0)
                        this->loadAzurShield(line);
                    else if (strncmp(optionType, "BSize", 5) == 0)
                        this->loadBoardSize(line);
                    else if (strncmp(optionType, "Turns", 5) == 0)
                        this->loadTurnsNumber(line);
                    else
                        Config::displayError("Unexpected token");
                    break;
                case thirdIndent:
                    sscanf(line, "%5s", optionType);
                    optionType[5] = 0; // "null termination"
                    if (strncmp(optionType, "Organ", 6) == 0) {
                        this->loadOrganism(line);
                    } else
                        Config::displayError("Unexpected token");
                    break;
                default:
                    Config::displayError("Invalid indentation");
            }
        }
        game->loadGame= true;
    }

    void loadConfig() {
        allPercent = 0;
        char optionType[7];

        while (!feof(this->file)) { // repeat until it's not the end of file EOF
            char line[CONFIG_MAX_LINE_LENGTH]; // Buffer to store the line

            fgets(line, CONFIG_MAX_LINE_LENGTH, this->file);
            auto len = strlen(line); // keep line length

            auto indent = 0;
            while (indent < len && line[indent] == ' ') { // cont indent -> number of spaces
                indent++;
            }

            returnToGameInitialSettings();

            switch (indent) {
                case firstIndent:
                    sscanf(line, "%6s", optionType);
                    optionType[6] = 0; // "null termination"
                    if (strncmp(optionType, "config", 7) != 0) {
                        Config::displayError("Unsupported config title");
                    }
                    break;
                case secondIndent:
                    sscanf(line, "%5s", optionType);
                    optionType[5] = 0; // "null termination"
                    if (strncmp(optionType, "BSize", 5) == 0)
                        this->loadBoardSizeAndAddHuman(line);
                    else
                        Config::displayError("Unexpected token");
                    break;
                case thirdIndent:
                    sscanf(line, "%5s", optionType);
                    optionType[5] = 0; // "null termination"
                    if (strncmp(optionType, "Organ", 6) == 0) {
                        this->createOrganismType(line);
                    } else
                        Config::displayError("Unexpected token");
                    break;
                default:
                    Config::displayError("Invalid indentation");
            }
        }
        game->loadGame= true;
    }

    ~Config() {
        fclose(this->file); // close file
    }

private:
    FILE *file;
    std::vector<Organism *> *organisms;
    Game *game;
    int allPercent;

    void returnToGameInitialSettings() {
        this->game->setAzurShield(NEVER_BEFORE);
        this->game->setTurnsNumber(NEVER_BEFORE);
    }

    static void displayError(const char *msg) { // enable to display errors
        printf("s to parse the config file: %s\n", msg);
        exit(1); // end program if there is an error
    }

    void loadAzurShield(char *line) {
        char optionType[6];
        int azur;
        sscanf(line, "%s %d", optionType, &azur);
        this->game->setAzurShield(azur);
    }

    void loadTurnsNumber(char *line) {
        char optionType[6];
        int turnsNumber;
        sscanf(line, "%s %d", optionType, &turnsNumber);
        this->game->setTurnsNumber(turnsNumber);
    }

    void loadOrganism(char *line) {
        int strength, initiative, age, x, y;
        char optionType[6], organismType[11];
        sscanf(line, "%5s %s %d %d %d %d %d", optionType, organismType, &strength, &initiative, &age, &x, &y);

        // "null termination"
        organismType[10] = 0;

        createOrganism(organismType, strength, initiative, age, math_vector(x, y));
    }

    void loadBoardSize(char *line) {
        char optionType[6];
        int width, height;
        sscanf(line, "%s %d %d", optionType, &width, &height);
        this->game->setBgDimensions(width, height);
    }

    void loadBoardSizeAndAddHuman(char *line) {
        loadBoardSize(line);

        // if there is an initialized board, there must be added a Human (once)
        char human[6] = "HUMAN";
        human[5] = 0;
        createOrganism(human, DEFAULT_ORGANISM_TRAIT, DEFAULT_ORGANISM_TRAIT, NEVER_BEFORE,
                       getRandomFreePosition());
    }

    void createOrganismType(char *line) {
        char optionType[6], organismType[12];
        organismType[11] = 0;
        int percent;
        sscanf(line, "%s %s %d", optionType, organismType, &percent);
        allPercent += percent;
        if (allPercent > 100) Config::displayError("too many Organisms! Please, repair config");

        for (int i = 0; i < FIELDS_OCCUPIED_BY_ORGANISM_PERCENT * percent; i++) {
            createOrganism(organismType, DEFAULT_ORGANISM_TRAIT, DEFAULT_ORGANISM_TRAIT, NEVER_BEFORE,
                           getRandomFreePosition());
        }
    }

    math_vector getRandomFreePosition() {
        math_vector position(-1, -1);
        while (position == math_vector(-1, -1)) {
            math_vector randomPos = randomPosition(game->getWidth(), game->getHeight());
            for (auto &organism: game->organisms) {
                if (organism->getPosition() == randomPos) break;
            }
            position = randomPos;
        }
        return position;
    }

    void createOrganism(char *organismType, int strength, int initiative, int age, math_vector position) {
        if (strncmp(organismType, "DANDELION", 10) == 0)
            this->game->organisms.push_back(
                    new Dandelion(this->game, strength == DEFAULT_ORGANISM_TRAIT ? PLANT_STRENGTH : strength,
                                  initiative == DEFAULT_ORGANISM_TRAIT ? PLANT_INITIATIVE : initiative, age, position));
        else if (strncmp(organismType, "GRASS", 6) == 0)
            this->game->organisms.push_back(
                    new Grass(this->game, strength == DEFAULT_ORGANISM_TRAIT ? PLANT_STRENGTH : strength,
                              initiative == DEFAULT_ORGANISM_TRAIT ? PLANT_INITIATIVE : initiative, age, position));
        else if (strncmp(organismType, "GUARANA", 8) == 0)
            this->game->organisms.push_back(
                    new Guarana(this->game, strength == DEFAULT_ORGANISM_TRAIT ? PLANT_STRENGTH : strength,
                                initiative == DEFAULT_ORGANISM_TRAIT ? PLANT_INITIATIVE : initiative, age, position));
        else if (strncmp(organismType, "NIGHTSHADE", 11) == 0)
            this->game->organisms.push_back(
                    new Nightshade(this->game, strength == DEFAULT_ORGANISM_TRAIT ? NIGHTSHADE_STRENGTH : strength,
                                   initiative == DEFAULT_ORGANISM_TRAIT ? PLANT_INITIATIVE : initiative, age,
                                   position));
        else if (strncmp(organismType, "SOSNOWSKY", 10) == 0)
            this->game->organisms.push_back(new Sosnowsky_hogweed(this->game, strength == DEFAULT_ORGANISM_TRAIT
                                                                              ? SOSNOWSKY_STRENGTH : strength,
                                                                  initiative == DEFAULT_ORGANISM_TRAIT
                                                                  ? PLANT_INITIATIVE : initiative, age, position));
        else if (strncmp(organismType, "ANTELOPE", 9) == 0)
            this->game->organisms.push_back(
                    new Antelope(this->game, strength == DEFAULT_ORGANISM_TRAIT ? ANTELOPE_STRENGTH : strength,
                                 initiative == DEFAULT_ORGANISM_TRAIT ? ANTELOPE_INITIATIVE : initiative, age,
                                 position));
        else if (strncmp(organismType, "FOX", 4) == 0)
            this->game->organisms.push_back(
                    new Fox(this->game, strength == DEFAULT_ORGANISM_TRAIT ? FOX_STRENGTH : strength,
                            initiative == DEFAULT_ORGANISM_TRAIT ? FOX_INITIATIVE : initiative, age, position));
        else if (strncmp(organismType, "LAMP", 5) == 0)
            this->game->organisms.push_back(
                    new Lamp(this->game, strength == DEFAULT_ORGANISM_TRAIT ? LAMP_STRENGTH : strength,
                             initiative == DEFAULT_ORGANISM_TRAIT ? LAMP_INITIATIVE : initiative, age, position));
        else if (strncmp(organismType, "TURTLE", 7) == 0)
            this->game->organisms.push_back(
                    new Turtle(this->game, strength == DEFAULT_ORGANISM_TRAIT ? TURTLE_STRENGTH : strength,
                               initiative == DEFAULT_ORGANISM_TRAIT ? TURTLE_INITIATIVE : initiative, age, position));
        else if (strncmp(organismType, "WOLF", 5) == 0)
            this->game->organisms.push_back(
                    new Wolf(this->game, strength == DEFAULT_ORGANISM_TRAIT ? WOLF_STRENGTH : strength,
                             initiative == DEFAULT_ORGANISM_TRAIT ? WOLF_INITIATIVE : initiative, age, position));
        else if (strncmp(organismType, "HUMAN", 6) == 0)
            this->game->organisms.push_back(
                    new Human(this->game, strength == DEFAULT_ORGANISM_TRAIT ? HUMAN_STRENGTH : strength,
                              initiative == DEFAULT_ORGANISM_TRAIT ? HUMAN_INITIATIVE : initiative, age, position));
        else
            Config::displayError("Unexpected token");
    }
};

#endif //C_CONFIG_H
