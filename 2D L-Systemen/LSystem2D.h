#ifndef ENGINE_LSYSTEM2D_H
#define ENGINE_LSYSTEM2D_H

#include "../easy_image.h"
#include "../ini_configuration.h"
#include "../l_parser.h"
#include "Line2D.h"

class LSystem2D {
public:
    static img::EasyImage parseLSystem2D(const ini::Configuration &configuration);

private:

    static std::string getString(const LParser::LSystem2D& system);

    static LParser::LSystem2D getLParser2D(const std::string& inputfile);

    static Lines2D getLines(LParser::LSystem2D system2D, std::string basicString, const img::Color& lineColor);

    static std::vector<double> scaleLines(Lines2D &lines, int maxSize);

    static img::EasyImage makeImage(int size, std::vector<double> maxAndMinValues, std::vector<double> backgroundColor);

    static void drawLines2D(const Lines2D& lines, img::EasyImage &image);
};


#endif //ENGINE_LSYSTEM2D_H
