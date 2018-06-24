#pragma once
#include "image.h"
#include "geom.h"
#include "vec3.h"
#include <memory>
#include "light.h"

class Scene {
public:
    Scene(color const& background, std::unique_ptr<Light> light);

    void AddSphere(Sphere const& sphere, color const& sphere_color);

    color ComputeColor(Ray const& ray) const;

private:
    std::vector<Sphere> spheres_;
    std::vector<color> colors_;
    color background_;
    std::unique_ptr<Light> light_;
};
