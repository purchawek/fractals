#include <iostream>

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

#include <SFGUI/Widgets.hpp>

#include "../include/render_ctx.hpp"

void create_window(render_ctx& ctx) {
    sf::RenderWindow window{sf::VideoMode(ctx.width(), ctx.height()), "Fractals"};
    window.setVerticalSyncEnabled(true);

    float z0_x = -0.789;
    float z0_y = 0.15;

    sfg::SFGUI sfgui;

    auto z0_label = sfg::Label::Create("Hello label");
    auto factor_label = sfg::Label::Create("Hello factor");
    auto dfactor_label = sfg::Label::Create("Hello dfactor");
    auto sfg_window = sfg::Window::Create();
    sfg_window->SetTitle("MenuBar");

    sfg::Desktop desktop;
    desktop.Add(sfg_window);

    auto z0_Re = sfg::Entry::Create();
    z0_Re->SetRequisition(sf::Vector2f{80.0f, 0.0f});
    auto z0_Im = sfg::Entry::Create();
    z0_Im->SetRequisition(sf::Vector2f{80.0f, 0.0f});

    auto accept_btn = sfg::Button::Create("Accept");

    accept_btn->GetSignal(sfg::Widget::OnMouseLeftPress).Connect([&z0_Re, &z0_Im, &z0_x, &z0_y] {
        z0_x = std::stod(std::string{z0_Re->GetText()});
        z0_y = std::stod(std::string{z0_Im->GetText()});
            });

    auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );
    box->Pack(z0_label);
    box->Pack(factor_label);
    box->Pack(dfactor_label);
    box->Pack(z0_Re);
    box->Pack(z0_Im);
    box->Pack(accept_btn);

    sfg_window->Add(box);

    window.resetGLStates();

    sf::Texture texture;
    texture.create(ctx.cs_width(), ctx.cs_height());
    sf::Sprite fractal;
    fractal.setTexture(texture);

    sf::Shader shader;
    shader.loadFromFile("julia_set.glsl", sf::Shader::Fragment);

    if (!shader.isAvailable()) {
        std::cerr << "Couldn't load the shader." << std::endl;
        if (window.isOpen()) window.close();
        return;
    }
    shader.setUniform("z0", sf::Glsl::Vec2(z0_x, z0_y));
    shader.setUniform("offset", sf::Glsl::Vec2(ctx.rel_x(), ctx.rel_y()));
    shader.setUniform("resolution", sf::Glsl::Vec2(ctx.cs_width(), ctx.cs_height()));
    shader.setUniform("factor", (float)ctx.zoom_factor());

    float dz0_x = 0.00001;

    sf::Font font;
    font.loadFromFile("inconsolata-regular.ttf");
    sf::Event event;
    sf::Clock clock;

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
                    break;
                    case sf::Keyboard::Subtract:
                        ctx.zoom(0.001);
                    break;
                    case sf::Keyboard::S:
                        dz0_x += -0.00001;
                    break;
                    case sf::Keyboard::R:
                        dz0_x += 0.00001;
                    break;
                    case sf::Keyboard::Space:
                        dz0_x = 0.0;
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
        z0_x += dz0_x;
        z0_y -= dz0_x;
        ctx.update_pos();
        ctx.update_zoom();
        shader.setUniform("factor", (float)ctx.zoom_factor());
        shader.setUniform("offset", sf::Glsl::Vec2(ctx.rel_x(), ctx.rel_y()));
        shader.setUniform("z0", sf::Glsl::Vec2(z0_x, z0_y));
        z0_label->SetText("z0 = (" + std::to_string(z0_x) + ", " + std::to_string(z0_y) + ")");
        factor_label->SetText("factor = " + std::to_string(ctx.zoom_factor()));
        dfactor_label->SetText("d_factor = " + std::to_string(ctx.d_zoom()));
        if(dz0_x != 0) {
            z0_Re->SetText(std::to_string(z0_x));
            z0_Im->SetText(std::to_string(z0_y));
        }
        sfgui.Display(window);
        window.display();
    }
}
