uniform vec3 color;
uniform vec2 resolution;
uniform vec2 offset;
uniform float factor;
uniform vec2 z0;

vec3 iters(float x, float y) {
    float result = 0.0;
    float tmp;
    for(; result < 100.0; ++result) {
        if ((x * x + y * y) >= 4.0) return result;
        tmp = x;
        x = x*x - y*y + z0[0];
        y = 2.0 * tmp * y + z0[1];
    }
    return vec3(result, x, y);
}

vec4 get_color(vec3 iter, float max_iter) {
    float div = iter[0] / max_iter;
    float color_r = div * color[0];
    float color_g = div * color[1];
    float color_b = div * color[2];
    return vec4(color_r, color_g, color_b, 1.0);
}

void main( void ) {
    float pos_x = (gl_FragCoord.x + offset[0])/resolution[0]*factor;
    float pos_y = (gl_FragCoord.y + offset[1])/resolution[1]*factor;
    vec3 it = iters(pos_x, pos_y);
    gl_FragColor = get_color(it, 100.0);
}
