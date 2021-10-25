#pragma once

#include "Ray.h"

Ray::Ray(){};

Ray::Ray(Point origin, Vector dir) {
    this->origin = origin;
    this->direction = dir;
};

Point Ray::project(float distance) {

};