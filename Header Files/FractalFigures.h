#include "Figure.h"
#include <vector>

class FractalFigures {
public:
    static Figures3d generateFractal(Figure &figure, int nrIterations, double fractalScale);
};