//
// Created by Muaz Moin on 21/03/2024.
//

#include "Header Files/l_SystemsFunc.h"
#include <fstream>
#include <stack>
#include <cmath>

LParser::LSystem3D L_SystemsFunc::parseLSystem3D(const std::string &inputfile) {
    LParser::LSystem3D l_system;
    std::ifstream
            input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    return l_system;
}

std::string L_SystemsFunc::getString(const LParser::LSystem3D &l_system) {
    int iterations = l_system.get_nr_iterations();
    std::string resultString = l_system.get_initiator();

    if (iterations == 0) {
        return resultString;
    }

    for (int i = 0; i < iterations; ++i) {
        std::string tempString;
        for (char c : resultString) {
            if (l_system.get_alphabet().count(c)) {
                tempString += l_system.get_replacement(c);
            } else {
                tempString += c;
            }
        }
        resultString = tempString;
    }

    return resultString;
}

void L_SystemsFunc::getFacesAndPoints(Figure &figure, const LParser::LSystem3D &l_system, const std::string &figureString) {

    double angle = l_system.get_angle() * M_PI / 180;
    Vector3D vectorH = Vector3D::vector(1, 0, 0);
    Vector3D vectorL = Vector3D::vector(0, 1, 0);
    Vector3D vectorU = Vector3D::vector(0, 0, 1);

    std::stack<std::vector<Vector3D>> bracketStack = {};
    Vector3D previousPosition = Vector3D::point(0, 0, 0);
    Vector3D currentPosition = Vector3D::point(0, 0, 0);

    std::vector<Vector3D> newface;

    for (char c : figureString){
        if (c == '+'){
            Vector3D newVectorH = vectorH*cos(angle) + vectorL * sin(angle);
            Vector3D newVectorL = -vectorH * sin(angle) + vectorL*cos(angle);
            vectorH = newVectorH;
            vectorL = newVectorL;
            continue;
        } else if (c == '-'){
            Vector3D newVectorH = vectorH*cos(-angle) + vectorL * sin(-angle);
            Vector3D newVectorL = -vectorH * sin(-angle) + vectorL*cos(-angle);
            vectorH = newVectorH;
            vectorL = newVectorL;
            continue;
        } else if (c == '^'){
            Vector3D newVectorH = vectorH*cos(angle) + vectorU * sin(angle);
            Vector3D newVectorU = -vectorH * sin(angle) + vectorU*cos(angle);
            vectorH = newVectorH;
            vectorU = newVectorU;
            continue;
        } else if (c == '&'){
            Vector3D newVectorH = vectorH*cos(-angle) + vectorU * sin(-angle);
            Vector3D newVectorU = -vectorH * sin(-angle) + vectorU*cos(-angle);
            vectorH = newVectorH;
            vectorU = newVectorU;
            continue;
        } else if (c == '\\'){
            Vector3D newVectorL = vectorL*cos(angle) - vectorU * sin(angle);
            Vector3D newVectorU = vectorL * sin(angle) + vectorU*cos(angle);
            vectorL = newVectorL;
            vectorU = newVectorU;
            continue;
        } else if (c == '/'){
            Vector3D newVectorL = vectorL*cos(-angle) - vectorU * sin(-angle);
            Vector3D newVectorU = vectorL * sin(-angle) + vectorU*cos(-angle);
            vectorL = newVectorL;
            vectorU = newVectorU;
            continue;
        } else if (c == '|'){
            vectorH *= -1;
            vectorL *= -1;
            continue;
        } else if (c == '('){
            bracketStack.push({currentPosition, vectorH, vectorL, vectorU});
            continue;
        } else if (c == ')'){
            std::vector<Vector3D> oldPosition = bracketStack.top();
            bracketStack.pop();

            currentPosition = oldPosition[0];
            vectorH = oldPosition[1];
            vectorL = oldPosition[2];
            vectorU = oldPosition[3];
            continue;

        } else {
            previousPosition = currentPosition;
            currentPosition = previousPosition + vectorH;

            if (l_system.draw(c)) {
                figure.points.push_back(previousPosition);
                figure.points.push_back(currentPosition);
                figure.faces.push_back(Face({int(figure.points.size() - 2), int(figure.points.size() - 1)}));

            }
        }
    }
}

