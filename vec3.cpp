#include "vec3.h"

vec3& vec3::operator+=(vec3 const& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

vec3& vec3::operator-=(vec3 const& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

vec3& vec3::operator*=(double rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

vec3& vec3::operator/=(double rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

bool vec3::operator==(vec3 const& rhs) const {
    return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
}

double vec3::dot(vec3 const& rhs) const {
    return (x * rhs.x + y * rhs.y + z * rhs.z);
}

vec3 operator+(vec3 lhs, vec3 const& rhs) {
    lhs += rhs;
    return lhs;
}

vec3 operator-(vec3 lhs, vec3 const& rhs) {
    lhs -= rhs;
    return lhs;
}

vec3 operator*(vec3 lhs, double rhs) {
    lhs *= rhs;
    return lhs;
}

vec3 operator*(double lhs, vec3 rhs) {
    rhs *= lhs;
    return rhs;
}

vec3 operator/(vec3 lhs, double rhs) {
    lhs /= rhs;
    return lhs;
}
