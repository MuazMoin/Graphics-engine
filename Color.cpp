//
// Created by Muaz Moin on 03/03/2024.
//
#include "Color.h"

img::Color Color::toEasyImageColor() const { //const zal nooit object veranderen, maakt mijn variablen nl red green blue (= memberveariablenen) onveranderlijk
    img::Color muaz(red * 255, green * 255, blue * 255);
    return muaz;
}

Color::Color() {
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}


