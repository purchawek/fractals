#include "../include/application.hpp"

application::application(render_ctx& ctx)
: ctx{ctx}, sfgui{}, desktop{}, window{sf::VideoMode(ctx.width(), ctx.height()), "Fractals"},
  gui{sfg::Window::Create()}, renderer{ctx, gui, window} {
   desktop.LoadThemeFromFile("./gui_themes/light.theme");


    sf::RenderWindow window{sf::VideoMode(ctx.width(), ctx.height()), "Fractals"};
    window.resetGLStates();
    gui->SetTitle("Julia menu");
    desktop.Add(gui);
}
void application::run() {
    window.setVerticalSyncEnabled(true);
    while( window.isOpen()) {
        while(window.pollEvent(event)) {
            gui->HandleEvent(event);
            if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                renderer.resized(event);
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
                renderer.handle_key(event);
        }
        desktop.Update(clock.restart().asSeconds());
        window.clear();
        renderer.render(window);
        ctx.set_z0(ctx.get_z0() + ctx.dz0);
        ctx.update_pos();
        ctx.update_zoom();
        sfgui.Display(window);

        window.display();
    }
}