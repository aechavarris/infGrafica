#pragma once

#include <iostream>
#include "../../../lib/geometry/vector/Vector.h"
#include "../ray/Ray.h"
using namespace std;

#ifndef _PRIMITIVE
#define _PRIMITIVE

class Primitive {
    public:
    
        /*
         * Constructor de la clase Primitive
         */
        Primitive();

        
        virtual bool intersect(Ray &ray, float* t1, float *t2) = 0;
};

#include  "Primitive.cpp"
#endif