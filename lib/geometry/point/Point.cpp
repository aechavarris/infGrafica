#pragma once

#include "Point.h"

Point::Point(){};

Point::Point(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 1;
};

float Point::module() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Point::dot(Point p) {
    return (this->x * p.x + this->y * p.y + this->z * p.z);
}

Point Point::pointBetweenPoint(Point p) {
    return Point();
}

float Point::distanceBetweenPoint(Point p) {
    float x = this->x - p.x;
    float y = this->y - p.y;
    float z = this->z - p.z;
    Point aux = Point(x, y, z);
    return aux.module();
}