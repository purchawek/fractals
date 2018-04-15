#include "../../../include/fractals/julia/keyboard.hpp"


void julia_keyboard::handle_event(const sf::Event& event) {
   if (event.type == sf::Event::KeyPressed) {
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