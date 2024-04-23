//
// Created by Muaz Moin on 15/03/2024.
//

#ifndef ENGINE_NOTPLATONIC_H
#define ENGINE_NOTPLATONIC_H

#include "Figure.h"

class NotPlatonic {

public:
    static void createCylinder(Figure &figure, const int &n, const double &height);

    static void createCone(Figure &figure, const int &n, const double &height);

    static void createSphere(Figure &figure, const int &n);

    static void createTorus(Figure &figure, const double &R, const double &r, const int &n, const int &m);

    static int calculateIndex(const int &i, const int &j, const int &m);
};
//

#endif //ENGINE_NOTPLATONIC_H
