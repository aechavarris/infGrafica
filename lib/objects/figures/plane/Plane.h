#pragma once

#include <iostream>
#include "../../../../lib/geometry/vector/Vector.h"
#include "../../../../lib/geometry/point/Point.h"
#include "../Primitive.h"
#include "../../../../lib/rgb/RGB.h"

using namespace std;

#ifndef _PLANE
#define _PLANE

class Plane :public Primitive{
    public:
        Point p;
        Vector normal;
        bool minus;
        Vector minus_normal;
        /*
         * Constructor de la clase Plane
         */
        Plane();
        Plane (Point p, Vector nor, RGB rgb,RGB rgbEs,RGB rgbR, Property prop,bool light);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * This function has been taken https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
         */
        bool intersect(Ray ray, float* t,float* t2, Point backgroundLeft, Point frontRight) override;

        /*
         * Pre:
         * Post:
         */
        Vector getNormal(Ray ray, float distancia) override;
};

#include  "Plane.cpp"
#endif