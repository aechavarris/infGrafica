#pragma once

#include <iostream>
#include "../../../../lib/geometry/vector/Vector.h"
#include "../../../../lib/geometry/point/Point.h"
using namespace std;

#ifndef _PLANET
#define _PLANET

class Planet {
    public:
        Point center;
        Vector axis;
        Point referenceCity;

        /*
         * Constructor de la clase Planet
         */
        Planet();
        Planet (Point center, Vector axis, Point referenceCity);
};

#include  "Planet.cpp"
#endif