#include "light.h"
#include "vec3.h"
#include "geom.h"
#include <memory>
#include <limits>
#include <cmath>

namespace {
struct ParallelLight : Light {
public:
    ParallelLight(vec3 const& direction)
        : direction_(direction.normalized()) {}

    vec3 Direction(vec3 const& point_on_sphere) override  {
        return (-1) * direction_;
    }

    double CoefTOfRay(Ray const& ray) override {
        return std::numeric_limits<double>::max();
    }

private:
    vec3 direction_;
};

struct PointLight : Light {
public:
    PointLight(vec3 const& source)
        : source_(source) {}

    vec3 Direction(vec3 const& point_on_sphere) override  {
        return (source_ - point_on_sphere).normalized();
    }

    double CoefTOfRay(Ray const& ray) override {
        auto focus = source_ - ray.GetOrigin();
        return std::sqrt(focus.dot(focus));
    }

private:
    vec3 source_;
};
}

std::unique_ptr<Light> Light::MakeParallel(vec3 const& direction) {
    return std::make_unique<ParallelLight>(direction);
}

std::unique_ptr<Light> Light::MakePoint(vec3 const& source) {
    return std::make_unique<PointLight>(source);
}
