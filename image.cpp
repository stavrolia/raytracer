#include "image.h"
#include <vector>

bool operator==(color const& lhs, color const& rhs) {
    return (lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B);
}

color& color::operator*=(double rhs) {
    R *= rhs;
    G *= rhs;
    B *= rhs;
    return *this;
}

color operator*(color lhs, double rhs) {
    lhs *= rhs;
    return lhs;
}

color operator*(double lhs, color rhs) {
    rhs *= lhs;
    return rhs;
}

Image::Image(uint32_t width, uint32_t height)
    : width_(width)
    , height_(height)
    , matrix_(width_ * height_, {255, 255, 255}) {}

color Image::Get(uint32_t x, uint32_t y) const {
    return matrix_[x + y * width_];
}

void Image::Set(uint32_t x, uint32_t y, color value) {
    matrix_[x + y * width_] = value;
}

uint32_t Image::Width() const {
    return width_;
}

uint32_t Image::Height() const {
    return height_;
}
