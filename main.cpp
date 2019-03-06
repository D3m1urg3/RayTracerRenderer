#include "globals.h"
#include "to_ppm.h"
#include "ray.h"

// Followed https://github.com/petershirley/raytracinginoneweekend Peter's Shirley Raytracer in a Weekend

rgb color(const ray& r)
{
    vec3f unit_dir  = unit_vec(r.direction());
    float t         = 0.5f*(unit_dir.y() + 1.0f);
    vec3f lerp      = (1.0f - t)*vec3f(1.0f, 1.0f, 1.0f) + t*vec3f(0.5f, 0.7f, 1.0f);
    return rgb{ int(255.99f*lerp.x()), int(255.99f*lerp.y()), int(255.99f*lerp.z()) };
}

int main()
{
    const int nx = 200;
    const int ny = 100;

    vec3f lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3f horizontal(4.0f, 0.0f, 0.0f);
    vec3f vertical(0.0f, 2.0f, 0.0f);
    vec3f origin(0.0f, 0.0f, 0.0f);

    rgb pixels[nx*ny];
    for (int n = 0; n < nx*ny; ++n)
    {
        float u = float(n % nx) / float(nx);
        float v = float(n / nx) / float(ny);
        ray r(origin, lower_left_corner + u*horizontal + v*vertical);
        pixels[n] = color(r);
    }

    to_ppm(nx, ny, pixels, "out.ppm");
        
    return 0;
}