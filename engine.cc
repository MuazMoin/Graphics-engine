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

using Lines2D = std::list<Line2D>; // Definieer een alias voor een lijst van 2D-lijnen
using namespace std; // Gebruik de standaardnaamruimte

inline int roundToInt(double d) { return static_cast<int>(round(d)); } // Definieer een hulpprogrammafunctie om een ​​drijvend punt naar het dichtstbijzijnde gehele getal te ronden

// Creëert een driehoek met drie lijnen en voegt ze toe aan de gegeven lijst
void CreateTriangle(Lines2D& triangleLines){
    Point2D p1(10,10); // Definieer het eerste punt van de driehoek
    Point2D p2(15,20); // Definieer het tweede punt van de driehoek
    Point2D p3(20,10); // Definieer het derde punt van de driehoek

    Line2D l1(p1,p3,Color(255,0,0)); // Maak de eerste lijn van de driehoek met de opgegeven kleur
    Line2D l2(p3,p2,Color(0,255,0)); // Maak de tweede lijn van de driehoek met de opgegeven kleur
    Line2D l3(p1,p2,Color(0,0,255)); // Maak de derde lijn van de driehoek met de opgegeven kleur

    triangleLines.push_back(l1); // Voeg de eerste lijn van de driehoek toe aan de lijst
    triangleLines.push_back(l2); // Voeg de tweede lijn van de driehoek toe aan de lijst
    triangleLines.push_back(l3); // Voeg de derde lijn van de driehoek toe aan de lijst
}

