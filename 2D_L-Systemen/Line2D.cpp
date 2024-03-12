//
// Created by Muaz Moin on 08/03/2024.
//
#include "Line2D.h"

void Line2D::scaleLine(const double &factor){
    p1.x *= factor;
    p1.y *= factor;
    p2.x *= factor;
    p2.y *= factor;
}

