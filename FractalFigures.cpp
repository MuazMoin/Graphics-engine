#include "Header Files/FractalFigures.h"
#include "Header Files/TransformationMatrix.h"

std::vector<Figure> FractalFigures::generateFractal(Figure &figure, int nrIterations, double fractalScale) {
    std::vector<Figure> resultingFigures = {figure};

    if (nrIterations == 0) {
        return resultingFigures;
    } else {
        for (int i = 0; i < nrIterations; ++i) {
            std::vector<Figure> newFigures;
            for (const Figure& figure : resultingFigures) {
                for (int j = 0; j < figure.points.size(); ++j) {
                    Figure newFigure = figure;
                    newFigure.center = figure.points[j];
                    newFigure.scale = figure.scale / fractalScale;
                    newFigures.push_back(newFigure);
                }
            }

            resultingFigures=newFigures;
        }
        return resultingFigures;
    }
}