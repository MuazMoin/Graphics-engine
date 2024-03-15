//
// Created by Muaz Moin on 15/03/2024.
//

#include "Platonic.h"
#include "Triangles.h"
#include <cmath>
#include <numeric>


Figure Platonic::createCube(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                            const img::Color &color) {

    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));
    points.emplace_back(Vector3D::point(1, 1, -1));
    points.emplace_back(Vector3D::point(-1, -1, -1));
    points.emplace_back(Vector3D::point(1, -1, 1));
    points.emplace_back(Vector3D::point(-1, 1, 1));

    std::vector<Face> face;

    face.emplace_back(Face({0, 1, 3, 2})); // Onderste vlak
    face.emplace_back(Face({1, 5, 7, 3})); // Voorkant vlak
    face.emplace_back(Face({5, 4, 6, 7})); // Bovenste vlak
    face.emplace_back(Face({4, 0, 2, 6})); // Achterkant vlak
    face.emplace_back(Face({2, 3, 7, 6})); // Rechterkant vlak
    face.emplace_back(Face({0, 4, 5, 1})); // Linkerkant vlak

}

Figure Platonic::createTetrahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                   const img::Color &color) {

    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));

    std::vector<Face> face;

    face.emplace_back(Face({0, 1, 3})); // Eerste vlak
    face.emplace_back(Face({1, 2, 3})); // Tweede vlak
    face.emplace_back(Face({0, 3, 2})); // Derde vlak
    face.emplace_back(Face({0, 2, 1})); // Vierde vlak



}

Figure Platonic::createOctahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                  const img::Color &color) {

    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, 0, 0));
    points.emplace_back(Vector3D::point(0, 1, 0));
    points.emplace_back(Vector3D::point(-1, 0, 0));
    points.emplace_back(Vector3D::point(0, -1, 0));
    points.emplace_back(Vector3D::point(0, 0, -1));
    points.emplace_back(Vector3D::point(0, 0, 1));

    std::vector<Face> face;

    face.emplace_back(Face({0, 1, 2})); // Eerste vlak
    face.emplace_back(Face({0, 2, 3})); // Tweede vlak
    face.emplace_back(Face({0, 3, 4})); // Derde vlak
    face.emplace_back(Face({0, 4, 1})); // Vierde vlak
    face.emplace_back(Face({5, 1, 2})); // Vijfde vlak
    face.emplace_back(Face({5, 2, 3})); // Zesde vlak
    face.emplace_back(Face({5, 3, 4})); // Zevende vlak
    face.emplace_back(Face({5, 4, 1})); // Achtste vlak


}

Figure Platonic::createIcosahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                   const img::Color &color) {

    std::vector<Face> face;
    std::vector<Vector3D> points;

}

Figure Platonic::createDodecahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                    const img::Color &color) {

    std::vector<Face> face;
    std::vector<Vector3D> points;
}
