#pragma once

#include <iostream>
#include "../../../../lib/geometry/vector/Vector.h"
#include "../../../../lib/geometry/point/Point.h"
#include "../Primitive.h"
#include "../../../../lib/rgb/RGB.h"

using namespace std;

#ifndef _LIGHT
#define _LIGHT

class Light {
    public:
        Point center;
        RGB color;
        /*
         * Constructor de la clase Light
         */
        Light();
        Light (Point center, RGB color);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

};

#include  "Light.cpp"
#endif