#pragma once

#include <iostream>
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/geometry/point/Point.h"
using namespace std;

#ifndef _RAY
#define _RAY

class Ray {
    public:
        Point origin;
        Vector direction;

        /*
         * Constructor de la clase Ray
         */
        Ray();
        Ray(Point origin, Vector dir);

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        Point project(float distance);
};

#include  "Ray.cpp"
#endif