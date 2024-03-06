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

Matrix TransformationMatrix::rotateX(const double angle) {
    Matrix matrix;
    matrix(2,2) = cos(angle);
    matrix(2,3) = -sin(angle);
    matrix(3,2) = sin(angle);
    matrix(3,3) = cos(angle);
    return matrix;
}

Matrix TransformationMatrix::rotateY(const double angle) {
    Matrix matrix;
    matrix(1,1) = cos(angle);
    matrix(1,3) = sin(angle);
    matrix(3,1) = -sin(angle);
    matrix(3,3) = cos(angle);
    return matrix;
}

Matrix TransformationMatrix::rotateZ(const double angle) {
    Matrix matrix;
    matrix(1,1) = cos(angle);
    matrix(1,2) = -sin(angle);
    matrix(2,1) = sin(angle);
    matrix(3,2) = cos(angle);
    return matrix;
}


