#include "vec3.h"
#include <cmath>
#include <cassert>
#include <iostream>


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

vec3 vec3::cross(vec3 const& rhs) const {
    return {
        y * rhs.z - rhs.y * z,
        - x * rhs.z + rhs.x * z,
        x * rhs.y - rhs.x * y
    };
}

vec3 vec3::normalized() const {
    double sqr = (*this).dot(*this);
    assert(sqr > 0);
    return (*this) / std::sqrt(sqr);
}

std::ostream& operator<<(std::ostream& os, vec3 const& rhs) {
    return os << '(' << rhs.x << ", " << rhs.y << ", " << rhs.z << ")"; 
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
