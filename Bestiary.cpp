//
// Created by apisti01 on 26/08/22.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Bestiary.h"

Bestiary::Bestiary() {
    // initialize by load from file
    std::ifstream file("Enemy_source_files/Enemy Data.txt");
    std::string habitat, line;

    Beast beast;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::istringstream ss(line);

            // load the attributes
            ss >> beast.id >> beast.discovered >> beast.name >> beast.type >> beast.health >> beast.speed
               >> beast.armor >> beast.strength >> beast.triggerRange;
            // and the habitats in which the enemy can be found
            int i = 0;
            while (ss >> habitat) {
                beast.habitats.push_back(habitat);
                i++;
            }

            // add the beast to the list
            beasts.push_back(beast);
            // clear the struct variable for the next enemy
            beast = {};
        }
    } else {
        std::cout << "File dei dati sui nemici non trovato" << std::endl;
    }
}

void Bestiary::update(Room* room) {}

void Bestiary::update(Enemy *enemy) {}
