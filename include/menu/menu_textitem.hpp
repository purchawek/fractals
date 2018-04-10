#ifndef MENU_TEXTITEM_HPP
#define MENU_TEXTITEM_HPP
#include <SFML/Graphics.hpp>

#include "menu_item.hpp"


class menu_textitem : public menu_item {
    sf::Text content;
public:
    menu_textitem(sf::Text content_)
    : content{std::move(content_)} {}

    sf::FloatRect get_global_bounds() const override;
    bool on_selected() override;
    bool on_unselected() override;

    void draw(sf::RenderWindow&) const override;

    void set_position(const sf::Vector2f&) override;
    const sf::Vector2f& get_position() const override;

    void set_text(const std::string& text);

    void set_dimensions(const sf::FloatRect&) override;

    const sf::FloatRect& get_dimensions() const override;
};

bool menu_textitem::on_selected() {
    content.setFillColor(sf::Color::Red);
    return true;
}

bool menu_textitem::on_unselected() {
    content.setFillColor(sf::Color::Black);
    return true;
}

void menu_textitem::draw(sf::RenderWindow& window) const {
    window.draw(content);
}

void menu_textitem::set_position(const sf::Vector2f& pos) {
    content.setPosition(pos);
}

const sf::Vector2f& menu_textitem::get_position() const {
    return content.getPosition();
}

sf::FloatRect menu_textitem::get_global_bounds() const {
    return {};
}

void menu_textitem::set_text(const std::string& text) {
    content.setString(text);
}

void menu_textitem::set_dimensions(const sf::FloatRect& dimensions) {
    content.setPosition(dimensions.left, dimensions.top);
    content.setCharacterSize(dimensions.height);
}

#endif
