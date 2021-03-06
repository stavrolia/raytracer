#pragma once
#include "vec3.h"
#include "geom.h"
#include "ray.h"
#include <memory>

struct Light {
    virtual vec3 Direction(vec3 const& point_on_sphere) const = 0;
    virtual double CoefTOfRay(Ray const& ray) const = 0;
    virtual ~Light() = default;

    static std::unique_ptr<Light> MakeParallel(vec3 const& direction);
    static std::unique_ptr<Light> MakePoint(vec3 const& source);
};
