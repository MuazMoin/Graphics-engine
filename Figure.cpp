//
// Created by Muaz Moin on 07/03/2024.
//

#include "Figure.h"
#include "TransformationMatrix.h"
#include "cmath"
#include "3D Lijntekeningen/vector3d.h"

Figure::Figure() {
    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;
    scale = 1;
    color = img::Color(0, 0, 0);
    center = Vector3D(0, 0, 0);
}

Figure::Figure(const std::vector<Face> &faces, const std::vector<Vector3D> &points, const std::vector<double> &rotations,
               double scale, Vector3D center, img::Color color) : faces(faces), points(points), center(center), scale(scale), color(color) {
    rotateX = rotations[0];
    rotateY = rotations[1];
    rotateZ = rotations[2];
}

const img::Color &Figure::getColor() const {
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

