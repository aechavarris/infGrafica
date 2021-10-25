#pragma once

#include "Camera.h"

Camera::Camera(){};

Camera::Camera (Point origin, Vector f, Vector u, Vector i) {
    this->origin = origin;
    this->f = f;
    this->u = u;
    this->i = i;

};