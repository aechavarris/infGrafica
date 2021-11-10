#pragma once

#include <iostream>
#include <math.h>
#include <random>
#include <string.h>
#include <time.h>
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/geometry/matrix/Matrix.h"
#include "../../../lib/ray_tracing/ray/Ray.h"
#include "../../../lib/rgb/RGB.h"
#include "../../../lib/objects/figures/property/Property.h"


using namespace std;
const float PI = 3.14159265358979323846;

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
        Vector difusion(Ray ray, float distancia, Point p);

        /*
         * Pre:
         * Post:
         */
        Vector refraccion(Ray ray, float distancia, Point o);

        /*
         * Pre:
         * Post:
         */
        Vector especular(Ray ray, float distancia);

        /*
         * Pre:
         * Post:
         */
        virtual Vector getNormal(Ray ray,float distancia) = 0;

        float floatRand(const float & min, const float & max);
};

#include  "Primitive.cpp"
#endif