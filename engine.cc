#include "easy_image.h" // Include headerbestand voor het EasyImage-bibliotheek
#include "ini_configuration.h" // Include headerbestand voor de INI Configuration-bibliotheek
#include "2D_L-Systemen/Line2D.h" // Include headerbestand voor de 2D-lijnbibliotheek
#include "l_parser.h" // Include headerbestand voor de L-parser-bibliotheek
#include <fstream> // Include headerbestand voor bestandsbewerkingen
#include <iostream> // Include headerbestand voor in-/uitvoerbewerkingen
#include <stdexcept> // Include headerbestand voor runtime fouten
#include <string> // Include headerbestand voor stringbewerkingen
#include <list> // Include headerbestand voor de lijstcontainer
#include <cmath> // Include headerbestand voor wiskundige bewerkingen zoals ronde, cosinus en sinus
#include <limits>

#include "2D_L-Systemen/LSystem2D.h"
#include "WireframeParser.h"

//Created by Muaz Moin on 05/03/2024.

using namespace std; // Gebruik de standaardnaamruimte

// Genereert een afbeelding op basis van configuratiegegevens
img::EasyImage generate_image(const ini::Configuration &configuration){
    try {
        cout << "Generating image..." << endl; // Geef aan dat de afbeelding wordt gegenereerd (debugging toegevoegd)

        string type = configuration["General"]["type"].as_string_or_die(); // Haal het type afbeelding op uit de configuratiegegevens

        if (type == "2DLSystem") {
            return LSystem2D::parseLSystem2D(configuration);
        } else if (type == "Wireframe") {
            return WireframeParser::parseWireframe(configuration);
        }
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return {};
    }
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

