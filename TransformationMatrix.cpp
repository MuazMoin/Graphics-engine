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
