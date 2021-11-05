#pragma once

#include <iostream>
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/ray_tracing/ray/Ray.h"
#include "../../../lib/rgb/RGB.h"
using namespace std;

#ifndef _PRIMITIVE
#define _PRIMITIVE

class Primitive {
    public:
    
        /*
         * Constructor de la clase Primitive
         */
        Primitive();

        virtual bool intersect(Ray ray, float* t, RGB* color) = 0;
};

#include  "Primitive.cpp"
#endif