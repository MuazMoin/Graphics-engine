//
// Created by Muaz Moin on 07/03/2024.
//

#include "Figure.h"
#include "TransformationMatrix.h"
#include <cmath>
#include "vector3d.h"

Figure::Figure() {
    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;
    scale = 1;
    color = Color(0, 0, 0);
    center.x = 0;
    center.y = 0;
    center.z = 0;
}

const Color &Figure::getColor() const {
    return color;
}

void Figure::applyTransformation(const Matrix& transformationMatrix) {
    for (auto &point : points){
        point = point * transformationMatrix;
    }
}

int Figure::getRotateX() const {
    return rotateX;
}

int Figure::getRotateY() const {
    return rotateY;
}

int Figure::getRotateZ() const {
    return rotateZ;
}

double Figure::getScale() const {
    return scale;
}

const Vector3D &Figure::getCenter() const {
    return center;
}

const std::string &Figure::getType() const {
    return type;
}

const std::vector<Vector3D> &Figure::getPoints() const {
    return points;
}

typedef std::list<Figure> Figures3d ;

