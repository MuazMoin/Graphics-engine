//
// Created by Muaz Moin on 05/03/2024.
//

#include "LSystem2D.h"
#include "../l_parser.h"
#include "Line2D.h"
#include "../ini_configuration.h"

#include <vector>
#include <fstream>

img::EasyImage LSystem2D::parseLSystem2D(const ini::Configuration &configuration) {
    // Get data form file
    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die(); // Haal het invoerbestand op uit de configuratiegegevens
    std::vector<double> configLineColor = configuration["2DLSystem"]["color"].as_double_tuple_or_die(); // Haal de kleur op uit de configuratiegegevens
    img::Color lineColor(configLineColor[0] * 255, configLineColor[1] * 255,
                         configLineColor[2] * 255); // Maak een kleur op basis van de opgegeven kleur
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die(); // Haal de achtergrondkleur op uit de configuratiegegevens
    int size = configuration["General"]["size"].as_int_or_die(); // Haal de grootte op uit de configuratiegegevens

    // get lsystem
    LParser::LSystem2D lSystem2D = getLParser2D(inputfile);

    // get string
    std::string string = getString(lSystem2D);

    // get lines
    Lines2D lines = getLines(lSystem2D, string, lineColor);

    // scale lines

    std::vector<double> maxAndMinValues = scaleLines(lines, size);

    // make image
    img::EasyImage image = makeImage(size, maxAndMinValues, backgroundColor);

    // draw lines
    drawLines2D(lines, image);

    // return image
    return image;
}

LParser::LSystem2D LSystem2D::getLParser2D(const std::string &inputfile) {
    // get 2DLSystem from file
    LParser::LSystem2D lSystem2D;
    std::ifstream input_stream(inputfile);
    input_stream >> lSystem2D;
    input_stream.close();

    return lSystem2D;
}

std::string LSystem2D::getString(const LParser::LSystem2D &system) {
    std::string oldString = system.get_initiator();
    std::string newString = oldString;

    auto alphabet = system.get_alphabet();

    for (int i = 0; i < system.get_nr_iterations(); i++) {
        newString = "";
        for (char letter: oldString) {
            if (alphabet.find(letter) != alphabet.end()) {
                newString += system.get_replacement(letter);
            }
            else {
                newString += letter;
            }
        }
        oldString = newString;
    }

    return newString;
}

Lines2D LSystem2D::getLines(LParser::LSystem2D &system2D, std::string basicString, const img::Color &lineColor) {
    Lines2D lines;

    double angleComponent = system2D.get_angle() * M_PI / 180; // Bereken de hoek in radialen
    double currentAngle = system2D.get_starting_angle() * M_PI / 180; // Bereken de huidige hoek in radialen

    Point2D oldPoint(0, 0); // Maak een punt met de huidige x- en y-coördinaten
    Point2D newPoint(0, 0); // Maak een punt voor de nieuwe x- en y-coördinaten

    std::vector<std::vector<double>> bracket_stack; // Maak een lijst om de punten van het L-systeem op te slaan

    for (char letter: basicString) {
        if (letter == '-') { // Controleer of de letter een draai naar links vertegenwoordigt
            currentAngle -= angleComponent;
        } else if (letter == '+') { // Controleer of de letter een draai naar rechts vertegenwoordigt
            currentAngle += angleComponent;
        } else if (letter == '(') { // Controleer of de letter een open haakje vertegenwoordigt
            bracket_stack.push_back({newPoint.x, newPoint.y,
                                     currentAngle}); // Voeg de huidige hoek en x- en y-coördinaten toe aan de lijst
        } else if (letter == ')') { // Controleer of de letter een sluit haakje vertegenwoordigt
            newPoint = Point2D(bracket_stack.back()[0],
                               bracket_stack.back()[1]); // Verander het oude punt in het laatste punt in de lijst
            currentAngle = bracket_stack.back()[2]; // Verander de huidige hoek in de laatste hoek in de lijst
            bracket_stack.pop_back(); // Verwijder het laatste punt uit de lijst
        } else { // Als de letter een teken voor een lijn is
            oldPoint = newPoint; // Verander het oude punt in het nieuwe punt
            newPoint = Point2D(oldPoint.x + cos(currentAngle),
                               oldPoint.y + sin(currentAngle)); // Bereken de nieuwe x- en y-coördinaten

            if (system2D.draw(letter)) { // Controleer of de letter een teken is voor een lijn
                Line2D line(oldPoint, newPoint, lineColor); // Maak een lijn tussen de oude en nieuwe punten
                lines.emplace_back(line); // Voeg de lijn toe aan de lijst
            }
        }
    }
    return lines;
}

