#pragma once

#include "Plane.h"

Plane::Plane(){};

Plane::Plane(Point p, Vector nor, RGB rgb) {
    this->p = p;
    this->normal = nor;
    this->rgb = rgb;
};

bool Plane::intersect(Ray &ray, float* t, RGB* color) {
    float denom = this->normal.dot(ray.direction);
    if (abs(denom) > 0.0001f) {
        Point p = Point(this->p.x - ray.origin.x, this->p.y - ray.origin.y, this->p.z - ray.origin.z);
        float tAux = p.dot(this->normal) / denom;
        if (tAux >= 0) {
            t = &tAux;
            color = &this->rgb;
            return true;
        } 
    }
    return false;
}