#include "../../../include/fractals/julia/renderer.hpp"
#include "../../../include/fractals/julia/menu.hpp"
#include "../../../include/fractals/julia/keyboard.hpp"
#include "../../../include/fractals/julia/shader.hpp"

julia_renderer::julia_renderer(render_ctx& ctx)
: ctx { ctx }, window{sf::VideoMode(ctx.width(), ctx.height()), "Fractals"},
sfgui{}, sfg_window{sfg::Window::Create()},
menu{sfg_window, ctx}, keyboard{menu, ctx}, shader{window, ctx} {
    window.setVerticalSyncEnabled(true);
    sfg_window->SetTitle("Julia menu");
    desktop.Add(sfg_window);

    desktop.LoadThemeFromFile("./gui_themes/light.theme");

    window.resetGLStates();

    texture.create(ctx.cs_width(), ctx.cs_height());
    fractal.setTexture(texture);

    // TODO extract it somewhere
    base = 0.0;
    phase = 3.1415 / 12;
    colors = {
            static_cast<float>(fabs(sin(base + phase))),
            static_cast<float>(fabs(sin(base + phase*2))),
            static_cast<float>(fabs(sin(base + phase*3)))
    };
}

void julia_renderer::render() {
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