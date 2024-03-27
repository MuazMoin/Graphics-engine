//
// Created by Muaz Moin on 27/03/2024.
//

#ifndef ENGINE_ZPARSER_H
#define ENGINE_ZPARSER_H
#include "ini_configuration.h"
#include "easy_image.h"
#include <iostream>

class ZParser {
public:
    static img::EasyImage parseZBuffer(const ini::Configuration &configuration);

};

#endif //ENGINE_ZPARSER_H
