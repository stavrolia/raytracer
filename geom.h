#pragma once
#include "vec3.h"

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

class Sphere {
public:
    Sphere(double rad, vec3 center);

    double IsIntersected(Ray const& ray) const;
    
    vec3 ComputeNormal(vec3 point_on_sphere) const;
    
private:
    double rad_;
    vec3 center_;
};

class Plane {
public:
    Plane(vec3 const&  normal, vec3 const& point);

    static Plane FromPointAndTwoVectors(vec3 const& point, vec3 const& alpha, vec3 const& beta);

    static Plane FromThreePoints(vec3 const& a, vec3 const& b, vec3 const& c);

    vec3 GetNormal() const;

    vec3 GetPoint() const;

private:
    vec3 normal_;
    vec3 point_;
};
