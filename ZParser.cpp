//
// Created by Muaz Moin on 27/03/2024.
//
#include "Header Files/ZParser.h"
#include "Header Files/ZBufferedWireframeParser.h"
#include "Header Files/FigureParser.h"
#include "Header Files/Projection.h"
#include "Header Files/ImageSize.h"
#include "Header Files/Scale.h"
#include "Header Files/Triangles.h"
#include "Header Files/Figure.h"
#include "2D_L-Systemen/LSystem2D.h"

img::EasyImage ZParser::parseZBuffer(const ini::Configuration &configuration) {

    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eyeTuple = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyeTuple[0], eyeTuple[1], eyeTuple[2]);

    Figures3d figures = FigureParser::parseWireframeFigures(configuration, eye, nrFigures);

    double xMax;
    double yMax;
    double xMin;
    double yMin;

    Lines2D lines = Projection::doZBufferProjection(figures);
    std::vector<int> imageSize = ImageSize::getImageSize(lines, size, xMin, xMax, yMin, yMax);

    img::EasyImage image = img::EasyImage(imageSize[0], imageSize[1],
                                          img::Color(backgroundcolor[0] * 255,
                                                     backgroundcolor[1] * 255,
                                                     backgroundcolor[2] * 255));


    Triangles::trifigures(figures);

    LSystem2D::drawtrifig(image, figures, xMin, xMax, yMin, yMax);

    return image;
}