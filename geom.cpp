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

class Triangle : public Surface {
public:
    Triangle(vec3 const& a, vec3 const& b, vec3 const& c)
        : point_a_(a)
        , a_b_(b - a)
        , a_c_(c - a) {}

    vec3 ComputeNormal(vec3 const& point) const override {
        return a_b_.cross(a_c_).normalized();
    }

    double IsIntersected(Ray const& ray) const override {
        vec3 triangle_normal = ComputeNormal(point_a_);
        double denominator = triangle_normal.dot(ray.GetDirect());
        if (!denominator) {
            return std::numeric_limits<double>::max();
        }
        double t = triangle_normal.dot(point_a_ - ray.GetOrigin()) / denominator;
        if (t < 0) {
            return std::numeric_limits<double>::max();
        }

        vec3 a_c_normal = a_c_.cross(triangle_normal).normalized();
        vec3 plane_point = ray.GetOrigin() + t * ray.GetDirect();
        double beta = (plane_point - point_a_).dot(a_c_normal) / a_b_.dot(a_c_normal);

        vec3 a_b_normal = a_b_.cross(triangle_normal).normalized();
        double alpha = (plane_point - point_a_).dot(a_b_normal) / a_c_.dot(a_b_normal);
        if (0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && alpha + beta <= 1) {
            return t;
        }
        return std::numeric_limits<double>::max();
    }

private:
    vec3 point_a_;
    vec3 a_b_;
    vec3 a_c_;
};
}

std::unique_ptr<Surface> Surface::MakeSphere(double rad, vec3 const& center) {
    return std::make_unique<Sphere>(rad, center);
}

std::unique_ptr<Surface> Surface::MakePlane(vec3 const&  point, vec3 const& normal) {
    return std::make_unique<Plane>(point, normal);
}

std::unique_ptr<Surface> Surface::MakeTriangle(vec3 const& a, vec3 const& b, vec3 const& c) {
    return std::make_unique<Triangle>(a, b, c);
}
