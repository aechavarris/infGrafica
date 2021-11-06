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
    Point image_start = Point(-1000 , 1000, 0);
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
            Point image_point = Point(image_start.x+j , image_start.y+i , 1.0);
            Point p = this->baseChange.productMatrixPoint(image_point);
            Vector dir = Vector(p.x - origen.x, p.y - origen.y, p.z);
            Ray actual_ray = Ray(origen, Vector(dir.x,dir.y,dir.z));
            //cout<<"Imagen: "<<actual_ray.direction.x<<"  "<<actual_ray.direction.y << "  " << actual_ray.direction.z << endl;
            //cout<<"Direccion: "<<dir.x<<"  "<<dir.y << "  " << dir.z << endl;
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