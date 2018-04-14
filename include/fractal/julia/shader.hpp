#ifndef JULIA_SHADER_HPP
#define JULIA_SHADER_HPP

#include <iostream>

#include <SFML/Graphics.hpp>
#include "../../render_ctx.hpp"


class julia_shader {
    render_ctx& ctx;
    sf::Shader shader;
public:
    julia_shader(sf::RenderWindow& window, render_ctx& ctx)
    : ctx{ctx} {
        shader.loadFromFile("shaders/julia_set.glsl", sf::Shader::Fragment);
        if (!shader.isAvailable()) {
            std::cerr << "Couldn't load the shader." << std::endl;
            if (window.isOpen()) window.close();
            return;
        }
        shader.setUniform("resolution", sf::Glsl::Vec2(ctx.cs_width(), ctx.cs_height()));
        update();
    }

    void update() {
        shader.setUniform("z0", sf::Glsl::Vec2(ctx.get_z0().real(), ctx.get_z0().imag()));
        shader.setUniform("offset", sf::Glsl::Vec2(ctx.rel_x(), ctx.rel_y()));
        shader.setUniform("factor", (float)ctx.zoom_factor());
    }

    void update(const sf::Vector3f& colors) {
        update();
        shader.setUniform("color", colors);
    }

    const sf::Shader* get() const noexcept { return &shader; }
};



#endif 