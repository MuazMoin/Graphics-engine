//
// Created by Muaz Moin on 08/03/2024.
//

#ifndef ENGINE_DOPROJECTION_H
#define ENGINE_DOPROJECTION_H
#include "vector3d.h"
#include "2D_L-Systemen/point2d.h"
#include "2D_L-Systemen/line2D.h"
#include "Figure.h"


class Projection {
public:
//    static Point2D doProjection(const Vector3D &point, double d);
//    static Lines2D doProjection(const Figures3d &figures);

    Point2D doProjectionPoint2D(const Vector3D *point, const double d);
    Lines2D doProjectionLines2D(const Figures3d &figures);
    };


#endif //ENGINE_DOPROJECTION_H
