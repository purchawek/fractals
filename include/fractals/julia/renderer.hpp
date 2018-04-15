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


    // the GUI context
    sf::RenderWindow window;
    sfg::SFGUI sfgui;
    sfg::Window::Ptr sfg_window;
    sfg::Desktop desktop;

    // julia-specific handlers
    julia_menu menu;
    julia_keyboard keyboard;
    julia_shader shader;


    // for rendering the fractal itself
    sf::Texture texture;
    sf::Sprite fractal;

    // for reacting at events and animating the GUI
    sf::Event event;
    sf::Clock clock;

    // for changing the color in time (will be moved from here)
    sf::Vector3f colors;
    double base, phase;

public:
    julia_renderer(render_ctx& ctx);

    void render();


};



#endif 