#include "easy_image.h"
#include "ini_configuration.h"
#include "Line2D.h"
#include "l_parser.h"
#include "l_parser.cc"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <list>
#include <cmath>

using Lines2D = std::list<Line2D>;
using namespace std;

inline int roundToInt(double d) { return static_cast<int>(round(d)); }

void CreateTriangle(Lines2D& triangleLines){
    Point2D p1(10,10);
    Point2D p2(15,20);
    Point2D p3(20,10);

    Line2D l1(p1,p3,Color(255,0,0));
    Line2D l2(p3,p2,Color(0,255,0));
    Line2D l3(p1,p2,Color(0,0,255));

    triangleLines.push_back(l1);
    triangleLines.push_back(l2);
    triangleLines.push_back(l3);
}

img::EasyImage draw2DLines (const Lines2D &lines, const int size){
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

    img::EasyImage image(imageX, imageY, img::Color(0, 0, 0));


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

        image.draw_line(roundToInt(x1), roundToInt(y1), roundToInt(x2), roundToInt(y2), line.color.toEasyImageColor());
    }
    return image;
}

LParser::LSystem2D createLSystem2D(const string& inputfile) { // Functie die een LSystem2D-object maakt op basis van een invoerbestand

    LParser::LSystem2D lSystem2D; // Initialisatie van een LSystem2D-object

    ifstream file(inputfile); // Open het opgegeven bestand

    if (!file.is_open())  { // Controleer of het bestand met succes is geopend

        throw std::runtime_error("File not found"); // Gooi een runtime fout als het bestand niet kan worden geopend
    }

    file >> lSystem2D; // Lees de inhoud van het bestand in het LSystem2D-object

    file.close(); // Sluit het bestand na het lezen

    return lSystem2D; // Geef het LSystem2D-object terug
}

img::EasyImage LSystem2D(const LParser::LSystem2D&  muaz, const vector<double>& backgroundColor, int size, vector<double> lineColor) {
    double currentAngle = muaz.get_starting_angle() * M_PI / 180;
    const set<char>& alphabet = muaz.get_alphabet();
    const string& initiator = muaz.get_initiator();
    img::EasyImage image(size, size, img::Color(backgroundColor[0], backgroundColor[1], backgroundColor[2]));

    for (int i = 0; i <size; i++) {
        for (int j = 0; j < size; j++) {
            image(i, j).red = roundToInt(255*backgroundColor[0]);
            image(i, j).green = roundToInt(255*backgroundColor[1]);
            image(i, j).blue = roundToInt(255*backgroundColor[2]);
        }

    }
    Lines2D lines;
    double x = 0;
    double y = 0;

    for (char letter: initiator) {
        if (letter == '-' ){
            currentAngle -= muaz.get_angle() * M_PI / 180;
        }
        else if (letter == '+') {
            currentAngle += muaz.get_angle() * M_PI / 180;
        }
        else{
            Line2D line{};
            bool lengthDraw = muaz.draw('F');
            if (lengthDraw){
                line.p1.x = x;
                line.p1.y = y;
                line.p2.x = x + cos(currentAngle);
                line.p2.y = y + sin(currentAngle);
                x = line.p2.x;
                y = line.p2.y;
                line.color.red = roundToInt(255*lineColor[0]);
                line.color.green = roundToInt(255*lineColor[1]);
                line.color.blue = roundToInt(255*lineColor[2]);
                lines.push_back(line);
            }

        }
    }

    image = draw2DLines(lines, size);
    return image;
}

img::EasyImage generate_image(const ini::Configuration &configuration){
    img::EasyImage image;
    string type = configuration["General"]["type"].as_string_or_die();

    if (type == "LSystem2D") {
        string inputfile = configuration["LSystem2D"]["inputfile"].as_string_or_die();
        LParser::LSystem2D lSystem2D = createLSystem2D(inputfile);
        vector<double> color = configuration["LSystem2D"]["color"].as_double_tuple_or_die();
        vector<double> backgroundColor = configuration["LSystem2D"]["backgroundcolor"].as_double_tuple_or_die();
        int size = configuration["LSystem2D"]["size"].as_int_or_die();
        vector<double> lineColor = configuration["LSystem2D"]["linecolor"].as_double_tuple_or_die();
        image = LSystem2D(lSystem2D, backgroundColor, size, color);
    }
    return image;
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

        // Voeg hier het stukje code toe om de driehoek te maken, te tekenen en op te slaan
        Lines2D triangleLines;
        CreateTriangle(triangleLines);
        img::EasyImage triangleImage = draw2DLines(triangleLines, 100); // Pas de grootte van de afbeelding aan indien nodig
        try
        {
            std::ofstream f_out("triangle.bmp", std::ios::trunc | std::ios::out | std::ios::binary);
            f_out << triangleImage;
        }
        catch(std::exception& ex)
        {
            std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
            retVal = 1;
        }
    }
    catch(const std::bad_alloc &exception)
    {
        std::cerr << "Error: insufficient memory" << std::endl;
        retVal = 100;
    }
    return retVal;
}
