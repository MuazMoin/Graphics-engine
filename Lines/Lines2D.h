//
// Created by Muaz Moin on 02/03/2024.
//
#include "Point2D.h"
#include "Lines2D.h"
#include "Color.h"

#ifndef CG_LINES2D_H
#define CG_LINES2D_H

class Line2D {
public:
    Point2D p1{},p2{}; //Mijn twee punten
    Color color{}; //kleur van mijn lijn

    Line2D() = default;

    Line2D(Point2D point1, Point2D point2, Color color) {
        Line2D::p1 = point1;
        Line2D::p2 = point2;
        Line2D::color = color;
    }


};


#endif //CG_LINES2D_H