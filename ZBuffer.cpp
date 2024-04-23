//
// Created by Muaz Moin on 21/03/2024.
//

#include "Header Files/ZBuffer.h"
#include <limits>
#include <cmath>


ZBuffer::ZBuffer(const int width, const int height)
        : zBuffer(width, std::vector<double>(height, std::numeric_limits<double>::infinity())) {}

bool
ZBuffer::z_close(unsigned int x0, unsigned int y0, unsigned int z0, unsigned int x1, unsigned int y1, unsigned int z1,
                 unsigned int xi, unsigned int yi) {
    double inv_z = 1.0 / z_interpolatie(z0, z1, x0, y0, x1, y1, xi, yi); // Calculate the 1/z value of the current point
    if (inv_z < zBuffer[xi][yi]) { // Check if the current point is closer to the origin than the value in the z-buffer
        zBuffer[xi][yi] = inv_z; // Update the z-buffer with the closer 1/z value
        return true;
    } else {
        return false;
    }
}

double ZBuffer::z_interpolatie(double z0, double z1, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,
                               unsigned int xi, unsigned int yi) {
    double dx = x1 - x0;
    double dy = y1 - y0;
    double dz = z1 - z0;
    double dist_x = xi - x0;
    double dist_y = yi - y0;
    double distance = std::sqrt(dx * dx + dy * dy);
    double z = z0 + (dist_x * dx + dist_y * dy) / distance * dz;

    return z;
}


double ZBuffer::getz_interpolatie(unsigned int xi, unsigned int yi) const {
    if (xi >= zBuffer.size() || yi >= zBuffer[0].size()) {
        return std::numeric_limits<double>::infinity();
    }

    return 1.0 / zBuffer[xi][yi];
}



