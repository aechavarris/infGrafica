#pragma once

#include <iostream>
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/geometry/point/Point.h"
#include "../../../objects/figures/Primitive.h"
#include "../../../lib/rgb/RGB.h"
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
         * This function has been taken from http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
         */
        bool intersect(Ray &ray, float* t1, float *t2) override;

};

#include  "Sphere.cpp"
#endif