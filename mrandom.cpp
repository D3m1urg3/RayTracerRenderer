#include "mramdon.h"
#include <cstdlib>
#include <time.h>
#include "vec3.h"

float rnd_uniform()
{
    return static_cast<float>(rand() / static_cast<float>(RAND_MAX));
}

vec3f rnd_vec3f_in_unit_sphere()
{
    vec3f p;
    do
    {
        p = 2.0f*vec3f(rnd_uniform(), rnd_uniform(), rnd_uniform()) - vec3f(1.0f, 1.0f, 1.0f);
    } while (p.squared_length() >= 1.0f);
    return p;
}