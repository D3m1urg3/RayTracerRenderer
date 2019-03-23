#include "globals.h"
#include "geometries.h"
#include "camera.h"
#include "to_ppm.h"
#include <cfloat>
#include <cstdlib>
#include <time.h>

// Followed https://github.com/petershirley/raytracinginoneweekend Peter's Shirley Raytracer in a Weekend

float random()
{
    return static_cast<float>(rand() / static_cast<float>(RAND_MAX));
}

vec3f random_in_unit_sphere()
{
    vec3f p;
    do
    {
        p = 2.0f*vec3f(random(), random(), random()) - vec3f(1.0f, 1.0f, 1.0f);
    } while (p.squared_length() >= 1.0f);
    return p;
}

rgb vec3f_to_rgb(const vec3f& v)
{
    return rgb{ static_cast<int>(255.99f*v.x()), static_cast<int>(255.99f*v.y()), static_cast<int>(255.99f*v.z()) };
}

vec3f colorf(const ray& r, const std::vector<geom*>& world)
{
    hit rec;
    vec3f ret;
    if(closest_hit_with_geoms(world, r, 0.0f, FLT_MAX, rec))
    {
        vec3f target = rec.pos + rec.normal + random_in_unit_sphere();
        ret = 0.5f*colorf(ray(rec.pos, target - rec.pos), world);
    }
    else
    {
        vec3f unit_dir  = unit_vec(r.direction());
        float t         = 0.5f*(unit_dir.y() + 1.0f);
        ret = (1.0f - t)*vec3f(1.0f, 1.0f, 1.0f) + t*vec3f(0.5f, 0.7f, 1.0f);
    }
    return ret;
}

int main()
{
    srand((unsigned)time(NULL));

    const int nx = 200;
    const int ny = 100;
    const int ns = 100;

    std::vector<geom*> world;
    world.push_back(new sphere(vec3f(0.0f, 0.0f, -1.0f), 0.5f));
    world.push_back(new sphere(vec3f(0.0f, -100.5f, -1.0f), 100.0f));

    camera cam;

    rgb pixels[nx*ny];
    for (int n = 0; n < nx*ny; ++n)
    {
        vec3f colf(0.0f, 0.0f, 0.0f);
        for (int s = 0; s < ns; ++s)
        {
            float u = (static_cast<float>(n%nx) + random()) / static_cast<float>(nx);
            float v = (static_cast<float>(n/nx) + random()) / static_cast<float>(ny);

            ray r = cam.shoot_ray(u, v);
            vec3f p = r.position_at(2.0f);
            colf += colorf(r, world);
        }
        colf /= static_cast<float>(ns);
        pixels[n] = vec3f_to_rgb(colf);
    }
    to_ppm(nx, ny, pixels, "out.ppm");
        
    return 0;
}