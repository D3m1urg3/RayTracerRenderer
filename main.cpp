#include "globals.h"
#include "to_ppm.h"

int main()
{
    const int nx = 200;
    const int ny = 100;
    rgb pixels[nx*ny];
    for (int k = 0; k < nx*ny; ++k)
    {
        rgb col(int(255.99*float(k%nx) / float(nx)),
                int(255.99*float(k/nx) / float(ny)),
                0.2);
        pixels[k] = col;
    }

    to_ppm(nx, ny, pixels, "out.ppm");
        
    return 0;
}