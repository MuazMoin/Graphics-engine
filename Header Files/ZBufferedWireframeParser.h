//
// Created by Muaz Moin on 22/03/2024.
//

#ifndef ENGINE_ZBUFFEREDWIREFRAMEPARSER_H
#define ENGINE_ZBUFFEREDWIREFRAMEPARSER_H
#include "easy_image.h"
#include "ini_configuration.h"
#include "Figure.h"


class ZBufferedWireframeParser{

public:
    static img::EasyImage ZBufferedParser(const ini::Configuration &configuration);

};

#endif //ENGINE_ZBUFFEREDWIREFRAMEPARSER_H
