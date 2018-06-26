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

class Plane {
public:
    Plane(vec3 const&  normal, vec3 const& point);

    static Plane FromPointAndTwoVectors(vec3 const& point, vec3 const& alpha, vec3 const& beta);

    static Plane FromThreePoints(vec3 const& a, vec3 const& b, vec3 const& c);

private:
    vec3 normal_;
    vec3 point_;
};

class Ray {
public:
    Ray(vec3 origin, vec3 direct);

    static Ray FromTo(vec3 const& start, vec3 const& finish);

    vec3 GetOrigin() const;

    vec3 GetDirect() const;

private:
    vec3 origin_;
    vec3 direct_;
};

double IsIntersected(Sphere const& sphere, Ray const& ray);
