#ifndef __VECTOR3__
#define __VECTOR3__

#include <iostream>
#include "globals.h"

class vec3f
{
public:
    vec3f() { e[0] = 0.0f; e[1] = 0.0f; e[2] = 0.0f;}
    vec3f(float xx) { e[0] = xx; e[1] = xx; e[2] = xx;}
    vec3f(float x, float y, float z) { e[0] = x; e[1] = y; e[2] = z;}
    vec3f(const vec3f& other) { e[0] = other.e[0]; e[1] = other.e[1]; e[2] = other.e[2];}
    ~vec3f() {}

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    inline float            operator[] (unsigned int i)      const   { return e[i]; }
    inline float&           operator[] (unsigned int i)              { return e[i]; }
    inline const vec3f&     operator+  ()                    const   { return *this; }
    inline vec3f            operator-  ()                    const   { return vec3f(-e[0], -e[1], -e[2]); }

    inline vec3f            operator+  (const vec3f& rhs)    const   { return vec3f(e[0] + rhs.e[0], e[1] + rhs.e[1], e[2] + rhs.e[2]); }
    inline vec3f            operator-  (const vec3f& rhs)    const   { return vec3f(e[0] - rhs.e[0], e[1] - rhs.e[1], e[2] - rhs.e[2]); }
    inline vec3f            operator*  (const vec3f& rhs)    const   { return vec3f(e[0]*rhs.e[0], e[1]*rhs.e[1], e[2]*rhs.e[2]); }
    inline vec3f            operator/  (const vec3f& rhs)    const   { return vec3f(e[0]/rhs.e[0], e[1]/rhs.e[1], e[2]/rhs.e[2]); }
    inline vec3f            operator/  (float rhs)           const   { return vec3f(e[0]/rhs, e[1]/rhs, e[2]/rhs); }

    inline bool             operator== (const vec3f& rhs)    const   { return e[0] == rhs.e[0] && e[1] == rhs.e[1] && e[2] == rhs.e[2]; }
    inline bool             operator!= (const vec3f& rhs)    const   { return e[0] != rhs.e[0] && e[1] != rhs.e[1] && e[2] != rhs.e[2]; }

    vec3f& operator=   (vec3f rhs);
    vec3f& operator+= (const vec3f& rhs);
    vec3f& operator-= (const vec3f& rhs);
    vec3f& operator*= (const vec3f& rhs);
    vec3f& operator/= (const vec3f& rhs);
    vec3f& operator*= (const float t);
    vec3f& operator/= (const float t);

    inline float   squared_length   () { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    inline float   length           () { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
    inline vec3f&   normalize       ()        
    { 
        float invlen = 1.f / length(); 
        e[0] *= invlen;
        e[1] *= invlen;
        e[2] *= invlen; 
        return *this;
    }

private:
    float e[3];

    void swap(vec3f& other) noexcept
    {
        std::swap(e[0], other.e[0]);
        std::swap(e[1], other.e[1]);
        std::swap(e[2], other.e[2]);
    }
}; 

inline vec3f& vec3f::operator= (vec3f rhs)
{
    rhs.swap(*this);
    return *this;
}

inline vec3f& vec3f::operator+= (const vec3f& rhs)
{
    e[0] += rhs.e[0]; 
    e[1] += rhs.e[1];
    e[2] += rhs.e[2];
    return *this;
}

inline vec3f& vec3f::operator-= (const vec3f& rhs)
{
    e[0] -= rhs.e[0];
    e[1] -= rhs.e[1];
    e[2] -= rhs.e[2];
    return *this;
}

inline vec3f& vec3f::operator*= (const vec3f& rhs)
{
    e[0] *= rhs.e[0];
    e[1] *= rhs.e[1];
    e[2] *= rhs.e[2];
    return *this;
}

inline vec3f& vec3f::operator/= (const vec3f& rhs)
{
    e[0] /= rhs.e[0];
    e[1] /= rhs.e[1];
    e[2] /= rhs.e[2];
    return *this;
}

inline vec3f& vec3f::operator*= (const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3f& vec3f::operator/= (const float t)
{
    float inv = 1.0f / t;
    e[0] *= inv;
    e[1] *= inv;
    e[2] *= inv;
    return *this;
}

inline std::istream& operator>> (std::istream& is, vec3f& v)
{
    is >> v[0] >> v[1] >> v[2];
    return is;
}

inline std::ostream& operator<< (std::ostream& os, vec3f& v)
{
    os << v[0] << " " << v[1] << " " << v[2];
    return os;
}

inline vec3f operator* (const vec3f& v, float t) 
{ 
    return vec3f(t*v[0], t*v[1], t*v[2]); 
}

inline vec3f operator* (float t, const vec3f& v) 
{ 
    return vec3f(t*v[0], t*v[1], t*v[2]); 
}

inline float dot(const vec3f& v1, const vec3f& v2)
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

inline vec3f cross(const vec3f& v1, const vec3f& v2)
{
    return vec3f( 
        v1[1]*v2[2] - v1[2]*v2[1],
        -(v1[0]*v2[2] - v1[2]*v2[0]),
        v1[0]*v2[1] - v1[1]*v2[0]
        );
}

inline vec3f unit_vec(vec3f v) 
{
    return v / v.length(); 
}

inline vec3f reflect_vec(const vec3f& v, const vec3f& n)
{
    return v - 2.0f*dot(v, n)*n;
}

inline bool refract_vec(const vec3f& v, const vec3f& n, float ni_over_nt, vec3f& refracted)
{
    bool is_refracted = false;
    vec3f unit_v      = unit_vec(v);
    float dt          = dot(unit_v, n);

    float discriminant = 1.0f - ni_over_nt*ni_over_nt*(1.0f - dt*dt);
    if (discriminant > 0.0f)
    {
        refracted       = ni_over_nt*(unit_v - n*dt) - n*sqrtf(discriminant);
        is_refracted    = true;
    }

    return is_refracted;
}

#endif