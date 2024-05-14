#include "Header Files/FractalFigures.h"
#include "Header Files/TransformationMatrix.h"

std::vector<Figure> FractalFigures::generateFractal(const Figure& figure, int nrIterations, double fractalScale) {
    std::vector<Figure> resultingFigures = {figure};

    if (nrIterations == 0) {
        return resultingFigures;
    } else {
        for (int i = 0; i < nrIterations; ++i) {
            std::vector<Figure> newFigures;

            for (const Figure& figure : resultingFigures) {
                for (int j = 0; j < (int)figure.points.size(); ++j) {
                    Figure newFigure = figure;
                    newFigure.applyTransformation(TransformationMatrix::scalefigure(1.0 / fractalScale));

                    Vector3D A = figure.points[j];
                    Vector3D B = newFigure.points[j];

                    newFigure.applyTransformation(TransformationMatrix::translate(A - B));
                    newFigures.push_back(newFigure);
                }
            }
            resultingFigures = newFigures;
        }
        return resultingFigures;
    }
}
