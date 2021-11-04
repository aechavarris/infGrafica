#pragma once

#include "RayTracing.h"

RayTracing::RayTracing(){};

RayTracing::RayTracing (Camera camera, int numRaysPerPixel, int width, int height) {
    this->camera = camera;
    this->numRaysPerPixel = numRaysPerPixel;
    this->width = width;
    this->height = height;
    this->baseChange = Matrix(camera.f, camera.i, camera.u, camera.origin);
    this->projection.resize(height);
    for(int i = 0; i < height; i++){
        this->projection[i].resize(width);
    }
};

void RayTracing::addPrimitive(Primitive *p){
    this->primitives.push_back(p);
};

void RayTracing::shootingRays() {
    Point origen = this->camera.origin;
    Point image_start = Point(RayTracing::ZERO.x - this->width/2, RayTracing::ZERO.y + this->height/2, RayTracing::ZERO.z);
    RGB* color = new RGB(0.0, 0.0, 0.0);
    for (float i = 0; i < this->height; i++){

        for (float j = 0; j < this->width; j++) {

            color->r = 0.0;
            color->g = 0.0;
            color->b = 0.0;
            Point image_point = Point(image_start.x + j, image_start.y + i, image_start.z);
            Point p = this->baseChange.productMatrixPoint(image_point);
            Vector dir = Vector(image_point.x - origen.x, image_point.y - origen.y, image_point.z - origen.z);
            Ray actual_ray = Ray(origen, Vector(dir.x/dir.module(),dir.y/dir.module(),dir.z/dir.module()));
            RGB* colorPrimitive;
            float minDist = numeric_limits<float>::max();
            for (int n = 0; n < this->numRaysPerPixel; n++) {
                float* t;
                bool isIntersect = false;
                for (int m = 0; m < this->primitives.size(); m++) {
                    if (this->primitives[m]->intersect(actual_ray, t, colorPrimitive)){ 
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