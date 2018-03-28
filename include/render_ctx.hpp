#ifndef RENDER_CTX
#define RENDER_CTX


struct render_ctx {
    render_ctx(int width, int height)
    : width_{width}, height_{height} {
        set_default_offset();
    }

    render_ctx& set_default_offset() {
        rel_x_ = -width_ / 2;
        rel_y_ = -height_ / 2;
        return *this;
    }

    int width() { return width_; }
    int height() { return height_; }

    int rel_x() { return rel_x_; }
    int rel_y() { return rel_y_; }

    void move(int horiz, int vert) {
        rel_x_ += horiz;
        rel_y_ += vert;
    }

    void resize(int width, int height) {
        width_ = width;
        height_ = height;
    }

private:
    int width_;
    int height_;
    int rel_x_, rel_y_;
};


#endif
