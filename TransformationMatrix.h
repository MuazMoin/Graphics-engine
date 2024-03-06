//
// Created by Muaz Moin on 06/03/2024.
//

#ifndef ENGINE_TRANSFORMATIONMATRIX_H
#define ENGINE_TRANSFORMATIONMATRIX_H

#include "3D Lijntekeningen/vector3d.h"

class TransformationMatrix {
public:
    static Matrix scalfigure(const double &scale);
    static Matrix translate(const Vector3D &vector3D);

    static Matrix rotateX(const double &angle);
    static Matrix rotateY(const double &angle);
    static Matrix rotateZ(const double &angle);

    static Matrix eyePointTransformation(const Vector3D &eyepoint);


};

#endif //ENGINE_TRANSFORMATIONMATRIX_H
