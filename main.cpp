#include "globals.h"
#include "geometries.h"
#include "to_ppm.h"
#include <cfloat>

// Followed https://github.com/petershirley/raytracinginoneweekend Peter's Shirley Raytracer in a Weekend

rgb color(const ray& r, const std::vector<geom*>& world)
{
    hit rec;
    vec3f ret;
    if(closest_hit_with_geoms(world, r, 0.0f, FLT_MAX, rec))
    {
        ret = 0.5f*vec3f(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    else
    {
        vec3f unit_dir  = unit_vec(r.direction());
        float t         = 0.5f*(unit_dir.y() + 1.0f);
        ret = (1.0f - t)*vec3f(1.0f, 1.0f, 1.0f) + t*vec3f(0.5f, 0.7f, 1.0f);
    }
    return rgb{ int(255.99f*ret.x()), int(255.99f*ret.y()), int(255.99f*ret.z()) };
}

int main()
{
    const int nx = 200;
    const int ny = 100;

    vec3f lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3f horizontal(4.0f, 0.0f, 0.0f);
    vec3f vertical(0.0f, 2.0f, 0.0f);
    vec3f origin(0.0f, 0.0f, 0.0f);

    std::vector<geom*> world;
    world.push_back(new sphere(vec3f(0.0f, 0.0f, -1.0f), 0.5f));
    world.push_back(new sphere(vec3f(0.0f, -100.5f, -1.0f), 100.0f));

    rgb pixels[nx*ny];
    for (int n = 0; n < nx*ny; ++n)
    {
        float u = float(n % nx) / float(nx);
        float v = float(n / nx) / float(ny);
        ray r(origin, lower_left_corner + u*horizontal + v*vertical);
        pixels[n] = color(r, world);
    }

    to_ppm(nx, ny, pixels, "out.ppm");
        
    return 0;
}