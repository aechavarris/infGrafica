#pragma once

#include "Vector.h"

Vector::Vector(){}

Vector::Vector(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
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