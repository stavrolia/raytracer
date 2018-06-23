#pragma once
#include "vec3.h"

class Sphere {
public:
    Sphere (double rad, vec3 centre);

    double GetRad() const;

    vec3 GetCentre() const;

private:
    double rad_;
    vec3 centre_;
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

bool IsIntersected(Sphere const& sphere, Ray const& ray);
