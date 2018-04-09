#include <SFML/Graphics.hpp>

#include "../include/fractals/julia_sets.hpp"
#include "../include/color/color.hpp"
#include "../include/render_ctx.hpp"

#include <iostream>

julia_sets julia{{-0.789, 0.12}};
using Number = std::complex<double>;


inline Number pos_to_comp(int row, int col, render_ctx& ctx) {
    return {
        (double)(col + ctx.rel_x())/ctx.width()*ctx.zoom_factor(),
        (double)(row + ctx.rel_y())/ctx.height()*ctx.zoom_factor()
    };
}



inline void copy_row(int from, int to, sf::Uint8* pixels, render_ctx& ctx) {
    const int base_from = ctx.cs_width() * from * 4;
    const int base_to   = ctx.cs_width() * to * 4;
    int i = base_from, j = base_to;
    for(int col = 0; col < ctx.cs_width(); ++col) {
        pixels[j] = pixels[i];
        pixels[j+1] = pixels[i+1];
        pixels[j+2] = pixels[i+2];
        pixels[j+3] = pixels[i+3];
        i += 4;
        j += 4;
    }
}

inline void copy_cell(int from, int to, sf::Uint8* pixels) {
    pixels[to] = pixels[from];
    pixels[to+1] = pixels[from+1];
    pixels[to+2] = pixels[from+2];
    pixels[to+3] = pixels[from+3];
}


void paintPixels(sf::Uint8* pixels, render_ctx& ctx) {
    static int counter = 0;
    std::cerr << "RENDER START " << counter++  << std::endl;
    for(int row = 0; row < ctx.cs_height(); ++row) {
        int i = ctx.cs_width() * row * 4;
        for(int col = 0; col < ctx.cs_width(); ++col) {
            auto color_ = get_color(julia.fits_cnt(pos_to_comp(row, col, ctx)));
            pixels[i] = color_.r;
            pixels[i + 1] = color_.g;
            pixels[i + 2] = color_.b;
            pixels[i + 3] = color_.a;
            i += 4;
        }
    }
    std::cerr << "RENDER END" << std::endl;
}

void repaintRight(sf::Uint8* pixels, render_ctx& ctx, int how_many) {
    for(int row = 0; row < ctx.cs_height(); ++row) {
        for(int col = 0; col < ctx.cs_width() - how_many; ++col) {
            auto i = (col + ctx.cs_width() * row) * 4;
            copy_cell(i + 4 * how_many, i, pixels);
        }
        for(int col = ctx.cs_width() - how_many; col < ctx.cs_width(); ++col) {
            auto color_ = get_color(julia.fits_cnt(pos_to_comp(row, col, ctx)));
            auto i = (col + ctx.cs_width() * row) * 4;
            pixels[i] = color_.r;
            pixels[i + 1] = color_.g;
            pixels[i + 2] = color_.b;
            pixels[i + 3] = color_.a;
        }
    }
}

void repaintLeft(sf::Uint8* pixels, render_ctx& ctx, int how_many) {
    for(int row = 0; row < ctx.cs_height(); ++row) {
        for(int col = ctx.cs_width() - 1; col >= how_many; --col) {
            auto i = (col + ctx.cs_width() * row) * 4;
            // *(pixels + i) = *(pixels + i + 4);
            copy_cell(i - 4 * how_many, i, pixels);
        }
        for(int col = how_many - 1; col >= 0; --col) {
            auto color_ = get_color(julia.fits_cnt(pos_to_comp(row, col, ctx)));
            auto i = (col + ctx.cs_width() * row) * 4;
            pixels[i] = color_.r;
            pixels[i + 1] = color_.g;
            pixels[i + 2] = color_.b;
            pixels[i + 3] = color_.a;
        }
    }
}

void repaintUp(sf::Uint8* pixels, render_ctx& ctx, int how_many) {
    for(int row = ctx.cs_height() - 1; row >= how_many; --row) {
        copy_row(row - how_many, row, pixels, ctx);
    }
    for(int row = how_many; row >= 0; --row) {
        for(int col = 0; col < ctx.cs_width(); ++col) {
            auto color_ = get_color(julia.fits_cnt(pos_to_comp(row, col, ctx)));
            auto i = (col + ctx.cs_width() * row) * 4;
            pixels[i] = color_.r;
            pixels[i + 1] = color_.g;
            pixels[i + 2] = color_.b;
            pixels[i + 3] = color_.a;
        }
    }
}

void repaintDown(sf::Uint8* pixels, render_ctx& ctx, int how_many) {
    for(int row = 0; row < ctx.cs_height() - how_many; ++row) {
        copy_row(how_many + row, row, pixels, ctx);
    }
    for(int row = ctx.cs_height() - how_many; row < ctx.cs_height(); ++row) {
        for(int col = 0; col < ctx.cs_width(); ++col) {
            auto i = (col + ctx.cs_width() * row) * 4;
            auto color_ = get_color(julia.fits_cnt(pos_to_comp(row, col, ctx)));
            pixels[i] = color_.r;
            pixels[i + 1] = color_.g;
            pixels[i + 2] = color_.b;
            pixels[i + 3] = color_.a;
        }
    }
}

void create_window(render_ctx& ctx) {
    sf::Uint8* pixels = new sf::Uint8[ctx.cs_width() * ctx.cs_height() * 4];
    paintPixels(pixels, ctx);

    sf::Texture texture;
    texture.create(ctx.cs_width(), ctx.cs_height());
    sf::Sprite fractal;
    fractal.setTexture(texture);


    sf::RenderWindow window(sf::VideoMode(ctx.width(), ctx.height()), "Fractals");
    window.setVerticalSyncEnabled(true);
    fractal.setPosition(
        ctx.width() / 2 + ctx.rel_x(),
        ctx.height() / 2 + ctx.rel_y());


    texture.update(pixels);
    texture.copyToImage().saveToFile("co_tam.png");

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
                texture.update(pixels);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                ctx.move(-8, 0);
                repaintLeft(pixels, ctx, 8);
                texture.update(pixels);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                ctx.move(8, 0);
                repaintRight(pixels, ctx, 8);
                texture.update(pixels);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                ctx.move(0, -8);
                repaintUp(pixels, ctx, 8);
                texture.update(pixels);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                ctx.move(0, 8);
                repaintDown(pixels, ctx, 8);
                texture.update(pixels);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
                ctx.zoom(0.5);
                // paintPixels(pixels, ctx);
                texture.update(pixels);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                ctx.zoom(2);
                // paintPixels(pixels, ctx);
                texture.update(pixels);
            }
        }
        julia.z0 += Number{0, 0.0001};
        paintPixels(pixels, ctx);
        ctx.update_pos();
        texture.update(pixels);
        window.clear();
        window.draw(fractal);
        window.display();
    }

    delete [] pixels;
}
