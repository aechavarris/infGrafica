/*****************************************************************
 * File:    Sphere.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase Sphere 
 *****************************************************************/

#pragma once

#include "Sphere.h"

Sphere::Sphere(){};

Sphere::Sphere(Point center, float radius, RGB rgbE, RGB rgbEs, RGB rgbR, Property prop, bool light) {
    this->center = center;
    this->radius = radius;
    this->emisionRGB = rgbE;
    this->emisionRGB = rgbEs;
    this->emisionRGB = rgbR;
    this->matProperties = prop;
    this->isLight = light;
    this->texture = new PPMFile();
};

Sphere::Sphere(Point center, float radius, RGB rgbE, RGB rgbEs, RGB rgbR, Property prop, bool light, PPMFile* texture) {
    this->center = center;
    this->radius = radius;
    this->emisionRGB = rgbE;
    this->emisionRGB = rgbEs;
    this->emisionRGB = rgbR;
    this->matProperties = prop;
    this->isLight = light;
    this->texture = texture;
};

bool Sphere::intersect(Ray ray, float* t, float *t2, Point backgroundLeft, Point frontRight) { 

        float t0, t1; // solutions for t if the ray intersects 

        // geometric solution
        Point L = this->center - ray.origin; 
        float tca = L.dot(Point(ray.direction.x, ray.direction.y, ray.direction.z));
        if (tca < 0) return false; 
        
        float d2 = L.dot(L) - tca * tca; 
        if (d2 > this->radius * this->radius) return false; 
        
        float thc = sqrt(this->radius * this->radius - d2); 
        t0 = tca - thc; 
        t1 = tca + thc;

        if(t0 > t1) swap(t0, t1); 
        if (t0 < 0) { 
            t0 = t1; // if t0 is negative, let's use t1 instead 
            if (t0 < 0) return false; // both t0 and t1 are negative 
        } 
 
        *t = t0; 
        *t2 = t1;
        return true; 
} 

Vector Sphere::getNormal(Ray ray, float distancia){
    Point p = Point(ray.origin.x + ray.direction.x * distancia,
                    ray.origin.y + ray.direction.y * distancia,
                    ray.origin.z + ray.direction.z * distancia);
    Vector normal = Vector(p.x - this->center.x, p.y - this->center.y, p.z - this->center.z);
    return normal.normalize();
}