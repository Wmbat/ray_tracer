#pragma once

#include "math/details.hpp"
#include "math/vec.hpp"
#include "ray.hpp"

#include <cmath>

class camera
{
public:
   struct create_info
   {
      vec eye;
      vec look_at;
      vec up;
      double vertical_fov;
      double aspect_ratio;
      double aperture;
      double focus_distance;
   };

public:
   camera(const create_info& info) noexcept : origin(info.eye), lens_radius(info.aperture / 2)
   {
      const auto theta = to_radians(info.vertical_fov);
      const auto half_height = tan(theta / 2);
      const auto half_width = info.aspect_ratio * half_height;

      {
         const vec z = normalise(origin - info.look_at);
         const vec x = normalise(cross(info.up, z));
         const vec y = cross(z, x);

         axis = ortho_normal_basis(x, y, z);
      }

      lower_left_corner = origin - half_width * info.focus_distance * axis.x() -
         half_height * info.focus_distance * axis.y() - info.focus_distance * axis.z();
      horizontal = 2 * half_width * info.focus_distance * axis.x();
      vertical = 2 * half_height * info.focus_distance * axis.y();
   }

   [[nodiscard]] ray shoot_ray(double u, double v) const noexcept
   {
      const vec random_disk = lens_radius * random_in_unit_disk();
      const vec offset = axis.x() * random_disk.x + axis.y() * random_disk.y;

      return ray(origin + offset, lower_left_corner + u * horizontal + v * vertical - origin - offset);
   }

private:
   const vec origin;
   vec horizontal;
   vec vertical;
   vec lower_left_corner;
   ortho_normal_basis axis;
   double lens_radius;
};
