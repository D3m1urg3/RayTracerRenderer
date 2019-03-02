#ifndef __MATH_UTILS__
#define __MATH_UTILS__

#include <iostream>
#include "globals.h";

template <typename T> 
class Vec3
{
public:
    Vec3() { e[0] = 0; e[1] = 0; e[2] = 0;}
    Vec3(T xx) { e[0] = xx; e[1] = xx; e[2] = xx;}
    Vec3(T x, T y, T z) { e[0] = x; e[1] = y; e[2] = z;}
    Vec3(const Vec3& other) { e[0] = other.e[0]; e[1] = other.e[1]; e[2] = other.e[2];}
    ~Vec3() {}

    T x() const { return e[0]; }
    T y() const { return e[1]; }
    T z() const { return e[2]; }
    T r() const { return e[0]; }
    T g() const { return e[1]; }
    T b() const { return e[2]; }

    T               operator[](uint i)  const { return e[i]; }
    T&              operator[](uint i)        { return e[i]; }
    const Vec3&     operator+()         const { return *this; }
    Vec3            operator-()         const {return vec3(-e[0], -e[1], -e[2]) }

    Vec3            operator+ (const Vec3& rhs)     const { return Vec3<T>(e[0] + rhs.e[0], e[1] + rhs.e[1], e[2] + rhs.e[2]); }
    Vec3            operator- (const Vec3& rhs)     const { return Vec3<T>(e[0] - rhs.e[0], e[1] - rhs.e[1], e[2] - rhs.e[2]); }
    Vec3            operator* (const Vec3<T>& rhs)  const { return Vec3<T>(e[0]*rhs.e[0], e[1]*rhs.e[1], e[2]*rhs.e[2]); }
    Vec3            operator/ (const Vec3<T>& rhs)  const { return Vec3<T>(e[0]/rhs.e[0], e[1]/rhs.e[1], e[2]/rhs.e[2]); }

    bool            operator== (const Vec3<T>& rhs) const { return e[0] == rhs.e[0] && e[1] == rhs.e[1] && e[2] == rhs.e[2]; }
    bool            operator!= (const Vec3<T>& rhs) const { return e[0] != rhs.e[0] && e[1] != rhs.e[1] && e[2] != rhs.e[2]; }

    Vec3& operator= (Vec3<T> rhs)
    {
        rhs.swap(*this);
        return *this;
    }

    Vec3& operator+= (const Vec3<T>& rhs)
    {
        e[0] += rhs.e[0]; 
        e[1] += rhs.e[1];
        e[2] += rhs.e[2];
        return *this;
    }

    Vec3& operator-= (const Vec3<T>& rhs)
    {
        e[0] -= rhs.e[0];
        e[1] -= rhs.e[1];
        e[2] -= rhs.e[2];
        return *this;
    }

    Vec3& operator*= (const Vec3<T>& rhs)
    {
        e[0] *= rhs.e[0];
        e[1] *= rhs.e[1];
        e[2] *= rhs.e[2];
        return *this;
    }

    Vec3& operator/= (const Vec3<T>& rhs)
    {
        e[0] /= rhs.e[0];
        e[1] /= rhs.e[1];
        e[2] /= rhs.e[2];
        return *this;
    }

    Vec3& operator*= (const T t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& operator/= (const T t)
    {
        float inv = 1.0f / t;
        e[0] *= inv;
        e[1] *= inv;
        e[2] *= inv;
        return *this;
    }

    T       dot   (const Vec3& other)   const { return e[0]*other.e[0] +e[1]*other.e[1] + e[1]*other.e[1]; }
    Vec3    cross(const Vec3& other)   const { return Vec3( e[1]*other[2] - e[2]*other[1], -(e[0]*other[2] - e[2]*other[0]), e[0]*other[1] - e[1]*other[0] ); }

    float   squared_length   () { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    float   length           () { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
    Vec3&   normalize        ()        
    { 
        T invlen = 1.f / length(); 
        e[0] *= invlen; e[1] *= invlen; e[2] *= invlen; 
        return *this;
    }

private:
    T e[3];

    void swap(Vec3<T>& other) noexcept
    {
        std::swap(e[0], other.e[0]);
        std::swap(e[1], other.e[1]);
        std::swap(e[2], other.e[2]);
    }
}; 

template <class T> Vec3<T> operator* (const Vec3<T>& v, T t) { return Vec3<T>(t*v[0], t*v[1], t*v[2]); }
template <class T> Vec3<T> operator* (T t, const Vec3<T>& v) { return Vec3<T>(t*v[0], t*v[1], t*v[2]); }

template <class T> Vec3<T> unit_vector (Vec3<T> v) { return v / v.length(); }

typedef Vec3<uint>  rgb;
typedef Vec3<float> vec3f;

#endif