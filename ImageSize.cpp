//
// Created by Muaz Moin on 11/03/2024.
//

#include "ImageSize.h"

std::vector<int>
ImageSize::getImageSize(Lines2D lines, int size, double &xMin, double &xMax, double &yMin, double &yMax) {
    xMax = -std::numeric_limits<double>::infinity();
    yMax = -std::numeric_limits<double>::infinity();
    xMin = std::numeric_limits<double>::infinity();
    yMin = std::numeric_limits<double>::infinity();

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

    double range_x = xMax - xMin;
    double range_y = yMax - yMin;

    // calculate max range
    double max_range = std::max(range_x, range_y);

    // calculate size of image
    double image_x = size * (range_x / max_range);
    double image_y = size * (range_y / max_range);

    return {int(image_x), int(image_y)};
}
