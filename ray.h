#pragma once
#include "vec3.h"

class Ray {
public:
    Ray(vec3 const& origin, vec3 const& direct);

    static Ray FromTo(vec3 const& start, vec3 const& finish);

    vec3 GetOrigin() const;

    vec3 GetDirect() const;

private:
    vec3 origin_;
    vec3 direct_;
};
