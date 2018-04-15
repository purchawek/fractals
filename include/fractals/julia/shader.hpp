#ifndef JULIA_SHADER_HPP
#define JULIA_SHADER_HPP

#include <iostream>

#include <SFML/Graphics.hpp>
#include "../../render_ctx.hpp"

static const int SHADERS_CNT = 2;

static const char* SHADERS_PATHS[SHADERS_CNT] = {
    "shaders/julia/linear.glsl",
    "shaders/julia/loglog.glsl"
};

class julia_shader {
    render_ctx& ctx;
    std::array<sf::Shader, SHADERS_CNT> shaders;

    sf::Shader* shader;
public:
    julia_shader(sf::RenderWindow& window, render_ctx& ctx)
    : ctx{ctx} {
        if (!initialize_shaders()) {
            if (window.isOpen()) window.close();
            return;
        }

        if (!shader->isAvailable()) {
            std::cerr << "Couldn't load the shader." << std::endl;
            if (window.isOpen()) window.close();
            return;
        }
        update();
    }

    void update() {
        shader->setUniform("z0", sf::Glsl::Vec2(ctx.get_z0().real(), ctx.get_z0().imag()));
        shader->setUniform("offset", sf::Glsl::Vec2(ctx.rel_x(), ctx.rel_y()));
        shader->setUniform("factor", (float)ctx.zoom_factor());
    }

    void update(const sf::Vector3f& colors) {
        update();
        shader->setUniform("color", colors);
    }

    const sf::Shader* get() const noexcept { return shader; }

    void swap_shader() {
        for(size_t i = 0; i < SHADERS_CNT; ++i)
            if(shader == &shaders[i]) {
                shader = &shaders[(i+1)%SHADERS_CNT];
                return;
            }
        update();
    }

private:
    bool initialize_shaders() {
        for(size_t i = 0; i < SHADERS_CNT; ++i) {
            shaders[i].loadFromFile(SHADERS_PATHS[i], sf::Shader::Fragment);
            if(!shaders[i].isAvailable()) {
                std::cerr << "Couldn't load the shader from file " << SHADERS_PATHS[i] << std::endl;
                return false;         
            }
            shaders[i].setUniform("resolution", sf::Glsl::Vec2(ctx.cs_width(), ctx.cs_height()));
        }
        shader = &shaders[0];
        return true;
    }
};



#endif 