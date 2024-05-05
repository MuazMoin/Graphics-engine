//
// Created by Muaz Moin on 15/03/2024.
//
#include "Figure.h"

class Platonic {
public:
    static void createCube(Figure& figure);
    static void createTetrahedron(Figure& figure);
    static void createOctahedron(Figure& figure);
    static void createIcosahedron(Figure& figure);
    static void createDodecahedron(Figure& figure);
    static void createMengerSponge(Figure& figure, int maxIterations);
    static void createSubcubes(Figure& figure, int maxIterations, int currentIteration, const Vector3D& center, double size);


};
#ifndef ENGINE_PLATONIC_H
#define ENGINE_PLATONIC_H

#endif //ENGINE_PLATONIC_H
