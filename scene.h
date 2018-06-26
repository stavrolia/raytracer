#pragma once
#include "image.h"
#include "geom.h"
#include "vec3.h"
#include "ray.h"
#include <memory>
#include "light.h"
#include <vector>
#include <utility>

class Scene {
public:
    Scene(color const& background, color const& ambient_light);

    void AddSurface(std::unique_ptr<Surface> surface, color const& surface_color);

    void AddLight(std::unique_ptr<Light> light, color const& color_of_light);

    std::pair<size_t, double> FindTheNearestSurface(Ray const& ray) const;

    color ComputeColor(Ray const& ray) const;

private:
    std::vector<std::unique_ptr<Surface>> surfaces_;
    std::vector<vec3> surfaces_colors_;
    std::vector<double> sphere_shininesses_;
    vec3 background_;
    vec3 ambient_light_;
    std::vector<std::unique_ptr<Light>> lights_;
    std::vector<vec3> light_colors_;
};
