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
        float temp = fabs((-b - sqrt(discriminant)) / a);
        float temp2 = fabs((-b + sqrt(discriminant)) / a);
        color->r = this->rgb.r;
        color->g = this->rgb.g;
        color->b = this->rgb.b;

        if (temp > temp2) {
            t = &temp2;
            return true;
        }
        *t = temp;
        return true;
    } 
    return false;
}