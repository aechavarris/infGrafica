/*****************************************************************
 * File:    Light.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Implementa las luces puntuales con sus coordenadas 
 *          Point()  
 *****************************************************************/

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
        int intensity;

        /*
         * Constructor de la clase Light
         */
        Light();
        Light (Point center, RGB color,int i);
};

#include  "Light.cpp"
#endif