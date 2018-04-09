#include <iostream>

#include <SFML/Graphics.hpp>

#include "../include/render_ctx.hpp"

#include "../include/menu/menu_textitem.hpp"
#include "../include/menu/menu.hpp"

void create_window(render_ctx& ctx) {
    sf::RenderWindow window{sf::VideoMode(ctx.width(), ctx.height()), "Fractals"};
    window.setVerticalSyncEnabled(true);

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
    float z0_x = -0.789;
    shader.setUniform("z0", sf::Glsl::Vec2(z0_x, 0.09));
    shader.setUniform("offset", sf::Glsl::Vec2(ctx.rel_x(), ctx.rel_y()));
    shader.setUniform("resolution", sf::Glsl::Vec2(ctx.cs_width(), ctx.cs_height()));
    shader.setUniform("factor", (float)ctx.zoom_factor());

    float dz0_x = 0.00001;

    sf::Font font;
    font.loadFromFile("inconsolata-regular.ttf");

    sf::Text z0_text;
    z0_text.setFont(font);
    z0_text.setString("z0 = " + std::to_string(z0_x) + ": " + std::to_string(0.09));
    z0_text.setCharacterSize(30);

    sf::Text factor_text;
    factor_text.setFont(font);
    factor_text.setString("factor = " + std::to_string(ctx.zoom_factor()));
    factor_text.setPosition(0, 60);

    menu menubar;
    menubar.set_position({0, (float)ctx.height() - 100});
    menubar.add_item(std::unique_ptr<menu_item>{new menu_textitem(z0_text)});
    menubar.add_item(std::unique_ptr<menu_item>{new menu_textitem(factor_text)});

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
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
                        dz0_x = -0.00001;
                    break;
                    case sf::Keyboard::R:
                        dz0_x = 0.00001;
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

            if (event.type == sf::Event::TextEntered) {
            }
        }

        window.clear();
        window.draw(fractal, &shader);
        z0_x += dz0_x;
        ctx.update_pos();
        ctx.update_zoom();
        shader.setUniform("factor", (float)ctx.zoom_factor());
        shader.setUniform("offset", sf::Glsl::Vec2(ctx.rel_x(), ctx.rel_y()));
        shader.setUniform("z0", sf::Glsl::Vec2(z0_x, 0.12));
        menubar.draw(window);
        window.display();
    }
}
