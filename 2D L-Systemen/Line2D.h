//
// Created by Muaz Moin on 02/03/2024.
//

#include <list>
#include "Point2D.h"
#include "Color.h"

#ifndef CG_LINES2D_H
#define CG_LINES2D_H

class Line2D {
public:
    Point2D p1{},p2{}; //Mijn twee punten
    img::Color color; //kleur van mijn lijn

    Line2D() = default;

    Line2D(Point2D point1, Point2D point2, const img::Color& color) : p1(point1), p2(point2), color(color){}

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
};

using Lines2D = std::list<Line2D>; // Definieer een alias voor een lijst van 2D-lijnen

#endif //CG_LINES2D_H