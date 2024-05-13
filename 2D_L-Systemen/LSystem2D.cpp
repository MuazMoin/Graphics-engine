//
// Created by Muaz Moin on 05/03/2024.
//

#include "LSystem2D.h"
#include "Line2D.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include "sstream"


img::EasyImage LSystem2D::parseLSystem2D(const ini::Configuration &configuration) {
    // Get data form file
    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die(); // Haal het invoerbestand op uit de configuratiegegevens
    std::vector<double> configLineColor = configuration["2DLSystem"]["color"].as_double_tuple_or_die(); // Haal de kleur op uit de configuratiegegevens
    Color lineColor(configLineColor[0], configLineColor[1],
                         configLineColor[2]); // Maak een kleur op basis van de opgegeven kleur
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
            } else {
                newString += letter;
            }
        }
        oldString = newString;
    }

    return newString;
}

Lines2D LSystem2D::getLines(LParser::LSystem2D &system2D, std::string basicString, const Color &lineColor) {
    Lines2D lines;

    double angleComponent = system2D.get_angle() * 3.14159265359 / 180; // Bereken de hoek in radialen
    double currentAngle = system2D.get_starting_angle() * 3.14159265359 / 180; // Bereken de huidige hoek in radialen

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
        throw std::runtime_error(
                "[LSystem2D][scaleLines]: No Lines Given"); // Gooi een runtime fout als er geen lijnen zijn
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
        image.draw_line(lround(line.p1.x), lround(line.p1.y), lround(line.p2.x), lround(line.p2.y), line.color.toEasyImageColor());
    }
}

void LSystem2D::drawZBufferLines(img::EasyImage &image, const Lines2D &lines) {
    if (image.get_width() == 0 || image.get_height() == 0) {
        throw std::runtime_error("Image dimensions must be greater than 0.");
    }

    ZBuffer zBuffer(image.get_width(), image.get_height());

    for (const Line2D &line : lines) {
        draw_zbuf_line(zBuffer, image, lround(line.p1.x), lround(line.p1.y), lround(line.z1),
                       lround(line.p2.x), lround(line.p2.y), lround(line.z2), line.color);
    }
}

void LSystem2D::drawZBufferLinesUsingInterpolation(img::EasyImage &image, const Lines2D &lines) {
    if (image.get_width() == 0 || image.get_height() == 0) {
        throw std::runtime_error("Image dimensions must be greater than 0.");
    }

    ZBuffer zBuffer(image.get_width(), image.get_height());

    for (const Line2D &line : lines) {
        unsigned int x0 = lround(line.p1.x);
        unsigned int y0 = lround(line.p1.y);
        unsigned int x1 = lround(line.p2.x);
        unsigned int y1 = lround(line.p2.y);

        double z0 = zBuffer.getz_interpolatie(x0, y0);
        double  z1 = zBuffer.getz_interpolatie(x1, y1);

        draw_zbuf_line(zBuffer, image, x0, y0, z0, x1, y1, z1, line.color);
    }
}

void LSystem2D::draw_zbuf_line(ZBuffer &zbuffer, img::EasyImage &image, unsigned int x0,
                               unsigned int y0, unsigned int z0, unsigned int x1, unsigned int y1, unsigned int z1,
                               const Color &color) {
    // Controleren op gevallen waarin (x0, y0) en (x1, y1) worden omgewisseld
    bool swapped = false;
    if ((x0 > x1) || (x0 == x1 && y0 > y1)) {
        std::swap(x0, x1);
        std::swap(y0, y1);
        std::swap(z0, z1);
        swapped = true;
    }

    // Variabele i wordt hier niet gebruikt zoals in de cursus beschreven
    // In plaats daarvan gebruiken we een variabele `dx` en `dy` om de richting van de lijn aan te geven
    int dx = x1 - x0;
    int dy = y1 - y0;

    // Stapgroottes voor x, y en z berekenen
    int x_step = (dx > 0) ? 1 : -1;
    int y_step = (dy > 0) ? 1 : -1;
    int z_step = (z1 - z0) / dx;

    // Absolute waarden van dx en dy berekenen
    dx = std::abs(dx);
    dy = std::abs(dy);

    // Startpositie voor z
    unsigned int z = z0;

    // Variabelen voor het bijhouden van de huidige positie
    unsigned int x = x0;
    unsigned int y = y0;

    // Lijn tekenen
    if (dx > dy) {
        int d = 2 * dy - dx;
        int incrE = 2 * dy;
        int incrNE = 2 * (dy - dx);

        while (x != x1) {
            if (zbuffer.z_close(x, y, z, x1, y1, z1, x, y)) {
                image(x, y) = color.toEasyImageColor();
            }

            if (d <= 0) {
                d += incrE;
                x += x_step;
            } else {
                d += incrNE;
                x += x_step;
                y += y_step;
            }

            z += z_step;
        }
    } else {
        int d = 2 * dx - dy;
        int incrE = 2 * dx;
        int incrNE = 2 * (dx - dy);

        while (y != y1) {
            if (zbuffer.z_close(x, y, z, x1, y1, z1, x, y)) {
                image(x, y) = color.toEasyImageColor();
            }

            if (d <= 0) {
                d += incrE;
                y += y_step;
            } else {
                d += incrNE;
                x += x_step;
                y += y_step;
            }

            z += z_step;
        }
    }

}

