//
// Created by Muaz Moin on 07/03/2024.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include "Face.h"
#include "3D_Lijntekeningen/vector3d.h"
#include "3D_Lijntekeningen/vector3d.cc"
#include "2D_L-Systemen/color.h"
#include "ini_configuration.h"
#include <list>
#include "easy_image.h"



class Figure {
public:  //Dit stukje heb ik laten genereren door de AI. Dit is niet mijn eigen code (Mithal AI).
        // Constructors

        Figure();
        Figure(const std::vector<Face> &faces, const std::vector<Vector3D> &points, const std::vector<double> &rotations,
             double scale, Vector3D center, img::Color color);



        std::vector<Face> faces;
        std::vector<Vector3D> points;


        // Getters
        const img::Color &getColor() const;
        int getRotateX() const;
        int getRotateY() const;
        int getRotateZ() const;
        double getScale() const;
        const Vector3D &getCenter() const;
        const std::string &getType() const;
        const std::vector<Vector3D> &getPoints() const;

    //setters
        void applyTransformation(const Matrix& transformationMatrix);

private:
        std::string type;
        double rotateX;
        double rotateY;
        double rotateZ;
        double scale;
        Vector3D center;
        img::Color color;



};
typedef std::list<Figure> Figures3d;

#endif //ENGINE_FIGURE_H