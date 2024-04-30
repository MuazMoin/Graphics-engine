//
// Created by Muaz Moin on 15/03/2024.
//

#ifndef ENGINE_TRIANGLES_H
#define ENGINE_TRIANGLES_H
#include "Face.h"
#include "Figure.h"


class Triangles {
    public:
    static std::pair<std::vector<Face>, std::vector<Vector3D>> split_Faces(const std::vector<Face> &faces, const std::vector<Vector3D> &points, const int &splitAmount);
    static void trifigures(Figure &figure);

};
#endif //ENGINE_TRIANGLES_H
