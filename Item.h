//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_ITEM_H
#define MAIN_CPP_ITEM_H

#include <string>
#include <SFML/Graphics.hpp>

enum class ItemRarity {
    Common,
    NonCommon,
    Rare,
    Legendary
};

class Item {
public:
    // Constructor and Destructor
    explicit Item(std::string  name, ItemRarity rarity = ItemRarity::Common, int price = 50, int quantity = 1, int slotOccupied = 1);
    virtual ~Item() = default;

    // getter and setter for quantity
    int getQuantity() const {
        return quantity;
    }
    void setQuantity(int quantity) {
        Item::quantity = quantity;
    }

protected:
    // Item name
    std::string name;

    // Quantity own
    int quantity;

    // Stats for the value on th market
    ItemRarity rarity;
    int price;

    // Slot occupied when in the Inventory
    int slotOccupied;

    // SFML sprite
    sf::Sprite body;

private:

};


#endif //MAIN_CPP_ITEM_H
