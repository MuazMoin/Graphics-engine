//
// Created by Muaz Moin on 11/03/2024.
//

#include "FigureParser.h"
#include "Figure.h"
#include "TransformationMatrix.h"
#include <fstream>
#include <cmath>
#include "NotPlatonic.h"
#include "Platonic.h"

Figures3d
FigureParser::parseWireframeFigures(const ini::Configuration &configuration, const Vector3D &eye, int nrFigures) {
    Figures3d figuresList;
    for (int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);


        Figure newFig = FigureParser::parseWireframeFigure(configuration[figureName]);
        auto transform = TransformationMatrix::linedrawing3DTransformation(newFig.scale,
                                                                           newFig.rotateX,
                                                                           newFig.rotateY,
                                                                           newFig.rotateZ, newFig.center,
                                                                           eye);
        newFig.applyTransformation(transform);
        figuresList.push_back(newFig);

    }

    return figuresList;
}

Figure FigureParser::parseWireframeFigure(const ini::Section &section) {
    std::string type = section["type"].as_string_or_die();

    Figure newFigure;

    newFigure.rotateX = section["rotateX"].as_double_or_die();
    newFigure.rotateY = section["rotateY"].as_double_or_die();
    newFigure.rotateZ = section["rotateZ"].as_double_or_die();
    newFigure.scale = section["scale"].as_double_or_die();


    auto centerTuple = section["center"].as_double_tuple_or_die();
    Vector3D center = Vector3D::vector(centerTuple[0], centerTuple[1], centerTuple[2]);

    newFigure.center = center;

    std::vector<double> figureColor = section["color"].as_double_tuple_or_die();
    Color color(figureColor[0], figureColor[1], figureColor[2]);


    newFigure.color = color;


    double height = section["height"].as_double_or_default(0);
    int nrIterations = section["nrIterations"].as_int_or_default(0);
    double R = section["R"].as_double_or_default(0);
    double r = section["r"].as_double_or_default(0);
    int n = section["n"].as_int_or_default(0);
    int m = section["m"].as_int_or_default(0);

    if (type == "LineDrawing") {
        FigureParser::createLineDrawing(section, newFigure);
    } else if (type == "Cube") {
        Platonic::createCube(newFigure);
    } else if (type == "Tetrahedron") {
        Platonic::createTetrahedron(newFigure);
    } else if (type == "Octahedron") {
        Platonic::createOctahedron(newFigure);
    } else if (type == "Icosahedron") {
        Platonic::createIcosahedron(newFigure);
    } else if (type == "Dodecahedron") {
        Platonic::createDodecahedron(newFigure);
        return {};

    }
//    else if (type == "Cylinder") {
//        return NotPlatonic::createCylinder(rotations, scale, center, color, n, height);
//    } else if (type == "Cone") {
//        return NotPlatonic::createCone(rotations, scale, center, color, n, height);
//    } else if (type == "Sphere") {
//        return NotPlatonic::createSphere(rotations, scale, center, color, n);
//    } else if (type == "Torus") {
//        return NotPlatonic::createTorus(rotations, scale, center, color, R, r, n, m);
//    }
    else {
        throw std::runtime_error("Invalid figure type: " + type);
    }
    return newFigure;
}

void FigureParser::createLineDrawing(const ini::Section &section, Figure &newFigure) {


    int nrPoints = section["nrPoints"].as_int_or_die();
    int nrLines = section["nrLines"].as_int_or_die();


    for (int i = 0; i < nrPoints; i++) {
        std::string pointName = "point" + std::to_string(i);
        auto Point = section[pointName].as_double_tuple_or_die();
        auto newPoint = Vector3D::point(Point[0], Point[1], Point[2]);
        newFigure.points.emplace_back(newPoint);
    }


    for (int i = 0; i < nrLines; i++) {
        std::string lineName = "line" + std::to_string(i);
        ini::IntTuple figureLine = section[lineName].as_int_tuple_or_die();
        auto newFace = Face(figureLine);
        newFigure.faces.emplace_back(newFace);
    }
}