#include "Header Files/FractalFigures.h"
#include "Header Files/TransformationMatrix.h"

Figures3d FractalFigures::generateFractal(Figure &figure, int nrIterations, double fractalScale) {
    Figures3d resultingFigures = {figure};

    if (nrIterations == 0) {
        return resultingFigures;
    } else {
        for (int i = 0; i < nrIterations; ++i) {
            Figures3d newFigures;
            for (const Figure& baseFigure : resultingFigures) {
                for (int j = 0; j < baseFigure.points.size(); ++j) {
                    Figure newFigure = baseFigure;
                    newFigure.applyTransformation(TransformationMatrix::scalefigure(1 / fractalScale));

                    Vector3D originalPoint = baseFigure.points[j];
                    Vector3D scaledPoint = newFigure.points[j];

                    newFigure.applyTransformation(TransformationMatrix::translate(originalPoint - scaledPoint));
                    newFigures.push_back(newFigure);
                }
            }
            resultingFigures = newFigures;
        }
        return resultingFigures;
    }
}
