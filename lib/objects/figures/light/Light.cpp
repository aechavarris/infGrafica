#pragma once

#include "Light.h"

Light::Light(){};

Light::Light(Point center, RGB c) {
    this->center = center;
    this->color = c;
}