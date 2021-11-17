#pragma once

#include "Sphere.h"

Sphere::Sphere(){};

Sphere::Sphere(Point center, float radius, RGB rgbE,RGB rgbEs, RGB rgbR, Property prop,bool light,bool puntualLight) {
    this->center = center;
    this->radius = radius;
    this->emisionRGB = rgbE;
    this->emisionRGB = rgbEs;
    this->emisionRGB = rgbR;
    this->matProperties = prop;
    this->isLight = light;
    this->isPuntualLight = puntualLight;
};

bool Sphere::intersect(Ray ray, float* t, float *t2) { 

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

Vector Sphere::getNormal(Ray ray,float distancia,Matrix base_change){
    Point p = Point(ray.origin.x + ray.direction.x * distancia,
                    ray.origin.y + ray.direction.y * distancia,
                    ray.origin.z + ray.direction.z * distancia);
    //cout<<"Origen rayo:" <<ray.origin.x<<" "<<ray.origin.y<<" "<<ray.origin.z<<" "<<endl;
    //cout<<"Direccion rayo:" <<ray.direction.x<<" "<<ray.direction.y<<" "<<ray.direction.z<<" "<<endl;
    //cout<<"Distancia:" <<distancia<<endl;
    //Point change_center = base_change.productMatrixPoint(this->center);
    Vector normal = Vector(p.x - this->center.x, p.y - this->center.y, p.z - this->center.z);
    //cout<<"Normal:" <<normal.x<<" "<<normal.y<<" "<<normal.z<<" "<<endl;
    return normal.normalize();
}