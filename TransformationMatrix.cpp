//
// Created by Muaz Moin on 06/03/2024.
//

#include "TransformationMatrix.h"

Matrix TransformationMatrix::scalefigure(const double &scale) {
    Matrix matrix;
    matrix(1,1) = scale;
    matrix(2,2) = scale;
    matrix(3,3) = scale;
    matrix(4,4) = 1;
    return matrix;
}

Matrix TransformationMatrix::rotateX(double a) {
    Matrix matrix;
    a = a * M_PI / 180;
    matrix(2,2) = cos(a);
    matrix(2,3) = sin(a);
    matrix(3,2) = -sin(a);
    matrix(3,3) = cos(a);
    matrix(1,1) = 1;
    matrix(4,4) = 1;

    return matrix;
}

Matrix TransformationMatrix::rotateY(double a) {
    Matrix matrix;
    a = a * M_PI / 180;
    matrix(1,1) = cos(a);
    matrix(1,3) = -sin(a);
    matrix(3,1) = sin(a);
    matrix(3,3) = cos(a);
    matrix(2,2) = 1;
    matrix(4,4) = 1;
    return matrix;
}

Matrix TransformationMatrix::rotateZ(double a) {
    Matrix matrix;
    a = a * M_PI / 180;
    matrix(1,1) = cos(a);
    matrix(1,2) = sin(a);
    matrix(2,1) = -sin(a);
    matrix(2,2) = cos(a);
    matrix(3,3) = 1;
    matrix(4,4) = 1;
    return matrix;
}

Matrix TransformationMatrix::translate(const Vector3D &vector3D) {
    Matrix matrix;
    matrix(4,1) = vector3D.x;
    matrix(4,2) = vector3D.y;
    matrix(4,3) = vector3D.z;
    matrix(4,4) = 1;
    return matrix;
}
//

Matrix TransformationMatrix::eyePointTransformation(const Vector3D &eyepoint) {
    double r = eyepoint.length();
    double theta = std::atan2(eyepoint.y, eyepoint.x);//slides practicum
    double phi = std::acos(eyepoint.z / r); //slides practicum


    Matrix matrix;
    matrix(1,1) = -sin(theta);
    matrix(1,2) = -cos(theta) * cos(phi);
    matrix(1,3) = cos(theta) * sin(phi);
    matrix(1,4) = 0;
    matrix(2,1) = cos(theta);
    matrix(2,2) = -sin(theta) * cos(phi);
    matrix(2,3) = -sin(theta) * sin(phi);
    matrix(2,4) = 0;
    matrix(3,1) = 0;
    matrix(3,2) = sin(phi);
    matrix(3,3) = cos(phi);
    matrix(3,4) = 0;
    matrix(4,1) = 0;
    matrix(4,2) = 0;
    matrix(4,3) = -r;
    matrix(4,4) = 1;
    return matrix;

}

// geeft transformatiematrix terug tekenen van 3D-lijnen
Matrix
TransformationMatrix::linedrawing3DTransformation(const double &scale, const double &aX, const double &aY,
                                                  const double &aZ, const Vector3D &center, Vector3D eye) {
    Matrix
    matrix = TransformationMatrix::scalefigure(scale) * TransformationMatrix::rotateX(aX) *
                     TransformationMatrix::rotateY(aY) * TransformationMatrix::rotateZ(aZ) *
                     TransformationMatrix::translate(center) * TransformationMatrix::eyePointTransformation(eye);
    return matrix;
}

