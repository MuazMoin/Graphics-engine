#include "Header Files/Figure.h"
#include <vector>

class FractalFigures {
public:
    static std::vector<Figure> generateFractal(const Figure& figure, int nrIterations, double fractalScale);
};