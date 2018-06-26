#include "ray.h"
#include "vec3.h"

Ray::Ray(vec3 const& origin, vec3 const& direct)
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
