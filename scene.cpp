#include "scene.h"
#include <limits>
#include "geom.h"
#include "vec3.h"
#include <cmath>
#include <memory>
#include "light.h"

namespace{
vec3 ColorToVec3(color const& from_color) {
    return vec3({
        static_cast<double>(from_color.R),
        static_cast<double>(from_color.G),
        static_cast<double>(from_color.B)
    }) / 255;
}

uint8_t To8BitColor(double value) {
    if (value <= 0) {
        return 0;
    }
    if (value > 1) {
        return 255;
    }
    return value * 255;
}
}
color Vec3ToColor(vec3 const& from_vec) {
    return {To8BitColor(from_vec.x), To8BitColor(from_vec.y), To8BitColor(from_vec.z)};
}

Scene::Scene(color const& background, color const& ambient_light)
    : background_(ColorToVec3(background))
    , ambient_light_(ColorToVec3(ambient_light)) {}

void Scene::AddSphere(Sphere const& sphere, color const& sphere_color) {
    spheres_.push_back(sphere);
    sphere_colors_.push_back(ColorToVec3(sphere_color));
}

void Scene::AddLight(std::unique_ptr<Light> light, color const& color_of_light) {
    lights_.emplace_back(std::move(light));
    light_colors_.push_back(ColorToVec3(color_of_light));
}



color Scene::ComputeColor(Ray const& ray) const {
    size_t ind_min = 0;
    double t_min = std::numeric_limits<double>::max();

    for (size_t i = 0; i < spheres_.size(); ++i) {
        double current_t = IsIntersected(spheres_[i], ray);
        if (current_t < t_min) {
            t_min = current_t;
            ind_min = i;
        }
    }

    if (t_min == std::numeric_limits<double>::max()) {
        return Vec3ToColor(background_);
    }
    vec3 accumulate = ambient_light_.pointwise(sphere_colors_[ind_min]);
    vec3 point_on_sphere = ray.GetOrigin() + t_min * ray.GetDirect();
    vec3 normal = (point_on_sphere - spheres_[ind_min].GetCenter()).normalized();
    for (size_t i = 0; i < light_colors_.size(); ++i) { 
        vec3 vec_light = lights_[i]->Direction(point_on_sphere); 
        double factor = normal.dot(vec_light);
        accumulate += factor < 0 ? background_ : factor * sphere_colors_[ind_min].pointwise(light_colors_[i]);
    }
    return Vec3ToColor(accumulate);
    
}
