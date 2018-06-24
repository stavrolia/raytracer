#include "geom.h"
#include <cmath>
#include <cassert>
#include <limits>

Sphere::Sphere(double rad, vec3 center)
    : rad_(rad)
    , center_(center) {
        assert(rad_ > 0);
    }

double Sphere::GetRad() const {
    return rad_;
}

vec3 Sphere::GetCenter() const {
    return center_;
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

double IsIntersected(Sphere const& sphere, Ray const& ray) {
    vec3 O_O = ray.GetOrigin() - sphere.GetCenter(); 
    double a = ray.GetDirect().dot(ray.GetDirect());
    double half_b = O_O.dot(ray.GetDirect());
    double c = O_O.dot(O_O) - sphere.GetRad() * sphere.GetRad();
    double half_d = half_b * half_b - a * c;
    if (half_d < 0) {
        return std::numeric_limits<double>::max();
    }
    double t = (-half_b - std::sqrt(half_d)) / a;
    return (t < 0 ? std::numeric_limits<double>::max() : (-half_b - std::sqrt(half_d)) / a);
}
