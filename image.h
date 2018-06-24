#pragma once
#include <vector>
#include <cstddef>
#include <cstdint>
#include <sstream>

struct color {
    uint8_t R;
    uint8_t G;
    uint8_t B;

    friend bool operator==(color const& lhs, color const& rhs);
    color& operator*=(double rhs);
    friend color operator*(color lhs, double rhs);
    friend color operator*(double lhs, color rhs);
};

std::ostream& operator<<(std::ostream& os, color const& rhs);

class Image {
public:
    Image(uint32_t width, uint32_t height);

    color Get(uint32_t x, uint32_t y) const;

    void Set(uint32_t x, uint32_t y, color value);

    uint32_t Width() const;

    uint32_t Height() const;

private:
    uint32_t width_;
    uint32_t height_;
    std::vector<color> matrix_;
};

template<class Ostream>
void Outputppm(Ostream& stream, Image const& image) {
    stream << "P3\n";
    stream << image.Width() << ' ' << image.Height() << '\n';
    stream << "255\n";
    for (uint32_t y = 0; y < image.Height(); ++y) {
        bool first = true;
        for (uint32_t x = 0; x < image.Width(); ++x) {
            if (!first) {
                stream << "   ";
            }
            auto cell = image.Get(x, y);
            stream << static_cast<int>(cell.R) << ' ' << static_cast<int>(cell.G) << ' ' << static_cast<int>(cell.B);
            first = false;
        }
        stream << '\n';
    }
}
