//
// Created by Muaz Moin on 02/03/2024.
//
#ifndef CG_POINT2D_H
#define CG_POINT2D_H

class Point2D {
public:
    double x,y;

    Point2D() = default;

    Point2D(double newx, double newy) {
        x = newx;
        y = newy;
    }
};

#endif //CG_POINT2D_H
