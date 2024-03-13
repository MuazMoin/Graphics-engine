//
// Created by Muaz Moin on 11/03/2024.
//

#include "FigureParser.h"
#include "Figure.h"
#include "TransformationMatrix.h"
#include <fstream>
#include <cmath>

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

Figure FigureParser::parseWireframeFigure(const ini::Section &figure) {
    std::string type = figure["type"].as_string_or_die();

    Figure newFigure;

    newFigure.rotateX = figure["rotateX"].as_double_or_die();
    newFigure.rotateY = figure["rotateY"].as_double_or_die();
    newFigure.rotateZ = figure["rotateZ"].as_double_or_die();
    newFigure.scale = figure["scale"].as_double_or_die();




    auto centerTuple = figure["center"].as_double_tuple_or_die();
    Vector3D center = Vector3D::vector(centerTuple[0], centerTuple[1], centerTuple[2]);

    newFigure.center = center;

    std::vector<double> figureColor = figure["color"].as_double_tuple_or_die();
    Color color(figureColor[0], figureColor[1], figureColor[2]);

    newFigure.color = color;

    int nrPoints = figure["nrPoints"].as_int_or_die();
    int nrLines = figure["nrLines"].as_int_or_die();


    for (int i = 0; i < nrPoints; i++) {
        std::string pointName = "point" + std::to_string(i);
        auto Point = figure[pointName].as_double_tuple_or_die();
        auto newPoint = Vector3D::point(Point[0], Point[1], Point[2]);
        newFigure.points.emplace_back(newPoint);
    }


    for (int i = 0; i < nrLines; i++) {
        std::string lineName = "line" + std::to_string(i);
        ini::IntTuple figureLine = figure[lineName].as_int_tuple_or_die();
        auto newFace = Face(figureLine);
        newFigure.faces.emplace_back(newFace);
    }

    return newFigure;
}
