//
// Created by Muaz Moin on 21/03/2024.
//

#ifndef ENGINE_L_SYSTEMSFUNC_H
#define ENGINE_L_SYSTEMSFUNC_H
#include "l_parser.h"
#include "Face.h"
#include <string>
#include <vector>
#include "vector3d.h"
#include "Figure.h"

class L_SystemsFunc {
public:
    static LParser::LSystem3D parseLSystem3D(const std::string &inputfile);
    static std::string getString(const LParser::LSystem3D &l_system);
    static void getFacesAndPoints(Figure &figure, const LParser::LSystem3D &l_system, const std::string &figureString);


};

#endif //ENGINE_L_SYSTEMSFUNC_H
