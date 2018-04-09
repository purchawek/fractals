#ifndef RENDER_CTX
#define RENDER_CTX


struct render_ctx {
    render_ctx(int c_width, int c_height)
    : c_width_{c_width},
      c_height_{c_height},
      width_{c_width},
      height_{c_height},
      rel_x_{0}, rel_y_{0},
      zoom_factor_{1}, factor_{1} {
        set_default_offset();
    }

    render_ctx& set_default_offset() {
        rel_x_ = -width_ / 2;
        rel_y_ = -height_ / 2;
        return *this;
    }

    int width() { return width_; }
    int height() { return height_; }

    int cs_width() { return c_width_; }
    int cs_height() { return c_height_; }

    int rel_x() { return rel_x_; }
    int rel_y() { return rel_y_; }

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
        double t = (factor_ <= 1 ? 1 - factor_ : factor_ - 1);
        rel_x_ += t * rel_x_;
        rel_y_ += t * rel_y_;
    }

    double zoom_factor() { return zoom_factor_; }


private:
    // canvas dimensions
    int c_width_, c_height_;

    int width_;
    int height_;
    int rel_x_, rel_y_;

    int horiz_v, vert_v;

    double zoom_factor_;

    double factor_;
};


#endif
