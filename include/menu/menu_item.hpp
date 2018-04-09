#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <SFML/Graphics.hpp>

class menu_item {
public:

    virtual ~menu_item() {}
    virtual sf::FloatRect get_global_bounds() const = 0;
    virtual bool on_selected() = 0;
    virtual bool on_unselected() = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual void set_position(const sf::Vector2f&) = 0;
    virtual const sf::Vector2f& get_position() const = 0;
};


#endif 
