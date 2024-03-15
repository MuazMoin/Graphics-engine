//
// Created by Muaz Moin on 15/03/2024.
//

#include "Platonic.h"
#include "Triangles.h"
#include <cmath>
#include <numeric>


Figure Platonic::createCube(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                            const img::Color &color) {

    std::vector<Face> faces;
    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));
    points.emplace_back(Vector3D::point(1, 1, -1));
    points.emplace_back(Vector3D::point(-1, -1, -1));
    points.emplace_back(Vector3D::point(1, -1, 1));
    points.emplace_back(Vector3D::point(-1, 1, 1));


}



Figure Platonic::createTetrahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                   const img::Color &color) {

    std::vector<Face> faces;
    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));


}

Figure Platonic::createOctahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                  const img::Color &color) {

    std::vector<Face> faces;
    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, 0, 0));
    points.emplace_back(Vector3D::point(0, 1, 0));
    points.emplace_back(Vector3D::point(-1, 0, 0));
    points.emplace_back(Vector3D::point(0, -1, 0));
    points.emplace_back(Vector3D::point(0, 0, -1));
    points.emplace_back(Vector3D::point(0, 0, 1));

}

Figure Platonic::createIcosahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                   const img::Color &color) {

    std::vector<Face> faces;
    std::vector<Vector3D> points;

}

Figure Platonic::createDodecahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                    const img::Color &color) {

    std::vector<Face> faces;
    std::vector<Vector3D> points;
}
