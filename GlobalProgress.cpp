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
    std::string line;

    Character character;
    Habitat habitat;
    if (file.is_open()) {
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
        file >> pearls;
    } else {
        std::cout << "File dei dati sui nemici non trovato" << std::endl;
    }
}