//
// Created by Muaz Moin on 06/03/2024.
//

#ifndef ENGINE_TRANSFORMATIONMATRIX_H
#define ENGINE_TRANSFORMATIONMATRIX_H

#include "vector3d.h"

class TransformationMatrix {
public:
    static Matrix scalefigure(const double &scale);

    static Matrix translate(const Vector3D &vector3D);

    static Matrix rotateX(const double a);

    static Matrix rotateY(const double a);

    static Matrix rotateZ(const double a);

    static Matrix eyePointTransformation(const Vector3D &eyepoint); //zorgt ervoor dat een 3d object op een 2d vlak getoond wordt.

    static Matrix linedrawing3DTransformation(const double &scale, const double &aX, const double &aY, const double &aZ,
                                const Vector3D &center, Vector3D eye);

};
//

#endif //ENGINE_TRANSFORMATIONMATRIX_H
