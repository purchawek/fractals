#ifndef JULIA_KEYBOARD_HPP
#define JULIA_KEYBOARD_HPP

#include <SFML/Graphics.hpp>

#include "../../render_ctx.hpp"
#include "menu.hpp"

class julia_renderer;

class julia_keyboard {
    render_ctx& ctx;
    julia_menu& menu;
    julia_renderer& renderer;

public:
    julia_keyboard(julia_menu& menu, render_ctx& ctx, julia_renderer& renderer)
    : ctx{ ctx }, menu { menu }, renderer { renderer } {}

    void handle_event(const sf::Event& evt);
};

#endif