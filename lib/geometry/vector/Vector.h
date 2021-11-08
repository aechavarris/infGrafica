#pragma once

#include <iostream>
#include <math.h>
#include "../../../lib/geometry/point/Point.h"
using namespace std;

#ifndef _VECTOR
#define _VECTOR

class Vector {
    public:
        float x;
        float y;
        float z;

        /*
         * Constructor de la clase Vector
         */
        Vector();
        Vector(float x, float y, float z);


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        float module();

        /*
         * Pre:
         * Post:
         */
        float dot(Vector v);

        /*
         * Pre:
         * Post:
         */
        float dot(Point p);

        /*
         * Pre:
         * Post:
         */
        Vector cross(Vector v);

        /*
         * Pre:
         * Post:
         */
        Vector vectorBetweenVector(Vector v);

        /*
         * Pre:
         * Post:
         */
        float distanceBetweenVector(Vector v);
};

#include  "Vector.cpp"
#endif