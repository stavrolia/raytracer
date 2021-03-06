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
#include "ray.h"


void DrawSnowman() {
    Camera camera({200, 0, 0}, {0, 0, 0}, {0, 0, 1}, 50, 320, 240);
    Image image(640, 480);
    Scene scene({0, 0, 0}, {10, 10, 10});

    scene.AddSurface(Surface::MakeSphere(50, {0, 0, 0}), {255, 255, 255}, 10);
    scene.AddSurface(Surface::MakeSphere(40, {0, 0, 45}), {255, 255, 255}, 10);
    scene.AddSurface(Surface::MakeSphere(30, {0, 0, 80}), {255, 255, 255}, 10);
    scene.AddLight(Light::MakePoint({200, 500, 500}), {255, 255, 255});

    for (uint32_t y = 0; y < image.Height(); ++y) {
        for (uint32_t x = 0; x < image.Width(); ++x) {
            Ray ray = camera.CastRay(uniform_scale(x, image.Width()), uniform_scale(y, image.Height()));
            image.Set(x, y, scene.ComputeColor(ray));
        }
    }

    Outputppm(std::cout, image);
}

int main() {



    Camera camera({400, 0, 100}, {0, 0, 0}, {0, 0, 1}, 50, 320, 240);
    Image image(640, 480);

    Scene scene({0, 0, 0}, {10, 10, 10});
    // Ray ray({0, 0, 0}, {0, 1, 0});
    // scene.AddSurface(Surface::MakeSphere(150, {0, 0, 0}), {255, 255, 255}, 50);
    // scene.AddSurface(Surface::MakePlane({0, 0, -150}, {0, 0, 1}), {255, 255, 255}, 50);
    scene.AddSurface(Surface::MakeTriangle({0, 0, -150}, {100, 0, -150}, {0, 100, -150}), {255, 255, 255}, 50);
    // auto tr = Surface::MakeTriangle({0, 0, 0}, {100, 0, 0}, {0, 100, 0});
    // std::cout << tr->IsIntersected(Ray::FromTo({0, 0, 1}, {0, 0, 0})) << '\n';
    // scene.AddSphere(Sphere(40, {0, 0, 45}), {255, 255, 255});
    // scene.AddSphere(Sphere(30, {0, 0, 80}), {255, 255, 255});
    scene.AddLight(Light::MakePoint({200, 500, 500}), {255, 0, 0});
    scene.AddLight(Light::MakePoint({200, -500, 500}), {0, 0, 255});
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
