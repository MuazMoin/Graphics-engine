#include "easy_image.h" // Include headerbestand voor het EasyImage-bibliotheek
#include "ini_configuration.h" // Include headerbestand voor de INI Configuration-bibliotheek
#include "Line2D.h" // Include headerbestand voor de 2D-lijnbibliotheek
#include "l_parser.h" // Include headerbestand voor de L-parser-bibliotheek
#include <fstream> // Include headerbestand voor bestandsbewerkingen
#include <iostream> // Include headerbestand voor in-/uitvoerbewerkingen
#include <stdexcept> // Include headerbestand voor runtime fouten
#include <string> // Include headerbestand voor stringbewerkingen
#include <list> // Include headerbestand voor de lijstcontainer
#include <cmath> // Include headerbestand voor wiskundige bewerkingen zoals ronde, cosinus en sinus
#include <limits>

#include "LSystem2D.h"


img::EasyImage parseLSystem2D(const ini::Configuration &configuration);

using namespace std; // Gebruik de standaardnaamruimte

inline int roundToInt(double d) { return static_cast<int>(round(d)); } // Definieer een hulpprogrammafunctie om een ​​drijvend punt naar het dichtstbijzijnde gehele getal te ronden

// Tekent 2D-lijnen op een afbeelding en geeft de afbeelding terug
img::EasyImage draw2DLines(const Lines2D &lines, const int size, const vector<double> &backgroundColor) {
    if (lines.empty()) { // Controleer of de lijst met lijnen leeg is
        throw std::runtime_error("No Lines Given"); // Gooi een runtime fout als er geen lijnen zijn
    }
    double xMin = std::numeric_limits<double>::infinity(); // Initialiseer de minimale x-coördinaat met de afbeeldingsgrootte
    double yMin = std::numeric_limits<double>::infinity();; // Initialiseer de minimale y-coördinaat met de afbeeldingsgrootte
    double xMax = -std::numeric_limits<double>::infinity();
    double yMax = -std::numeric_limits<double>::infinity();; // Initialiseer de maximale y-coördinaat met nul

    // Bepaalt de minimale en maximale x- en y-coördinaten van de lijnen
    for (const auto& line : lines) {
        // x max
        xMax = max(xMax, line.p1.x);
        xMax = max(xMax, line.p2.x);

        // x min
        xMin = min(xMin, line.p1.x);
        xMin = min(xMin, line.p2.x);

        // y max
        yMax = max(yMax, line.p1.y);
        yMax = max(yMax, line.p2.y);

        // y min
        yMin = min(yMin, line.p1.y);
        yMin = min(yMin, line.p2.y);
    }

    cout << "xMin: " << xMin << " xMax: " << xMax << " yMin: " << yMin << " yMax: " << yMax << endl; // Geef de minimale en maximale coördinaten weer

    // Berekeningen voor het bepalen van de schaal en verschuiving
    double xRange = xMax - xMin; // Bereken het bereik van de x-coördinaten
    double yRange = yMax - yMin; // Bereken het bereik van de y-coördinaten

    cout << "xRange: " << xRange << " yRange: " << yRange << endl; // Geef de x- en y-bereiken weer (debugging toegevoegd)

    double maxRange = max(xRange, yRange); // Bepaal het maximale bereik tussen de x- en y-coördinaten

    double imageX = size * (xRange/ maxRange); // Bereken de breedte van de afbeelding op basis van de maximale x- en y-bereiken
    double imageY = size * (yRange / maxRange); // Bereken de hoogte van de afbeelding op basis van de maximale x- en y-bereiken

    cout << "imageX: " << imageX << " imageY: " << imageY << endl; // Geef de breedte en hoogte van de afbeelding weer (debugging toegevoegd)

    img::EasyImage image(imageX, imageY, img::Color(backgroundColor[0]*255, backgroundColor[1]*255, backgroundColor[2]*255)); // Creëer een afbeelding met de berekende breedte en hoogte, en een zwarte achtergrond

    double scalingFactorD = 0.95 * (imageX / xRange); // Bereken de schaalfactor voor de lijnen
    double DcX = scalingFactorD * (xMin + xMax) / 2; // Bereken de x-coördinaat van het midden van de afbeelding na schaling
    double DcY = scalingFactorD * (yMin + yMax) / 2; // Bereken de y-coördinaat van het midden van de afbeelding na schaling
    double dx = (imageX / 2) - DcX; // Bereken de verschuiving voor de x-coördinaat
    double dy = (imageY / 2) - DcY; // Bereken de verschuiving voor de y-coördinaat

    // Teken de lijnen op de afbeelding
    for (const auto& line : lines) {
        double x1 = scalingFactorD * line.p1.x + dx; // Bereken de x-coördinaat van het eerste punt na schaling en verschuiving
        double y1 = scalingFactorD * line.p1.y + dy; // Bereken de y-coördinaat van het eerste punt na schaling en verschuiving
        double x2 = scalingFactorD * line.p2.x + dx; // Bereken de x-coördinaat van het tweede punt na schaling en verschuiving
        double y2 = scalingFactorD * line.p2.y + dy; // Bereken de y-coördinaat van het tweede punt na schaling en verschuiving

        image.draw_line(roundToInt(x1), roundToInt(y1), roundToInt(x2), roundToInt(y2), line.color); // Teken een lijn tussen de twee punten op de afbeelding
    }
    return image; // Geef de afbeelding terug
}

