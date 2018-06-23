#pragma once
#include "vec3.h"
#include "geom.h"

class Camera {
public:
    Camera(
        vec3 const& position,
        vec3 const& look_at,
        vec3 const& up,
        double focus,
        double width,
        double height
    );

    Ray CastRay(double x, double y) const;

private:
    vec3 position_;
    vec3 screen_center_;
    vec3 dx_;
    vec3 dy_;
};

double uniform_scale(uint32_t coord, uint32_t scale);
