#ifndef __CAMERA__
#define __CAMERA__

#include "ray.h"

class camera
{
public:
    camera() 
    {
        _lower_left_corner = vec3f(-2.0f, -1.0f, -1.0f);
        _horizontal        = vec3f(4.0f, 0.0f, 0.0f);
        _vertical          = vec3f(0.0f, 2.0f, 0.0f);
        _origin            = vec3f(0.0f, 0.0f, 0.0f);
    }

    ray     shoot_ray(float u, float v) { return ray(_origin, _lower_left_corner + u*_horizontal + v*_vertical - _origin); }

    vec3f   origin()              const { return _origin; }
    vec3f   lower_left_corner()   const { return _lower_left_corner; }
    vec3f   horizontal()          const { return _horizontal; }
    vec3f   vertical()            const { return _vertical; }
    vec3f&  origin()                    { return _origin; }
    vec3f&  lower_left_corner()         { return _lower_left_corner; }
    vec3f&  horizontal()                { return _horizontal; }
    vec3f&  vertical()                  { return _vertical; }
private:
    vec3f _origin;
    vec3f _lower_left_corner;
    vec3f _horizontal;
    vec3f _vertical;
};
#endif
