#pragma once

#include "Plane.h"

Plane::Plane(){};

Plane::Plane(Point p, Vector nor, RGB rgb) {
    this->p = p;
    this->normal = nor;
    this->rgb = rgb;
};

bool Plane::intersect(Ray ray, float* t, RGB* color) {
    float denom = this->normal.dot(ray.direction);
    if (abs(denom) > 0.0001f) {
        Point p = Point(this->p.x - ray.origin.x, this->p.y - ray.origin.y, this->p.z - ray.origin.z);
        float tAux = (p.x * this->normal.x + p.y * this->normal.y + p.z * this->normal.z) / denom;
        if (tAux > 0) {
            *t = tAux;
            color->r = this->rgb.r;
            color->g = this->rgb.g;
            color->b = this->rgb.b;
            //cout <<"Soy plano "<<color->r<<" "<<color->g<<" "<<color->b<<endl;
            return true;
            
        } 
    }
    return false;
}