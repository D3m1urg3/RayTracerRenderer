#ifndef __CAMERA__
#define __CAMERA__

#include "globals.h"
#include "ray.h"
#include "mramdon.h"

class camera
{
public:
    camera() 
        :_lens_radius(0.0f)
    {
        _lower_left_corner = vec3f(-2.0f, -1.0f, -1.0f);
        _horizontal        = vec3f(4.0f, 0.0f, 0.0f);
        _vertical          = vec3f(0.0f, 2.0f, 0.0f);
        _origin            = vec3f(0.0f, 0.0f, 0.0f);
    }

    camera(float vfov, float aspect) 
        :_lens_radius(0.0f)
    {
        // vfov: vertical camera opening angle in deg
        float theta        = vfov*M_PI / 180.0f;
        float half_height  = tan(theta / 2.0f);
        float half_width   = aspect * half_height;
        _lower_left_corner = vec3f(-half_width, -half_height, -1.0f);
        _horizontal        = vec3f(2.0f*half_width, 0.0f, 0.0f);
        _vertical          = vec3f(0.0f, 2.0f*half_height, 0.0f);
        _origin            = vec3f(0.0f, 0.0f, 0.0f);
    }

    camera(const vec3f& lookfrom, const vec3f& lookat, const vec3f& vup, float vfov, float aspect) 
        :_lens_radius(0.0f)
    {
        // vfov: vertical camera opening angle in deg
        float theta        = vfov*M_PI / 180.0f;
        float half_height  = tan(theta / 2.0f);
        float half_width   = aspect * half_height;

        _origin = lookfrom;
        _w = unit_vec(lookfrom - lookat);
        _u = unit_vec(cross(vup, _w));
        _v = cross(_w, _u);

        _lower_left_corner  = _origin - half_width*_u - half_height*_v - _w;
        _horizontal         = 2.0f*half_width*_u;
        _vertical           = 2.0f*half_height*_v;
    }

    camera(const vec3f& lookfrom, const vec3f& lookat, const vec3f& vup, float vfov, float aspect, float aperture, float focus_dist) 
    {
        // vfov: vertical camera opening angle in deg
        _lens_radius = aperture / 2.0f;
        float theta        = vfov*M_PI / 180.0f;
        float half_height  = tan(theta / 2.0f);
        float half_width   = aspect * half_height;

        _origin = lookfrom;
        _w = unit_vec(lookfrom - lookat);
        _u = unit_vec(cross(vup, _w));
        _v = cross(_w, _u);

        _lower_left_corner  = _origin - half_width*focus_dist*_u - half_height*focus_dist*_v - focus_dist*_w;
        _horizontal         = 2.0f*half_width*focus_dist*_u;
        _vertical           = 2.0f*half_height*focus_dist*_v;
    }

    ray     shoot_ray(float s, float t) 
    { 
        vec3f rd = _lens_radius*rnd_vec3f_in_unit_disk();
        vec3f offset = _u*rd.x() + _v*rd.y();
        return ray(_origin + offset, _lower_left_corner + s*_horizontal + t*_vertical - _origin - offset); 
    }

    vec3f   origin()              const { return _origin; }
    vec3f   lower_left_corner()   const { return _lower_left_corner; }
    vec3f   horizontal()          const { return _horizontal; }
    vec3f   vertical()            const { return _vertical; }
    vec3f   u()                   const { return _u; }
    vec3f   v()                   const { return _v; }
    vec3f   w()                   const { return _w; }
    vec3f&  origin()                    { return _origin; }
    vec3f&  lower_left_corner()         { return _lower_left_corner; }
    vec3f&  horizontal()                { return _horizontal; }
    vec3f&  vertical()                  { return _vertical; }
    vec3f&  u()                         { return _u; }
    vec3f&  v()                         { return _v; }
    vec3f&  w()                         { return _w; }
private:
    vec3f _origin;
    vec3f _lower_left_corner;
    vec3f _horizontal;
    vec3f _vertical;
    vec3f _u, _v, _w;
    float _lens_radius;
};
#endif
