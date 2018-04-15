#ifndef RENDER_CTX
#define RENDER_CTX

#include <complex>


struct render_ctx {
    render_ctx(int c_width, int c_height)
    : c_width_{c_width},
      c_height_{c_height},
      width_{c_width},
      height_{c_height},
      rel_x_{0}, rel_y_{0},
      horiz_v{0}, vert_v{0},
      zoom_factor_{1}, factor_{1}, z0_{-0.789, 0.12}, dz0{0, 0} {
        set_default_offset();
    }

    render_ctx& set_default_offset() {
        rel_x_ = -width_ / 2;
        rel_y_ = -height_ / 2;
        return *this;
    }

    void set_z0(std::complex<double> z0) { z0_ = z0; }
    std::complex<double> get_z0() const { return z0_; }

    int width() { return width_; }
    int height() { return height_; }

    int cs_width() { return c_width_; }
    int cs_height() { return c_height_; }

    double rel_x() { return rel_x_; }
    double rel_y() { return rel_y_; }

    void move(int horiz, int vert) {
        horiz_v = horiz;
        vert_v = vert;
    }

    void resize(int width, int height) {
        width_ = width;
        height_ = height;
        set_default_offset();
    }

    void zoom(double factor) {
        factor_ += factor;
    }

    void update_pos() {
        rel_x_ += horiz_v;
        rel_y_ += vert_v;
    }

    void update_zoom() {
        zoom_factor_ *= factor_;
        rel_x_ /= factor_;
        rel_y_ /= factor_;
    }

    double d_zoom() const { return factor_; }

    double zoom_factor() const { return zoom_factor_; }

    int threshold;
private:
    // canvas dimensions
    int c_width_, c_height_;

    int width_;
    int height_;
    double rel_x_, rel_y_;

    int horiz_v, vert_v;
public:
    double zoom_factor_;
    double factor_;
private:


    std::complex<double> z0_;

public:
    std::complex<double> dz0;
};


#endif
