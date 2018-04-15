#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include "render_ctx.hpp"

#include "fractals/julia/renderer.hpp"

class application {
    render_ctx& ctx;

    sfg::SFGUI sfgui;
    sfg::Desktop desktop;
    sf::RenderWindow window;
    sfg::Window::Ptr gui;


    // TODO currently only julia
    julia_renderer renderer;

    sf::Event event;
    sf::Clock clock;
public:
    application(render_ctx& ctx);
    void run();
};



#endif