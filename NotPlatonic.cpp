////
//// Created by Muaz Moin on 15/03/2024.
////
//
//#include "NotPlatonic.h"
//#include "Triangles.h"
//#include <cmath>
//#include <numeric>
//#include "Platonic.h"
//
//int NotPlatonic::calculateIndex(const int &i, const int &j, const int &m) {
//    return i * m + j;
//}
//
//void  NotPlatonic::createCylinder(Figure &figure, const int &n, const double &height) {
//
//    for (int i = 0; i < n; ++i) {
//        double angle = 2 * i * M_PI / n;
//        double x = cos(angle);
//        double y = sin(angle);
//
//        figure.points.push_back(Vector3D::point(x, y, height));
//        figure.points.push_back(Vector3D::point(x, y, 0));
//    }
//
//
//    for (int i = 0; i < n; ++i) {
//        int v0 = 2 * i;
//        int v1 = 2 * i + 1;
//        int v2 = (2 * i + 3) % (2 * n);
//        int v3 = (2 * i + 2) % (2 * n);
//
//        figure.faces.push_back(Face({v0, v1, v2, v3}));
//    }
//
//    std::vector<int> topFace;
//    std::vector<int> bottomFace;
//
//    for (int i = 0; i < 2 * n; ++i) {
//        if (i % 2 == 0) {
//            topFace.push_back(i);
//        } else {
//            bottomFace.push_back(i);
//        }
//    }
//
//    return figure;
//
//}

//Figure NotPlatonic::createCone(Figure &figure, const int &n, const double &height) {
//
//
//    const double BS = 2 * M_PI / n;
//    for (int i = 0; i < n; ++i) {
//        double angle = i * BS;
//        double c = cos(angle);
//        double s = sin(angle);
//        figure.points.push_back(Vector3D::point(c, s, 0));
//    }
//    figure.points.emplace_back(Vector3D::point(0, 0, height));
//
//
//    for (int i = 0; i < n; ++i) {
//        int a = i % n;
//        int b = (i + 1) % n;
//        figure.faces.push_back(Face({n, a, b}));
//    }
//
//
//    for (int i = 0; i < n; ++i) {
//        figure.faces.push_back(Face({i, (i + 1) % n, n}));
//    }
//
//
//}
//
//Figure NotPlatonic::createSphere(Figure &figure, const int &n) {
//    if (n == 0) {
//        return Platonic::createIcosahedron(figure);
//    } else {
//        Figure icosahedron = Platonic::createIcosahedron(figure);
//        auto splitFaces = Triangles::split_Faces(icosahedron.faces, icosahedron.points, n);
//
//        // De punten normaliseren tijdens het splitsen
//        for (Vector3D &point: splitFaces.second) {
//            point.normalise();
//        }
//
//
//    }
//
//}
//
//Figure NotPlatonic::createTorus(Figure &figure, const double &R, const double &r, const int &n,
//                                const int &m) {
//
//
//    const double U = 2 * M_PI / n;
//    const double V = 2 * M_PI / m;
//
//    Figure newFigure;
//
//    for (int i = 0; i < n; ++i) {
//        double u = i * U;
//        for (int j = 0; j < m; ++j) {
//            double v = j * V;
//
//            figure.points.push_back(Vector3D::point((R + r * cos(v)) * cos(u),
//                                                    (R + r * cos(v)) * sin(u),
//                                                    r * sin(v)));
//
//
//            int index1 = calculateIndex(i, j, m);
//            int index2 = calculateIndex((i + 1) % n, j, m);
//            int index3 = calculateIndex((i + 1) % n, (j + 1) % m, m);
//            int index4 = calculateIndex(i, (j + 1) % m, m);
//
//            figure.faces.push_back(Face({index1, index2, index3, index4}));
//        }
//
//    }
//    return newFigure;
//
//}
//
