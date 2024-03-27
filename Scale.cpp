//
// Created by Muaz Moin on 12/03/2024.
//

#include "Scale.h"

void scaleLines::scale2DLines(Lines2D &lines, std::vector<int> imageSize, const double &xMin, const double &xMax,
                              const double &yMin, const double &yMax) {

    double range_x = xMax - xMin;

    double scalingFactorD = 0.95 * (imageSize[0] / range_x); // Bereken de schalingsfactor

    for (Line2D &line : lines) {
        line.scale(scalingFactorD); // Schaal de lijn
    }

    double DcX = scalingFactorD * (xMin + xMax) / 2; // Bereken de x-coördinaat van het midden van de afbeelding na schaling
    double DcY = scalingFactorD * (yMin + yMax) / 2; // Bereken de y-coördinaat van het midden van de afbeelding na schaling
    double dx = (imageSize[0] / 2) - DcX; // Bereken de verschuiving voor de x-coördinaat
    double dy = (imageSize[1]/ 2) - DcY; // Bereken de verschuiving voor de y-coördinaat

    for (Line2D &line : lines) {
        line.moveLine(dx, dy); // Verschuif de lijn
    }



}
