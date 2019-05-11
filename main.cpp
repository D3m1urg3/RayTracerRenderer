#include "globals.h"
#include "geometries.h"
#include "camera.h"
#include "mramdon.h"
#include <cfloat>
#include <time.h>
#include <fstream>

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

std::vector<geom*> random_scene()
{
    int n = 500;
    std::vector<geom*> world;

    world.push_back(new sphere(vec3f(0.0f, -1000.0f, 0.0f), 1000.0f, new lambertian(vec3f(0.5f, 0.5f, 0.5f))));
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        { 
            float choose_mat = rnd_uniform();
            vec3f center(a + 0.9f*rnd_uniform(), 0.2f, b + 0.9f*rnd_uniform());
            if ((center-vec3f(4.0f,0.2f,0.0f)).length() > 0.9f)
            {
                if (choose_mat < 0.8f) // diffuse
                {
                    world.push_back(new sphere(center, 0.2f, 
                        new lambertian(vec3f(rnd_uniform()*rnd_uniform(), rnd_uniform()*rnd_uniform(), rnd_uniform()*rnd_uniform()))));
                }
                else if (choose_mat < 0.95) // metal
                {
                    world.push_back(new sphere(center, 0.2f,
                        new metal(vec3f(0.5f*(1.0f + rnd_uniform()), 0.5f*(1.0f + rnd_uniform()), 0.5f*(1.0f + rnd_uniform())), 0.5f*rnd_uniform())));
                }
                else // glass
                {
                    world.push_back(new sphere(center, 0.2f, new dielectric(1.5f)));
                }
            }
        }
    }

    world.push_back(new sphere(vec3f(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(1.5f)));
    world.push_back(new sphere(vec3f(-4.0f, 1.0f, 0.0f), 1.0f, new lambertian(vec3f(0.4f, 0.2f, 0.1f))));
    world.push_back(new sphere(vec3f(4.0f, 1.0f, 0.0f), 1.0f, new metal(vec3f(0.7f, 0.6f, 0.5f), 0.0f)));

    return world;
}

int main()
{
    srand((unsigned)time(NULL));

    const int nx = 1200;
    const int ny = 800;
    const int ns = 10;

    std::cout << "Generating scene ..." << std::endl;
    std::vector<geom*> world = random_scene();
    world.push_back(new sphere(vec3f(0.0f, 0.0f, -1.0f), 0.5f, new lambertian(vec3f(0.1f, 0.2f, 0.5f))));
    world.push_back(new sphere(vec3f(0.0f, -100.5f, -1.0f), 100.0f, new lambertian(vec3f(0.8f, 0.8f, 0.0f))));
    world.push_back(new sphere(vec3f(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3f(0.8f, 0.6f, 0.2f))));
    world.push_back(new sphere(vec3f(-1.0f, 0.0f, -1.0f), 0.5f, new dielectric(1.5f)));
    world.push_back(new sphere(vec3f(-1.0f, 0.0f, -1.0f), -0.45f, new dielectric(1.5f)));
    std::cout << "... done." << std::endl;

    std::cout << "Setting camera ..." << std::endl;
    vec3f lookfrom(13.0f, 2.0f, 3.0f);
    vec3f lookat(0.0f, 0.0f, 0.0f);
    float dist_to_focus = 10.0f;
    float aperture = 0.1f;
    camera cam(lookfrom, lookat, vec3f(0.0f, 1.0f, 0.0f), 20.0f, (float)nx/(float)ny, aperture, dist_to_focus);
    std::cout << "... done." << std::endl;

    std::cout << "Raytracing ..." << std::endl;
    std::ofstream ofile("out.ppm");
    ofile << "P3\n" << nx << " " << ny << "\n255\n";
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
        rgb col = vec3f_to_rgb(colf);

        ofile << col.r << " " << col.g << " " << col.b << "\n";

        if (n%1000 == 0)
        {
            std::cout << "... " << n << "/" << nx*ny << " ..." << std::endl;
        }
    }
    std::cout << "... done." << std::endl;
    ofile.close();
        
    while(world.size())
    {
        geom* g = world.back();
        world.pop_back();
        delete g;
    }
    
    return 0;
}