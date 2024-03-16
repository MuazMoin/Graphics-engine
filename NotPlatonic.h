//
// Created by Muaz Moin on 15/03/2024.
//

#ifndef ENGINE_NOTPLATONIC_H
#define ENGINE_NOTPLATONIC_H
#include "Figure.h"

class NotPlatonic{
    public:
    static Figure createCylinder(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height);
    static Figure createHalfCylinder(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height);
    static Figure createCone(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height);
    static Figure createSphere(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n);
    static Figure createTorus(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const double &R, const double &r, const int &n, const int &m);
    static int calculateIndex(const int &i, const int &j, const int &m);


};

#endif //ENGINE_NOTPLATONIC_H
