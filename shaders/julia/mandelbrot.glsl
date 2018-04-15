uniform vec3 color;
uniform vec2 resolution;
uniform vec2 offset;
uniform float factor;
uniform vec2 z0;

vec3 iters(float x, float y) {
    float zx = z0[0];
    float zy = z0[1];
    float result = 0.0;
    float tmp;
    for(; result < 100.0; ++result) {
        if ((zx * zx + zy * zy) >= 4.0) return vec3(result, zx, zy);
        tmp = zx;
        zx = zx*zx - zy*zy + x;
        zy = 2.0 * tmp * zy + y;
    }
    return vec3(result, zx, zy);
}

vec4 get_color(vec3 iter, float max_iter) {
    float modulus = sqrt(iter[1]*iter[1] + iter[2]*iter[2]);
    float div = (iter[0] - log(log(modulus)))/100.0;
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

