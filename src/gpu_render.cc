#include <iostream>
#include <cmath>

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

#include <SFGUI/Widgets.hpp>

#include "../include/render_ctx.hpp"

#include "../include/menus/julia.hpp"

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

    window.resetGLStates();

    sf::Texture texture;
    texture.create(ctx.cs_width(), ctx.cs_height());
    sf::Sprite fractal;
    fractal.setTexture(texture);

    sf::Shader shader;
    shader.loadFromFile("shaders/julia_set.glsl", sf::Shader::Fragment);

    if (!shader.isAvailable()) {
        std::cerr << "Couldn't load the shader." << std::endl;
        if (window.isOpen()) window.close();
        return;
    }
    shader.setUniform("z0", sf::Glsl::Vec2(ctx.get_z0().real(), ctx.get_z0().imag()));
    shader.setUniform("offset", sf::Glsl::Vec2(ctx.rel_x(), ctx.rel_y()));
    shader.setUniform("resolution", sf::Glsl::Vec2(ctx.cs_width(), ctx.cs_height()));
    shader.setUniform("factor", (float)ctx.zoom_factor());


    sf::Font font;
    font.loadFromFile("inconsolata-regular.ttf");
    sf::Event event;
    sf::Clock clock;

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
            } else if (event.type == sf::Event::KeyPressed) {
                switch(event.key.code) {
                    case sf::Keyboard::Left:
                        ctx.move(-8, 0);
                    break;
                    case sf::Keyboard::Right:
                        ctx.move(8, 0);
                    break;
                    case sf::Keyboard::Up:
                        ctx.move(0, 8);
                    break;
                    case sf::Keyboard::Down:
                        ctx.move(0, -8);
                    break;
                    case sf::Keyboard::Add:
                        ctx.zoom(-0.001);
                        menu.update_dzoom(ctx);
                    break;
                    case sf::Keyboard::Subtract:
                        ctx.zoom(0.001);
                        menu.update_dzoom(ctx);
                    break;
                    case sf::Keyboard::S:
                        ctx.dz0 += std::complex<double>{-0.00001, -0.00001};
                        menu.update_dz(ctx);
                    break;
                    case sf::Keyboard::R:
                        ctx.dz0 += std::complex<double>{0.00001, 0.00001};
                        menu.update_dz(ctx);
                    break;
                    case sf::Keyboard::Space:
                        ctx.dz0 = {0, 0};
                    break;
                    default:
                    break;
                }
            } else if (event.type == sf::Event::KeyReleased) {
                switch(event.key.code) {
                    case sf::Keyboard::Left:
                        ctx.move(0, 0);
                    break;
                    case sf::Keyboard::Right:
                        ctx.move(0, 0);
                    break;
                    case sf::Keyboard::Up:
                        ctx.move(0, 0);
                    break;
                    case sf::Keyboard::Down:
                        ctx.move(0, 0);
                    break;
                    default:
                    break;
                }
            }
        }
        desktop.Update(clock.restart().asSeconds());
        window.clear();
        window.draw(fractal, &shader);
        ctx.set_z0(ctx.get_z0() + ctx.dz0);
        ctx.update_pos();
        ctx.update_zoom();
        shader.setUniform("factor", (float)ctx.zoom_factor());
        shader.setUniform("offset", sf::Glsl::Vec2(ctx.rel_x(), ctx.rel_y()));
        shader.setUniform("z0", sf::Glsl::Vec2(ctx.get_z0().real(), ctx.get_z0().imag()));
        shader.setUniform("color", colors);
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
