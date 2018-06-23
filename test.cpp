#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <limits>
#include "image.h"
#include "vec3.h"
#include "geom.h"
#include "camera.h"

void test_image() {
    Image image(6, 8);

    int rad = 2;
    int center_x = 4;
    int center_y = 2;

    for (int y = 0; static_cast<uint32_t>(y) < image.Height(); ++y) {
        for (int x = 0; static_cast<uint32_t>(x) < image.Width(); ++x) {
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
}

void test_vec3() {
    vec3 a = {1, 1, 1};
    vec3 b = {1, 2, 3};
    vec3 exp_sum = {2, 3, 4};

    assert(a + b == exp_sum);
    assert(a == exp_sum - b);
    assert(a.dot(b) == 6);

    vec3 twob = {2, 4, 6};

    assert(b * 2 == twob);
    assert(2 * b == twob);
    assert(twob / 2 == b);

    vec3 long_vect1 = {0, 0, 4};
    vec3 long_vect2 = {0, 4, 0};
    vec3 long_vect3 = {4, 0, 0};

    vec3 norm_vect1 = {0, 0, 1};
    vec3 norm_vect2 = {0, 1, 0};
    vec3 norm_vect3 = {1, 0, 0};

    assert(norm_vect1 == long_vect1.normalized());
    assert(norm_vect2 == long_vect2.normalized());
    assert(norm_vect3 == long_vect3.normalized());

    vec3 i = {1, 0, 0};
    vec3 j = {0, 1, 0};
    vec3 k = {0, 0, 1};

    assert(k == i.cross(j));
    assert(j == k.cross(i));
    assert(i == j.cross(k));
}

void test_geom() {
    Sphere sp(1, {0, 0, 0});
    Ray ray({2, 2, 2}, {1, 1, 1});
    assert(IsIntersected(sp, ray) == std::numeric_limits<double>::max());

    Ray another_ray({2, 2, 2}, {-1, -1, -1});
    assert(IsIntersected(sp, another_ray) != std::numeric_limits<double>::max());

    Ray one_more_ray({10, 0, 0}, {-1, -1, -1});
    assert(IsIntersected(sp, one_more_ray) == std::numeric_limits<double>::max());
}

void test_camera() {
    Ray test_ray = Camera({-100, 0, 0}, {0, 0, 0}, {0, 0, 1}, 50, 320, 240).CastRay(0, 0);
    assert((test_ray.GetOrigin() == vec3{-100, 0, 0}));
    assert((test_ray.GetDirect() == vec3{1, 0, 0}));
}

int main() {
    test_image();
    test_vec3();        
    test_geom();
    test_camera();
    return 0;
}
