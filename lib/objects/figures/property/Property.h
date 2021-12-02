/*****************************************************************
 * File:    Property.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Recoge las propiedades de cada material (coeficientes 
 *          de difusion, refraccion, ...)
 *****************************************************************/

#pragma once

#include <iostream>

using namespace std;

#ifndef _PROPERTY
#define _PROPERTY

class Property {
    public:
        float lambertianDiffuse;
        float deltaBRDF;
        float deltaBTDF;
        float snell;

        /*
         * Constructor de la clase Property
         */
        Property();
        Property(float lambertian, float deltaBRDF, float deltaBTDF, float snell);
};

#include  "Property.cpp"
#endif