#pragma once

#include "RayTracing.h"

RayTracing::RayTracing(){};

RayTracing::RayTracing (Camera camera, int numRaysPerPixel, int width, int height) {
    this->camera = camera;
    this->numRaysPerPixel = numRaysPerPixel;
    this->width = width;
    this->height = height;
    this->baseChange = Matrix(camera.u, camera.i, camera.f, camera.origin);
    this->projection.resize(height);
    for(int i = 0; i < height; i++){
        this->projection[i].resize(width);
    }
};

void RayTracing::shootingRays() {
    Point origen = this->camera.origin;
    RGB color = RGB(0.0, 0.0, 0.0);
    RGB* colorPrimitive = new RGB(0.0,0.0,0.0);
    RGB countColor = RGB(0.0,0.0,0.0);

    float pixelXSide = (float)2 / this->height;
    float pixelYSide = (float)2 / this->width;

    srand(time(0));
    cout <<"Starting ray tracing..."<<endl;
    for (float i = 0; i < this->height; i++){

        for (float j = 0; j < this->width; j++) {

            color.r = 0.0;
            color.g = 0.0;
            color.b = 0.0;
            countColor.r = 0.0;
            countColor.g = 0.0;
            countColor.b = 0.0;

            float x = i * pixelXSide - 1.0; 
            float y = j * pixelYSide - 1.0;
            
            float minDist = numeric_limits<float>::max();
            for (int n = 0; n < this->numRaysPerPixel; n++) {

                // This two lines have been taken from https://stackoverflow.com/questions/686353/random-float-number-generation
                float xIter = x + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((x + pixelXSide) - x)));
                float yIter = y + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((y + pixelYSide) - y)));
                Point image_point = Point(xIter, yIter, 1); 
                
                Point p = this->baseChange.productMatrixPoint(image_point);
                Vector dir = Vector(p.x - origen.x, p.y - origen.y, p.z - origen.z);
                Ray actual_ray = Ray(origen, dir);
                
                float* t = new float;
                bool isIntersect = false;
                for (int m = 0; m < this->primitives.size(); m++) {
                    if (this->primitives[m]->intersect(actual_ray, t, colorPrimitive)){ 
                        if( *t < minDist){
                            minDist = *t; 
                            countColor.r = colorPrimitive->r;
                            countColor.g = colorPrimitive->g;
                            countColor.b = colorPrimitive->b;
                            isIntersect = true;
                        }
                    }
                }
                if(isIntersect){
                    color.r = color.r + countColor.r;
                    color.g = color.g + countColor.g;
                    color.b = color.b + countColor.b;
                    isIntersect = false;
                }
                minDist = numeric_limits<float>::max();
            }
            this->projection[i][j].r = color.r / numRaysPerPixel;
            this->projection[i][j].g = color.g / numRaysPerPixel;
            this->projection[i][j].b = color.b / numRaysPerPixel;
        }

    }
};