#pragma once

#include <iostream>
#include <cmath>
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/ray_tracing/ray/Ray.h"
#include "../../../lib/rgb/RGB.h"
#include "../../../lib/objects/figures/property/Property.h"
#include <string.h>

using namespace std;

#ifndef _PRIMITIVE
#define _PRIMITIVE

class Primitive {
    public:
        Property matProperties;
        bool isLight;

        /*
         * Constructor de la clase Primitive
         */
        Primitive();


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        virtual bool intersect(Ray ray, float* t, RGB* color) = 0;

        /*
         * Pre:
         * Post:
         */
        string russianRoulette();

        /*
         * Pre:
         * Post:
         */
        Vector difusion(Ray ray, float distancia, Point* o);

        /*
         * Pre:
         * Post:
         */
        Vector refraccion(Ray ray, float distancia, Point* o);

        /*
         * Pre:
         * Post:
         */
        Vector especular(Ray ray, float distancia, Point* o);

        /*
         * Pre:
         * Post:
         */
        virtual Vector getNormal(Ray ray,float distancia) = 0;


};

#include  "Primitive.cpp"
#endif