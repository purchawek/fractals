#ifndef JULIA_KEYBOARD_HPP
#define JULIA_KEYBOARD_HPP

#include <SFML/Graphics.hpp>

#include "../../render_ctx.hpp"
#include "menu.hpp"

class julia_keyboard {
    render_ctx& ctx;
    julia_menu& menu;

public:
    julia_keyboard(render_ctx& ctx, julia_menu& menu)
    : ctx{ ctx }, menu { menu } {}

    void handle_event(const sf::Event& evt);
};

#endif