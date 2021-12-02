/*****************************************************************
 * File:    Primitive.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Implementa la clase padre de la que heredan todos los 
 *          objetos de la escena y sus posible operaciones
 *****************************************************************/

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
        RGB emisionRGB;
        RGB especularRGB;
        RGB refraccionRGB;
        PPMFile* texture;

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
        virtual bool intersect(Ray ray, float* t, float* t2, Point backgroundLeft, Point frontRight) = 0;

        /*
         * Pre:
         * Post:
         */
        string russianRoulette(int rebotes, float* random);

        /*
         * Pre:
         * Post:
         */
        Vector difusion(Ray ray, float distancia, Point p, Matrix change_base);

        /*
         * Pre:
         * Post:
         */
        Ray refraccion(Ray ray, float distancia, Matrix change_base, Point backgroundLeft, Point frontRight);

        /*
         * Pre:
         * Post:
         */
        Vector especular(Ray ray, float distancia, Matrix change_base);

        /*
         * Pre:
         * Post:
         */
        virtual Vector getNormal(Ray ray, float distancia) = 0;

        float floatRand(const float & min, const float & max);
};

#include  "Primitive.cpp"
#endif