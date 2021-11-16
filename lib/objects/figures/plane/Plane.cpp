#pragma once

#include "Plane.h"

Plane::Plane(Point p, Vector nor, RGB rgbE,RGB rgbEs,RGB rgbR, Property prop, bool light) {
    this->p = p;
    this->normal = nor;
    this->emisionRGB = rgbE;
    this->emisionRGB = rgbEs;
    this->emisionRGB = rgbR;
    this->matProperties=prop;
    this->isLight = light;
    this->minus=false;
    this->minus_normal = Vector(-nor.x,-nor.y,-nor.z);
};

bool Plane::intersect(Ray ray, float* t) {
    float denom = this->normal.dot(ray.direction);
    float d = ray.direction.dot(this->normal);
    float d2 = ray.direction.dot(this->minus_normal);
    if(d != 0){
        this->minus = false;
        float denom = this->normal.dot(ray.direction);
        if (abs(denom) > 0.0001f) {
            Point p = Point(this->p.x - ray.origin.x, this->p.y - ray.origin.y, this->p.z - ray.origin.z);
            float tAux = (p.x * this->normal.x + p.y * this->normal.y + p.z * this->normal.z) / denom;
            if (tAux > 0) {
                *t = tAux;
                return true;
            } 
        }
    }else if(d2 != 0){
        float denom = this->minus_normal.dot(ray.direction);
        this->minus = true;
        if (abs(denom) > 0.0001f) {
            Point p = Point(this->p.x - ray.origin.x, this->p.y - ray.origin.y, this->p.z - ray.origin.z);
            float tAux = (p.x * this->minus_normal.x + p.y * this->minus_normal.y + p.z * this->minus_normal.z) / denom;
            if (tAux > 0) {
                *t = tAux;
                return true; 
            } 
        }
    }
    return false;
    

    /*
    Vector rd = ray.direction;
    Point pp = this->p;
    Point ro = ray.origin;
    Vector n = this->normal;
    Vector minus_n = Vector(-n.x, -n.y, -n.z);

    bool intersection = false;
    float dist = 0.0f;
    float denominator = rd.dot(n);
    float denominator2 = rd.dot(minus_n);

    if (denominator != 0) {
        Vector daux = Vector(pp.x - ro.x, pp.y - ro.y, pp.z - ro.z);
        dist = ( n.dot(daux)) / denominator;
        if (dist < 10000000 && dist > 0) {
            *color = this->rgb;
            *t = dist;
            intersection = true;
        }

    } else if (denominator2 != 0) {
        Vector daux = Vector(pp.x - ro.x, pp.y - ro.y, pp.z - ro.z);
        n = Vector(-n.x, -n.y, -n.z);
        dist = ( n.dot(daux)) / denominator2;
        if (dist < 10000000 && dist > 0) {
            *color = this->rgb;
            *t = dist;
            intersection = true;
        }
    }

    return intersection;
    */
}
Vector Plane::getNormal(Ray ray,float distancia,Matrix base_change){
    if(this->minus){
        return Vector(-this->normal.x/this->normal.module(),
                  -this->normal.y/this->normal.module(),
                  -this->normal.z/this->normal.module());
    }else{
        return Vector(this->normal.x/this->normal.module(),
                    this->normal.y/this->normal.module(),
                    this->normal.z/this->normal.module());
    }
}