// Creëert een LSystem2D-object op basis van een invoerbestand
LParser::LSystem2D createLSystem2D(const string& inputfile) {
    LParser::LSystem2D lSystem2D; // Initialisatie van een LSystem2D-object

    ifstream file(inputfile); // Open het opgegeven bestand

    if (!file.is_open())  { // Controleer of het bestand met succes is geopend
        throw std::runtime_error("File not found"); // Gooi een runtime fout als het bestand niet kan worden geopend
    }

    file >> lSystem2D; // Lees de inhoud van het bestand in het LSystem2D-object

    file.close(); // Sluit het bestand na het lezen

    return lSystem2D; // Geef het LSystem2D-object terug
}

// Genereert een afbeelding op basis van een LSystem2D-object en configuratiegegevens
img::EasyImage LSystem2D(const LParser::LSystem2D& muaz, const vector<double>& backgroundColor, int size, const img::Color& lineColor) {
    // Haal de configuratiegegevens op uit het LSystem2D-object
    double angleComponent = muaz.get_angle() * M_PI / 180; // Bereken de huidige hoek in radialen
    const set<char>& alphabet = muaz.get_alphabet(); // Haal het alfabet op uit het LSystem2D-object
    const string& initiator = muaz.get_initiator(); // Haal de initiatorreeks op uit het LSystem2D-object



    Lines2D lines; // Maak een lijst om de lijnen van het L-systeem op te slaan
    double x = 0; // Initialiseer de x-coördinaat
    double y = 0; // Initialiseer de y-coördinaat

    // Genereert de lijnen op basis van de initiatorreeks en de regels van het L-systeem
    string oldString = initiator;
    string newString ;

    for (int i = 0; i < muaz.get_nr_iterations(); i++){
        newString = "";
        for (char letter : oldString){
            if (alphabet.find(letter) != alphabet.end()){
                newString += muaz.get_replacement(letter);
            } else {
                newString += letter;
            }
        }
        oldString = newString;
    }

    double currentAngle = muaz.get_starting_angle() * M_PI / 180; // Bereken de huidige hoek in radialen
    Point2D oldPoint(0, 0); // Maak een punt met de huidige x- en y-coördinaten
    Point2D newPoint(0,0); // Maak een punt voor de nieuwe x- en y-coördinaten

    std::vector<vector<double>> bracket_stack; // Maak een lijst om de punten van het L-systeem op te slaan

    for (char letter : newString) {
        if (letter == '-') { // Controleer of de letter een draai naar links vertegenwoordigt
            currentAngle -= angleComponent;
        } else if (letter == '+') { // Controleer of de letter een draai naar rechts vertegenwoordigt
            currentAngle += angleComponent;
        }else if (letter == '(') { // Controleer of de letter een open haakje vertegenwoordigt
            bracket_stack.push_back({newPoint.x, newPoint.y, currentAngle}); // Voeg de huidige hoek en x- en y-coördinaten toe aan de lijst
        } else if (letter == ')') { // Controleer of de letter een sluit haakje vertegenwoordigt
            newPoint = Point2D(bracket_stack.back()[0], bracket_stack.back()[1]); // Verander het oude punt in het laatste punt in de lijst
            currentAngle = bracket_stack.back()[2]; // Verander de huidige hoek in de laatste hoek in de lijst
            bracket_stack.pop_back(); // Verwijder het laatste punt uit de lijst
        } else { // Als de letter een teken voor een lijn is
            oldPoint = newPoint; // Verander het oude punt in het nieuwe punt
            newPoint = Point2D(oldPoint.x + cos(currentAngle), oldPoint.y + sin(currentAngle)); // Bereken de nieuwe x- en y-coördinaten

            if (muaz.draw(letter)) { // Controleer of de letter een teken is voor een lijn
                Line2D line(oldPoint, newPoint, lineColor); // Maak een lijn tussen de oude en nieuwe punten
                lines.emplace_back(line); // Voeg de lijn toe aan de lijst
            }
        }
    }

    cout << "Number of lines: " << lines.size() << endl; // Geef het aantal gegenereerde lijnen weer (debugging toegevoegd)

    return draw2DLines(lines, size, backgroundColor); // Tekent de gegenereerde lijnen op de afbeelding
}

// Genereert een afbeelding op basis van configuratiegegevens
img::EasyImage generate_image(const ini::Configuration &configuration){
    cout << "Generating image..." << endl; // Geef aan dat de afbeelding wordt gegenereerd (debugging toegevoegd)

    string type = configuration["General"]["type"].as_string_or_die(); // Haal het type afbeelding op uit de configuratiegegevens

    if (type == "2DLSystem") {
        return LSystem2D::parseLSystem2D(configuration);
    } else {
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

