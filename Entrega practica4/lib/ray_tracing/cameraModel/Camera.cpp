/*****************************************************************
 * File:    Camera.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase Camera 
 *****************************************************************/

#pragma once

#include "Camera.h"

Camera::Camera(){};

Camera::Camera (Point origin, Vector f, Vector u, Vector i) {
    this->origin = origin;
    this->f = f;
    this->u = u;
    this->i = i;

};