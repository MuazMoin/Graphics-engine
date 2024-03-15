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

    points.push_back(Vector3D::point(1, -1, -1));
    points.push_back(Vector3D::point(-1, 1, -1));
    points.push_back(Vector3D::point(1, 1, 1));
    points.push_back(Vector3D::point(-1, -1, 1));
    points.push_back(Vector3D::point(1, 1, -1));
    points.push_back(Vector3D::point(-1, -1, -1));
    points.push_back(Vector3D::point(1, -1, 1));
    points.push_back(Vector3D::point(-1, 1, 1));

    std::vector<Face> face;

    face.push_back(Face({0, 1, 3, 2})); // Onderste vlak
    face.push_back(Face({1, 5, 7, 3})); // Voorkant vlak
    face.push_back(Face({5, 4, 6, 7})); // Bovenste vlak
    face.push_back(Face({4, 0, 2, 6})); // Achterkant vlak
    face.push_back(Face({2, 3, 7, 6})); // Rechterkant vlak
    face.push_back(Face({0, 4, 5, 1})); // Linkerkant vlak



}

Figure Platonic::createTetrahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                   const img::Color &color) {

    std::vector<Vector3D> points;

    points.push_back(Vector3D::point(1, -1, -1));
    points.push_back(Vector3D::point(-1, 1, -1));
    points.push_back(Vector3D::point(1, 1, 1));
    points.push_back(Vector3D::point(-1, -1, 1));

    std::vector<Face> face;

    face.push_back(Face({0, 1, 3})); // Eerste vlak
    face.push_back(Face({1, 2, 3})); // Tweede vlak
    face.push_back(Face({0, 3, 2})); // Derde vlak
    face.push_back(Face({0, 2, 1})); // Vierde vlak



}

Figure Platonic::createOctahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                  const img::Color &color) {

    std::vector<Vector3D> points;

    points.push_back(Vector3D::point(1, 0, 0));
    points.push_back(Vector3D::point(0, 1, 0));
    points.push_back(Vector3D::point(-1, 0, 0));
    points.push_back(Vector3D::point(0, -1, 0));
    points.push_back(Vector3D::point(0, 0, -1));
    points.push_back(Vector3D::point(0, 0, 1));

    std::vector<Face> face;

    face.push_back(Face({0, 1, 2})); // Eerste vlak
    face.push_back(Face({0, 2, 3})); // Tweede vlak
    face.push_back(Face({0, 3, 4})); // Derde vlak
    face.push_back(Face({0, 4, 1})); // Vierde vlak
    face.push_back(Face({5, 1, 2})); // Vijfde vlak
    face.push_back(Face({5, 2, 3})); // Zesde vlak
    face.push_back(Face({5, 3, 4})); // Zevende vlak
    face.push_back(Face({5, 4, 1})); // Achtste vlak


}

Figure Platonic::createIcosahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                   const img::Color &color) {

    std::vector<Vector3D> points;

    for (int i = 1; i < 6; ++i) {
        points.push_back(Vector3D::point(cos((i - 2) * 2 * M_PI / 5), sin((i - 2) * 2 * M_PI / 5), 0.5));
    }
    for (int i = 6; i < 11; ++i) {
        points.push_back(
                Vector3D::point(cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5), sin(M_PI / 5 + (i - 7) * 2 * M_PI / 5), -0.5));
    }
    points.push_back(Vector3D::point(0, 0, 1));

    std::vector<Face> face;

    face.push_back(Face({0, 1, 2}));   // Eerste vlak
    face.push_back(Face({0, 2, 3}));   // Tweede vlak
    face.push_back(Face({0, 3, 4}));   // Derde vlak
    face.push_back(Face({0, 4, 5}));   // Vierde vlak
    face.push_back(Face({0, 5, 1}));   // Vijfde vlak
    face.push_back(Face({1, 6, 2}));   // Zesde vlak
    face.push_back(Face({2, 6, 7}));   // Zevende vlak
    face.push_back(Face({2, 7, 3}));   // Achtste vlak
    face.push_back(Face({3, 7, 8}));   // Negende vlak
    face.push_back(Face({3, 8, 4}));   // Tiende vlak
    face.push_back(Face({4, 8, 9}));   // Elfde vlak
    face.push_back(Face({4, 9, 5}));   // Twaalfde vlak
    face.push_back(Face({5, 9, 10}));  // Dertiende vlak
    face.push_back(Face({5, 10, 1}));  // Veertiende vlak
    face.push_back(Face({1, 10, 6}));  // Vijftiende vlak
    face.push_back(Face({11, 7, 6}));  // Zestiende vlak
    face.push_back(Face({11, 8, 7}));  // Zeventiende vlak
    face.push_back(Face({11, 9, 8}));  // Achttiende vlak
    face.push_back(Face({11, 10, 9})); // Negentiende vlak
    face.push_back(Face({11, 6, 10})); // Twintigste vlak


}

Figure Platonic::createDodecahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                    const img::Color &color) {

    std::vector<Vector3D> points;

    Figure icosahedron = createIcosahedron({0, 0, 0}, 1, Vector3D::vector(0, 0, 0), color);
    for (const Face &face: icosahedron.faces) {
        double x =
                (icosahedron.points[face.point_indexes[0]].x)/3 +
                        (icosahedron.points[face.point_indexes[1]].x)/3 +
                            (icosahedron.points[face.point_indexes[2]].x) / 3;
        double y =
                (icosahedron.points[face.point_indexes[0]].y)/3 +
                        (icosahedron.points[face.point_indexes[1]].y)/3 +
                            (icosahedron.points[face.point_indexes[2]].y) / 3;

        double z =
                (icosahedron.points[face.point_indexes[0]].z)/3 +
                        (icosahedron.points[face.point_indexes[1]].z)/3 +
                            (icosahedron.points[face.point_indexes[2]].z) / 3;
        points.push_back(Vector3D::point(x, y, z));

    }

    std::vector<Face> face;

    face.push_back(Face({0, 1, 2, 3, 4}));   // Eerste vlak
    face.push_back(Face({0, 5, 10, 15, 6})); // Tweede vlak
    face.push_back(Face({1, 6, 11, 16, 7})); // Derde vlak
    face.push_back(Face({2, 7, 12, 17, 8})); // Vierde vlak
    face.push_back(Face({3, 8, 13, 18, 9})); // Vijfde vlak
    face.push_back(Face({4, 9, 14, 19, 5})); // Zesde vlak
    face.push_back(Face({0, 4, 9, 18, 10})); // Zevende vlak
    face.push_back(Face({0, 10, 5, 14, 15}));// Achtste vlak
    face.push_back(Face({1, 6, 15, 19, 11}));// Negende vlak
    face.push_back(Face({1, 11, 16, 17, 2})); // Tiende vlak
    face.push_back(Face({2, 7, 12, 13, 3}));  // Elfde vlak
    face.push_back(Face({3, 8, 13, 12, 17})); // Twaalfde vlak

}
