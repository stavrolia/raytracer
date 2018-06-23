#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <limits>
#include <cmath>
#include <algorithm>
#include "image.h"
#include "vec3.h"
#include "geom.h"
#include "camera.h"

int main() {
    

    Camera camera({100, 0, 0}, {0, 0, 0}, {0, 0, 1}, 50, 320, 240);

    // Ray test_ray2.CastRay(1, 1);

    // std::cout << "origin: " << "\n" << test_ray2.GetOrigin();
    // std::cout << "direct: " << "\n" << test_ray2.GetDirect();


    Image image(640, 480);

    Sphere sphere1(50, {0, 0, 0});
    Sphere sphere2(20, {50, 0, 0});
    color color1 = {225, 225, 0};
    color color2 = {225, 0, 0};

    for (uint32_t y = 0; y < image.Height(); ++y) {
        for (uint32_t x = 0; x < image.Width(); ++x) {
            Ray ray = camera.CastRay(uniform_scale(x, image.Width()), uniform_scale(y, image.Height()));
            double first_t = IsIntersected(sphere1, ray);
            double second_t = IsIntersected(sphere2, ray);
            if (std::min(first_t, second_t) != std::numeric_limits<double>::max()) {
                image.Set(x, y, (first_t < second_t ? color1 : color2));
            }
        }
    }

    Outputppm(std::cout, image);
    
    return 0;
}
