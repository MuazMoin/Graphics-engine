#include "Triangles.h"

std::pair<std::vector<Face>, std::vector<Vector3D>> Triangles::split_Faces(const std::vector<Face> &faces, const std::vector<Vector3D> &points, const int &splitAmount) {
    std::vector<Face> splitFaces = faces;
    std::vector<Vector3D> splitPoints = points;

    for (int i = 0; i < splitAmount; ++i) {
        std::vector<Face> newFaces;

        // Split each face
        for (int j = 0; j < splitFaces.size(); ++j) {
            Face face = splitFaces[j];

            // Current point of triangle
            const Vector3D& A = splitPoints[face.point_indexes[0]];
            const Vector3D& B = splitPoints[face.point_indexes[1]];
            const Vector3D& C = splitPoints[face.point_indexes[2]];

            // New split points of triangle
            Vector3D D = Vector3D::point((A.x + B.x)/2,
                                         (A.y + B.y)/2,
                                         (A.z + B.z)/2);
            Vector3D E = Vector3D::point((A.x + C.x)/2,
                                         (A.y + C.y)/2,
                                         (A.z + C.z)/2);
            Vector3D F = Vector3D::point((B.x + C.x)/2,
                                         (B.y + C.y)/2,
                                         (B.z + C.z)/2);

            splitPoints.push_back(D);
            splitPoints.push_back(E);
            splitPoints.push_back(F);

            int Ai = face.point_indexes[0];
            int Bi = face.point_indexes[1];
            int Ci = face.point_indexes[2];
            int Di = splitPoints.size()-3;
            int Ei = splitPoints.size()-2;
            int Fi = splitPoints.size()-1;

            newFaces.push_back(Face({Ai, Di, Ei}));
            newFaces.push_back(Face({Bi, Fi, Di}));
            newFaces.push_back(Face({Ci, Ei, Fi}));
            newFaces.push_back(Face({Di, Fi, Ei}));
        }

        splitFaces = newFaces;
    }
    return {splitFaces, splitPoints};
}
