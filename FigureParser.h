//
// Created by Muaz Moin on 11/03/2024.
//

#include "Figure.h"
#include "ini_configuration.h"
#include "easy_image.h"

class FigureParser {
public:
    static std::vector<Figure> parseFigures(const ini::Configuration &configuration);
    static Figure parseWireframeFigures(const ini::Configuration &configuration, const Vector3D &eye, int nrFigures);
    static Figure parseWireframeFigure(const ini::Section& figure);

};
#ifndef ENGINE_FIGUREPARSER_H
#define ENGINE_FIGUREPARSER_H

#endif //ENGINE_FIGUREPARSER_H
