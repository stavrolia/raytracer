#include "camera.h"
#include <cassert>
#include "ray.h"

namespace {
    vec3 ComputeScreenCenter(vec3 const& position, vec3 const& look_at, double focus) {
        return position + (look_at - position).normalized() * focus;
    }
}

Camera::Camera(
    vec3 const& position,
    vec3 const& look_at,
    vec3 const& up,
    double focus,
    double width,
    double height
) : position_(position)
  , screen_center_(ComputeScreenCenter(position, look_at, focus)) {
    vec3 right_direction = (look_at - position).cross(up);
    dx_ = right_direction.normalized() * width / 2;
    vec3 up_direction = (dx_).cross(look_at - position);
    dy_ = up_direction.normalized() * height / 2;
  }

Ray Camera::CastRay(double x, double y) const {
    assert(-1 <= x && x <= 1);
    assert(-1 <= y && y <= 1);
    vec3 point_on_screen = screen_center_ + x * dx_ + y * dy_;
    return Ray::FromTo(position_, point_on_screen);
}

double uniform_scale(uint32_t coord, uint32_t scale) {
    return 2.0 * coord / scale - 1;
}
