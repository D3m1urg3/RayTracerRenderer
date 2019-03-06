#include "vec3.h"

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

std::istream& operator>> (std::istream& is, vec3f& v)
{
    is >> v[0] >> v[1] >> v[2];
    return is;
}

std::ostream& operator<< (std::ostream& os, vec3f& v)
{
    os << v[0] << " " << v[1] << " " << v[2];
    return os;
}

vec3f operator* (const vec3f& v, float t) 
{ 
    return vec3f(t*v[0], t*v[1], t*v[2]); 
}

vec3f operator* (float t, const vec3f& v) 
{ 
    return vec3f(t*v[0], t*v[1], t*v[2]); 
}

vec3f unit_vec(vec3f v) 
{
    return v / v.length(); 
}