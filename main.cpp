#include "globals.h"
#include "geometries.h"
#include "camera.h"
#include "to_ppm.h"
#include "mramdon.h"
#include <cfloat>
#include <time.h>

// Followed https://github.com/petershirley/raytracinginoneweekend Peter's Shirley Raytracer in a Weekend

rgb vec3f_to_rgb(const vec3f& v)
{
    return rgb{ static_cast<int>(255.99f*v.x()), static_cast<int>(255.99f*v.y()), static_cast<int>(255.99f*v.z()) };
}

vec3f colorf(const ray& r, const std::vector<geom*>& world, uint depth)
{
    hit rec;
    vec3f ret;
    if(closest_hit_with_geoms(world, r, 0.001f, FLT_MAX, rec))
    {
        ray scattered;
        vec3f attenuation;
        if (depth < MAX_RAY_DEPTH && rec.pmaterial != nullptr && rec.pmaterial->scatter(r, rec, attenuation, scattered))
        {
            ret = attenuation*colorf(scattered, world, depth + 1);
        }
        else
        {
            ret = vec3f();
        }

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
    world.push_back(new sphere(vec3f(0.0f, 0.0f, -1.0f), 0.5f, new lambertian(vec3f(0.1f, 0.2f, 0.5f))));
    world.push_back(new sphere(vec3f(0.0f, -100.5f, -1.0f), 100.0f, new lambertian(vec3f(0.8f, 0.8f, 0.0f))));
    world.push_back(new sphere(vec3f(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3f(0.8f, 0.6f, 0.2f))));
    world.push_back(new sphere(vec3f(-1.0f, 0.0f, -1.0f), 0.5f, new dielectric(1.5f)));

    camera cam(vec3f(-2.0f, 2.0f, 1.0f), vec3f(0.0f, 0.0f, -1.0f),vec3f(0.0f, 1.0f, 0.0f), 90.0f, (float)nx/(float)ny);
    // camera cam(90.0f, (float)nx/(float)ny);

    rgb pixels[nx*ny];
    for (int n = 0; n < nx*ny; ++n)
    {
        vec3f colf(0.0f, 0.0f, 0.0f);
        for (int s = 0; s < ns; ++s)
        {
            float u = (static_cast<float>(n%nx) + rnd_uniform()) / static_cast<float>(nx);
            float v = (static_cast<float>(n/nx) + rnd_uniform()) / static_cast<float>(ny);

            ray r = cam.shoot_ray(u, v);
            vec3f p = r.position_at(2.0f);
            colf += colorf(r, world, 0);
        }
        colf /= static_cast<float>(ns);
        colf = vec3f(sqrtf(colf[0]), sqrtf(colf[1]), sqrtf(colf[2]));
        pixels[n] = vec3f_to_rgb(colf);
    }
    to_ppm(nx, ny, pixels, "out.ppm");
        
    while(world.size())
    {
        geom* g = world.back();
        world.pop_back();
        delete g;
    }
    
    return 0;
}