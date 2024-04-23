//
// Created by Muaz Moin on 08/03/2024.
//

#ifndef ENGINE_DOPROJECTION_H
#define ENGINE_DOPROJECTION_H
#include "vector3d.h"
#include "../2D_L-Systemen/Point2D.h"
#include "../2D_L-Systemen/Line2D.h"
#include "Figure.h"


class Projection {
public:
//    static Point2D doProjection(const Vector3D &point, double d);
//    static Lines2D doProjection(const Figures3d &figures);

    static Point2D doProjection(const Vector3D &point, double d);
    static Lines2D doProjection(const Figures3d &figures);

    static Lines2D doZBufferProjection(const Figures3d &figures);

    };


#endif //ENGINE_DOPROJECTION_H
