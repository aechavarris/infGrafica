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

void RayTracing::shootingRays() {
    Point origen = this->camera.origin;
    Point image_start = Point(RayTracing::ZERO.x - this->width/2, RayTracing::ZERO.y + this->height/2, RayTracing::ZERO.z);
    RGB color = RGB(0.0, 0.0, 0.0);
    RGB* colorPrimitive = new RGB(0.0,0.0,0.0);
    RGB countColor = RGB(0.0,0.0,0.0);

    for (float i = 0; i < this->height; i++){

        for (float j = 0; j < this->width; j++) {

            color.r = 0.0;
            color.g = 0.0;
            color.b = 0.0;
            countColor.r = 0.0;
            countColor.g = 0.0;
            countColor.b = 0.0;
            Point image_point = Point(image_start.x + j, image_start.y + i, image_start.z);
            Point p = this->baseChange.productMatrixPoint(image_point);
            Vector dir = Vector(image_point.x - origen.x, image_point.y - origen.y, image_point.z - origen.z);
            Ray actual_ray = Ray(origen, Vector(dir.x/dir.module(),dir.y/dir.module(),dir.z/dir.module()));
            cout<<actual_ray.direction.x<<"  "<<actual_ray.direction.y << "  " << actual_ray.direction.z << endl;
            
            float minDist = numeric_limits<float>::max();
            for (int n = 0; n < this->numRaysPerPixel; n++) {
                float* t;
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
            //cout<<color.r/numRaysPerPixel<<"  "<<color.g/numRaysPerPixel<<"  "<<color.b/numRaysPerPixel<<endl;
            this->projection[i][j].r = color.r / numRaysPerPixel;
            this->projection[i][j].g = color.g / numRaysPerPixel;
            this->projection[i][j].b = color.b / numRaysPerPixel;
        }

    }
};