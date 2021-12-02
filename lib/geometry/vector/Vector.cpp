/*****************************************************************
 * File:    Vector.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase Vector
 *****************************************************************/

#pragma once

#include "Vector.h"

Vector::Vector(){
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Vector::Vector(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(Point p){
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
}

float Vector::module() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector::dot(Vector v) {
    return (this->x * v.x + this->y * v.y + this->z * v.z);
}

float Vector::dot(Point p) {
    return (this->x * p.x + this->y * p.y + this->z * p.z);
}

Vector Vector::normalize() {
    float module = this->module();
    return Vector(this->x / module,this->y / module,this->z / module);
}

Vector Vector::cross(Vector v) {
    float x = this->y * v.z - this->z * v.y;
    float y = this->z * v.x - this->x * v.z;
    float z = this->x * v.y - this->y * v.x;
    return Vector(x, y, z);
}

Vector Vector::vectorBetweenVector(Vector v) {
    return Vector();
}

float Vector::distanceBetweenVector(Vector v) {
    return abs(this->module() - v.module());
}