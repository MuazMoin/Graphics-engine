#include "Figure.h"
#include <vector>

class FractalFigures {
public:
    static std::vector<Figure> generateFractal(Figure &figure, int nrIterations, double fractalScale);
};