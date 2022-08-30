//
// Created by longo on 28/08/2022.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "GlobalProgress.h"

GlobalProgress::GlobalProgress() {
    // initialize by load from file
    std::ifstream file("Global Progress.txt");

    // if file is not found
    if (!file.is_open()) {
        // it has to be created
        std::ofstream file ("Global Progress.txt");

        // characters
        file << "1 BrownCrab 5 3 1 3 0 0 0 0 0" << std::endl;
        file << "0 FiddlerCrab 3 4 0.5 6 0 0 0 0 500" << std::endl;
        file << "0 TriangleTannerCrab 4 6 0.5 3 0 0 0 0 500" << std::endl;
        file << "0 AsianGreatPaddle 6 3 1.5 5 0 0 0 0 500" << std::endl;
        file << std::endl;

        // maps
        file << "1 CoralReef 0 1" << std::endl;
        file << "0 MangroveForest 200 1.5" << std::endl;
        file << "0 TemperateReef 400 1.5" << std::endl;
        file << "0 KelpForest 400 1.5" << std::endl;
        file << "0 PosidoniaMeadow 400 1.5" << std::endl;
        file << "0 IceFloe 600 2" << std::endl;
        file << std::endl;

        // pearls
        file << "0" << std::endl;
        file << std::endl;

        // settings values
        file << "0 Normal 10 10" << std::endl;
        file << std::endl;

        file.close();
    }

    // then it is processed
    file.open("Global Progress.txt");
    std::string line;
    Character character;
    Habitat habitat;

    // characters
    while (std::getline(file, line) && line != "") {
        std::istringstream ss(line);

        // load the attributes
        ss >> character.unlocked >> character.name >> character.health >> character.speed >> character.armor >>
           character.strength >> character.healthUpgrades >> character.speedUpgrades >> character.armorUpgrades >>
           character.strengthUpgrades >> character.price;

        // add the beast to the list
        characters.push_back(character);
        // clear the struct variable for the next enemy
        character = {};
    }

    // habitats
    while (std::getline(file, line) && line != "") {
        std::istringstream ss(line);

        // load the attributes
        ss >> habitat.unlocked >> habitat.name >> habitat.price;

        // add the beast to the list
        habitats.push_back(habitat);
        // clear the struct variable for the next enemy
        habitat = {};
    }

    // pearls
    file >> pearls >> language >> difficulty >> effectsVolume >> musicVolume;
}