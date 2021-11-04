#pragma once

#include "Plane.h"

Plane::Plane(){};

Plane::Plane(Point p, Vector nor, RGB rgb) {
    this->p = p;
    this->normal = nor;
    this->rgb = rgb;
};

bool Plane::intersect(Ray &ray, float* t1, float *t2) {
    float denom = this->normal.dot(ray.direction);
    if (abs(denom) > 0.0001f) {
        Point p = Point(this->p.x - ray.origin.x, this->p.y - ray.origin.y, this->p.z - ray.origin.z);
        float t = p.dot(this->normal) / denom;
        if (t >= 0) return true;
    }
    return false;
}