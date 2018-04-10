#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>

#include <vector>

#include <memory>

#include <SFML/Graphics.hpp>

#include "menu_item.hpp"

class menu {
    std::vector<std::shared_ptr<menu_item>> items;
    sf::Vector2f position;
    sf::Vector2f size;

public:
    menu(const sf::FloatRect& dimensions);

    void add_item(std::shared_ptr<menu_item> item);
    
    void draw(sf::RenderWindow& window) const;

    void set_position(const sf::Vector2f& position_);
    const sf::Vector2f& get_position() const;

    bool on_click(const sf::Event& e);
};

menu::menu(const sf::FloatRect& dimensions)
: position{dimensions.left, dimensions.top},
  size{dimensions.width, dimensions.height}  {
}

void menu::add_item(std::shared_ptr<menu_item> item) {
    item->set_position(item->get_position() + position);
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

bool menu::on_click(const sf::Event& e) {


    return false;
}

#endif 
