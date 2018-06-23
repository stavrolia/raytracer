#pragma once
#include "vec3.h"

class Sphere {
public:
    Sphere(double rad, vec3 center);

    double GetRad() const;

    vec3 GetCenter() const;

private:
    double rad_;
    vec3 center_;
};

class Ray {
public:
    Ray(vec3 origin, vec3 direct);

    vec3 GetOrigin() const;

    vec3 GetDirect() const;

private:
    vec3 origin_;
    vec3 direct_;
};

double IsIntersected(Sphere const& sphere, Ray const& ray);
