//
// Created by Muaz Moin on 11/03/2024.
//

#include "Header Files/FigureParser.h"
#include "Header Files/Figure.h"
#include "Header Files/TransformationMatrix.h"
#include <fstream>
#include <cmath>
#include "Header Files/NotPlatonic.h"
#include "Header Files/Platonic.h"
#include <sstream>
#include "2D_L-Systemen/LSystem2D.h"
#include "Header Files/l_SystemsFunc.h"
#include "Header Files/ZBuffer.h"
#include "Header Files/FractalFigures.h"


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
    double fractalScale = section["fractalScale"].as_double_or_default(0);
    double R = section["R"].as_double_or_default(0);
    double r = section["r"].as_double_or_default(0);
    int n = section["n"].as_int_or_default(0);
    int m = section["m"].as_int_or_default(0);

    if (type == "LineDrawing") {
        FigureParser::createLineDrawing(section, newFigure);
    }else if (type == "3DLSystem"){
        FigureParser::parse3DLSystem(newFigure, section["inputfile"].as_string_or_die());

        // platonic figures
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

        // not platonic figures
    }else if (type == "Cylinder") {
        NotPlatonic::createCylinder(newFigure, n, height);
    } else if (type == "Cone") {
        NotPlatonic::createCone(newFigure, n, height);
    } else if (type == "Sphere") {
        NotPlatonic::createSphere(newFigure, n);
    } else if (type == "Torus") {
        NotPlatonic::createTorus(newFigure, R, r, n, m);

        // fractal figures
    }else if(type == "FractalCube") {
        Platonic::createCube(newFigure);
        auto fractalFigures = FractalFigures::generateFractal(newFigure, nrIterations, fractalScale);


    } else if(type == "FractalTetrahedron") {
        Platonic::createTetrahedron(newFigure);
        auto fractalFigures = FractalFigures::generateFractal(newFigure, nrIterations, fractalScale);

    } else if(type == "FractalOctahedron") {
        Platonic::createOctahedron(newFigure);
        auto fractalFigures = FractalFigures::generateFractal(newFigure, nrIterations, fractalScale);

    } else if(type == "FractalIcosahedron") {
        Platonic::createIcosahedron(newFigure);
        auto fractalFigures = FractalFigures::generateFractal(newFigure, nrIterations, fractalScale);

    } else if(type == "FractalDodecahedron") {
        Platonic::createDodecahedron(newFigure);
        auto fractalFigures = FractalFigures::generateFractal(newFigure, nrIterations, fractalScale);

    }else if (type == "MengerSponge") {
            int nrIterations = section["nrIterations"].as_int_or_die();

            // Figuur maken
            Platonic platonic;
            Figure mengerSpongeFigure;
            platonic.createMengerSponge(mengerSpongeFigure, nrIterations);

            // Toevoegen aan de lijst met figuren

            return mengerSpongeFigure;

        //runtime error
    }else {
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

void FigureParser::parse3DLSystem(Figure &newFigure, const std::string &inputfile) {

    LParser::LSystem3D l_system = L_SystemsFunc::parseLSystem3D(inputfile);
    std::string figureString = L_SystemsFunc::getString(l_system);
    L_SystemsFunc::getFacesAndPoints(newFigure, l_system, figureString);
}