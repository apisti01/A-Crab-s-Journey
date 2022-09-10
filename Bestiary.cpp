//
// Created by apisti01 on 26/08/22.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Bestiary.h"
#include "Room.h"

Bestiary::Bestiary() {
    // initialize by load from file
    std::ifstream file;

    file.open("Data/Enemies.txt");

    // if file is not found it has to be created
    if (!file.is_open())
        createFile();
    else
        file.close();

    // then it's processed
    readFile();
}

void Bestiary::createFile() {
    std::ofstream file("Data/Enemies.txt");

    // enemies
    file << "00 0 0 Squid ChasingRanged 6 4 3 4 360 1 CoralReef" << std::endl;
    file << "01 0 0 PufferFish DefensiveMelee 4 2 2 5 240 1 CoralReef" << std::endl;
    file << "02 0 0 SeaTurtle AggressiveMelee 8 3 6 5 180 1 CoralReef" << std::endl;
    file << "03 0 0 HermitCrab StaticRanged 3 0 7 3 -1 1 CoralReef";

    file.close();
}

void Bestiary::readFile() {
    std::ifstream file("Data/Enemies.txt");
    std::string habitat, line;
    Beast beast;

    // enemies
    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::istringstream ss(line);

            // load the attributes
            ss >> beast.id >> beast.discovered >> beast.analized >> beast.name >> beast.type >> beast.health >> beast.speed
               >> beast.armor >> beast.strength >> beast.triggerRange >> beast.attackTimer;

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
    }
}

void Bestiary::update(Room* room) {
    for (auto &enemy: room->enemyList) {
        auto iter = find_if(beasts.begin(), beasts.end(),
                            [&enemy](const Beast &beast) { return enemy->getId() == beast.id; });

        if (iter != beasts.end()) {
            if (!iter->discovered) {
                iter->discovered = true;
                updateTxtFile();
            }
        }
    }
}

void Bestiary::update(Enemy *enemy) {
    auto iter = find_if(beasts.begin(), beasts.end(),
                        [&enemy](const Beast &beast) { return enemy->getId() == beast.id; });

    if (iter != beasts.end()) {
        if (!iter->analized) {
            iter->analized = true;
            updateTxtFile();
        }
    }
}


void Bestiary::updateTxtFile() {
    // create a new file that substitute the old one
    std::ofstream file("Data/Enemies.txt");

    // load all enemies with their attributes
    for (auto &beast : beasts) {
        file << beast.id << " " << beast.discovered << " " << beast.analized << " " << beast.name << " " << beast.type
             << " " << beast.health << " " << beast.speed << " " << beast.armor << " " << beast.strength << " "
             << beast.triggerRange << " " << beast.attackTimer;

        for (auto &habitat : beast.habitats)
            file << " " << habitat;

        file << std::endl;
    }

    file.close();
}