#pragma once

#include <iostream>
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/geometry/point/Point.h"
#include "../../rgb/RGB.h"
#include <vector>
using namespace std;

#ifndef _CAMERA
#define _CAMERA

class Camera {
    public:
        Point origin;
        Vector f, u, i;

        /*
         * Constructor de la clase Camera
         */
        Camera();
        Camera (Point origin, Vector f, Vector u, Vector i, int width, int height);
};

#include  "Camera.cpp"
#endif