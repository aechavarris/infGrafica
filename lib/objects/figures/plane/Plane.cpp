#pragma once

#include "Plane.h"

Plane::Plane(){};

Plane::Plane (Point p, Vector nor, RGB rgb) {
    this->p = p;
    this->normal = nor;
    this->rgb = rgb;
};

bool Plane::intersect(Ray &ray, float* t1, float *t2) {
    // assuming vectors are all normalized
    float denom = this->normal.dot(ray.direction); 
    if (denom > 1e-6) { 
        Vec3f p0l0 = p0 - l0; 
        t = dotProduct(p0l0, n) / denom; 
        return (t >= 0); 
    } 
 
    return false;
}