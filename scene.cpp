#include "scene.h"
#include <limits>
#include "geom.h"
#include "vec3.h"
#include <cmath>
#include <memory>
#include "light.h"


Scene::Scene(color const& background, std::unique_ptr<Light> light)
    : background_(background)
    , light_(std::move(light)) {}

void Scene::AddSphere(Sphere const& sphere, color const& sphere_color) {
    spheres_.push_back(sphere);
    colors_.push_back(sphere_color);
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

    if (t_min != std::numeric_limits<double>::max()) {
        vec3 point_on_sphere = ray.GetOrigin() + t_min * ray.GetDirect();
        vec3 normal = (point_on_sphere - spheres_[ind_min].GetCenter()).normalized();
        vec3 vec_light = light_->Direction(point_on_sphere);  ////////
        double factor = normal.dot(vec_light);      ////////
        return (factor < 0 ? background_ : factor * colors_[ind_min]);
    }
    return background_;
}
