#ifndef ENGINE_LSYSTEM2D_H
#define ENGINE_LSYSTEM2D_H

#include "../Header Files/easy_image.h"
#include "../Header Files/ini_configuration.h"
#include "../Header Files/l_parser.h"
#include "Line2D.h"
#include "../Header Files/Face.h"
#include "Point2D.h"
#include "../Header Files/vector3d.h"
#include "../Header Files/ZBuffer.h"
#include "../Header Files/Figure.h"

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
    static void draw_zbuf_line(ZBuffer &zbuffer, img::EasyImage &image, unsigned int x0,
                               unsigned int y0, unsigned int z0, unsigned int x1, unsigned int y1, unsigned int z1,
                               const Color &color);
    static void drawtrifig(img::EasyImage &image, const Figures3d &figures  , double &Xmin,
                           double &Xmax, double &Ymin, double &Ymax);
    static void draw_zbuf_triag(ZBuffer &zBuffer, img::EasyImage &image, Vector3D const& A, Vector3D const& B, Vector3D const& C, double d, double dx, double dy, img::Color color);
    static void drawZBufferLinesUsingInterpolation(img::EasyImage &image, const Lines2D &lines);


};


#endif //ENGINE_LSYSTEM2D_H
