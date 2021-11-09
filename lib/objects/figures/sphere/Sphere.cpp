#pragma once

#include "Sphere.h"

Sphere::Sphere(){};

Sphere::Sphere(Point center, float radius, RGB rgb,Property prop,bool light) {
    this->center = center;
    this->radius = radius;
    this->rgb = rgb;
    this->matProperties=prop;
    this->isLight = light;
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
Vector Sphere::getNormal(Ray ray,float distancia){
    Point p = Point(ray.origin.x + ray.direction.x * distancia,
                    ray.origin.y + ray.direction.y * distancia,
                    ray.origin.z + ray.direction.z * distancia);
    Vector normal = Vector(p.x - this->center.x, p.y - this->center.y, p.z - this->center.z);
    return Vector(normal.x / normal.module(), normal.y / normal.module(), normal.z / normal.module());
}