#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <limits>
#include <cmath>
#include <algorithm>
#include <memory>
#include "image.h"
#include "vec3.h"
#include "geom.h"
#include "camera.h"
#include "scene.h"


int main() {
    

    Camera camera({200, 0, 0}, {0, 0, 0}, {0, 0, 1}, 50, 320, 240);

    // Ray test_ray2.CastRay(1, 1);

    // std::cout << "origin: " << "\n" << test_ray2.GetOrigin();
    // std::cout << "direct: " << "\n" << test_ray2.GetDirect();


    Image image(640, 480);

    Scene scene({0, 0, 0}, {10, 10, 10});
    // Ray ray({0, 0, 0}, {0, 1, 0});
    scene.AddSphere(Sphere(50, {0, 0, 0}), {255, 255, 255});
    scene.AddSphere(Sphere(40, {0, 0, 45}), {255, 255, 255});
    scene.AddSphere(Sphere(30, {0, 0, 80}), {255, 255, 255});
    scene.AddLight(Light::MakePoint({200, 500, 500}), {255, 255, 255});
    // scene.AddLight(Light::MakePoint({0, 100, 100}), {0, 0, 150});
    // scene.AddLight(Light::MakePoint({0, -50, 0}), {255, 255, 0});
    // scene.AddLight(Light::MakePoint({0, 0, -50}), {0, 0, 255});
    // scene.AddSphere(Sphere(50, {0, 0, 0}), {225, 225, 255});
    // scene.AddSphere(Sphere(20, {50, 0, 0}), {225, 0, 0});
    

    for (uint32_t y = 0; y < image.Height(); ++y) {
        for (uint32_t x = 0; x < image.Width(); ++x) {
            Ray ray = camera.CastRay(uniform_scale(x, image.Width()), uniform_scale(y, image.Height()));
            image.Set(x, y, scene.ComputeColor(ray));
        }
    }

    Outputppm(std::cout, image);
    
    return 0;
}
