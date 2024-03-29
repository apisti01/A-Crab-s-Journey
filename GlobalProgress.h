//
// Created by longo on 28/08/2022.
//

#ifndef ACRABSJOURNEY_GLOBALPROGRESS_H
#define ACRABSJOURNEY_GLOBALPROGRESS_H

#include <vector>

struct Character {
    bool unlocked;
    std::string name;
    float health, speed, armor, strength;
    float healthUpgrades, speedUpgrades, armorUpgrades, strengthUpgrades;
    int price;
};

struct Habitat {
    bool unlocked;
    std::string name;
    int price;
    float multiplier;
};

class GlobalProgress {
public:
    // constructor and destructor
    GlobalProgress();
    ~GlobalProgress() = default;

    // progress
    std::vector<Character> characters;
    std::vector<Habitat> habitats;
    int pearls, price;

    // settings
    int language;
    std::string difficulty;
    int effectsVolume, musicVolume;

    // unlock elements
    void unlockCharacter(int currCharacter);
    void unlockMap(int currMap);

    // update the global progress .txt file
    void updateTxtFile();

private:
    void createFile();
    void readFile();
};


#endif //ACRABSJOURNEY_GLOBALPROGRESS_H