std::vector<double> LSystem2D::scaleLines(Lines2D &lines, int maxSize) {
    if (lines.empty()) { // Controleer of de lijst met lijnen leeg is
        throw std::runtime_error("[LSystem2D][scaleLines]: No Lines Given"); // Gooi een runtime fout als er geen lijnen zijn
    }

    double xMin = std::numeric_limits<double>::infinity(); // Initialiseer de minimale x-coördinaat met de afbeeldingsgrootte
    double yMin = std::numeric_limits<double>::infinity();; // Initialiseer de minimale y-coördinaat met de afbeeldingsgrootte
    double xMax = -std::numeric_limits<double>::infinity();
    double yMax = -std::numeric_limits<double>::infinity();; // Initialiseer de maximale y-coördinaat met nul

    // Bepaalt de minimale en maximale x- en y-coördinaten van de lijnen
    for (const auto &line: lines) {
        // x max
        xMax = std::max(xMax, line.p1.x);
        xMax = std::max(xMax, line.p2.x);

        // x min
        xMin = std::min(xMin, line.p1.x);
        xMin = std::min(xMin, line.p2.x);

        // y max
        yMax = std::max(yMax, line.p1.y);
        yMax = std::max(yMax, line.p2.y);

        // y min
        yMin = std::min(yMin, line.p1.y);
        yMin = std::min(yMin, line.p2.y);
    }


    // Berekeningen voor het bepalen van de schaal en verschuiving
    double xRange = xMax - xMin; // Bereken het bereik van de x-coördinaten
    double yRange = yMax - yMin; // Bereken het bereik van de y-coördinaten

    double maxRange = std::max(xRange, yRange); // Bepaal het maximale bereik tussen de x- en y-coördinaten

    double imageX = maxSize * (xRange /
                               maxRange); // Bereken de breedte van de afbeelding op basis van de maximale x- en y-bereiken
    double imageY = maxSize * (yRange /
                               maxRange); // Bereken de hoogte van de afbeelding op basis van de maximale x- en y-bereiken

    double scalingFactorD = 0.95 * (imageX / xRange); // Bereken de schaalfactor voor de lijnen
    double DcX =
            scalingFactorD * (xMin + xMax) / 2; // Bereken de x-coördinaat van het midden van de afbeelding na schaling
    double DcY =
            scalingFactorD * (yMin + yMax) / 2; // Bereken de y-coördinaat van het midden van de afbeelding na schaling
    double dx = (imageX / 2) - DcX; // Bereken de verschuiving voor de x-coördinaat
    double dy = (imageY / 2) - DcY; // Bereken de verschuiving voor de y-coördinaat

    for (auto &line: lines) {
        line.scale(scalingFactorD);
        line.translate(Point2D(dx, dy));
    }


    return {xMin, xMax, yMin, yMax};

}

img::EasyImage
LSystem2D::makeImage(int size, std::vector<double> maxAndMinValues, std::vector<double> backgroundColor) {
    double rangeX = maxAndMinValues[1] - maxAndMinValues[0]; // Bereken het bereik van de x-coördinaten
    double rangeY = maxAndMinValues[3] - maxAndMinValues[2]; // Bereken het bereik van de y-coördinaten

    double maxRange = std::max(rangeX, rangeY); // Bepaal het maximale bereik tussen de x- en y-coördinaten

    int imageX = size * (rangeX / maxRange); // Bereken de breedte van de afbeelding
    int imageY = size * (rangeY / maxRange); // Bereken de hoogte van de afbeelding

    img::EasyImage image(imageX, imageY, img::Color(backgroundColor[0] * 255, backgroundColor[1] * 255,
                                                    backgroundColor[2] *
                                                    255)); // Maak een afbeelding met de opgegeven achtergrondkleur
    return image;
}

void LSystem2D::drawLines2D(const Lines2D &lines, img::EasyImage &image) {
    for (const auto &line: lines) {
        image.draw_line(lround(line.p1.x), lround(line.p1.y), lround(line.p2.x), lround(line.p2.y), line.color);
    }
}
// Created by Muaz Moin on 05/03/2024.