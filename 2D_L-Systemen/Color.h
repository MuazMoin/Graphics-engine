//
// Created by Muaz Moin on 03/03/2024.
//

#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H
#include "../easy_image.h"


class Color{
public:
    double red;
    double green;
    double blue;

    Color();

    Color(double r, double g, double b) {
        this->red = r;
        this->green = g;
        this->blue = b;
    }

    img::Color toEasyImageColor() const;
};



#endif //ENGINE_COLOR_H
