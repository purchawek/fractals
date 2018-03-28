#include <SFML/Graphics.hpp>

#include "../lib/purlib/argparser/arg_parser.hpp"

#include "../include/fractals/julia_sets.hpp"
#include "../include/color/color.hpp"
#include "../include/render_ctx.hpp"

#include <iostream>

#include <complex>

using Number = std::complex<double>;

using pur::arg_parser;
using pur::arg;

julia_sets julia{{-0.789, 0.12}};

bool validate_params(int width, int height) {
    return width > 10 && height > 10;
}

inline Number pos_to_comp(int row, int col, render_ctx& ctx) {
    return {(double)(col)/ctx.width(), (double)(row)/ctx.height()};
}

void paintPixels(sf::Uint8* pixels, render_ctx& ctx) {
    for(int col = 0; col < ctx.width(); ++col) {
        for(int row = 0; row < ctx.height(); ++row) {
            auto color_ = get_color(julia.fits_cnt(pos_to_comp(row, col, ctx)));
            auto i = (col + ctx.width() * row) * 4;
            pixels[i] = color_.r;
            pixels[i + 1] = color_.g;
            pixels[i + 2] = color_.b;
            pixels[i + 3] = color_.a;
        }
    }
}


void create_window(render_ctx& ctx) {
    sf::Uint8 pixels[ctx.width() * ctx.height() * 4];
    std::cerr << "RENDER START" << std::endl;
    paintPixels(pixels, ctx);
    std::cerr << "RENDER END" << std::endl;

    

    sf::Texture texture;
    texture.create(ctx.width(), ctx.height());
    sf::Sprite fractal;
    fractal.setTexture(texture);


    sf::Image image;
    sf::RenderWindow window(sf::VideoMode(ctx.width(), ctx.height()), "Fractals");
    window.setVerticalSyncEnabled(true);
    fractal.setPosition(
        ctx.width() / 2 + ctx.rel_x(),
        ctx.height() / 2 + ctx.rel_y());


    texture.update(pixels);

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                ctx.resize(window.getSize().x, window.getSize().y);
                fractal.setPosition(
                    ctx.width() / 2 + ctx.rel_x(),
                    ctx.height() / 2 + ctx.rel_y());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                ctx.move(-1, 0);
                fractal.setPosition(
                    ctx.width() / 2 + ctx.rel_x(),
                    ctx.height() / 2 + ctx.rel_y());
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                ctx.move(1, 0);
                fractal.setPosition(
                    ctx.width() / 2 + ctx.rel_x(),
                    ctx.height() / 2 + ctx.rel_y());
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                ctx.move(0, -1);
                fractal.setPosition(
                    ctx.width() / 2 + ctx.rel_x(),
                    ctx.height() / 2 + ctx.rel_y());
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                ctx.move(0, 1);
                fractal.setPosition(
                    ctx.width() / 2 + ctx.rel_x(),
                    ctx.height() / 2 + ctx.rel_y());
            }
        }

        texture.update(pixels);
        window.clear();
        window.draw(fractal);
        window.display();

        std::cerr << "Hello" << std::endl;
    }
}

int main(int argc, char **argv) {
    arg_parser parser;
    parser.register_arg(arg<int>{"--width", 640});
    parser.register_arg(arg<int>{"--height", 480});

    if (!parser.parse_program_params(argc, argv)) return 1;

    int width = parser.get_val<int>("--width");
    int height = parser.get_val<int>("--height");

    if (!validate_params(width, height)) {
        std::cerr << "Invalid screen dimensions" << std::endl;
        return 1;
    }

    render_ctx ctx{width, height};

    create_window(ctx);
}

