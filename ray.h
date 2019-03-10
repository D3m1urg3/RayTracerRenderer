#ifndef __RAY__
#define __RAY__

#include "vec3.h"

class ray
{
public:
    ray() {}
    ray(const vec3f& o, const vec3f& n) : o(o), n(n) {}
    vec3f   origin      ()        const { return o; }
    vec3f&  origin      ()              { return o; }
    vec3f   direction   ()        const { return n; }
    vec3f&  direction   ()              { return n; }
    vec3f   position_at (float t) const { return o + t*n; }
private:
    vec3f o;
    vec3f n;
};

#endif
