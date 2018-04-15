#include <iostream>
#include <complex>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include <pur/argparser/arg_parser.hpp>
#include <pur/argparser/helper.hpp>

#include "../include/color/color.hpp"
#include "../include/render_ctx.hpp"

#include "../include/application.hpp"

using pur::arg_parser;
using pur::arg;

bool validate_params(const arg_parser& parser) {
    int width = parser.get_val<int>("--width");
    int height = parser.get_val<int>("--height");
    return width > 10 && height > 10;
}

render_ctx create_ctx(const arg_parser& parser) {
    int width = parser.get_val<int>("--width");
    int height = parser.get_val<int>("--height");
    render_ctx ctx{width, height};
    ctx.resize(width, height);
    return ctx;
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

    if (!validate_params(parser)) {
        std::cerr << "Invalid program parameters, quitting" << std::endl;
        return 1;
    }
    auto ctx = create_ctx(parser);
    application app{ctx};
    app.run();
}
