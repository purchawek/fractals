#include <SFML/Graphics.hpp>

#include "../lib/purlib/argparser/arg_parser.hpp"

#include "../include/fractals/julia_sets.hpp"
#include "../include/color/color.hpp"
#include "../include/render_ctx.hpp"

// #include "cpu_render.cc"
#include "gpu_render.cc"

#include <iostream>

#include <complex>

using pur::arg_parser;
using pur::arg;

bool validate_params(int width, int height) {
    return width > 10 && height > 10;
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
    ctx.resize(width, height);
    create_window(ctx);
}
