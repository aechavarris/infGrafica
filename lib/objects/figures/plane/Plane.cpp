/*****************************************************************
 * File:    Plane.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase Plane 
 *****************************************************************/

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
    this->texture = new PPMFile();
};
Plane::Plane(Point p, Vector nor, RGB rgbE,RGB rgbEs,RGB rgbR, Property prop, bool light,PPMFile* texture) {
    this->p = p;
    this->normal = nor;
    this->emisionRGB = rgbE;
    this->emisionRGB = rgbEs;
    this->emisionRGB = rgbR;
    this->matProperties=prop;
    this->isLight = light;
    this->minus=false;
    this->minus_normal = Vector(-nor.x,-nor.y,-nor.z);
    this->texture = texture;
};

bool Plane::intersect(Ray ray, float* t,float* t2, Point backgroundLeft, Point frontRight) {
    float d = ray.direction.dot(this->normal);
    float d2 = ray.direction.dot(this->minus_normal);
    if(d != 0){
        this->minus = false;
        float denom = d ;
        if (abs(denom) > 0.0001f) {
            Point p = this->p- ray.origin;
            float tAux = (p.x * this->normal.x + p.y * this->normal.y + p.z * this->normal.z) / denom;
            Point o = Point(ray.origin.x + ray.direction.x * tAux,
                                                    ray.origin.y + ray.direction.y * tAux,
                                                    ray.origin.z + ray.direction.z * tAux);
            if (tAux > 0) {
                *t = tAux;
                return true;
            } 
        }
    }else if(d2 != 0){
        float denom = d2;
        this->minus = true;
        if (abs(denom) > 0.0001f) {
            Point p = Point(this->p.x - ray.origin.x, this->p.y - ray.origin.y, this->p.z - ray.origin.z);
            float tAux = (p.x * this->minus_normal.x + p.y * this->minus_normal.y + p.z * this->minus_normal.z) / denom;
            Point o = Point(ray.origin.x + ray.direction.x * tAux,
                                                    ray.origin.y + ray.direction.y * tAux,
                                                    ray.origin.z + ray.direction.z * tAux);
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
Vector Plane::getNormal(Ray ray,float distancia){
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