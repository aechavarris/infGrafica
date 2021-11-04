#pragma once

#include "RayTracing.h"

RayTracing::RayTracing(){};

RayTracing::RayTracing (Camera camera, int numRaysPerPixel, int width, int height) {
    this->camera = camera;
    this->numRaysPerPixel = numRaysPerPixel;
    this->width = width;
    this->height = height;
    this->projection.resize(height);
    for(int i = 0; i < height; i++){
        this->projection[i].resize(width);
    }
};

void RayTracing::addPrimitive(Primitive *p){
    this->primitives.push_back(p);
};

void RayTracing::shootingRays(vector<Primitive*> primitives) {
    Point origen = this->camera.origin;
    Point image_start = Point(RayTracing::ZERO.x - this->width/2, RayTracing::ZERO.y + this->height/2, RayTracing::ZERO.z);
    for (float i = 0; i < height; i++){

        for (float j = 0; j < width; j++) {

            RGB* color = new RGB(0.0, 0.0, 0.0);

            for (int n = 0; n < this->numRaysPerPixel; n++) {
                RGB* colorPrimitive;
                Point image_point = Point(image_start.x + j/numRaysPerPixel, image_start.y + i/numRaysPerPixel, image_start.z);
                Vector dir = Vector(image_point.x - origen.x, image_point.y - origen.y, image_point.z - origen.z);

                Ray actual_ray = Ray(origen, dir);
                float minDist = numeric_limits<float>::max();
                float* t;
                bool isIntersect = false;
                for (int m = 0; m < primitives.size(); m++) {
                    if (primitives[m]->intersect(actual_ray, t, colorPrimitive)){ 
                        if( *t < minDist){
                            minDist = *t; 
                            isIntersect = true;
                        }
                    }
                }
                if(isIntersect){
                    color->r = color->r + colorPrimitive->r;
                    color->g = color->g + colorPrimitive->g;
                    color->b = color->b + colorPrimitive->b;
                    isIntersect = false;
                    minDist = numeric_limits<float>::max();
                }
            }
            this->projection[i][j].r = color->r;
            this->projection[i][j].g = color->g;
            this->projection[i][j].r = color->b;
        }
    }
};