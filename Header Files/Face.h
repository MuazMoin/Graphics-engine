//
// Created by Muaz Moin on 07/03/2024.
//

#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H

#include <vector>
#include "../2D_L-Systemen/Point2D.h"


class Face {
public:
    Face() = default;

    Face(const std::vector<int> &point_indexes);

    // Getters
    std::vector<Point2D> doProjection(); //haakjes mmaak daaar een functie van

    std::vector<int> point_indexes;
};




#endif //ENGINE_FACE_H
