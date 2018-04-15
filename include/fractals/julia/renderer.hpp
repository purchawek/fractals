#ifndef JULIA_RENDERER_HPP
#define JULIA_RENDERER_HPP

#include <SFML/Graphics.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include "menu.hpp"
#include "shader.hpp"
#include "keyboard.hpp"

#include "../../render_ctx.hpp"

class julia_renderer {
    // fractal context
    render_ctx& ctx;

    // julia-specific handlers
    julia_menu menu;
    julia_keyboard keyboard;
    julia_shader shader;


    // for rendering the fractal itself
    sf::Texture texture;
    sf::Sprite fractal;

    // for changing the color in time (will be moved from here)
    sf::Vector3f colors;
    double base, phase;

public:
    julia_renderer(render_ctx& ctx, sfg::Window::Ptr gui, sf::RenderWindow& window);

    void render(sf::RenderWindow& window);

    void resized(const sf::Event& event);
    void handle_key(const sf::Event& event);
    void swap_shader();

};



#endif 