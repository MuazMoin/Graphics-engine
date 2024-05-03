//
// Created by Muaz Moin on 21/03/2024.
//

#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include <vector>
#include "vector3d.h"

class ZBuffer : public std::vector<std::vector<double> > {
public:
    ZBuffer();
    ZBuffer(int width, int height);
    bool z_close(unsigned int x0, unsigned int y0, unsigned int z0, unsigned int x1, unsigned int y1, unsigned int z1,
                 unsigned int xi, unsigned int yi);
    bool close(int x, int y, double zvalue);

private:
    double z_interpolatie(double z0, double z1, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int xi, unsigned int yi);
public:
    double getz_interpolatie(unsigned int xi, unsigned int yi) const;

    std::vector<std::vector<double>> zBuffer;
};
#endif //ENGINE_ZBUFFER_H
