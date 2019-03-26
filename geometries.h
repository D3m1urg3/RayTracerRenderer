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
    metal(const vec3f& a) : _albedo(a), _fuzz(0.0f) {}
    metal(const vec3f& a, float f) : _albedo(a) { _fuzz = (f < 1.0f) ? _fuzz = f : _fuzz = 1.0f; }
    bool scatter(const ray& r_in, const hit& rec, vec3f& attenuation, ray& scattered) const;
private:
    vec3f _albedo;
    float _fuzz;
};

class dielectric : public material
{
public:
    dielectric(float r) :_refraction_idx(r) {}
    bool scatter(const ray& r_in, const hit& rec, vec3f& attenuation, ray& scattered) const;
    inline float schlick_fresnel(float cosine) const
    {
        float r0 = (1.0f - _refraction_idx) / (1.0f + _refraction_idx);
        r0 = r0*r0;
        return r0 + (1.0f - r0)*powf(1.0f - cosine, 5.0f);
    }
private:
    float _refraction_idx;
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
