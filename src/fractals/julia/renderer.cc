// #include <SFML/Graphics.hpp>

#include "../../../include/fractals/julia/renderer.hpp"
#include "../../../include/fractals/julia/menu.hpp"
#include "../../../include/fractals/julia/keyboard.hpp"
#include "../../../include/fractals/julia/shader.hpp"

static constexpr double BASE_DEF = 0.0;
static constexpr double PHASE_DEF = 3.1415 / 12;


julia_renderer::julia_renderer(render_ctx& ctx, sfg::Window::Ptr gui, sf::RenderWindow& window)
: ctx { ctx }, menu{gui, ctx}, keyboard{menu, ctx, *this}, shader{window, ctx} {
    texture.create(ctx.cs_width(), ctx.cs_height());
    fractal.setTexture(texture);

    // TODO extract it somewhere
    base = BASE_DEF;
    phase = PHASE_DEF;
    colors = {
            static_cast<float>(fabs(sin(base + phase))),
            static_cast<float>(fabs(sin(base + phase*2))),
            static_cast<float>(fabs(sin(base + phase*3)))
    };
}


void julia_renderer::resized(const sf::Event& event) {
    texture.create(event.size.width, event.size.height);
    fractal.setTexture(texture, true);
}

void julia_renderer::handle_key(const sf::Event& event) {
    keyboard.handle_event(event);
}

void julia_renderer::render(sf::RenderWindow& window) {
    window.draw(fractal, shader.get());
    shader.update(colors);
    colors = {
            static_cast<float>(fabs(sin(base + phase))),
            static_cast<float>(fabs(sin(base + phase*2))),
            static_cast<float>(fabs(sin(base + phase*3)))
    };
    menu.update(ctx);
    base += 0.0002;
}

void julia_renderer::swap_shader() {
    shader.swap_shader();
}