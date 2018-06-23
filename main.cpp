#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include "image.h"

int main() {
    Image image(6, 8);

    int rad = 2;
    int center_x = 4;
    int center_y = 2;

    for (size_t y = 0; y < image.Height(); ++y) {
        for (size_t x = 0; x < image.Width(); ++x) {
            if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= rad * rad) {
                image.Set(x, y, {255, 255, 0});
            }
        }
    }

    std::stringstream s;
    Outputppm(s, image);
    auto expected = R"(P3
6 8
255
255 255 255   255 255 255   255 255 255   255 255 255   255 255 0   255 255 255
255 255 255   255 255 255   255 255 255   255 255 0   255 255 0   255 255 0
255 255 255   255 255 255   255 255 0   255 255 0   255 255 0   255 255 0
255 255 255   255 255 255   255 255 255   255 255 0   255 255 0   255 255 0
255 255 255   255 255 255   255 255 255   255 255 255   255 255 0   255 255 255
255 255 255   255 255 255   255 255 255   255 255 255   255 255 255   255 255 255
255 255 255   255 255 255   255 255 255   255 255 255   255 255 255   255 255 255
255 255 255   255 255 255   255 255 255   255 255 255   255 255 255   255 255 255
)";
    assert(s.str() == expected);
    return 0;
}
