#pragma once
#include "image.h"
#include "geom.h"
#include "vec3.h"
#include <memory>
#include "light.h"
#include <vector>

class Scene {
public:
    Scene(color const& background, color const& ambient_light);

    void AddSphere(Sphere const& sphere, color const& sphere_color);

    void AddLight(std::unique_ptr<Light> light, color const& color_of_light);

    color ComputeColor(Ray const& ray) const;

private:
    std::vector<Sphere> spheres_;
    std::vector<vec3> sphere_colors_;
    vec3 background_;
    vec3 ambient_light_;
    std::vector<std::unique_ptr<Light>> lights_;
    std::vector<vec3> light_colors_;
};
