//
// Created by Muaz Moin on 08/03/2024.
//

#ifndef ENGINE_WIREFRAMEPARSER_H
#define ENGINE_WIREFRAMEPARSER_H
#include "easy_image.h"
#include "ini_configuration.h"
#include "Figure.h"


class WireframeParser {
public:
    static img::EasyImage parseWireframe(const ini::Configuration &configuration);

};

#endif //ENGINE_WIREFRAMEPARSER_H
