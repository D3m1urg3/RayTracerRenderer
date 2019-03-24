#include "geometries.h"
#include "ray.h"
#include "mramdon.h"

//------------------------------------------------------------------------------------------------------
// Materials

bool lambertian::scatter(const ray& r_in, const hit& rec, vec3f& attenuation, ray& scattered) const
{
    vec3f target = rec.pos + rec.normal + rnd_vec3f_in_unit_sphere();
    scattered    = ray(rec.pos, target - rec.pos);
    attenuation  = _albedo;
    return true;
}

bool metal::scatter(const ray& r_in, const hit& rec, vec3f& attenuation, ray& scattered) const
{
    vec3f reflected = reflect_vec(unit_vec(r_in.direction()), rec.normal);
    scattered    = ray(rec.pos, reflected);
    attenuation  = _albedo;
    return (dot(scattered.direction(), rec.normal)) > 0;
}
//------------------------------------------------------------------------------------------------------
// Geometries

bool sphere::is_hit(const ray& r, float t_min, float t_max, hit& rec) const
{
    vec3f oc = r.origin() - _pos;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction()); // actualy b/2
    float c = dot(oc, oc) - _radius*_radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0)
    {
        float t = (-b - sqrt(discriminant)) / a; // Closest hit 
        if (t_min < t && t < t_max)
        {
            rec.t         = t;
            rec.pos       = r.position_at(t);
            rec.normal    = (rec.pos - _pos) / _radius;
            rec.pmaterial = pmaterial;
            return true;
        }

        t = (-b + sqrt(discriminant)) / a;
        if (t_min < t && t < t_max)
        {
            rec.t         = t;
            rec.pos       = r.position_at(t);
            rec.normal    = (rec.pos - _pos) / _radius;
            rec.pmaterial = pmaterial;
            return true;
        }
    }
    return false;
}

bool closest_hit_with_geoms(std::vector<geom*> geoms, const ray& r, float t_min, float t_max, hit& rec)
{
    hit current_hit;
    bool there_is_a_hit = false;
    float closest_t = t_max;
    for (auto&& g : geoms)
    {
        if (g->is_hit(r, t_min, closest_t, current_hit))
        {
            there_is_a_hit = true;
            closest_t = current_hit.t;
            rec = current_hit;
        }
    }
    return there_is_a_hit;
}