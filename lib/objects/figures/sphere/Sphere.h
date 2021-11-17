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
        Sphere (Point center, float radius, RGB rgbE,RGB rgbEs, RGB rgbR, Property propl,bool light,bool puntualLight);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * To program this function, we have been inspired from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
         */
        bool intersect(Ray ray, float* t,float* t2) override;

        /*
         * Pre:
         * Post:
         */
        Vector getNormal(Ray ray, float distancia,Matrix base_change) override;

};

#include  "Sphere.cpp"
#endif