//
// Created by Muaz Moin on 11/03/2024.
//

#include "Figure.h"
#include "ini_configuration.h"
#include "easy_image.h"

class FigureParser {
public:
    static Figures3d parseWireframeFigures(const ini::Configuration &configuration, const Vector3D &eye, int nrFigures);
    static Figure parseWireframeFigure(const ini::Section& figure);
    static void createLineDrawing(const ini::Section &section,  Figure &newFigure);
    static Figure parse3DLSystem(Figure &figure, const std::string &inputfile);



};
#ifndef ENGINE_FIGUREPARSER_H
#define ENGINE_FIGUREPARSER_H

#endif //ENGINE_FIGUREPARSER_H
