//
// Created by Muaz Moin on 02/03/2024.
//

#include <list>
#include "Point2D.h"
#include "Color.h"

#ifndef CG_LINES2D_H
#define CG_LINES2D_H

#include <limits>

#if !defined(M_PI)
#define M_PI 3.14159265359
#endif

class Line2D {
public:

    Point2D p1{}, p2{}; //Mijn twee punten
    Color color; //kleur van mijn lijn

    // Z-Buffer z coordinates
    double z1 = 0;
    double z2 = 0;

    Line2D() = default;

    Line2D(Point2D point1, Point2D point2, const Color &color) : p1(point1), p2(point2), color(color) {}

    Line2D(const Point2D &pointA, const Point2D &pointB, double z1, double z2, const Color &color) : p1(pointA),
                                                                                                     p2(pointB),
                                                                                                     z1(z1),
                                                                                                     z2(z2),
                                                                                                     color(color) {}


    void scale(double factor) {
        p1.x *= factor;
        p1.y *= factor;
        p2.x *= factor;
        p2.y *= factor;
    }

    void translate(Point2D translation) {
        p1.x += translation.x;
        p1.y += translation.y;
        p2.x += translation.x;
        p2.y += translation.y;
    }

    void moveLine(const double dx, const double dy) {
        p1.x += dx;
        p1.y += dy;
        p2.x += dx;
        p2.y += dy;
    }

};


using Lines2D = std::list<Line2D>; // Definieer een alias voor een lijst van 2D-lijnen

#endif //CG_LINES2D_H