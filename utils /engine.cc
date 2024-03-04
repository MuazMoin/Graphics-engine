#include "easy_image.h"
#include "ini_configuration.h"
#include "../Lines/Line2D.h"
#include "../l_parser.h"
#include "../l_parser.cc"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <list>
#include <cmath>
#include "../Lines/drawLines2D.h"
using Lines2D = std::list<Line2D>;
using namespace std;

inline int roundToInt(double d) { return static_cast<int>(round(d)); }

img::EasyImage draw2DLines (img::EasyImage& image, const Lines2D &lines, const int size){
    if (lines.empty()){
        throw std::runtime_error("No Lines Given");
    }
    double xMin = lines.front().p1.x;
    double xMax = lines.front().p1.x;
    double yMin = lines.front().p1.y;
    double yMax = lines.front().p1.y;

    for (const auto& line : lines) {

        // xMin, xMax, yMin, yMax updaten
        if (line.p1.x < xMin) {
            xMin = line.p1.x;
        }
        if (line.p2.x < xMin) {
            xMin = line.p2.x;
        }
        if (line.p2.x < xMin) {
            xMin = line.p2.x;
        }
        if (line.p1.x > xMax) {
            xMax = line.p1.x;
        }
        if (line.p2.x > xMax) {
            xMax = line.p2.x;
        }
        if (line.p1.y < yMin) {
            yMin = line.p1.y;
        }
        if (line.p2.y < yMin) {
            yMin = line.p2.y;
        }
        if (line.p1.y > yMax) {
            yMax = line.p1.y;
        }
        if (line.p2.y > yMax) {
            yMax = line.p2.y;
        }
    }

    cout << "xMin: " << xMin << " xMax: " << xMax << " yMin: " << yMin << " yMax: " << yMax << endl;

    // Berekeningen voor het bepalen van de schaal en verschuiving

    double xRange = xMax - xMin;
    double yRange = yMax - yMin;

    double imageX = size*(xRange/max(xRange,yRange));
    double imageY = size*(yRange/max(xRange,yRange));


    double scalingFactorD = 0.95*(imageX/xRange);

    double DcX = scalingFactorD*(xMin+xMax)/2;
    double DcY = scalingFactorD*(yMin+yMax)/2;

    double dx = (imageX/2) - DcX;
    double dy = (imageY/2) - DcY;

    // Teken de lijnen
    for (const auto& line : lines) {
        double x1 = scalingFactorD * line.p1.x + dx;
        double y1 = scalingFactorD * line.p1.y + dy;
        double x2 = scalingFactorD * line.p2.x + dx;
        double y2 = scalingFactorD * line.p2.y + dy;

        image.draw_line(roundToInt(x1), roundToInt(y1), roundToInt(x2), roundToInt(y2), img::Color(255, 255, 255));
    }
    return image;

}

LParser::LSystem2D createLSystem2D(const string& inputfile) {
    LParser::LSystem2D lSystem2D;
    ifstream file(inputfile);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }
    file >> lSystem2D;
    file.close();
    return lSystem2D;
}

img::EasyImage generate_image(const ini::Configuration &configuration)
{
	return img::EasyImage();
}



int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                std::vector<std::string> args = std::vector<std::string>(argv+1, argv+argc);
                if (args.empty()) {
                        std::ifstream fileIn("filelist");
                        std::string filelistName;
                        while (std::getline(fileIn, filelistName)) {
                                args.push_back(filelistName);
                        }
                }
                for(std::string fileName : args)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(fileName);
                                if (fin.peek() == std::istream::traits_type::eof()) {
                                    std::cout << "Ini file appears empty. Does '" <<
                                    fileName << "' exist?" << std::endl;
                                    continue;
                                }
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << fileName << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
