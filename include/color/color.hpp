#ifndef COLOR_HPP
#define COLOR_HPP


struct color {
    unsigned char r, g, b, a;
};

inline color get_color(double iter, int max_iter=100) {
    iter /= max_iter;
    unsigned char color_g = (1-iter*(iter - 2)) * 255;
    unsigned char color_r = color_g, color_b = color_g;
    if( color_g > 100 ) color_r /= 2, color_b /= 3;
    return {color_r, color_g, color_b, 255};
}

#endif
