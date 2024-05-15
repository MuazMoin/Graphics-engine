//
// Created by Muaz Moin on 21/03/2024.
//

#include "Header Files/ZBuffer.h"
#include <limits>
#include <cmath>


ZBuffer::ZBuffer(const int width, const int height)
        : zBuffer(width, std::vector<double>(height, std::numeric_limits<double>::infinity())) {}

bool
ZBuffer::z_close(unsigned int x0, unsigned int y0, double z0, unsigned int x1, unsigned int y1, double z1,
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
    double dx = (double) x1 - (double)x0;
    double dy = (double) y1 - (double)y0;
    double dz = (double)z1 - (double)z0;
    double dist_x = (double)xi -(double) x0;
    double dist_y = (double)yi - (double) y0;
    double distance = std::sqrt(dx * dx + dy * dy);
    //std::cout <<distance << " " <<  std::sqrt(dist_x * dist_x + dist_y * dist_y) / distance<< std::endl;
    double z = z0 + std::sqrt(dist_x * dist_x + dist_y * dist_y) / distance * dz;
//    std::cout << z0 << " " << z1 << " " << z << std::endl;
    return z;
}


double ZBuffer::getz_interpolatie(unsigned int xi, unsigned int yi) const {
    if (xi >= zBuffer.size() || yi >= zBuffer[0].size()) {
        return std::numeric_limits<double>::infinity();
    }

    return 1.0 / zBuffer[xi][yi];
}

bool ZBuffer::close(int x, int y, double zvalue) {
    if (x >= 0 && x < zBuffer.size() && y >= 0 && y < zBuffer[0].size()) {
        if (zvalue < zBuffer[x][y]) {
            zBuffer[x][y] = zvalue;
            return true;
        }
    }
    return false;
}
