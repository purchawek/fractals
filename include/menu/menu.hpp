#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>

#include <vector>

#include <SFML/Graphics.hpp>

#include "menu_item.hpp"

class menu {
    std::vector<std::unique_ptr<menu_item>> items;
    sf::Vector2f position;

public:
    void add_item(std::unique_ptr<menu_item>&& item);
    
    void draw(sf::RenderWindow& window) const;

    void set_position(const sf::Vector2f& position_);
    const sf::Vector2f& get_position() const;
};

void menu::add_item(std::unique_ptr<menu_item>&& item) {
    item->set_position(item->get_position() + position);
    std::cout << item->get_position().x << ": " << item->get_position().y << std::endl;
    items.push_back(std::move(item));
}

void menu::draw(sf::RenderWindow& window) const {
    for(const auto& it: items)
        it->draw(window);
}

void menu::set_position(const sf::Vector2f& position_) {
    position = position_;
}

const sf::Vector2f& menu::get_position() const {
    return position;
}

#endif 
