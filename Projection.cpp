//
// Created by Muaz Moin on 08/03/2024.
//

#include "Projection.h"


Point2D Projection::doProjectionPoint2D(const Vector3D *point, const double d) {
    double x = (d * point->x) / (-point->z);
    double y = (d * point->y) / (-point->z);

    return {x, y};
}



Lines2D Projection::doProjectionLines2D(const Figures3d &figures) {
    Lines2D lines;

    for (const auto &figure: figures) {
        std::vector<Face> faces = figure.faces;
        std::vector<Vector3D> points = figure.points;

        for (const auto &face: faces) {
            auto point_indexes = face.point_indexes;

            for (int i = 0; i < point_indexes.size(); ++i) {
                Point2D point1 = doProjectionPoint2D(&points[point_indexes[i]], 1);
                Point2D point2 = doProjectionPoint2D(&points[point_indexes[(i + 1) % point_indexes.size()]], 1);

                lines.emplace_back(point1,
                                   point2,
                                   figure.getColor());
            }
        }
    }
    return lines;
}
