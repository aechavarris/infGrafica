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
        RGB rgb;

        /*
         * Constructor de la clase Plane
         */
        Plane();
        Plane (Point p, Vector nor, RGB rgb);

        /*
         * This function has been taken https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
         */
        bool intersect(Ray ray, float* t, RGB* color) override;
};

#include  "Plane.cpp"
#endif