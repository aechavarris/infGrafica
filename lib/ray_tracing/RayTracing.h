#pragma once

#include <iostream>
#include "../../lib/geometry/vector/Vector.h"
#include "../../lib/geometry/point/Point.h"
#include "../objects/figures/Primitive.h"
#include "cameraModel/Camera.h"
#include "../rgb/RGB.h"
#include "ray/Ray.h"
#include "../img_files/PPMFile.h"
#include <vector>
#include <limits>
using namespace std;

#ifndef _RAYTRACING
#define _RAYTRACING

class RayTracing {
    public:
        const Point ZERO = Point(0.0,0.0,0.0);
        Camera camera;
        vector<Primitive*> primitives;
        int width, height;
        vector<vector<RGB> > projection;
        vector<vector<Ray> > rays;
        int numRaysPerPixel;
        
        /*
         * Constructor de la clase RayTracing
         */
        RayTracing();
        RayTracing (Camera camera, int ray_pixel,int width,int height);
        void addPrimitive(Primitive *p);    
        void shootingRays();
};

#include  "RayTracing.cpp"
#endif