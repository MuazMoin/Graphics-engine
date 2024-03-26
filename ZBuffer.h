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
    std::vector<std::vector<double>> zBuffer;
};
#endif //ENGINE_ZBUFFER_H
