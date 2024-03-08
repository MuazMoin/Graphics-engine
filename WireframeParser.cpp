//
// Created by Muaz Moin on 08/03/2024.
//

#include "WireframeParser.h"
#include "Projection.h"
#include "2D_L-Systemen/LSystem2D.h"
#include "2D_L-Systemen/Color.h"


img::EasyImage WireframeParser::parseWireframe(const ini::Configuration &configuration) {
    // Get all general settings from configuration
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eyeTuple = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyeTuple[0], eyeTuple[1], eyeTuple[2]);

    // Get all figures from configuration
}