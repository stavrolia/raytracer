#include "geom.h"
#include <cmath>
#include <cassert>

Sphere::Sphere(double rad, vec3 centre)
    : rad_(rad)
    , centre_(centre) {
        assert(rad_ > 0);
    }

double Sphere::GetRad() const {
    return rad_;
}

vec3 Sphere::GetCentre() const {
    return centre_;
}

Ray::Ray(vec3 origin, vec3 direct)
    : origin_(origin)
    , direct_(direct) {
        assert(direct_.dot(direct_) > 0);
        direct_ /= std::sqrt(direct_.dot(direct_));
    }

vec3 Ray::GetOrigin() const {
    return origin_;
}

vec3 Ray::GetDirect() const {
    return direct_;
}

bool IsIntersected(Sphere const& sphere, Ray const& ray) {
    vec3 O_O = ray.GetOrigin() - sphere.GetCentre(); 
    double a = ray.GetDirect().dot(ray.GetDirect());
    double half_b = O_O.dot(ray.GetDirect());
    double c = O_O.dot(O_O) - sphere.GetRad() * sphere.GetRad();
    double half_d = half_b * half_b - a * c;
    if (half_d < 0) {
        return false;
    }
    double max_factor = (-half_b + std::sqrt(half_d)) / a;
    return max_factor > 0;
}