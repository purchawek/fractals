#include <pur/argparser/arg_parser.hpp>
#include <pur/argparser/helper.hpp>

#include "../include/color/color.hpp"
#include "../include/render_ctx.hpp"

// #include "cpu_render.cc"
// #include "gpu_render.cc"

#include "../include/fractals/julia/renderer.hpp"

#include <iostream>

#include <complex>

using pur::arg_parser;
using pur::arg;

bool validate_params(int width, int height) {
    return width > 10 && height > 10;
}

int main(int argc, char **argv) {
    arg_parser parser;
    parser.register_arg(arg<int>{"--width", 640}
        .set_help("Initial value for the width of the canvas"));
    parser.register_arg(arg<int>{"--height", 480}
        .set_help("Initial value for the height of the canvas"));

    pur::helper helper;

    pur::helper::section subtitle{"Fractals", "Renders julia sets"};

    try {
        parser.parse_program_params(argc, argv);
    } catch (const std::exception& exc) {
        helper.add_section(subtitle)
            .add_args_section(parser.get_args())
            .print_help();
        return 1;
    }

    int width = parser.get_val<int>("--width");
    int height = parser.get_val<int>("--height");

    if (!validate_params(width, height)) {
        std::cerr << "Invalid screen dimensions" << std::endl;
        return 1;
    }

    render_ctx ctx{width, height};
    ctx.resize(width, height);
    // create_window(ctx);
    julia_renderer renderer{ctx};
    renderer.render();
}
