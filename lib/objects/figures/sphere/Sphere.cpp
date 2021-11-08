#pragma once

#include "Sphere.h"

Sphere::Sphere(){};

Sphere::Sphere(Point center, float radius, RGB rgb) {
    this->center = center;
    this->radius = radius;
    this->rgb = rgb;
};

bool Sphere::intersect(Ray ray, float* t, RGB* color) { 
    float a = ray.direction.dot(ray.direction);
    float b = this->center.dot(Point(ray.direction.x, ray.direction.y, ray.direction.z));
    float c = this->center.dot(this->center) - (this->radius * this->radius);
    
    float discriminant = (b * b) - ((a * c));
    if (discriminant > 0) {
        float t1 = fabs((-b - sqrt(discriminant)) / a);
        float t2 = fabs((-b + sqrt(discriminant)) / a);
        
        color->r = this->rgb.r;
        color->g = this->rgb.g;
        color->b = this->rgb.b;

        if (t1 > t2) {
            t = &t2;
            return true;
        }
        *t = t1;
        return true;
    } 
    return false;
}