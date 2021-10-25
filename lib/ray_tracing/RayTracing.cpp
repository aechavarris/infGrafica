#pragma once

#include "RayTracing.h"

RayTracing::RayTracing(){};

RayTracing::RayTracing (Camera camera, int ray_pixel, int width, int height) {
    this->camera=camera;
    this->ray_pixel=ray_pixel;
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
void RayTracing::shootingRays(){
    Point origen=this->camera.origin;
    Point image_start=Point(RayTracing::ZERO.x-this->width/2,RayTracing::ZERO.y+this->height/2,RayTracing::ZERO.z);
    for(float i = 0; i < height; i++){

        for(float j = 0; j < width; j++){

            for(int n = 0; n < this->ray_pixel; n++){
                Point image_point=Point(image_start.x+j,image_start.y+i,image_start.z);
                Vector dir=Vector(image_point.x-origen.x,image_point.y-origen.y,image_point.z-origen.z);
                Ray actual_ray = Ray(origen, dir);
            }

        }

    }

};