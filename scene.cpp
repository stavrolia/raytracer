#include "scene.h"
#include <limits>
#include "geom.h"
#include "vec3.h"
#include "ray.h"
#include <cmath>
#include <memory>
#include "light.h"
#include <utility>

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

color Vec3ToColor(vec3 const& from_vec) {
    return {To8BitColor(from_vec.x), To8BitColor(from_vec.y), To8BitColor(from_vec.z)};
}
}

Scene::Scene(color const& background, color const& ambient_light)
    : background_(ColorToVec3(background))
    , ambient_light_(ColorToVec3(ambient_light)) {}

void Scene::AddSurface(std::unique_ptr<Surface> surface, color const& surface_color) {
    surfaces_.emplace_back(std::move(surface));
    surfaces_colors_.push_back(ColorToVec3(surface_color));
}

void Scene::AddLight(std::unique_ptr<Light> light, color const& color_of_light) {
    lights_.emplace_back(std::move(light));
    light_colors_.push_back(ColorToVec3(color_of_light));
}

std::pair<size_t, double> Scene::FindTheNearestSurface(Ray const& ray) const {
    size_t ind_min = 0;
    double t_min = std::numeric_limits<double>::max();

    for (size_t i = 0; i < surfaces_.size(); ++i) {
        double current_t = surfaces_[i]->IsIntersected(ray);
        if (current_t < t_min) {
            t_min = current_t;
            ind_min = i;
        }
    }

    return std::make_pair(ind_min, t_min);
}

color Scene::ComputeColor(Ray const& ray) const {
    auto ind_and_t = FindTheNearestSurface(ray);
    auto surface_ind = ind_and_t.first;

    if (ind_and_t.second == std::numeric_limits<double>::max()) {
        return Vec3ToColor(background_);
    }

    vec3 vec_from_viewer = ray.GetDirect();
    auto color_nearest_surface = surfaces_colors_[surface_ind];
    vec3 accumulate = ambient_light_.pointwise(color_nearest_surface);
    vec3 point_on_surface = ray.GetOrigin() + ind_and_t.second * vec_from_viewer;
    vec3 normal = surfaces_[surface_ind]->ComputeNormal(point_on_surface);  //////

    for (size_t i = 0; i < light_colors_.size(); ++i) { 
        vec3 vec_light = lights_[i]->Direction(point_on_surface);
        Ray ray_of_light(point_on_surface, vec_light);
        double t_of_light = lights_[i]->CoefTOfRay(ray_of_light);
        auto barrier = FindTheNearestSurface(ray_of_light);
        if (barrier.second < t_of_light) {
            continue;
        }


        double factor = normal.dot(vec_light);
        // vec3 reflect = 2 * factor * normal - vec_light;
        // double coef_of_reflect = reflect.dot((-1) * vec_from_viewer);
        // if (coef_of_reflect > 0) {
        //     coef_of_reflect = std::pow(coef_of_reflect, sphere_shininesses_[sphere_ind]);
        // } else {
        //     coef_of_reflect = 0;
        // }

        accumulate += factor < 0 
            ? background_ 
            : (/*coef_of_reflect + */factor) * color_nearest_surface.pointwise(light_colors_[i]);
    }
    return Vec3ToColor(accumulate);
    
}


// void Scene::AddSphere(Sphere const& sphere, color const& sphere_color, double shininess) {
//     spheres_.push_back(sphere);
//     sphere_colors_.push_back(ColorToVec3(sphere_color));
//     sphere_shininesses_.push_back(shininess);
// }

// void Scene::AddSphere(Sphere const& sphere, color const& sphere_color) {
//     AddSphere(sphere, sphere_color, 10);
// }