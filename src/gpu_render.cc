#include <iostream>
#include <cmath>

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

#include <SFGUI/Widgets.hpp>

#include "../include/render_ctx.hpp"

#include "../include/fractal/julia/menu.hpp"
#include "../include/fractal/julia/keyboard.hpp"
#include "../include/fractal/julia/shader.hpp"

void create_window(render_ctx& ctx) {
    sf::RenderWindow window{sf::VideoMode(ctx.width(), ctx.height()), "Fractals"};
    window.setVerticalSyncEnabled(true);

    sfg::SFGUI sfgui;

    auto sfg_window = sfg::Window::Create();
    sfg_window->SetTitle("MenuBar");

    sfg::Desktop desktop;
    desktop.Add(sfg_window);

    desktop.LoadThemeFromFile("./gui_themes/light.theme");

    julia_menu menu(sfg_window, ctx);
    julia_keyboard keyboard(ctx, menu);

    window.resetGLStates();

    sf::Texture texture;
    texture.create(ctx.cs_width(), ctx.cs_height());
    sf::Sprite fractal;
    fractal.setTexture(texture);

    julia_shader shader(window, ctx);

    sf::Event event;
    sf::Clock clock;


    // TODO create a separate class for changing the color with time
    double base = 0.0;
    double phase = 3.1415 / 12;
    sf::Vector3f colors{
            static_cast<float>(sin(base + phase)),
            static_cast<float>(sin(base + phase*2)),
            static_cast<float>(sin(base + phase*3))
    };

    while (window.isOpen()) {
        while(window.pollEvent(event)) {
            sfg_window->HandleEvent(event);
            if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                texture.create(event.size.width, event.size.height);
                fractal.setTexture(texture, true);
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            keyboard.handle_event(event);
        }
        desktop.Update(clock.restart().asSeconds());
        window.clear();
        window.draw(fractal, shader.get());
        ctx.set_z0(ctx.get_z0() + ctx.dz0);
        ctx.update_pos();
        ctx.update_zoom();
        shader.update(colors);
        colors = {
                static_cast<float>(fabs(sin(base + phase))),
                static_cast<float>(fabs(sin(base + phase*2))),
                static_cast<float>(fabs(sin(base + phase*3)))
        };
        menu.update(ctx);
        sfgui.Display(window);
        base += 0.0002;
        window.display();
    }
}
