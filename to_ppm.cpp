#include <fstream>
#include "to_ppm.h"

void to_ppm(uint size_x, uint size_y, rgb* pixels, const char* filename)
{
    std::ofstream ofile(filename);

    if (!ofile.is_open())
    {
        std::cout << "Error opening output PPM file '" << filename << "'." << std::endl;
        return;
    }

    ofile << "P3\n" << size_x << " " << size_y << "\n255\n";
    for (int j = size_y - 1; j >= 0; --j)
    {
        for (int i = 0; i < size_x; ++i)
        {
            rgb& color = pixels[i + j*size_x];
            ofile << color.r() << " " << color.g() << " " << color.b() << "\n";
        }
    }

    ofile.close();
}