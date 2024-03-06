//
// Created by Muaz Moin on 06/03/2024.
//

#include "TransformationMatrix.h"
#include "cmath"

Matrix TransformationMatrix::scalefigure(const double &scale) {
    Matrix matrix;
    matrix(1,1) = scale;
    matrix(2,2) = scale;
    matrix(3,3) = scale;
    matrix(4,4) = 1;
    return matrix;
}

Matrix TransformationMatrix::rotateX(const double a) {
    Matrix matrix;
    matrix(2,2) = cos(a);
    matrix(2,3) = -sin(a);
    matrix(3,2) = sin(a);
    matrix(3,3) = cos(a);
    return matrix;
}

Matrix TransformationMatrix::rotateY(const double a) {
    Matrix matrix;
    matrix(1,1) = cos(a);
    matrix(1,3) = sin(a);
    matrix(3,1) = -sin(a);
    matrix(3,3) = cos(a);
    return matrix;
}

Matrix TransformationMatrix::rotateZ(const double a) {
    Matrix matrix;
    matrix(1,1) = cos(a);
    matrix(1,2) = -sin(a);
    matrix(2,1) = sin(a);
    matrix(3,2) = cos(a);
    return matrix;
}

Matrix TransformationMatrix::translate(const Vector3D &vector3D) {
    Matrix matrix;
    matrix(1,4) = vector3D.x;
    matrix(2,4) = vector3D.y;
    matrix(3,4) = vector3D.z;
    matrix(4,4) = 1;
    return matrix;
}

Matrix TransformationMatrix::eyePointTransformation(const Vector3D &eyepoint) {
    double r = eyepoint.length();
    double theta = std::atan2(eyepoint.y, eyepoint.x);//slides practicum
    double phi = std::acos(eyepoint.z / r); //slides practicum


    Matrix matrix;
    matrix(1,1) = -sin(theta);
    matrix(1,2) = -cos(theta);
    matrix(1,3) = 0;
    matrix(1,4) = 0;
    matrix(2,1) = cos(theta) * cos(phi);
    matrix(2,2) = -sin(theta) * cos(phi);
    matrix(2,3) = -sin(phi);
    matrix(2,4) = 0;
    matrix(3,1) = cos(theta) * sin(phi);
    matrix(3,2) = -sin(theta) * sin(phi);
    matrix(3,3) = cos(phi);
    matrix(3,4) = 0;
    matrix(4,1) = -r * cos(theta) * sin(phi);
    matrix(4,2) = -r * sin(theta) * sin(phi);
    matrix(4,3) = -r * cos(phi);
    matrix(4,4) = 1;
    return matrix;

}


