//
// Created by Muaz Moin on 07/03/2024.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include "Face.h"
#include "vector3d.h"
#include "2D_L-Systemen/Color.h"
#include "ini_configuration.h"
#include <list>
#include "easy_image.h"

#include "Include.hpp"



class Figure {
public:  //Dit stukje heb ik laten genereren door de AI. Dit is niet mijn eigen code (Mithal AI).
        // Constructors

        Figure();
        Figure(const std::vector<Face> &faces, const std::vector<Vector3D> &points, const std::vector<double> &rotations,
             double scale, Vector3D center, img::Color color);


        std::vector<Face> faces;
        std::vector<Vector3D> points;


        // Getters
        const Color &getColor() const;
        const std::string &getType() const;
        const std::vector<Vector3D> &getPoints() const;

    //setters
        void applyTransformation(const Matrix& transformationMatrix);

public:
        std::string type;
        double rotateX;
        double rotateY;
        double rotateZ;
        double scale;
        Vector3D center;
        Color color;



};
typedef std::list<Figure> Figures3d;

#endif //ENGINE_FIGURE_H