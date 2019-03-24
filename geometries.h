#ifndef __GEOMETRIES__
#define __GEOMETRIES__

#include <vector>
#include "vec3.h"

struct hit;
class ray;
//------------------------------------------------------------------------------------------------------
// Materials

class material
{
public:
    virtual ~material() {}
    virtual bool scatter(const ray& r_in, const hit& rec, vec3f& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:
    lambertian(const vec3f& a) : _albedo(a) {}
    bool scatter(const ray& r_in, const hit& rec, vec3f& attenuation, ray& scattered) const;

private:
    vec3f _albedo;
};

class metal : public material
{
public:
    metal(const vec3f& a) : _albedo(a) {}
    bool scatter(const ray& r_in, const hit& rec, vec3f& attenuation, ray& scattered) const;

private:
    vec3f _albedo;
};

//------------------------------------------------------------------------------------------------------
// Geometries

class geom {
public:
    virtual ~geom(){}
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit& rec) const = 0;
};

class sphere: public geom
{
public:
    sphere(vec3f p, float r): _pos(p), _radius(r), pmaterial(nullptr) {}
    sphere(vec3f p, float r, material* m): _pos(p), _radius(r), pmaterial(m) {}
    ~sphere() 
    {
        if (pmaterial != nullptr)
        {
            delete pmaterial;
            pmaterial = nullptr;
        }
    }
    const vec3f&    pos()       const { return _pos; }
    float           radius()    const { return _radius; }
    bool            is_hit(const ray& r, float t_min, float t_max, hit& rec) const;
private:
    vec3f _pos;
    float _radius;
    material* pmaterial;
};

bool closest_hit_with_geoms(std::vector<geom*> geoms, const ray& r, float t_min, float t_max, hit& rec);
//------------------------------------------------------------------------------------------------------

struct hit
{
    float t;
    vec3f pos;
    vec3f normal;
    material* pmaterial;
};

#endif
