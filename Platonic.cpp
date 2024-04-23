//
// Created by Muaz Moin on 15/03/2024.
//

#include "Header Files/Platonic.h"
#include "Header Files/Triangles.h"
#include <cmath>
#include <numeric>


void Platonic::createCube(Figure& figure) {

    figure.points.push_back(Vector3D::point(1, -1, -1));
    figure.points.push_back(Vector3D::point(-1, 1, -1));
    figure.points.push_back(Vector3D::point(1, 1, 1));
    figure.points.push_back(Vector3D::point(-1, -1, 1));
    figure.points.push_back(Vector3D::point(1, 1, -1));
    figure.points.push_back(Vector3D::point(-1, -1, -1));
    figure.points.push_back(Vector3D::point(1, -1, 1));
    figure.points.push_back(Vector3D::point(-1, 1, 1));

    figure.faces.push_back(Face({0, 4, 2, 6})); // Onderste vlak
    figure.faces.push_back(Face({4, 1, 7, 2})); // Voorkant vlak
    figure.faces.push_back(Face({1, 5, 3, 7})); // Bovenste vlak
    figure.faces.push_back(Face({5, 0 , 6, 3})); // Achterkant vlak
    figure.faces.push_back(Face({6, 2, 7, 3})); // Rechterkant vlak
    figure.faces.push_back(Face({0, 5, 1, 4})); // Linkerkant vlak
}

void Platonic::createTetrahedron(Figure& figure) {

    figure.points.push_back(Vector3D::point(1, -1, -1));
    figure.points.push_back(Vector3D::point(-1, 1, -1));
    figure.points.push_back(Vector3D::point(1, 1, 1));
    figure.points.push_back(Vector3D::point(-1, -1, 1));

    figure.faces.push_back(Face({0, 1, 2})); // Eerste vlak
    figure.faces.push_back(Face({1, 3, 2})); // Tweede vlak
    figure.faces.push_back(Face({0, 3, 1})); // Derde vlak
    figure.faces.push_back(Face({0, 2, 3})); // Vierde vlak

}

void Platonic::createOctahedron(Figure& figure) {

    figure.points.push_back(Vector3D::point(1, 0, 0));
    figure.points.push_back(Vector3D::point(0, 1, 0));
    figure.points.push_back(Vector3D::point(-1, 0, 0));
    figure.points.push_back(Vector3D::point(0, -1, 0));
    figure.points.push_back(Vector3D::point(0, 0, -1));
    figure.points.push_back(Vector3D::point(0, 0, 1));


    figure.faces.push_back(Face({0, 1, 5})); // Eerste vlak
    figure.faces.push_back(Face({1, 2, 5})); // Tweede vlak
    figure.faces.push_back(Face({2, 3, 5})); // Derde vlak
    figure.faces.push_back(Face({3, 0, 5})); // Vierde vlak
    figure.faces.push_back(Face({1, 0, 4})); // Vijfde vlak
    figure.faces.push_back(Face({2, 1, 4})); // Zesde vlak
    figure.faces.push_back(Face({3, 2, 4})); // Zevende vlak
    figure.faces.push_back(Face({0, 3, 4})); // Achtste vlak


}

void Platonic::createIcosahedron(Figure& figure) {

    figure.points.emplace_back(Vector3D::point(0, 0, (sqrt(5))/2)); // Top vertex

    for (int i = 1; i < 6; ++i) {
        figure.points.emplace_back(Vector3D::point(cos((i - 2) * 2 * M_PI / 5), sin((i - 2) * 2 * M_PI / 5), 0.5));
    }

    for (int i = 6; i < 11; ++i) {
        figure.points.emplace_back(Vector3D::point(cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5), sin(M_PI / 5 + (i - 7) * 2 * M_PI / 5), -0.5));
    }

    figure.points.emplace_back(Vector3D::point(0, 0, -(sqrt(5))/2)); // Bottom vertex


    figure.faces.emplace_back(Face({0, 1, 2}));
    figure.faces.emplace_back(Face({0, 2, 3}));
    figure.faces.emplace_back(Face({0, 3, 4}));
    figure.faces.emplace_back(Face({0, 4, 5}));
    figure.faces.emplace_back(Face({0, 5, 1}));
    figure.faces.emplace_back(Face({1, 6, 2}));
    figure.faces.emplace_back(Face({2, 6, 7}));
    figure.faces.emplace_back(Face({2, 7, 3}));
    figure.faces.emplace_back(Face({3, 7, 8}));
    figure.faces.emplace_back(Face({3, 8, 4}));
    figure.faces.emplace_back(Face({4, 8, 9}));
    figure.faces.emplace_back(Face({4, 9, 5}));
    figure.faces.emplace_back(Face({5, 9, 10}));
    figure.faces.emplace_back(Face({5, 10, 1}));
    figure.faces.emplace_back(Face({1, 10, 6}));
    figure.faces.emplace_back(Face({11, 7, 6}));
    figure.faces.emplace_back(Face({11, 8, 7}));
    figure.faces.emplace_back(Face({11, 9, 8}));
    figure.faces.emplace_back(Face({11, 10, 9}));
    figure.faces.emplace_back(Face({11, 6, 10}));
}


void Platonic::createDodecahedron(Figure& figure) {
    // Definieer de punten van de icosahedron
    Figure icosahedron;
    createIcosahedron(icosahedron);

    // Bereken het gemiddelde van de punten van elke face en voeg deze toe aan de dodecahedron
    for (const Face& face : icosahedron.faces) {
        Vector3D centroid = Vector3D::point(0.0, 0.0, 0.0);
        for (int index : face.point_indexes) {
            centroid += icosahedron.points[index];
        }
        centroid /= face.point_indexes.size();
        figure.points.push_back(centroid);
    }

    // Voeg de faces van de icosahedron toe aan de dodecahedron
    figure.faces = {
            Face({0, 1, 2, 3, 4}),
            Face({0, 5, 6, 7, 1}),
            Face({1, 7, 8, 9, 2}),
            Face({2, 9, 10, 11, 3}),
            Face({3, 11, 12, 13, 4}),
            Face({4, 13, 14, 5, 0}),
            Face({19, 18, 17, 16, 15}),
            Face({19, 14, 13, 12, 18}),
            Face({18, 12, 11, 10, 17}),
            Face({17, 10, 9, 8, 16}),
            Face({16, 8, 7, 6, 15}),
            Face({15, 6, 5, 14, 19})
    };
}






