#pragma once
#include "image.h"
#include "geom.h"
#include "vec3.h"

class Scene {
public:
    Scene(color const& background, vec3 const& light);

    void AddSphere(Sphere const& sphere, color const& sphere_color);

    color ComputeColor(Ray const& ray) const;

private:
    std::vector<Sphere> spheres_;
    std::vector<color> colors_;
    color background_;
    vec3 light_;
};
