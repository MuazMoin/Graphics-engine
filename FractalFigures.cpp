#include "Header Files/FractalFigures.h"
#include "Header Files/TransformationMatrix.h"

Figures3d FractalFigures::generateFractal(Figure &figure, int nrIterations, double fractalScale) {
            Figures3d resultingFigures = {figure};

    if (nrIterations == 0) {
        return resultingFigures;
    } else {
        for (int i = 0; i < nrIterations; ++i) {
            Figures3d newFigures;
            for (const Figure& figure : resultingFigures) {
                for (int j = 0; j < figure.points.size(); ++j) {
                    Figure newFigure = figure;
                    newFigure.center = figure.points[j];
                    newFigure.scale = figure.scale / fractalScale;
                    newFigures.push_back(newFigure);
                }
            }

            resultingFigures = newFigures;
        }
        return resultingFigures;
    }
}