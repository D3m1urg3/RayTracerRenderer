#ifndef __GEOMETRIES__
#define __GEOMETRIES__

#include "ray.h"
#include <vector>

struct hit
{
    float t;
    vec3f pos;
    vec3f normal;
};

class geom {
public:
    virtual ~geom(){}
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit& rec) const = 0;
};

class sphere: public geom
{
public:
    sphere(vec3f p, float r): _pos(p), _radius(r){}
    const vec3f&    pos()       const { return _pos; }
    float           radius()    const { return _radius; }
    bool            is_hit(const ray& r, float t_min, float t_max, hit& rec) const;
private:
    vec3f _pos;
    float _radius;
};

bool closest_hit_with_geoms(std::vector<geom*> geoms, const ray& r, float t_min, float t_max, hit& rec);

#endif
