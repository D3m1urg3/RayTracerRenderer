#ifndef __RAY__
#define __RAY__

#include "globals.h"
#include "vec3.h"

class ray
{
public:
    ray() {}
    ray(const vec3f& o, const vec3f& n) : _o(o), _n(n) {}
    vec3f   origin      ()        const { return _o; }
    vec3f&  origin      ()              { return _o; }
    vec3f   direction   ()        const { return _n; }
    vec3f&  direction   ()              { return _n; }
    vec3f   position_at (float t) const { return _o + t*_n; }
private:
    vec3f _o;
    vec3f _n;
};

#endif