// Tekent 2D-lijnen op een afbeelding en geeft de afbeelding terug
img::EasyImage draw2DLines(const Lines2D& lines, const int size) {
    if (lines.empty()) { // Controleer of de lijst met lijnen leeg is
        throw std::runtime_error("No Lines Given"); // Gooi een runtime fout als er geen lijnen zijn
    }
    double xMin = size; // Initialiseer de minimale x-coördinaat met de afbeeldingsgrootte
    double xMax = 0; // Initialiseer de maximale x-coördinaat met nul
    double yMin = size; // Initialiseer de minimale y-coördinaat met de afbeeldingsgrootte
    double yMax = 0; // Initialiseer de maximale y-coördinaat met nul

    // Bepaalt de minimale en maximale x- en y-coördinaten van de lijnen
    for (const auto& line : lines) {
        if (line.p1.x < xMin) { // Controleer of de x-coördinaat van het eerste punt kleiner is dan de huidige minimale x-coördinaat
            xMin = line.p1.x; // Update de minimale x-coördinaat
        }
        if (line.p2.x < xMin) { // Controleer of de x-coördinaat van het tweede punt kleiner is dan de huidige minimale x-coördinaat
            xMin = line.p2.x; // Update de minimale x-coördinaat
        }
        if (line.p2.x < xMin) { // Controleer of de x-coördinaat van het tweede punt kleiner is dan de huidige minimale x-coördinaat
            xMin = line.p2.x; // Update de minimale x-coördinaat
        }
        if (line.p1.x > xMax) { // Controleer of de x-coördinaat van het eerste punt groter is dan de huidige maximale x-coördinaat
            xMax = line.p1.x; // Update de maximale x-coördinaat
        }
        if (line.p2.x > xMax) { // Controleer of de x-coördinaat van het tweede punt groter is dan de huidige maximale x-coördinaat
            xMax = line.p2.x; // Update de maximale x-coördinaat
        }
        if (line.p1.y < yMin) { // Controleer of de y-coördinaat van het eerste punt kleiner is dan de huidige minimale y-coördinaat
            yMin = line.p1.y; // Update de minimale y-coördinaat
        }
        if (line.p2.y < yMin) { // Controleer of de y-coördinaat van het tweede punt kleiner is dan de huidige minimale y-coördinaat
            yMin = line.p2.y; // Update de minimale y-coördinaat
        }
        if (line.p1.y > yMax) { // Controleer of de y-coördinaat van het eerste punt groter is dan de huidige maximale y-coördinaat
            yMax = line.p1.y; // Update de maximale y-coördinaat
        }
        if (line.p2.y > yMax) { // Controleer of de y-coördinaat van het tweede punt groter is dan de huidige maximale y-coördinaat
            yMax = line.p2.y; // Update de maximale y-coördinaat
        }
    }

    cout << "xMin: " << xMin << " xMax: " << xMax << " yMin: " << yMin << " yMax: " << yMax << endl; // Geef de minimale en maximale coördinaten weer

    // Berekeningen voor het bepalen van de schaal en verschuiving
    double xRange = xMax - xMin; // Bereken het bereik van de x-coördinaten
    double yRange = yMax - yMin; // Bereken het bereik van de y-coördinaten

    cout << "xRange: " << xRange << " yRange: " << yRange << endl; // Geef de x- en y-bereiken weer (debugging toegevoegd)

    double imageX = size * (xRange / max(xRange, yRange)); // Bereken de breedte van de afbeelding op basis van de maximale x- en y-bereiken
    double imageY = size * (yRange / max(xRange, yRange)); // Bereken de hoogte van de afbeelding op basis van de maximale x- en y-bereiken

    cout << "imageX: " << imageX << " imageY: " << imageY << endl; // Geef de breedte en hoogte van de afbeelding weer (debugging toegevoegd)

    img::EasyImage image(imageX, imageY, img::Color(0, 0, 0)); // Creëer een afbeelding met de berekende breedte en hoogte, en een zwarte achtergrond

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

        image.draw_line(roundToInt(x1), roundToInt(y1), roundToInt(x2), roundToInt(y2), line.color.toEasyImageColor()); // Teken een lijn tussen de twee punten op de afbeelding
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
img::EasyImage LSystem2D(const LParser::LSystem2D& muaz, const vector<double>& backgroundColor, int size, vector<double> lineColor) {
    double currentAngle = muaz.get_starting_angle() * M_PI / 180; // Bereken de huidige hoek in radialen
    const set<char>& alphabet = muaz.get_alphabet(); // Haal het alfabet op uit het LSystem2D-object
    const string& initiator = muaz.get_initiator(); // Haal de initiatorreeks op uit het LSystem2D-object
    img::EasyImage image(size, size, img::Color(backgroundColor[0], backgroundColor[1], backgroundColor[2])); // Creëer een afbeelding met de opgegeven grootte en achtergrondkleur

    for (int i = 0; i < size; i++) { // Loop over alle pixels in de afbeelding
        for (int j = 0; j < size; j++) {
            image(i, j).red = roundToInt(255 * backgroundColor[0]); // Stel de rode component van de pixelkleur in op basis van de achtergrondkleur
            image(i, j).green = roundToInt(255 * backgroundColor[1]); // Stel de groene component van de pixelkleur in op basis van de achtergrondkleur
            image(i, j).blue = roundToInt(255 * backgroundColor[2]); // Stel de blauwe component van de pixelkleur in op basis van de achtergrondkleur
        }
    }

    Lines2D lines; // Maak een lijst om de lijnen van het L-systeem op te slaan
    double x = 0; // Initialiseer de x-coördinaat
    double y = 0; // Initialiseer de y-coördinaat

    // Genereert de lijnen op basis van de initiatorreeks en de regels van het L-systeem
    for (char letter : initiator) {
        if (letter == '-') { // Controleer of de letter een draai naar links vertegenwoordigt
            currentAngle -= muaz.get_angle() * M_PI / 180; // Verander de huidige hoek naar links
        } else if (letter == '+') { // Controleer of de letter een draai naar rechts vertegenwoordigt
            currentAngle += muaz.get_angle() * M_PI / 180; // Verander de huidige hoek naar rechts
        } else { // Als de letter een teken voor een lijn is
            Line2D line{}; // Maak een nieuwe lege lijn
            bool lengthDraw = muaz.draw('F'); // Controleer of er een lijn moet worden getekend op basis van de tekenregel van het L-systeem
            if (lengthDraw) { // Als er een lijn moet worden getekend
                line.p1.x = x; // Stel de x-coördinaat van het eerste punt van de lijn in
                line.p1.y = y; // Stel de y-coördinaat van het eerste punt van de lijn in
                line.p2.x = x + cos(currentAngle); // Bereken de x-coördinaat van het tweede punt van de lijn
                line.p2.y = y + sin(currentAngle); // Bereken de y-coördinaat van het tweede punt van de lijn
                x = line.p2.x; // Update de x-coördinaat voor de volgende lijn
                y = line.p2.y; // Update de y-coördinaat voor de volgende lijn
                line.color.red = roundToInt(255 * lineColor[0]); // Stel de rode component van de lijnkleur in op basis van de opgegeven kleur
                line.color.green = roundToInt(255 * lineColor[1]); // Stel de groene component van de lijnkleur in op basis van de opgegeven kleur
                line.color.blue = roundToInt(255 * lineColor[2]); // Stel de blauwe component van de lijnkleur in op basis van de opgegeven kleur
                lines.push_back(line); // Voeg de lijn toe aan de lijst met lijnen
            }
        }
    }

    cout << "Number of lines: " << lines.size() << endl; // Geef het aantal gegenereerde lijnen weer (debugging toegevoegd)

    image = draw2DLines(lines, size); // Tekent de gegenereerde lijnen op de afbeelding
    return image; // Geeft de afbeelding terug
}

// Genereert een afbeelding op basis van configuratiegegevens
img::EasyImage generate_image(const ini::Configuration &configuration){
    cout << "Generating image..." << endl; // Geef aan dat de afbeelding wordt gegenereerd (debugging toegevoegd)

    img::EasyImage image; // Initialiseer een lege afbeelding
    string type = configuration["General"]["type"].as_string_or_die(); // Haal het type afbeelding op uit de configuratiegegevens

    if (type == "LSystem2D") { // Controleer of het type afbeelding een LSystem2D is
        cout << "LSystem2D type found." << endl; // Geef aan dat een LSystem2D-type is gevonden (debugging toegevoegd)

        string inputfile = configuration["LSystem2D"]["inputfile"].as_string_or_die(); // Haal het invoerbestand op uit de configuratiegegevens
        cout << "Input file: " << inputfile << endl; // Geef het invoerbestand weer (debugging toegevoegd)

        LParser::LSystem2D lSystem2D = createLSystem2D(inputfile); // Creëer een LSystem2D-object op basis van het invoerbestand
        vector<double> color = configuration["LSystem2D"]["color"].as_double_tuple_or_die(); // Haal de kleur op uit de configuratiegegevens
        vector<double> backgroundColor = configuration["LSystem2D"]["backgroundcolor"].as_double_tuple_or_die(); // Haal de achtergrondkleur op uit de configuratiegegevens
        int size = configuration["LSystem2D"]["size"].as_int_or_die(); // Haal de grootte op uit de configuratiegegevens
        vector<double> lineColor = configuration["LSystem2D"]["linecolor"].as_double_tuple_or_die(); // Haal de lijnkleur op uit de configuratiegegevens
        image = LSystem2D(lSystem2D, backgroundColor, size, color); // Genereer de LSystem2D-afbeelding met de opgegeven configuratiegegevens

        // Voeg de driehoekslijnen toe aan de afbeelding
        Lines2D triangleLines; // Initialiseer een lijst voor de driehoekslijnen
        CreateTriangle(triangleLines); // Genereer de driehoekslijnen
        for (const auto& line : triangleLines) { // Loop over alle driehoekslijnen
            image.draw_line(roundToInt(line.p1.x), roundToInt(line.p1.y), // Teken een lijn tussen de twee punten van elke driehoek
                            roundToInt(line.p2.x), roundToInt(line.p2.y),
                            line.color.toEasyImageColor()); // Geef de kleur van de lijn op basis van de kleur van de driehoek
        }
    }
    return image; // Geeft de afbeelding terug
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


        Lines2D triangleLines;
        CreateTriangle(triangleLines);
        img::EasyImage triangleImage = draw2DLines(triangleLines, 100);
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


