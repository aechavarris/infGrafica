#pragma once

#include <iostream>
#include <math.h>
using namespace std;

#ifndef _POINT
#define _POINT

class Point{
    public:
        float x;
        float y;
        float z;
        float w;

        /*
         * Constructor de la clase Point
         */
        Point();
        Point(float x, float y, float z);


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
        float dot(Point p);

        /*
         * Pre:
         * Post:
         */
        Point pointBetweenPoint(Point p);

        /*
         * Pre:
         * Post:
         */
        float distanceBetweenPoint(Point p);
};

#include  "Point.cpp"
#endif