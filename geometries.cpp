#include "globals.h"
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
    scattered    = ray(rec.pos, reflected + _fuzz*rnd_vec3f_in_unit_sphere());
    attenuation  = _albedo;
    return (dot(scattered.direction(), rec.normal)) > 0;
}

bool dielectric::scatter(const ray& r_in, const hit& rec, vec3f& attenuation, ray& scattered) const
{
    vec3f outward_normal;
    vec3f reflected = reflect_vec(r_in.direction(), rec.normal);
    float ni_over_nt;
    attenuation = vec3f(1.0f, 1.0f, 1.0f);
    vec3f refracted;
    float reflect_prob;
    float cosine;

    if (dot(r_in.direction(), rec.normal) > 0.0f)
    {
        outward_normal  = -rec.normal;
        ni_over_nt      = _refraction_idx;
        cosine          = _refraction_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    else
    {
        outward_normal  = rec.normal;
        ni_over_nt      = 1.0f / _refraction_idx;
        cosine          = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }

    if (refract_vec(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
        reflect_prob = schlick_fresnel(cosine);
    }
    else
    {
        reflect_prob = 1.0f;
    }

    if (rnd_uniform() < reflect_prob)
    {
        scattered = ray(rec.pos, reflected);
    }
    else
    {
        scattered = ray(rec.pos, refracted);
    }

    return true;
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