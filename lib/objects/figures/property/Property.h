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
        
        /*
         * Constructor de la clase Property
         */
        Property();
        Property(float lambertian, float deltaBRDF, float deltaBTDF);
};

#include  "Property.cpp"
#endif