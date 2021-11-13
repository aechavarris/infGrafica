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
    
    // float a = ray.direction.dot(ray.direction);
    // float b = this->center.dot(Point(ray.direction.x, ray.direction.y, ray.direction.z));
    // float c = this->center.dot(this->center) - (this->radius * this->radius);
    
    // float discriminant = (b * b) - ((a * c));
    // if (discriminant > 0) {
    //     float t1 = fabs((-b - sqrt(discriminant)) / a);
    //     float t2 = fabs((-b + sqrt(discriminant)) / a);
        
    //     color->r = this->rgb.r;
    //     color->g = this->rgb.g;
    //     color->b = this->rgb.b;

    //     if (t1 > t2) {
    //         t = &t2;
    //         return true;
    //     }
    //     *t = t1;
    //     return true;
    // } 
    // return false;
    
    Vector oc = Vector(ray.origin.x - this->center.x,ray.origin.y - this->center.y, ray.origin.z - this->center.z);
    float a = ray.direction.dot(ray.direction);
    float b = 2.0 * oc.dot(ray.direction);
    float c = oc.dot(oc) - this->radius * this->radius;
    float discriminant = b*b - 4*a*c;
    *color=this->rgb;
    if(discriminant < 0){
        *t= -1.0;
    }
    else{
        *t= abs((-b - sqrt(discriminant)) / (2.0*a));
    }
    return (discriminant>0);
    /*
    Point o = ray.origin;
    Point c = this->center;
    float r = this->radius;
    Vector d = ray.direction;

    // Two intersects are possible
    float t1,t2; // t1 is t0 and t2 is t1, regarding to the link's explanation
    Vector l = Vector(c.x - o.x, c.y - o.y, c.z - o.z);
    float tca = l.dot(d);

    // Not on camera
    if(tca < 0) return false;

    float d2 = l.dot(l) - tca*tca;

    // Ray doesnt intersect with sphere
    if(d2 > r*r) return false;

    float thc = sqrt((r*r)-d2);
    t1 = tca - thc;
    t2 = tca + thc;

    if(t1 > t2) swap(t1,t2);
    if(t1 < 0) {
        t1 = t2;
        if(t1 < 0){
            return false;
        }
    }

    *color = this->rgb;
    *t = t1;

    return true;
    */
}
Vector Sphere::getNormal(Ray ray,float distancia){
    Point p = Point(ray.origin.x + ray.direction.x * distancia,
                    ray.origin.y + ray.direction.y * distancia,
                    ray.origin.z + ray.direction.z * distancia);
    //cout<<"Origen rayo:" <<ray.origin.x<<" "<<ray.origin.y<<" "<<ray.origin.z<<" "<<endl;
    //cout<<"Direccion rayo:" <<ray.direction.x<<" "<<ray.direction.y<<" "<<ray.direction.z<<" "<<endl;
    //cout<<"Distancia:" <<distancia<<endl;
    
    Vector normal = Vector(p.x - this->center.x, p.y - this->center.y, p.z - this->center.z);
    //cout<<"Normal:" <<normal.x<<" "<<normal.y<<" "<<normal.z<<" "<<endl;
    return Vector(normal.x / normal.module(), normal.y / normal.module(), normal.z / normal.module());
}