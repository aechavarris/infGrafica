#pragma once

#include "Sphere.h"

Sphere::Sphere(){};

Sphere::Sphere(Point center, float radius, RGB rgb) {
    this->center = center;
    this->radius = radius;
    this->rgb = rgb;
};

/*
bool Sphere::intersect(Ray ray, float* t, RGB* color) { 
        float t0, t1; // solutions for t if the ray intersects  

        // geometric solution
        Vector L = Vector(this->center.x - ray.origin.x, this->center.y - ray.origin.y, this->center.z - ray.origin.z); 
        float tca = L.dot(ray.direction); 
		cout<< ray.direction.x<<"  "<<ray.direction.y<<"  "<<ray.direction.z<<endl;
        if (tca < 0) return false;

        float d2 = L.dot(L) - tca * tca; 

        if (d2 > this->radius * this->radius) return false; 

        float thc = sqrt(this->radius * this->radius - d2); 
        t0 = tca - thc; 
        t1 = tca + thc; 

		if (t0 > t1) swap(t0, t1); 
 
        if (t0 < 0) { 
            t0 = t1; 				  // if t0 is negative, let's use t1 instead 
            if (t0 < 0) return false; // both t0 and t1 are negative 
        } 
 
        t = &t0;
		color->r = this->rgb.r;
		color->g = this->rgb.g;
		color->b = this->rgb.b; 
 
        return true; 
} 
*/

bool Sphere::intersect(Ray ray, float* t, RGB* color) { 
    Vector d = ray.direction;
    Point o = ray.origin;

    Point oc = this->center;

    float t_min = -1;
    float t_max = 999999999999999;

    float a = d.dot(d);
    float b = oc.dot(d);
    float c = oc.dot(oc) - (this->radius * this->radius);
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
        t = &temp;
        return true;
    } 
    return false;
}