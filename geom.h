#pragma once
#include "vec3.h"
#include <memory>
#include "ray.h"

class Surface {
public:
    virtual double IsIntersected(Ray const& ray) const = 0;
    virtual vec3 ComputeNormal(vec3 const& point) const = 0;
    virtual ~Surface() = default;

    static std::unique_ptr<Surface> MakeSphere(double rad, vec3 const& center);
    static std::unique_ptr<Surface> MakePlane(vec3 const& point, vec3 const&  normal);
    static std::unique_ptr<Surface> MakeTriangle(vec3 const& a, vec3 const& b, vec3 const& c);
};
