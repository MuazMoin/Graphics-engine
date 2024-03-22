#ifndef ENGINE_LSYSTEM2D_H
#define ENGINE_LSYSTEM2D_H

#include "../easy_image.h"
#include "../ini_configuration.h"
#include "../l_parser.h"
#include "Line2D.h"
#include "../Face.h"
#include "Point2D.h"
#include "../vector3d.h"

class LSystem2D {
public:
    static img::EasyImage parseLSystem2D(const ini::Configuration &configuration);

    static std::string getString(const LParser::LSystem2D& system);



private:

    static LParser::LSystem2D getLParser2D(const std::string& inputfile);

    static Lines2D getLines(LParser::LSystem2D& system2D, std::string basicString, const Color& lineColor);

    static std::vector<double> scaleLines(Lines2D &lines, int maxSize);

    static img::EasyImage makeImage(int size, std::vector<double> maxAndMinValues, std::vector<double> backgroundColor);

public:

    static void drawLines2D(const Lines2D& lines, img::EasyImage &image);
    static void drawZBufferLines(img::EasyImage &image, const Lines2D &lines);
    static void draw_zbuf_line(std::vector<std::vector<double>> &zbuffer, img::EasyImage &image, unsigned int x0, unsigned int y0, unsigned int z0, unsigned int x1,
                               unsigned int y1, unsigned int z1, const Color &color);
};


#endif //ENGINE_LSYSTEM2D_H
