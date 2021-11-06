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
        RGB rgb;

        /*
         * Constructor de la clase Sphere
         */
        Sphere();
        Sphere (Point center, float radius, RGB rgb);

        /*
         * This function has been taken from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
         */
        bool intersect(Ray ray, float* t, RGB* color) override;

};

#include  "Sphere.cpp"
#endif