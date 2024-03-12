//
// Created by Muaz Moin on 11/03/2024.
//

#include "FigureParser.h"
#include "Figure.h"
#include "TransformationMatrix.h"
#include <fstream>
#include <cmath>

Figure
FigureParser::parseWireframeFigures(const ini::Configuration &configuration, const Vector3D &eye, int nrFigures) {
    Figure figuresList;
    for (int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);


        Figure newFigures = FigureParser::parseWireframeFigure(configuration[figureName]);

        for (Figure figure: newFigures) {
            figure.applyTransformation(TransformationMatrix::linedrawing3DTransformation(figure.getScale(),
                                                                                         figure.getRotateX() * M_PI /
                                                                                         180.0,
                                                                                         figure.getRotateY() * M_PI /
                                                                                         180.0,
                                                                                         figure.getRotateZ() * M_PI /
                                                                                         180.0, figure.getCenter(),
                                                                                         eye));
            figuresList.push_back(figure);
        }

    }

    return figuresList;

}

Figure FigureParser::parseWireframeFigure(const ini::Section &figure) {
    std::string type = figure["type"].as_string_or_die();

    double rotateX = figure["rotateX"].as_double_or_die();
    double rotateY = figure["rotateY"].as_double_or_die();
    double rotateZ = figure["rotateZ"].as_double_or_die();
    const std::vector<double> &rotations = {rotateX, rotateY, rotateZ};

    const double &scale = figure["scale"].as_double_or_die();

    auto centerTuple = figure["center"].as_double_tuple_or_die();
    Vector3D center = Vector3D::vector(centerTuple[0], centerTuple[1], centerTuple[2]);

    std::vector<double> figureColor = figure["color"].as_double_tuple_or_die();
    img::Color color = img::Color(figureColor[0] * 255, figureColor[1] * 255, figureColor[2] * 255);
}
