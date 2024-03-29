/*****************************************************************
 * File:    Sphere.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Implementa el objeto esfera mediante su centro y su radio 
 *          y sus posibles operaciones.
 *****************************************************************/

#pragma once

#include <iostream>
#include "../../../../lib/geometry/vector/Vector.h"
#include "../../../../lib/geometry/point/Point.h"
#include "../Primitive.h"
#include "../../../../lib/rgb/RGB.h"

using namespace std;

#ifndef _SPHERE
#define _SPHERE

class Sphere : public Primitive{
    public:
        Point center;
        float radius;

        /*
         * Constructor de la clase Sphere
         */
        Sphere();
        Sphere(Point center, float radius, RGB rgbE,RGB rgbEs, RGB rgbR, Property propl, bool light);
        Sphere(Point center, float radius, RGB rgbE,RGB rgbEs, RGB rgbR, Property propl, bool light, PPMFile* texture);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * To program this function, we have been inspired from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
         */
        bool intersect(Ray ray, float* t, float* t2, Point backgroundLeft, Point frontRight) override;

        /*
         * Pre:
         * Post:
         */
        Vector getNormal(Ray ray, float distancia) override;
};

#include  "Sphere.cpp"
#endif