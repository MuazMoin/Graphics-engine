
#include "FractalFigures.h"
#include "Header Files/TransformationMatrix.h"

std::vector<Figure> FractalFigures::generateFractal(const Figure& figure, int nrIterations, double fractalScale) {
    std::vector<Figure> resultingFigures = {figure};

    if (nrIterations == 0) {
        return resultingFigures;
    } else {
        for (int i = 0; i < nrIterations; ++i) {
            std::vector<Figure> newFigures;
            for (const Figure& baseFigure : resultingFigures) {
                Figure newFigure = baseFigure;

                for (int j = 0; j < newFigure.points.size(); ++j) {
                    Vector3D& point = newFigure.points[j];
                    point = (point - newFigure.center) / fractalScale + newFigure.center;
                }

                newFigures.push_back(newFigure);
            }
            resultingFigures.insert(resultingFigures.end(), newFigures.begin(), newFigures.end());
        }
        return resultingFigures;
    }
}
