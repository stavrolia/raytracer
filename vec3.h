#pragma once

struct vec3 {
    double x;
    double y;
    double z;

    vec3& operator+=(vec3 const& rhs);

    vec3& operator-=(vec3 const& rhs);

    vec3& operator*=(double rhs);

    vec3& operator/=(double rhs);

    bool operator==(vec3 const& rhs) const;

    double dot(vec3 const& rhs) const;

    friend vec3 operator+(vec3 lhs, vec3 const& rhs);

    friend vec3 operator-(vec3 lhs, vec3 const& rhs);

    friend vec3 operator*(vec3 lhs, double rhs);

    friend vec3 operator*(double lhs, vec3 rhs);

    friend vec3 operator/(vec3 lhs, double rhs);
};