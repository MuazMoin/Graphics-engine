//
// Created by Muaz Moin on 03/03/2024.
//

#include "Line2D.h"
#include <vector>
#include "../utils /easy_image.h"

img::EasyImage drawLines2D(std::vector<Line2D> lines, int size, int width, int height) {
    img::EasyImage image(width, height);
    for (auto &line : lines) {
        image.draw_line(line.p1.x, line.p1.y, line.p2.x, line.p2.y, line.color);
    }
    return image;
}


#ifndef ENGINE_DRAWLINES2D_H
#define ENGINE_DRAWLINES2D_H

#endif //ENGINE_DRAWLINES2D_H
