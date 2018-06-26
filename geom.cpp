#include "geom.h"
#include <cmath>
#include <cassert>
#include <limits>
#include <memory>
#include "vec3.h"
#include "ray.h"
#include <iostream>

namespace {
class Sphere : public Surface {
public:
    Sphere(double rad, vec3 const& center)
        : rad_(rad)
        , center_(center) {
            assert(rad_ > 0);
        }

    double IsIntersected(Ray const& ray) const override {
        vec3 O_O = ray.GetOrigin() - center_; 
        double a = ray.GetDirect().dot(ray.GetDirect());
        double half_b = O_O.dot(ray.GetDirect());
        double c = O_O.dot(O_O) - rad_ * rad_;
        double half_d = half_b * half_b - a * c;
        if (half_d < 0) {
            return std::numeric_limits<double>::max();
        }
        double t = (-half_b - std::sqrt(half_d)) / a;
        return (t < 0 ? std::numeric_limits<double>::max() : t);
    }
    
    vec3 ComputeNormal(vec3 const& point) const override {
        return (point - center_).normalized();
    }

private:
    double rad_;
    vec3 center_;
};

class Plane : public Surface {
public:
    Plane(vec3 const& point, vec3 const&  normal)
        : point_(point)
        , normal_(normal.normalized()) {}

    double IsIntersected(Ray const& ray) const override {
        double denominator = normal_.dot(ray.GetDirect());
        if (!denominator) {
            return std::numeric_limits<double>::max();
        }
        double t = normal_.dot(point_ - ray.GetOrigin()) / denominator;
        return (t < 0 ? std::numeric_limits<double>::max() : t);
    }

    vec3 ComputeNormal(vec3 const& point) const override {
        return normal_;
    }

private:
    vec3 point_;
    vec3 normal_;
};
}

std::unique_ptr<Surface> Surface::MakeSphere(double rad, vec3 const& center) {
    return std::make_unique<Sphere>(rad, center);
}

std::unique_ptr<Surface> Surface::MakePlane(vec3 const&  point, vec3 const& normal) {
    return std::make_unique<Plane>(point, normal);
}

// std::unique_ptr<Surface> Surface::PlaneFromPointAndTwoVec(vec3 const& point,
//                                         vec3 const& alpha, vec3 const& beta) {
//     return std::make_unique<Plane>(point, alpha.pointwise(beta).normalized());
// }

// std::unique_ptr<Surface> Surface::PlaneFromThreePoints(vec3 const& a, vec3 const& b, vec3 const& c) {
//     return PlaneFromPointAndTwoVec(a, b - a, c - a);
// }

// double Sphere::IsIntersected(Ray const& ray) const {
//     vec3 O_O = ray.GetOrigin() - center_; 
//     double a = ray.GetDirect().dot(ray.GetDirect());
//     double half_b = O_O.dot(ray.GetDirect());
//     double c = O_O.dot(O_O) - rad_ * rad_;
//     double half_d = half_b * half_b - a * c;
//     if (half_d < 0) {
//         return std::numeric_limits<double>::max();
//     }
//     double t = (-half_b - std::sqrt(half_d)) / a;
//     return (t < 0 ? std::numeric_limits<double>::max() : t);
// }

// double Plane::IsIntersected(Ray const& ray) const {
//     double denominator = normal_.dot(ray.GetDirect());
//     if (!denominator) {
//         return std::numeric_limits<double>::max();
//     }
//     double t = normal_.dot(point_ - ray.GetOrigin()) / denominator;
//     return (t < 0 ? std::numeric_limits<double>::max() : t);
// }


// Sphere::Sphere(double rad, vec3 const& center)
//     : rad_(rad)
//     , center_(center) {
//         assert(rad_ > 0);
//     }

// vec3 Sphere::ComputeNormal(vec3 const& point) const {
//     return (point - center_).normalized();
// }

// Plane::Plane(vec3 const&  point, vec3 const& normal)
//     : point_(point)
//     , normal_(normal.normalized()) {}

// vec3 Plane::ComputeNormal(vec3 const& point) const{
//     return normal_;
// }