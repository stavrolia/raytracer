#include "geom.h"
#include <cmath>
#include <cassert>
#include <limits>

Sphere::Sphere(double rad, vec3 center)
    : rad_(rad)
    , center_(center) {
        assert(rad_ > 0);
    }

vec3 Sphere::ComputeNormal(vec3 point_on_sphere) const {
    return (point_on_sphere - center_).normalized();
}

Plane::Plane(vec3 const&  normal, vec3 const& point)
    : normal_(normal)
    , point_(point) {}

Plane Plane::FromPointAndTwoVectors(vec3 const& point, vec3 const& alpha, vec3 const& beta) {
    return Plane(alpha.pointwise(beta).normalized(), point);
}

Plane Plane::FromThreePoints(vec3 const& a, vec3 const& b, vec3 const& c) {
    return FromPointAndTwoVectors(a, b - a, c - a);
}

Ray::Ray(vec3 origin, vec3 direct)
    : origin_(origin)
    , direct_(direct.normalized()) {}

Ray Ray::FromTo(vec3 const& start, vec3 const& finish) {
    return Ray(start, finish - start);
}

vec3 Ray::GetOrigin() const {
    return origin_;
}

vec3 Ray::GetDirect() const {
    return direct_;
}

double Sphere::IsIntersected(Ray const& ray) const {
    vec3 O_O = ray.GetOrigin() - center_; 
    double a = ray.GetDirect().dot(ray.GetDirect());
    double half_b = O_O.dot(ray.GetDirect());
    double c = O_O.dot(O_O) - rad_ * rad_;
    double half_d = half_b * half_b - a * c;
    if (half_d < 0) {
        return std::numeric_limits<double>::max();
    }
    double t = (-half_b - std::sqrt(half_d)) / a;
    return (t < 0 ? std::numeric_limits<double>::max() : (-half_b - std::sqrt(half_d)) / a);
}

// double IsIntersected(Plane const& plane, Ray const& ray) {
// }