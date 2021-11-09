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
        Sphere (Point center, float radius, RGB rgb, Property prop);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * To program this function, we have been inspired from https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
         */
        bool intersect(Ray ray, float* t, RGB* color, bool* end) override;

};

#include  "Sphere.cpp"
#endif