//
// Created by Muaz Moin on 21/03/2024.
//

#include "ZBuffer.h"
#include <limits>

ZBuffer::ZBuffer(const int width, const int height)
        : zBuffer(width, std::vector<double>(height, std::numeric_limits<double>::infinity())) {}



