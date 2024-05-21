//
// Created by Muaz Moin on 11/03/2024.
//

#include "Header Files/ImageSize.h"
#include <limits>
#include <algorithm>

std::vector<int> ImageSize::getImageSize(const Lines2D& lines, int size, double &xMin, double &xMax, double &yMin, double &yMax) {
    xMax = yMax = -std::numeric_limits<double>::infinity();
    xMin = yMin = std::numeric_limits<double>::infinity();

    for (const auto &line : lines) {
        xMax = std::max({xMax, line.p1.x, line.p2.x});
        xMin = std::min({xMin, line.p1.x, line.p2.x});
        yMax = std::max({yMax, line.p1.y, line.p2.y});
        yMin = std::min({yMin, line.p1.y, line.p2.y});
    }

    double range_x = xMax - xMin;
    double range_y = yMax - yMin;

    double max_range = std::max(range_x, range_y);

    double image_x = size * (range_x / max_range);
    double image_y = size * (range_y / max_range);

    return {static_cast<int>(image_x), static_cast<int>(image_y)};
}
