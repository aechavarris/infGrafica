#pragma once

#include <iostream>
#include "../../lib/geometry/vector/Vector.h"
#include "../../lib/geometry/point/Point.h"
#include "../../lib/geometry/matrix/Matrix.h" 
#include "../objects/figures/light/Light.h"
#include "cameraModel/Camera.h"
#include "../rgb/RGB.h"
#include "ray/Ray.h"
#include "../img_files/PPMFile.h"
#include <time.h>
#include <random>
#include <vector>
#include <limits>
#include <thread>

using namespace std;

#ifndef _RAYTRACING
#define _RAYTRACING

class RayTracing {
    public:
        const Point ZERO = Point(0.0, 0.0, 0.0);
        Camera camera;
        Matrix baseChange;
        vector<Primitive*> primitives;
        vector<Light*> lights;
        int width, height;
        vector<vector<RGB> > projection;
        vector<vector<Ray> > rays;
        int numRaysPerPixel;
        
        /*
         * Constructor de la clase RayTracing
         */
        RayTracing();
        RayTracing (Camera camera, int ray_pixel,int width,int height);
        

        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        void shootingRaysAux(int start, int end);

        /*
         * Pre:
         * Post:
         */
        void shootingRays();

        /*
         * Pre:
         * Post:
         */
        void checkLights(Primitive* mas_cercano,Ray ray,float distancia, RGB raycolor,RGB* luzDirecta);
};

#include  "RayTracing.cpp"
#endif