//
// Created by Muaz Moin on 15/03/2024.
//
#include "Figure.h"


class Platonic {
    static Figure createCube(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure createTetrahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure createOctahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure createIcosahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);


};
#ifndef ENGINE_PLATONIC_H
#define ENGINE_PLATONIC_H

#endif //ENGINE_PLATONIC_H