void LSystem2D::drawtrifig(img::EasyImage &image, const Figures3d &figures, double &Xmin, double &Xmax, double &Ymin,
                           double &Ymax) {
    // Initialize ZBuffer with image dimensions
    ZBuffer zBuffer = ZBuffer(static_cast<int>(image.get_width()), static_cast<int>(image.get_height()));

// Compute center of the figure
    double dtempo = 0.95 * image.get_width();
    double d = dtempo / (Xmax - Xmin);

    double DCx = d * (Xmin + Xmax) / 2.0;
    double DCy = d * (Ymin + Ymax) / 2.0;

// Compute the offset for centering the figure in the image
    double dXtempo = image.get_width() / 2.0;
    double dx = dXtempo - DCx;

    double dYtempo = image.get_height() / 2.0;
    double dy = dYtempo - DCy;

// Iterate over each figure
    for (auto& figure : figures) {
        // Iterate over each face in the figure
        for (auto& face : figure.faces) {
            // Get the points of the face
            std::vector<Vector3D> points;
            for (auto& index : face.point_indexes) {
                points.push_back(figure.points[index]);
            }

            img::Color imgColor = figure.getColor().toEasyImageColor();
            draw_zbuf_triag(zBuffer, image, points[0], points[1], points[2], d, dx, dy, imgColor);
        }
    }
    }

void LSystem2D::draw_zbuf_triag(ZBuffer &zBuffer, img::EasyImage &image, const Vector3D &A, const Vector3D &B,
                                 const Vector3D &C, double d, double dx, double dy, img::Color color) {
    // Project 3D points to 2D space
    Point2D A_proj(d * A.x / (-A.z) + dx, d * A.y / (-A.z) + dy);
    Point2D B_proj(d * B.x / (-B.z) + dx, d * B.y / (-B.z) + dy);
    Point2D C_proj(d * C.x / (-C.z) + dx, d * C.y / (-C.z) + dy);

    // Find the minimum and maximum y coordinates of the triangle and round them to integer values
    int y_min = static_cast<int>(round(std::min({A_proj.y, B_proj.y, C_proj.y}) + 0.5));
    int y_max = static_cast<int>(round(std::max({A_proj.y, B_proj.y, C_proj.y}) - 0.5));

    // Calculate the coordinates of the centroid and the reciprocal of the depth of the centroid
    double xG = (A_proj.x + B_proj.x + C_proj.x) / 3;
    double yG = (A_proj.y + B_proj.y + C_proj.y) / 3;
    double oneOverZG = 1 / (3 * A.z) + 1 / (3 * B.z) + 1 / (3 * C.z);

    // Loop through each row of the triangle
    for (int y = y_min; y <= y_max; ++y) {
        // Initialize the left and right x coordinates to infinity and negative infinity, respectively
        double xL = std::numeric_limits<double>::infinity();
        double xR = -std::numeric_limits<double>::infinity();

        // Calculate left and right intersections of each triangle edge with the scanline
        auto updateBounds = [&](double xIntersect) {
            xL = std::min(xL, xIntersect);
            xR = std::max(xR, xIntersect);
        };

        // Check and update bounds for each edge of the triangle
        auto checkAndUpdateEdge = [&](const Point2D &p1, const Point2D &p2) {
            if ((y - p1.y) * (y - p2.y) <= 0 && p1.y != p2.y) {
                double xIntersect = p2.x + (p1.x - p2.x) * (y - p2.y) / (p1.y - p2.y);
                updateBounds(xIntersect);
            }
        };

        checkAndUpdateEdge(A_proj, B_proj);
        checkAndUpdateEdge(B_proj, C_proj);
        checkAndUpdateEdge(C_proj, A_proj);

        // Round bounds to integer values
        int xLeft = static_cast<int>(round(xL + 0.5));
        int xRight = static_cast<int>(round(xR - 0.5));

        // Iterate over pixels in the row
        for (int x = xLeft; x <= xRight; ++x) {
            // Calculate plane equation coefficients for perspective correction
            Vector3D u = B - A;
            Vector3D v = C - A;
            Vector3D w = Vector3D::point(u.y * v.z - u.z * v.y,
                                         u.z * v.x - u.x * v.z,
                                         u.x * v.y - u.y * v.x);

            double k = w.x * A.x + w.y * A.y + w.z * A.z;

            double dzdxtempo = w.x;
                double dzdx = dzdxtempo / (-d * k);

            double dzdytempo = w.y;
                double dzdy = dzdytempo / (-d * k);

            // Calculate depth value for the current pixel
            double oneOverZ = 1.0001 * oneOverZG + (x - xG) * dzdx + (y - yG) * dzdy;

            // Check and update Z-buffer
            if (zBuffer.close(x, y, oneOverZ)) {
                image(x, y) = color;
            }
        }
    }
}
