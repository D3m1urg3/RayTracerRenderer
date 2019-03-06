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

    inline vec3f&           operator=   (vec3f rhs);
    inline vec3f&           operator+= (const vec3f& rhs);
    inline vec3f&           operator-= (const vec3f& rhs);
    inline vec3f&           operator*= (const vec3f& rhs);
    inline vec3f&           operator/= (const vec3f& rhs);
    inline vec3f&           operator*= (const float t);
    inline vec3f&           operator/= (const float t);

    inline float            dot        (const vec3f& other)   const { return e[0]*other.e[0] +e[1]*other.e[1] + e[1]*other.e[1]; }
    inline vec3f            cross      (const vec3f& other)   const { return vec3f( e[1]*other[2] - e[2]*other[1], -(e[0]*other[2] - e[2]*other[0]), e[0]*other[1] - e[1]*other[0] ); }

    inline float   squared_length   () { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    inline float   length           () { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
    inline vec3f&   normalize       ()        
    { 
        float invlen = 1.f / length(); 
        e[0] *= invlen; e[1] *= invlen; e[2] *= invlen; 
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

std::istream& operator>> (std::istream& is, vec3f& v);
std::ostream& operator<< (std::ostream& os, vec3f& v);
vec3f operator* (const vec3f& v, float t);
vec3f operator* (float t, const vec3f& v);
vec3f unit_vec(vec3f v);
#endif